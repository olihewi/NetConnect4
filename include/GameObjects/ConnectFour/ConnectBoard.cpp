//
// Created by hewis on 03/03/2021.
//

#include "ConnectBoard.h"
#include <iostream>
ConnectBoard::ConnectBoard(
  ASGE::Renderer* renderer, uint16_t board_width, uint16_t board_height, float board_scale,
  GCNetClient& _client) :
  client(_client),
  width(board_width), height(board_height)
{
  for (uint16_t y = 0; y < board_height; y++)
  {
    for (uint16_t x = 0; x < board_width; x++)
    {
      counters.emplace_back(0);
      auto& board_sprite = board_sprites.emplace_back(
        SpriteComponent(renderer, "data/images/connectblock.png", ASGE::Point2D(0, 0)));
      float block_size = board_sprite.getSprite()->width() * board_scale;
      board_sprite.getSprite()->width(block_size);
      board_sprite.getSprite()->height(block_size);
      board_sprite.getSprite()->setGlobalZOrder(1);
      board_sprite.setPosition(
        ASGE::Point2D(static_cast<float>(x) * block_size, static_cast<float>(y) * block_size));
    }
  }
  // int drop_index = dropCounter(1);
  // counter_sprites.emplace_back(SpriteComponent(renderer,
  // "data/images/chips/green.png",board_sprites[static_cast<size_t>(drop_index)].getPosition()));
}
int ConnectBoard::dropCounter(size_t column, size_t player_id)
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
void ConnectBoard::render(ASGE::Renderer* renderer)
{
  for (auto& board_sprite : board_sprites)
  {
    board_sprite.render(renderer);
  }
  for (auto& counter_sprite : counter_sprites)
  {
    counter_sprite.render(renderer);
  }
}
bool ConnectBoard::clickInput(const ASGE::ClickEvent* click, ASGE::Renderer* renderer)
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
      int click_x = static_cast<int>(
        ((click->xpos - board_sprites.front().getPosition().x) /
         (board_sprites.back().getPosition().x + board_sprites.back().getSprite()->width())) *
        width);
      int click_y = static_cast<int>(
        ((click->ypos - board_sprites.front().getPosition().y) /
         (board_sprites.back().getPosition().y + board_sprites.back().getSprite()->height())) *
        height);
      int drop_index = dropCounter(static_cast<size_t>(click_x), client.getThisPlayer().user_id);
      if (drop_index != -1)
      {
        auto sprite_path = UserClient::getCounterFilepath(client.getThisPlayer().colour);
        counter_sprites.emplace_back(SpriteComponent(
          renderer, sprite_path, board_sprites[static_cast<size_t>(drop_index)].getPosition()));
      }
    }
  }
  return true;
}
