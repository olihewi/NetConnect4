//
// Created by huxy on 23/02/2020.
//
// additional libraries.
#include "GCNetClient.hpp"
#include <atomic>
#include <iostream>
#include <kissnet.hpp>
#include <thread>

void GCNetClient::update(double /*dt*/) {}

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
      std::cout << "disconnected" << std::endl;
      socket.close();
    }
  }
}
void GCNetClient::processMessage(kissnet::buffer<4096> buffer)
{
  const auto* message = reinterpret_cast<const char*>(buffer.data());
  std::string message_string(message);
  auto command_id = static_cast<NetUtil::CommandID>(message[0]);
  message_string  = message_string.substr(message_string.find_first_of(':') + 1);
  switch (command_id)
  {
    case NetUtil::CHAT_MESSAGE:
      std::cout << message_string << std::endl;
      break;
    case NetUtil::CHANGE_USERNAME:
      std::cout << " changed their username to " << message << std::endl;
      break;
    case NetUtil::ASSIGN_PLAYER_ID:
      if (players.empty())
      {
        players.emplace_back(UserClient(static_cast<size_t>(std::stoi(message_string))));
      }
      else
      {
        players[0].ID = static_cast<size_t>(std::stoi(message_string));
      }
      std::cout << "Player ID assigned to " + message_string << std::endl;
      break;
    case NetUtil::CHANGE_COLOUR:
      std::cout << message << std::endl;
      break;
    case NetUtil::MAX_COMMAND_ID:
      // default:
      std::cout << "Recieved an invalid message: " << message << std::endl;
      break;
  }
}
GCNetClient::GCNetClient() : GameComponent(ID::NETWORK_CLIENT) {}
