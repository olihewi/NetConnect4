//
// Created by hewis on 21/02/2021.
//

#include "LobbyScene.h"
#include <Engine/FileIO.h>
#include <iostream>
#include <utility>
LobbyScene::LobbyScene(
  ASGE::Renderer* renderer, std::function<void(Scene::SceneID)> _scene_callback,
  GCNetClient& _client) :
  scene_callback(std::move(_scene_callback)),
  chat_window(
    renderer, ASGE::Point2D(static_cast<float>(ASGE::SETTINGS.window_width) - 676, 0), _client),
  ready_button(renderer, UIButton::GREEN, ASGE::Point2D(0, 0), 300, 50, "READY")
{
}
void LobbyScene::render(ASGE::Renderer* renderer)
{
  chat_window.render(renderer);
  ready_button.render(renderer);
}
void LobbyScene::keyInput(const ASGE::KeyEvent* keyEvent)
{
  chat_window.keyInput(keyEvent);
}
void LobbyScene::clickInput(const ASGE::ClickEvent* clickEvent)
{
  chat_window.clickInput(clickEvent);
  ready_button.clickInput(clickEvent);
  if (ready_button.getClick())
  {
    scene_callback(Scene::SceneID::GAME);
  }
}
void LobbyScene::netInput(
  ASGE::Renderer* renderer, NetUtil::CommandID command_id, const std::string& message)
{
  if (command_id == NetUtil::CHAT_MESSAGE)
  {
    std::cout << "Received Message: " << message << std::endl;
    chat_window.addMessage(renderer, message);
  }
}
