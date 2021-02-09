//
// Created by huxy on 23/02/2020.
//

#ifndef GAMELIB_GCNETSERVER_HPP
#define GAMELIB_GCNETSERVER_HPP

#include "GComponent.hpp"
#include <atomic>
#include <kissnet.hpp>
#include <list>
#include <thread>
#include <vector>

class GCNetServer final : public GameComponent
{
 public:
  GCNetServer();
  ~GCNetServer() override;
  void update(double dt) override;
  void start();

  GCNetServer(const GCNetServer&) = delete;
  GCNetServer& operator=(const GCNetServer&) = delete;

 private:
  void listen(kissnet::tcp_socket& socket);
  kissnet::tcp_socket server;
  std::list<kissnet::tcp_socket> connections;
  std::vector<std::thread> workers;
  std::atomic<bool> accept_connections = false;
};

#endif // GAMELIB_GCNETSERVER_HPP
