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
#include <GameObjects/ConnectFour/ClientBoard.h>
#include <GameObjects/Scenes/Scene.h>
#include <GameObjects/UI/ChatWindow.h>
#include <GameObjects/UI/UIButton.h>

class GameScene : public Scene
{
 public:
  GameScene(
    ASGE::Renderer* renderer, GCNetClient& _client,
    std::function<void(Scene::SceneID)> _scene_callback);
  void render(ASGE::Renderer* renderer) override;
  bool clickInput(const ASGE::ClickEvent* click, ASGE::Renderer* renderer) override;
  void keyInput(const ASGE::KeyEvent* key) override;
  void mouseInput(const ASGE::MoveEvent* mouse) override;
  void update(float dt) override;
  void netInput(
    ASGE::Renderer* renderer, NetUtil::CommandID command_id, UserClient& origin,
    const std::string& message) override;

 private:
  std::function<void(Scene::SceneID)> scene_callback;
  GCNetClient& client;
  ClientBoard board;
  ChatWindow chat_window;
  SpriteComponent background;
  UIButton forfeit;
};

#endif // ASGENETGAME_GAMESCENE_H
