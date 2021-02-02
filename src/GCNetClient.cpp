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
  std::string hello_message = "Hello from Client!";
  socket.send(reinterpret_cast<const std::byte*>(hello_message.c_str()), hello_message.size());
}

GCNetClient::~GCNetClient()
{
  socket.close();
}
