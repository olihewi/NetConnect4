//
// Created by huxy on 23/02/2020.
//

#include "GCNetServer.hpp"
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
      auto& client = connections.emplace_back(server.accept());
      std::cout << "Connection received from " << client.get_recv_endpoint().address << ":"
                << client.get_recv_endpoint().port << std::endl;

      /// Client worker thread
      workers.emplace_back([&] {
        listen(client);
        std::cout << "Detected disconnect from " << client.get_recv_endpoint().address << ":"
                  << client.get_recv_endpoint().port << std::endl;
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

void GCNetServer::listen(kissnet::tcp_socket& socket)
{
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
      std::cout << reinterpret_cast<const char*>(static_buffer.data()) << '\n';
      send(static_buffer, static_buffer.size(), { socket });
    }
    else
    {
      continue_receiving = false;
      socket.close();
    }
  }
}

void GCNetServer::send(
  const kissnet::buffer<4096>& buffer, size_t length, const socket_list& exclude)
{
  for (auto& socket : connections)
  {
    if (auto it = std::find(exclude.cbegin(), exclude.cend(), socket); it == exclude.cend())
    {
      socket.send(buffer, length);
    }
  }
}
