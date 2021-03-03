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
    switch (colour)
    {
      case RED:
        file_path += "red";
        break;
      case ORANGE:
        file_path += "orange";
        break;
      case YELLOW:
        file_path += "yellow";
        break;
      case GREEN:
        file_path += "green";
        break;
      case BLUE:
        file_path += "blue";
        break;
      case PURPLE:
        file_path += "purple";
        break;
      case PINK:
        file_path += "pink";
        break;
      case BLACK:
        file_path += "black";
        break;
      case WHITE:
        file_path += "white";
    }
    return file_path + ".png";
  }
  kissnet::tcp_socket socket;
  size_t user_id       = 0;
  PlayerColour colour  = WHITE;
  std::string username = "UNNAMED";
};

#endif // ASGENETGAME_USERCLIENT_H
