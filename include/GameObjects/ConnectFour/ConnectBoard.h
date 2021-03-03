//
// Created by hewis on 03/03/2021.
//

#ifndef ASGENETGAME_CONNECTBOARD_H
#define ASGENETGAME_CONNECTBOARD_H
#include "../GameObject.h"
#include <ASGENetLib/GCNetClient.hpp>
#include <GameComponents/SpriteComponent.hpp>
class ConnectBoard : public GameObject
{
 public:
  ConnectBoard(
    ASGE::Renderer* renderer, uint16_t board_width, uint16_t board_height, float board_scale,
    GCNetClient& _client);
  int dropCounter(size_t column, size_t player_id);
  void render(ASGE::Renderer* renderer) override;
  bool clickInput(const ASGE::ClickEvent* click, ASGE::Renderer* /*renderer*/) override;
  void inputDrop(ASGE::Renderer* renderer, UserClient& origin, int input);

 private:
  GCNetClient& client;
  uint16_t width;
  uint16_t height;
  std::vector<size_t> counters;
  std::vector<SpriteComponent> board_sprites;
  std::vector<SpriteComponent> counter_sprites;
};

#endif // ASGENETGAME_CONNECTBOARD_H
