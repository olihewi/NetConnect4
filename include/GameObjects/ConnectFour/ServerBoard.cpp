//
// Created by hewis on 06/03/2021.
//

#include "ServerBoard.h"
#include <algorithm>
ServerBoard::ServerBoard(const BoardSettings& _settings) : settings(_settings)
{
  constructBoard();
}
bool ServerBoard::drop(size_t column, const UserClient& player)
{
  if (column > settings.width)
  {
    return false;
  } /// Check for invalid input
  if (counters[column] != 0)
  {
    return false;
  } /// If column is not full
  for (size_t drop_index = column; drop_index < settings.width * (settings.height - 1);
       drop_index += settings.width)
  {
    if (counters[drop_index + settings.width] != 0)
    {
      counters[drop_index] = player.user_id;
      return true;
    }
  }
  counters[column + (settings.width * (settings.height - 1))] = player.user_id; /// For bottom
  return true;
}
bool ServerBoard::pop(size_t column, const UserClient& player)
{
  if (!settings.pop_out)
  {
    return false;
  }
  if (column > settings.width)
  {
    return false;
  } /// Check for invalid input
  if (counters[(settings.width * settings.height - settings.width) + column] != player.user_id)
  {
    return false;
  }
  for (size_t row = settings.height - 1; row > 0; row--)
  {
    counters[column + row * settings.width] = counters[column + (row - 1) * settings.width];
  }
  counters[column] = 0;
  return true;
}
size_t ServerBoard::checkVictory()
{
  auto horizontal = checkHorizontal();
  if (horizontal != 0)
  {
    return horizontal;
  }
  auto vertical = checkVertical();
  if (vertical != 0)
  {
    return vertical;
  }
  auto diagonal = checkDiagonal();
  if (diagonal != 0)
  {
    return diagonal;
  }
  return 0;
}
size_t ServerBoard::checkHorizontal()
{
  size_t count = 0;
  for (size_t row = 0; row < settings.height; row++)
  {
    size_t last_player = 0;
    for (size_t column = 0; column < settings.width; column++)
    {
      size_t this_counter = counters[column + row * settings.width];
      if (this_counter == last_player && this_counter != 0)
      {
        count++;
        if (count >= settings.num_counters_to_win - 1)
        {
          return this_counter;
        }
      }
      else
      {
        count = 0;
      }
      last_player = this_counter;
    }
    count = 0;
  }
  return 0;
}
size_t ServerBoard::checkVertical()
{
  size_t count = 0;
  for (size_t column = 0; column < settings.width; column++)
  {
    size_t last_player = 0;
    for (size_t row = 0; row < settings.height; row++)
    {
      size_t this_counter = counters[column + row * settings.width];
      if (this_counter == last_player && this_counter != 0)
      {
        count++;
        if (count >= settings.num_counters_to_win - 1)
        {
          return this_counter;
        }
      }
      else
      {
        count = 0;
      }
      last_player = this_counter;
    }
    count = 0;
  }
  return 0;
}
size_t ServerBoard::checkDiagonal()
{
  size_t count = 0;
  for (int row = static_cast<int>(settings.width) - static_cast<int>(settings.num_counters_to_win);
       row < static_cast<int>(settings.height + settings.num_counters_to_win);
       row++)
  {
    size_t last_player = 0;
    for (int iter_up = row * static_cast<int>(settings.width); iter_up > 0;
         iter_up += 1 - static_cast<int>(settings.width))
    {
      if (iter_up > static_cast<int>(counters.size() - 1))
      {
        continue;
      }
      size_t this_counter = counters[static_cast<size_t>(iter_up)];
      if (this_counter == last_player && this_counter != 0)
      {
        count++;
        if (count >= settings.num_counters_to_win - 1)
        {
          return this_counter;
        }
      }
      else
      {
        count = 0;
      }
      last_player = this_counter;
    }
    count = 0;
  }
  for (int row = static_cast<int>(settings.num_counters_to_win) - static_cast<int>(settings.width);
       row < static_cast<int>(settings.height + 1) - static_cast<int>(settings.num_counters_to_win);
       row++)
  {
    size_t last_player = 0;
    for (int iter_down = row * static_cast<int>(settings.width);
         iter_down < static_cast<int>(counters.size());
         iter_down += static_cast<int>(settings.width) + 1)
    {
      if (iter_down < 0)
      {
        continue;
      }
      size_t this_counter = counters[static_cast<size_t>(iter_down)];
      if (this_counter == last_player && this_counter != 0)
      {
        count++;
        if (count >= settings.num_counters_to_win - 1)
        {
          return this_counter;
        }
      }
      else
      {
        count = 0;
      }
      last_player = this_counter;
    }
    count = 0;
  }
  return 0;
}
void ServerBoard::constructBoard()
{
  counters.clear();
  for (size_t y = 0; y < settings.height; y++)
  {
    for (size_t x = 0; x < settings.width; x++)
    {
      counters.emplace_back(0);
    }
  }
}
std::string ServerBoard::getBoardString()
{
  std::string board_string;
  for (size_t y = 0; y < settings.height; y++)
  {
    for (size_t x = 0; x < settings.width; x++)
    {
      board_string += std::to_string(counters[x + y * settings.width]);
    }
    board_string += ',';
  }
  board_string.pop_back();
  return board_string;
}
bool ServerBoard::isEmpty()
{
  return !(std::any_of(counters.begin(), counters.end(), [](int i) { return i != 0; }));
}
