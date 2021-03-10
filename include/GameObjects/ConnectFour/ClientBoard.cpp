//
// Created by hewis on 03/03/2021.
//

#include "ClientBoard.h"
#include <iostream>
ClientBoard::ClientBoard(
  ASGE::Renderer* renderer, uint16_t board_width, uint16_t board_height, float board_scale,
  GCNetClient& _client, bool _pop_out) :
  client(_client),
  width(board_width), height(board_height), pop_out(_pop_out)
{
  for (uint16_t y = 0; y < board_height; y++)
  {
    for (uint16_t x = 0; x < board_width; x++)
    {
      counters.emplace_back(0);
      auto& board_sprite = board_sprites.emplace_back(
        SpriteComponent(renderer, "data/images/board/regular.png", ASGE::Point2D(0, 0)));
      if (pop_out && y == board_height - 1)
      {
        board_sprite.loadSprite(renderer, "data/images/board/pop_out.png");
      }
      float block_size = board_sprite.getSprite()->width() * board_scale;
      board_sprite.getSprite()->width(block_size);
      board_sprite.getSprite()->height(block_size);
      board_sprite.getSprite()->setGlobalZOrder(1);
      board_sprite.setPosition(
        ASGE::Point2D(static_cast<float>(x) * block_size, static_cast<float>(y) * block_size));
    }
  }
}
int ClientBoard::dropCounter(size_t column, size_t player_id)
{
  if (column < width)
  {
    if (counters[column] == 0) /// If the top counter of this row is empty
    {
      for (size_t drop_index = column; drop_index < width * (height - 1); drop_index += width)
      {
        if (counters[drop_index + width] != 0)
        {
          counters[drop_index] = player_id;
          return static_cast<int>(drop_index);
        }
      }
      counters[column + (width * (height - 1))] = 1;
      return static_cast<int>(column) + (width * (height - 1));
    }
  }
  return -1;
}
int ClientBoard::popOut(size_t column, size_t player_id)
{
  if (column < width)
  {
    if (counters[(width * height - width) + column] == player_id) /// If it is the player's counter
    {
      for (size_t row = height - 1; row > 0; row--)
      {
        counters[column + row * width] = counters[column + (row - 1) * width];
      }
      counters[column] = 0;
      return 1;
    }
  }
  return -1;
}

void ClientBoard::render(ASGE::Renderer* renderer)
{
  /// Range-based for loops cannot be used due to multithreading...
  for (size_t i = 0; i < board_sprites.size(); i++)
  {
    board_sprites[i].render(renderer);
  }
  for (size_t i = 0; i < counter_sprites.size(); i++)
  {
    counter_sprites[i].render(renderer);
  }
}
bool ClientBoard::clickInput(const ASGE::ClickEvent* click, ASGE::Renderer* /*renderer*/)
{
  if (click->action == ASGE::KEYS::KEY_PRESSED)
  {
    if (
      click->xpos >= board_sprites.front().getPosition().x &&
      click->xpos <=
        board_sprites.back().getPosition().x + board_sprites.back().getSprite()->width() &&
      click->ypos >= board_sprites.front().getPosition().y &&
      click->ypos <=
        board_sprites.back().getPosition().x + board_sprites.back().getSprite()->height())
    {
      size_t click_x = static_cast<size_t>(
        ((click->xpos - board_sprites.front().getPosition().x) /
         (board_sprites.back().getPosition().x + board_sprites.back().getSprite()->width())) *
        width);
      if (
        pop_out && click->ypos >= board_sprites.back().getPosition().y &&
        counters[(width * height - width) + click_x] == client.getThisPlayer().user_id)
      {
        client.send(NetUtil::POP_OUT_COUNTER, std::to_string(click_x));
      }
      else
      {
        client.send(NetUtil::DROP_COUNTER, std::to_string(click_x));
      }
    }
  }
  return true;
}
void ClientBoard::inputDrop(ASGE::Renderer* renderer, const UserClient& origin, int input)
{
  int drop_index = dropCounter(static_cast<size_t>(input), origin.user_id);
  if (drop_index != -1)
  {
    if (checkVictory() != 0)
    {
      std::cout << "has won" << std::endl;
    }
    auto sprite_path = UserClient::getCounterFilepath(origin.colour);
    counter_sprites.emplace_back(SpriteComponent(
      renderer, sprite_path, board_sprites[static_cast<size_t>(drop_index)].getPosition()));
  }
}
void ClientBoard::inputPop(ASGE::Renderer* /*renderer*/, const UserClient& /*origin*/, int /*input*/)
{
}

size_t ClientBoard::checkVictory()
{
  auto horizontal = horizontalCheck();
  if (horizontal != 0)
  {
    return horizontal;
  }
  auto vertical = verticalCheck();
  if (vertical != 0)
  {
    return vertical;
  }
  auto diag_up = upwardsDiagonalCheck();
  if (diag_up != 0)
  {
    return diag_up;
  }
  auto diag_down = downwardsDiagonalCheck();
  if (diag_down != 0)
  {
    return diag_down;
  }
  return 0;
}
size_t ClientBoard::horizontalCheck()
{
  int count = 0;
  for (size_t row = 0; row < height; row++)
  {
    size_t last_player = 0;
    for (size_t column = 0; column < width; column++)
    {
      size_t this_counter = counters[column + row * width];
      if (this_counter == last_player && this_counter != 0)
      {
        count++;
        if (count >= num_counters_to_win - 1)
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
size_t ClientBoard::verticalCheck()
{
  int count = 0;
  for (size_t column = 0; column < width; column++)
  {
    size_t last_player = 0;
    for (size_t row = 0; row < height; row++)
    {
      size_t this_counter = counters[column + row * width];
      if (this_counter == last_player && this_counter != 0)
      {
        count++;
        if (count >= num_counters_to_win - 1)
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
size_t ClientBoard::upwardsDiagonalCheck()
{
  int count = 0;
  for (int row = width - num_counters_to_win; row < height + num_counters_to_win; row++)
  {
    size_t last_player = 0;
    for (int iter_up = row * width; iter_up > 0; iter_up += 1 - width)
    {
      if (iter_up > static_cast<int>(counters.size() - 1))
      {
        continue;
      }
      size_t this_counter = counters[static_cast<size_t>(iter_up)];
      if (this_counter == last_player && this_counter != 0)
      {
        count++;
        if (count >= num_counters_to_win - 1)
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
size_t ClientBoard::downwardsDiagonalCheck()
{
  int count = 0;
  for (int row = num_counters_to_win - width; row < height + 1 - num_counters_to_win; row++)
  {
    size_t last_player = 0;
    for (int iter_down = row * width; iter_down < static_cast<int>(counters.size());
         iter_down += width + 1)
    {
      if (iter_down < 0)
      {
        continue;
      }
      size_t this_counter = counters[static_cast<size_t>(iter_down)];
      if (this_counter == last_player && this_counter != 0)
      {
        count++;
        if (count >= num_counters_to_win - 1)
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