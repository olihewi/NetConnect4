//
// Created by huxy on 23/02/2020.
//

#include "GCNetServer.hpp"
#include <algorithm>
#include <chrono>
#include <iostream>
#include <kissnet.hpp>
#include <random>

// TCP section
namespace
{
  kissnet::tcp_socket bind(const std::string& ip_address, kissnet::port_t port)
  {
    // create endpoint and assigning to a socket
    kissnet::tcp_socket server(kissnet::endpoint(ip_address, port));

    // bind and listen on it
    server.bind();
    server.listen();

    std::cout << "Starting server at " << ip_address << ":" << port << std::endl;
    // return it
    return server;
  }
} // namespace

GCNetServer::GCNetServer() : GameComponent(ID::NETWORK_SERVER), ai_player(9) {}

GCNetServer::~GCNetServer()
{
  accept_connections = false;
  server.close();
}

void GCNetServer::start()
{
  server             = bind("0.0.0.0", 31276);
  accept_connections = true;

  std::thread thread([&]() {
    while (accept_connections)
    {
      UserClient this_user;
      this_user.socket = server.accept();
      onConnection(this_user);
      this_user.username = this_user.socket.get_recv_endpoint().address + ":" +
                           std::to_string(this_user.socket.get_recv_endpoint().port);
      auto& user_in_list = clients.emplace_back(std::move(this_user));
      std::cout << "Connection received from " << user_in_list.socket.get_recv_endpoint().address
                << ":" << user_in_list.socket.get_recv_endpoint().port << std::endl;

      /// Client worker thread
      workers.emplace_back([&] {
        listen(user_in_list);
        std::cout << user_in_list.username << " ("
                  << user_in_list.socket.get_recv_endpoint().address << ":"
                  << user_in_list.socket.get_recv_endpoint().port << ") has disconnected."
                  << std::endl;
        relay(NetUtil::DISCONNECTED, user_in_list, user_in_list.username, { user_in_list.socket });
        clients.erase(std::find(clients.begin(), clients.end(), user_in_list));
      });
      workers.back().detach();
    }
  });

  thread.detach();
}

void GCNetServer::update(double /*dt*/) {}

void GCNetServer::listen(UserClient& client)
{
  auto& socket            = client.socket;
  bool continue_receiving = true;
  kissnet::buffer<4096> static_buffer;
  while (continue_receiving)
  {
    if (auto [size, valid] = socket.recv(static_buffer); valid)
    {
      if (valid.value == kissnet::socket_status::cleanly_disconnected)
      {
        continue_receiving = false;
      }
      if (size < static_buffer.size())
      {
        static_buffer[size] = std::byte{ 0 };
      }
      processMessage(client, static_buffer);
    }
    else
    {
      continue_receiving = false;
      socket.close();
    }
  }
}

void GCNetServer::processMessage(UserClient& client, kissnet::buffer<4096>& buffer)
{
  const auto* message = reinterpret_cast<const char*>(buffer.data());
  std::string message_string(message);
  if (message_string.find(':') != std::string::npos)
  {
    auto command_id              = static_cast<NetUtil::CommandID>(message[0]);
    std::string message_contents = message_string.substr(message_string.find_first_of(':') + 1);
    switch (command_id)
    {
      case NetUtil::CHANGE_USERNAME: /// Username change
        std::cout << client.username << " changed their username to " << message_contents
                  << std::endl;
        client.username = message_contents;
        relay(NetUtil::CHANGE_USERNAME, client, message_contents, {});
        break;
      case NetUtil::CHAT_MESSAGE:
        std::cout << client.username << " > " << message_contents << '\n';
        relay(NetUtil::CHAT_MESSAGE, client, message_contents, {});
        break;
      case NetUtil::CHANGE_COLOUR:
        client.colour = static_cast<UserClient::PlayerColour>(message_contents[0]);
        relay(NetUtil::CHANGE_COLOUR, client, message_contents, {});
        break;
      case NetUtil::DROP_COUNTER:
        if (board.turn != client.user_id)
        {
          return;
        }
        board.drop(static_cast<size_t>(std::stoi(message_contents)), client);
        board.turn = board.turn % clients.size() + 1;
        relay(command_id, client, message_contents, {});
        if (board.checkVictory() != 0)
        {
          relay(NetUtil::WON_GAME, getPlayer(board.checkVictory()), "1", {});
          board.constructBoard();
          break;
        }
        if (clients.size() < 2)
        {
          board.turn++;
          std::thread ai_thread([&]() {
            std::this_thread::sleep_for(std::chrono::seconds(1));
            aiTurn();
          });
          ai_thread.detach();
        }
        break;
      case NetUtil::POP_OUT_COUNTER:
        if (board.turn != client.user_id)
        {
          return;
        }
        board.pop(static_cast<size_t>(std::stoi(message_contents)), client);
        board.turn = board.turn % clients.size() + 1;
        relay(command_id, client, message_contents, {});
        if (board.checkVictory() != 0)
        {
          relay(NetUtil::WON_GAME, getPlayer(board.checkVictory()), "1", {});
          board.constructBoard();
          break;
        }
        if (clients.size() < 2)
        {
          board.turn++;
          std::thread ai_thread([&]() {
            std::this_thread::sleep_for(std::chrono::seconds(1));
            aiTurn();
          });
          ai_thread.detach();
        }
        break;
      case NetUtil::SET_BOARD_WIDTH:
        board.settings.width = static_cast<size_t>(std::stoi(message_contents));
        relay(command_id, client, message_contents, {});
        break;
      case NetUtil::SET_BOARD_HEIGHT:
        board.settings.height = static_cast<size_t>(std::stoi(message_contents));
        relay(command_id, client, message_contents, {});
        break;
      case NetUtil::SET_BOARD_POP_OUT:
        board.settings.pop_out = message_contents[0] == '1';
        std::cout << "Pop-Out gamemode " << (board.settings.pop_out ? "enabled" : "disabled")
                  << std::endl;
        relay(command_id, client, message_contents, {});
        break;
      case NetUtil::SET_BOARD_NUM_TO_WIN:
        board.settings.num_counters_to_win = static_cast<size_t>(std::stoi(message_contents));
        relay(command_id, client, message_contents, {});
        break;
      case NetUtil::READY_UP:
        if (board.isEmpty() || clients.size() < 2)
        {
          board.constructBoard();
        }
        send(client.socket, NetUtil::SET_BOARD_POP_OUT, client, board.settings.pop_out ? "1" : "0");
        send(client.socket, NetUtil::FILL_ENTIRE_BOARD, client, board.getBoardString());
        break;
      case NetUtil::FORFEIT:
        relay(NetUtil::FORFEIT, client, "1", {});
        break;
      case NetUtil::START_GAME:
      case NetUtil::DISCONNECTED:
      case NetUtil::FILL_ENTIRE_BOARD:
      case NetUtil::ASSIGN_PLAYER_ID:
      case NetUtil::WON_GAME:
      case NetUtil::MAX_COMMAND_ID:
        // default:
        std::cout << client.username << " sent an invalid message: " << message << std::endl;
        break;
    }
  }
  else
  {
    std::cout << client.username << " sent an invalid message: " << message << std::endl;
  }
}

