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
  client(_client),
  chat_window(
    renderer, ASGE::Point2D(static_cast<float>(ASGE::SETTINGS.window_width) - 676, 0), _client),
  ready_button(
    renderer, UIButton::GREEN, ASGE::Point2D(0, 0), 300, 50, "READY",
    [this]() { onReadyButton(); }),
  disconnect_button(
    renderer, UIButton::RED, ASGE::Point2D(500, 0), 300, 50, "DISCONNECT",
    [this]() { onDisconnectButton(); })
{
}
void LobbyScene::render(ASGE::Renderer* renderer)
{
  chat_window.render(renderer);
  ready_button.render(renderer);
  disconnect_button.render(renderer);
}
void LobbyScene::keyInput(const ASGE::KeyEvent* keyEvent)
{
  chat_window.keyInput(keyEvent);
}
void LobbyScene::clickInput(const ASGE::ClickEvent* clickEvent, ASGE::Renderer* renderer)
{
  chat_window.clickInput(clickEvent, renderer);
  disconnect_button.clickInput(clickEvent, renderer);
  ready_button.clickInput(clickEvent, renderer);
}

void LobbyScene::netInput(
  ASGE::Renderer* renderer, NetUtil::CommandID command_id, UserClient& origin,
  const std::string& message)
{
  if (command_id == NetUtil::CHAT_MESSAGE)
  {
    std::string message_string = origin.username + " > " + message;
    std::cout << message_string << std::endl;
    chat_window.addMessage(renderer, message_string);
  }
  else if (command_id == NetUtil::CHANGE_USERNAME)
  {
    chat_window.addMessage(renderer, origin.username + " joined the lobby.");
  }
}
void LobbyScene::onReadyButton()
{
  scene_callback(SceneID::GAME);
}
void LobbyScene::onDisconnectButton()
{
  client.disconnect();
  scene_callback(SceneID::TITLE);
}
