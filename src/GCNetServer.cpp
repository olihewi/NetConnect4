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
      UserClient& this_user = clients.emplace_back(UserClient());
      this_user.socket      = server.accept();
      this_user.username    = this_user.socket.get_recv_endpoint().address + ":" +
                           std::to_string(this_user.socket.get_recv_endpoint().port);
      auto& client = this_user.socket;
      std::cout << "Connection received from " << this_user.socket.get_recv_endpoint().address
                << ":" << client.get_recv_endpoint().port << std::endl;

      /// Client worker thread
      workers.emplace_back([&] {
        listen(this_user);
        std::cout << this_user.username << " (" << client.get_recv_endpoint().address << ":"
                  << client.get_recv_endpoint().port << ") has disconnected." << std::endl;
        if (const auto SOCKET_ITER =
              std::find(connections.begin(), connections.end(), std::ref(client));
            SOCKET_ITER != connections.end())
        {
          std::cout << "Closing socket...\n";
          connections.erase(SOCKET_ITER);
        }
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
    std::cout << command_id;
    message_string = message_string.substr(message_string.find_last_of(':') + 1);
    switch (command_id)
    {
      case NetUtil::CHANGE_USERNAME: /// Username change
        std::cout << client.username << " changed their username to " << message_string
                  << std::endl;
        client.username = message_string;
        break;
      case NetUtil::CHAT_MESSAGE:
        std::cout << "[" << client.username << "] " << message_string << '\n';
        relay(buffer, { client.socket });
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
  for (auto& socket : connections)
  {
    if (auto it = std::find(exclude.cbegin(), exclude.cend(), socket); it == exclude.cend())
    {
      socket.send(buffer, buffer.size());
    }
  }
}
