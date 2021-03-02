//
// Created by Andrei on 21/02/2021.
//

#ifndef ASGENETGAME_GAMESCENE_H
#define ASGENETGAME_GAMESCENE_H

#include "ASGENetLib/GCNetClient.hpp"
#include "Utilities/FontManager.h"
#include "Utilities/UserClient.h"
#include <GameComponents/SpriteComponent.hpp>
#include <GameComponents/TextComponent.hpp>
#include <GameObjects/Scenes/Scene.h>

class GameScene : public Scene
{
 public:
  explicit GameScene(ASGE::Renderer* renderer);
  void render(ASGE::Renderer* renderer) override;
  void boardGame(ASGE::Renderer* renderer);
  void clickInput(const ASGE::ClickEvent*, ASGE::Renderer* renderer) override;

 private:
  std::array<SpriteComponent, 32 * 2> board_space;
  std::array<SpriteComponent, 32 * 2> game_board;
  TextComponent playerTurn;
  UserClient user;
};

#endif // ASGENETGAME_GAMESCENE_H
