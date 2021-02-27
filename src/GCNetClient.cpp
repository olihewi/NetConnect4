//
// Created by huxy on 23/02/2020.
//
// additional libraries.
#include "GCNetClient.hpp"
#include <atomic>
#include <iostream>
#include <kissnet.hpp>
#include <thread>
#include <utility>

kissnet::tcp_socket& GCNetClient::connect(
  const std::string& server_ip, kissnet::port_t server_port, const std::string& username)
{
  socket = (kissnet::endpoint{ server_ip, server_port });
  socket.connect();
  send(NetUtil::CHANGE_USERNAME, username);
  connected = true;
  std::thread listener_thread([&] { run(); });
  listener_thread.detach();
  return socket;
}

void GCNetClient::send(NetUtil::CommandID command_id, const std::string& message)
{
  std::string message_string = std::string(1, static_cast<char>(command_id)) + ":" + message;
  const auto* as_byte        = reinterpret_cast<const std::byte*>(message_string.c_str());
  socket.send(as_byte, message_string.size());
}

GCNetClient::~GCNetClient()
{
  socket.close();
}
void GCNetClient::run()
{
  while (connected)
  {
    kissnet::buffer<4096> static_buffer;
    if (auto [size, valid] = socket.recv(static_buffer); valid)
    {
      if (valid.value == kissnet::socket_status::cleanly_disconnected)
      {
        connected = false;
        std::cout << "clean disconnection" << std::endl;
        socket.close();
      }
      if (size < static_buffer.size())
      {
        static_buffer[size] = std::byte{ 0 };
      }
      processMessage(static_buffer);
    }
    else
    {
      connected = false;
      std::cout << "Disconnected from server." << std::endl;
      socket.close();
    }
  }
}
void GCNetClient::processMessage(kissnet::buffer<4096> buffer)
{
  std::string net_string(reinterpret_cast<const char*>(buffer.data()));
  std::vector<std::string> net_messages;
  std::string current_message;
  for (char c : net_string)
  {
    if (c == '|')
    {
      net_messages.emplace_back(current_message);
      current_message = "";
    }
    else
    {
      current_message += c;
    }
  }
  for (auto& message : net_messages)
  {
    std::string message_contents = message.substr(message.find_first_of(':') + 1);
    auto command_id              = static_cast<NetUtil::CommandID>(message[0]);
    if (command_id == NetUtil::ASSIGN_PLAYER_ID)
    {
      if (players.empty())
      {
        players.emplace_back(UserClient(static_cast<size_t>(std::stoi(message_contents))));
      }
      else
      {
        players.front().user_id = static_cast<size_t>(std::stoi(message_contents));
      }
      std::cout << "User ID assigned: " << message_contents << std::endl;
    }
    auto& origin = getPlayer(static_cast<size_t>(message[1] - 64));
    if (command_id == NetUtil::CHANGE_USERNAME)
    {
      std::cout << origin.username << " set their username to " << message_contents << std::endl;
      origin.username = message_contents;
    }
    else if (command_id == NetUtil::CHANGE_COLOUR)
    {
      origin.colour = static_cast<UserClient::PlayerColour>(message_contents[0]);
      std::cout << origin.username << " set their colour to " << origin.colour << std::endl;
    }
    net_callback(message.c_str());
  }
}
GCNetClient::GCNetClient() : GameComponent(ID::NETWORK_CLIENT) {}
void GCNetClient::setCallback(std::function<void(const char*)> _callback)
{
  net_callback = std::move(_callback);
}
UserClient& GCNetClient::getPlayer(size_t index)
{
  for (auto& player : players)
  {
    if (player.user_id == index)
    {
      return player;
    }
  }
  return players.emplace_back(UserClient(index));
}

void GCNetClient::disconnect()
{
  socket.close();
  connected = false;
}
