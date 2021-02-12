//
// Created by huxy on 23/02/2020.
//

#ifndef NETGAME_GCNETCLIENT_HPP
#define NETGAME_GCNETCLIENT_HPP
#include "GComponent.hpp"
#include <kissnet.hpp>
#include <string>

class GCNetClient : public GameComponent
{
 public:
  GCNetClient();
  ~GCNetClient() override;
  kissnet::tcp_socket& connect(const std::string& server_ip, unsigned short server_port);
  void run();
  void update(double dt) override;
  void send(const std::string& message);
  std::atomic<bool> connected = false;
  std::atomic<bool> running   = false;

  GCNetClient(const GCNetClient&) = delete;
  GCNetClient& operator=(const GCNetClient&) = delete;

 private:
  kissnet::tcp_socket socket;
};

#endif // NETGAME_GCNETCLIENT_HPP
