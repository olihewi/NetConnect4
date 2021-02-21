//
// Created by huxy on 23/02/2020.
//

#include "GCNetServer.hpp"
#include "../Utilities/NetUtil.h"
#include <iostream>
#include <kissnet.hpp>

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

GCNetServer::GCNetServer() : GameComponent(ID::NETWORK_SERVER) {}

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
      assignPlayerID(this_user);
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
    auto command_id = static_cast<NetUtil::CommandID>(message[0]);
    message_string  = message_string.substr(message_string.find_last_of(':') + 1);
    switch (command_id)
    {
      case NetUtil::CHANGE_USERNAME: /// Username change
        std::cout << client.username << " changed their username to " << message_string
                  << std::endl;
        client.username = message_string;
        break;
      case NetUtil::CHAT_MESSAGE:
        std::cout << client.username << "> " << message_string << '\n';
        relay(buffer, { client.socket });
        break;
      case NetUtil::CHANGE_COLOUR:
        client.colour = static_cast<UserClient::PlayerColour>(message_string[0]);
        relay(buffer, { client.socket });
        break;
      case NetUtil::ASSIGN_PLAYER_ID:
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

void GCNetServer::relay(const kissnet::buffer<4096>& buffer, const socket_list& exclude)
{
  for (auto& client : clients)
  {
    if (auto it = std::find(exclude.cbegin(), exclude.cend(), client.socket); it == exclude.cend())
    {
      client.socket.send(buffer, buffer.size());
    }
  }
}
void GCNetServer::send(
  kissnet::tcp_socket& socket, NetUtil::CommandID command_id, const std::string& message)
{
  std::string message_string = std::string(1, static_cast<char>(command_id)) + ":" + message;
  const auto* as_byte        = reinterpret_cast<const std::byte*>(message_string.c_str());
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
      if (client.ID == id)
      {
        id++;
        found = false;
      }
    }
  }
  player.ID = id;
  send(player.socket, NetUtil::ASSIGN_PLAYER_ID, std::to_string(id));
}
