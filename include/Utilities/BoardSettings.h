//
// Created by hewis on 08/03/2021.
//

#ifndef ASGENETGAME_BOARDSETTINGS_H
#define ASGENETGAME_BOARDSETTINGS_H
#include <stddef.h>
struct BoardSettings
{
 public:
  BoardSettings(
    size_t _width = 7, size_t _height = 6, bool _pop_out = false, size_t _num_counters_to_win = 4) :
    width(_width),
    height(_height), pop_out(_pop_out), num_counters_to_win(_num_counters_to_win)
  {
  }
  size_t width;
  size_t height;
  bool pop_out;
  size_t num_counters_to_win;
};
#endif // ASGENETGAME_BOARDSETTINGS_H
