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
namespace
{
  std::atomic<bool> connected = false;
  std::atomic<bool> running   = false;
}
kissnet::tcp_socket connect(const std::string& server_address, kissnet::port_t server_port)
{
  kissnet::tcp_socket client_socket(kissnet::endpoint{ server_address, server_port });
  client_socket.connect(0);
  connected = true;
  return client_socket;
}
/// TODO: FIX FUNCTION CONNECT ERROR.

void run(kissnet::tcp_socket&);

int main(int /*argc*/, char* /*argv*/[])
{
  auto socket = connect("127.0.0.1", 12321);
  return EXIT_SUCCESS;
}

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