void GCNetServer::relay(
  NetUtil::CommandID command_id, const UserClient& origin, const std::string& message,
  const socket_list& exclude)
{
  for (auto& client : clients)
  {
    if (auto it = std::find(exclude.cbegin(), exclude.cend(), client.socket); it == exclude.cend())
    {
      send(client.socket, command_id, origin, message);
    }
  }
}
void GCNetServer::send(
  kissnet::tcp_socket& socket, NetUtil::CommandID command_id, const UserClient& origin,
  const std::string& message)
{
  std::string message_string;
  message_string += static_cast<char>(command_id);
  message_string += static_cast<char>(origin.user_id + 64);
  message_string += ':';
  message_string += message;
  message_string += '|';
  const auto* as_byte = reinterpret_cast<const std::byte*>(message_string.c_str());
  socket.send(as_byte, message_string.size());
}
void GCNetServer::assignPlayerID(UserClient& player)
{
  size_t id  = 1;
  bool found = false;
  while (!found)
  {
    found = true;
    for (auto& client : clients)
    {
      if (client.user_id == id)
      {
        id++;
        found = false;
      }
    }
  }
  player.user_id = id;
  send(player.socket, NetUtil::ASSIGN_PLAYER_ID, player, std::to_string(id));
}

void GCNetServer::onConnection(UserClient& client)
{
  assignPlayerID(client);
  for (auto& user : clients)
  {
    send(client.socket, NetUtil::CHANGE_USERNAME, user, user.username);
    send(
      client.socket, NetUtil::CHANGE_COLOUR, user, std::string(1, static_cast<char>(user.colour)));
  }
}
UserClient& GCNetServer::getPlayer(size_t player_id)
{
  auto player =
    std::find_if(clients.begin(), clients.end(), [&player_id](const UserClient& _client) {
      return _client.user_id == player_id;
    });
  if (player != clients.end())
  {
    return *player;
  }
  return ai_player;
}
void GCNetServer::aiTurn()
{
  int ai_move = aiScore();
  board.drop(static_cast<size_t>(ai_move), UserClient(9));
  relay(NetUtil::DROP_COUNTER, UserClient(9), std::to_string(ai_move), {});
  board.turn--;
  if (board.checkVictory() != 0)
  {
    relay(NetUtil::WON_GAME, getPlayer(board.checkVictory()), "1", {});
    board.constructBoard();
  }
  std::cout << "AI player has played." << std::endl;
}

int GCNetServer::aiScore()
{
  auto board_copy = board.getBoard();
  std::vector<int> boring_moves;
  for (size_t x = 0; x < board.settings.width; x++)
  {
    board.setBoard(board_copy);
    if (!board.drop(x, UserClient(9)))
    {
      continue; /// If it's an invalid move, don't do it!
    }
    auto victory = board.checkVictory();
    if (victory == 9)
    {
      return static_cast<int>(x); /// If this is a winning move, play it!
    }
    auto board_copy2    = board.getBoard();
    bool is_losing_move = false;
    for (size_t x2 = 0; x2 < board.settings.width; x2++)
    {
      board.setBoard(board_copy2);
      if (!board.drop(x2, clients.front()))
      {
        continue;
      }
      if (board.checkVictory() != 0)
      {
        is_losing_move = true;
      }
    }
    if (!is_losing_move)
    {
      boring_moves.emplace_back(x);
    }
  }
  if (!boring_moves.empty())
  {
    std::random_device r;
    std::default_random_engine gen(r());
    std::uniform_int_distribution<int> distribution(0, static_cast<int>(boring_moves.size() - 1));
    auto dice_roll = static_cast<size_t>(distribution(gen));
    return boring_moves[dice_roll];
  }
  return 0;
}
