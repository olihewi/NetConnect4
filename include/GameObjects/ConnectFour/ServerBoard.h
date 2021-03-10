//
// Created by hewis on 06/03/2021.
//

#ifndef ASGENETGAME_SERVERBOARD_H
#define ASGENETGAME_SERVERBOARD_H
#include <Utilities/BoardSettings.h>
#include <Utilities/UserClient.h>
#include <vector>
class ServerBoard
{
 public:
  ServerBoard(BoardSettings _settings = BoardSettings());
  void constructBoard();
  bool drop(size_t column, const UserClient& player);
  bool pop(size_t column, const UserClient& player);
  std::string getBoardString();
  size_t checkVictory();
  BoardSettings settings;

 private:
  size_t checkHorizontal();
  size_t checkVertical();
  size_t checkDiagonal();
  std::vector<size_t> counters;
};

#endif // ASGENETGAME_SERVERBOARD_H