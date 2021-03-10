//
// Created by hewis on 03/03/2021.
//

#ifndef ASGENETGAME_CLIENTBOARD_H
#define ASGENETGAME_CLIENTBOARD_H
#include "../GameObject.h"
#include <ASGENetLib/GCNetClient.hpp>
#include <GameObjects/ConnectFour/CounterSprite.h>
class ClientBoard : public GameObject
{
 public:
  ClientBoard(
    ASGE::Renderer* renderer, uint16_t board_width, uint16_t board_height, float board_scale,
    GCNetClient& _client, bool _pop_out = false);
  int dropCounter(size_t column, size_t player_id);
  int popOut(size_t column, size_t player_id);
  void render(ASGE::Renderer* renderer) override;
  void update(float dt) override;
  bool clickInput(const ASGE::ClickEvent* click, ASGE::Renderer* /*renderer*/) override;
  void mouseInput(const ASGE::MoveEvent* mouse) override;
  void inputDrop(ASGE::Renderer* renderer, const UserClient& origin, int input);
  void inputPop(ASGE::Renderer* renderer, const UserClient& origin, int input);
  size_t checkVictory();

  size_t horizontalCheck();
  size_t verticalCheck();
  size_t upwardsDiagonalCheck();
  size_t downwardsDiagonalCheck();

 private:
  GCNetClient& client;
  uint16_t width;
  uint16_t height;
  uint16_t num_counters_to_win = 4;
  bool pop_out;
  std::vector<size_t> counters;
  std::vector<SpriteComponent> board_sprites;
  std::vector<CounterSprite> counter_sprites;
  SpriteComponent cursor;
  float opacity_timer = 0;
};

#endif // ASGENETGAME_CLIENTBOARD_H
