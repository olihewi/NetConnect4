//
// Created by hewis on 18/02/2021.
//

#ifndef ASGENETGAME_USERCLIENT_H
#define ASGENETGAME_USERCLIENT_H
#include <kissnet.hpp>

class UserClient
{
 public:
  kissnet::tcp_socket socket;
  std::string username = "UNNAMED";
};

#endif // ASGENETGAME_USERCLIENT_H
