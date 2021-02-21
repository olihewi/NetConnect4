//
// Created by Andrei on 21/02/2021.
//

#ifndef ASGENETGAME_GAMESCENE_H
#define ASGENETGAME_GAMESCENE_H

#include <GameComponents/SpriteComponent.hpp>
#include <GameObjects/GameObject.h>

class GameScene : public GameObject
{
 public:
  GameScene(ASGE::Renderer* renderer);
  void render(ASGE::Renderer* renderer) override;
  void board_game(ASGE::Renderer* renderer);

 private:
  std::array<SpriteComponent, 32 * 2> game_board;
};

#endif // ASGENETGAME_GAMESCENE_H
