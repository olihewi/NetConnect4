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
#include <GameObjects/ConnectFour/ConnectBoard.h>
#include <GameObjects/Scenes/Scene.h>

class GameScene : public Scene
{
 public:
  GameScene(ASGE::Renderer* renderer, GCNetClient& _client);
  void render(ASGE::Renderer* renderer) override;
  bool clickInput(const ASGE::ClickEvent* click, ASGE::Renderer* renderer) override;
  void netInput(
    ASGE::Renderer* renderer, NetUtil::CommandID command_id, UserClient& origin,
    const std::string& message) override;

 private:
  GCNetClient& client;
  ConnectBoard board;
};

#endif // ASGENETGAME_GAMESCENE_H
