//
// Created by huxy on 23/02/2020.
//
// additional libraries.
#include "GCNetClient.hpp"
#include <atomic>
#include <iostream>
#include <kissnet.hpp>
#include <thread>

GCNetClient::GCNetClient() : GameComponent(ID::NETWORK_CLIENT) {}

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
      std::cout << reinterpret_cast<const char*>(static_buffer.data()) << '\n';
    }
    else
    {
      connected = false;
      std::cout << "disconnected" << std::endl;
      socket.close();
    }
  }
}
