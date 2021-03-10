//
// Created by hewis on 10/03/2021.
//
#include "CounterSprite.h"
#include <iostream>
CounterSprite::CounterSprite(
  ASGE::Renderer* renderer, UserClient::PlayerColour colour, ASGE::Point2D start_pos,
  float _end_pos, size_t _grid_pos) :
  grid_pos(_grid_pos),
  sprite(renderer, UserClient::getCounterFilepath(colour), start_pos), end_pos(_end_pos)
{
}
void CounterSprite::update(float dt)
{
  if (sprite.getPosition().y < end_pos)
  {
    y_vel += 20 * dt;
    sprite.translate(ASGE::Point2D(0, y_vel));
    if (sprite.getPosition().y >= end_pos)
    {
      sprite.setPosition(ASGE::Point2D(sprite.getPosition().x, end_pos));
      y_vel = 0;
    }
  }
}
void CounterSprite::render(ASGE::Renderer* renderer)
{
  sprite.render(renderer);
}
void CounterSprite::dropDownOne()
{
  end_pos += sprite.getSprite()->height();
}
