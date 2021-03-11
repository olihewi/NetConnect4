//
// Created by huxy on 23/02/2020.
//

#ifndef GAMELIB_GCNETSERVER_HPP
#define GAMELIB_GCNETSERVER_HPP

#include "GComponent.hpp"
#include "Utilities/NetUtil.h"
#include <GameObjects/ConnectFour/ServerBoard.h>
#include <Utilities/UserClient.h>
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
  void listen(UserClient& client);
  void processMessage(UserClient& client, kissnet::buffer<4096>& buffer);
  void onConnection(UserClient& client);
  kissnet::tcp_socket server;
  std::list<UserClient> clients;
  std::vector<std::thread> workers;
  ServerBoard board;
  std::atomic<bool> accept_connections = false;
  void relay(
    NetUtil::CommandID command_id, const UserClient& origin, const std::string& message,
    const socket_list& exclude);
  void send(
    kissnet::tcp_socket& socket, NetUtil::CommandID command_id, const UserClient& origin,
    const std::string& message);
  void assignPlayerID(UserClient& player);
  UserClient& getPlayer(size_t player_id);
  void aiTurn();
};

#endif // GAMELIB_GCNETSERVER_HPP
