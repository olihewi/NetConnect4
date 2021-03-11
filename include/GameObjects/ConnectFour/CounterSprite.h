//
// Created by hewis on 10/03/2021.
//

#ifndef ASGENETGAME_COUNTERSPRITE_H
#define ASGENETGAME_COUNTERSPRITE_H
#include <GameComponents/SpriteComponent.hpp>
#include <GameObjects/GameObject.h>
#include <Utilities/UserClient.h>
class CounterSprite : public GameObject
{
 public:
  CounterSprite(
    ASGE::Renderer* renderer, UserClient::PlayerColour colour, ASGE::Point2D start_pos,
    float _end_pos, size_t _grid_pos);
  void update(float dt) override;
  void render(ASGE::Renderer* renderer) override;
  void dropDownOne();
  size_t grid_pos;

 private:
  SpriteComponent sprite;
  float end_pos;
  float y_vel = 0;
};

#endif // ASGENETGAME_COUNTERSPRITE_H
