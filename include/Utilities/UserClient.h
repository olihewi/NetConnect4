//
// Created by hewis on 18/02/2021.
//

#ifndef ASGENETGAME_USERCLIENT_H
#define ASGENETGAME_USERCLIENT_H
#include <kissnet.hpp>

class UserClient
{
 public:
  enum PlayerColour
  {
    RED,
    YELLOW,
    CYAN,
    GREEN,
    BLUE,
    PURPLE,
    PINK,
    BLACK,
    WHITE
  };
  bool operator==(const UserClient& rhs) const { return rhs.socket == socket; }
  UserClient(size_t _ID) : ID(_ID) {}
  UserClient() = default;
  kissnet::tcp_socket socket;
  size_t ID;
  PlayerColour colour;
  std::string username = "UNNAMED";
};

#endif // ASGENETGAME_USERCLIENT_H
