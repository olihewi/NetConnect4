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
    RED = 64,
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
  explicit UserClient(size_t this_id) : user_id(this_id) {}
  UserClient() = default;
  kissnet::tcp_socket socket;
  size_t user_id       = 0;
  PlayerColour colour  = WHITE;
  std::string username = "UNNAMED";
};

#endif // ASGENETGAME_USERCLIENT_H
