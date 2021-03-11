//
// Created by hewis on 03/03/2021.
//

#include "ClientBoard.h"
#include <iostream>
#include <math.h>
ClientBoard::ClientBoard(
  ASGE::Renderer* renderer, uint16_t board_width, uint16_t board_height, float board_scale,
  GCNetClient& _client, bool _pop_out) :
  client(_client),
  width(board_width), height(board_height), pop_out(_pop_out),
  cursor(renderer, "data/images/chips/white.png", ASGE::Point2D(0, 0))
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
  cursor.setVisibility(false);
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
  cursor.render(renderer);
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
    is_it_my_turn = false;
    counter_sprites.emplace_back(CounterSprite(
      renderer,
      origin.colour,
      ASGE::Point2D(board_sprites[static_cast<size_t>(drop_index)].getPosition().x, -128),
      board_sprites[static_cast<size_t>(drop_index)].getPosition().y,
      static_cast<size_t>(drop_index)));
  }
}
void ClientBoard::inputPop(ASGE::Renderer* /*renderer*/, const UserClient& origin, int input)
{
  int pop_index = popOut(static_cast<size_t>(input), origin.user_id);
  if (pop_index != -1)
  {
    if (origin.user_id == client.getThisPlayer().user_id)
    {
      is_it_my_turn = false;
    }
    for (size_t i = 0; i < counter_sprites.size(); i++)
    {
      if (counter_sprites[i].grid_pos == (width * height - width) + static_cast<size_t>(input))
      {
        counter_sprites.erase(counter_sprites.begin() + static_cast<int>(i));
        i--;
        if (i >= counter_sprites.size())
        {
          continue;
        }
      }
      if (counter_sprites[i].grid_pos % width == static_cast<size_t>(input))
      {
        counter_sprites[i].dropDownOne();
        counter_sprites[i].grid_pos += width;
      }
    }
  }
}

void ClientBoard::update(float dt)
{
  for (size_t i = 0; i < counter_sprites.size(); i++)
  {
    counter_sprites[i].update(dt);
  }
  opacity_timer += dt;
  cursor.getSprite()->opacity(sin(3 * opacity_timer) / 8 + 0.25F);
}
void ClientBoard::mouseInput(const ASGE::MoveEvent* mouse)
{
  if (
    mouse->xpos >= board_sprites.front().getPosition().x &&
    mouse->xpos <=
      board_sprites.back().getPosition().x + board_sprites.back().getSprite()->width() &&
    mouse->ypos >= board_sprites.front().getPosition().y &&
    mouse->ypos <= board_sprites.back().getPosition().y + board_sprites.back().getSprite()->width())
  {
    cursor.setVisibility(true);
    size_t click_x = static_cast<size_t>(
      ((mouse->xpos - board_sprites.front().getPosition().x) /
       (board_sprites.back().getPosition().x + board_sprites.back().getSprite()->width())) *
      width);
    cursor.setPosition(ASGE::Point2D(
      board_sprites.front().getPosition().x +
      static_cast<float>(click_x) * board_sprites.front().getSprite()->width()));
  }
  else
  {
    cursor.setVisibility(false);
  }
  if (!is_it_my_turn)
  {
    cursor.setVisibility(false);
  }
}
