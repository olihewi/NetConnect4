//
// Created by james on 28/01/2021.
//

#ifndef ASGENETGAME_ASGESERVER_HPP
#define ASGENETGAME_ASGESERVER_HPP

#include <ASGENetLib/GCNetServer.hpp>
class ASGEServer
{
 public:
  ASGEServer()  = default;
  ~ASGEServer() = default;

  bool init();
  int run();

 private:
  GCNetServer net_server;
};

#endif // ASGENETGAME_ASGESERVER_HPP
