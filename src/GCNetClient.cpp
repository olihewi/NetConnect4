//
// Created by huxy on 23/02/2020.
//

#include "GCNetClient.hpp"

GCNetClient::GCNetClient() : GameComponent(ID::NETWORK_CLIENT) {}

void GCNetClient::update(double /*dt*/) {}

void GCNetClient::connect(const std::string& server_ip, unsigned short server_port)
{
  socket = (kissnet::endpoint{ server_ip, server_port });
  socket.connect();
  send("Hello from client!");
}

void GCNetClient::send(const std::string& message)
{
  socket.send(reinterpret_cast<const std::byte*>(message.c_str()), message.size());
}

GCNetClient::~GCNetClient()
{
  socket.close();
}
