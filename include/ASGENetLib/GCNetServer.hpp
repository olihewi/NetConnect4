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
  void render(ASGE::Renderer* /*renderer*/) override {}

  void start();

  GCNetServer(const GCNetServer&) = delete;

  GCNetServer& operator=(const GCNetServer&) = delete;
  using socket_cref                          = std::reference_wrapper<const kissnet::tcp_socket>;
  using socket_list                          = std::list<socket_cref>;

 private:
  void listen(kissnet::tcp_socket& socket);

  kissnet::tcp_socket server;
  std::list<kissnet::tcp_socket> connections;
  std::vector<std::thread> workers;
  std::atomic<bool> accept_connections = false;
  void send(const kissnet::buffer<4096>& buffer, size_t length, const socket_list& exclude);
};

#endif // GAMELIB_GCNETSERVER_HPP
