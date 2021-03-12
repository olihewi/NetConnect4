//
// Created by huxy on 23/02/2020.
//

#ifndef NETGAME_GCNETCLIENT_HPP
#define NETGAME_GCNETCLIENT_HPP
#include "GComponent.hpp"
#include "Utilities/UserClient.h"
#include <Utilities/NetUtil.h>
#include <functional>
#include <kissnet.hpp>
#include <string>
#include <vector>

class GCNetClient : public GameComponent
{
 public:
  GCNetClient();
  GCNetClient(const GCNetClient&) = delete;
  GCNetClient& operator=(const GCNetClient&) = delete;
  ~GCNetClient() override;

  void setCallback(std::function<void(const char*)> _callback);

  kissnet::tcp_socket&
  connect(const std::string& server_ip, unsigned short server_port, const std::string& username);
  void run();

  void render(ASGE::Renderer* /*renderer*/) override {}
  void send(NetUtil::CommandID command_id, const std::string& message);
  void processMessage(kissnet::buffer<4096> buffer);
  void disconnect();

  [[nodiscard]] UserClient& getPlayer(size_t index);
  [[nodiscard]] UserClient& getThisPlayer();

  void update(double /*dt*/) override {}

 private:
  kissnet::tcp_socket socket;
  std::atomic<bool> connected = false;
  std::function<void(const char*)> net_callback;
  std::vector<UserClient> players{};
  UserClient ai_player;
};

#endif // NETGAME_GCNETCLIENT_HPP
