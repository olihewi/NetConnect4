//
// Created by hewis on 18/02/2021.
//

#ifndef ASGENETGAME_NETUTIL_H
#define ASGENETGAME_NETUTIL_H

class NetUtil
{
 public:
  enum CommandID
  {
    CHAT_MESSAGE = 65,
    CHANGE_USERNAME,
    MAX_COMMAND_ID
  };
};

#endif // ASGENETGAME_NETUTIL_H
