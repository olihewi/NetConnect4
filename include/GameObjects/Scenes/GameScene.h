//
// Created by Andrei on 21/02/2021.
//

#ifndef ASGENETGAME_GAMESCENE_H
#define ASGENETGAME_GAMESCENE_H

#include <GameComponents/SpriteComponent.hpp>
#include <GameObjects/Scenes/Scene.h>

class GameScene : public Scene
{
 public:
  explicit GameScene(ASGE::Renderer* renderer);
  void render(ASGE::Renderer* renderer) override;
  void boardGame(ASGE::Renderer* renderer);

 private:
  std::array<SpriteComponent, 32 * 2> game_board;
};

#endif // ASGENETGAME_GAMESCENE_H
