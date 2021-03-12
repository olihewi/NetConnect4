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
    ASSIGN_PLAYER_ID, /// Server-only
    CHANGE_COLOUR,
    DROP_COUNTER,
    POP_OUT_COUNTER,
    DISCONNECTED,
    SET_BOARD_WIDTH,
    SET_BOARD_HEIGHT,
    SET_BOARD_POP_OUT,
    SET_BOARD_NUM_TO_WIN,
    READY_UP,
    START_GAME,
    FILL_ENTIRE_BOARD,
    WON_GAME,
    MAX_COMMAND_ID
  };
};

#endif // ASGENETGAME_NETUTIL_H
