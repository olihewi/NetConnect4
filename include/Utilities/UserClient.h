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
    ORANGE,
    YELLOW,
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
  static std::string getCounterFilepath(PlayerColour colour)
  {
    std::string file_path = "data/images/chips/";
    file_path += getColourName(colour);
    return file_path + ".png";
  }
  static std::string getColourName(PlayerColour colour)
  {
    switch (colour)
    {
      case RED:
        return "red";
      case ORANGE:
        return "orange";
      case YELLOW:
        return "yellow";
      case GREEN:
        return "green";
      case BLUE:
        return "blue";
      case PURPLE:
        return "purple";
      case PINK:
        return "pink";
      case BLACK:
        return "black";
      case WHITE:
        return "white";
    }
  }
  kissnet::tcp_socket socket;
  size_t user_id       = 0;
  PlayerColour colour  = WHITE;
  std::string username = "UNNAMED";
  bool ready           = false;
};

#endif // ASGENETGAME_USERCLIENT_H
