//
// Created by Andrei on 21/02/2021.
//

#include "GameScene.h"

#include <utility>

GameScene::GameScene(
  ASGE::Renderer* renderer, GCNetClient& _client,
  std::function<void(Scene::SceneID)> _scene_callback) :
  scene_callback(std::move(_scene_callback)),
  client(_client), board(renderer, 7, 6, 1, client, true),
  chat_window(
    renderer, ASGE::Point2D(static_cast<float>(ASGE::SETTINGS.window_width) - 676, 0), _client),
  background(renderer, "data/images/background3.png", ASGE::Point2D(0, 0))
{
  background.getSprite()->setGlobalZOrder(-2);
}

bool GameScene::clickInput(const ASGE::ClickEvent* click, ASGE::Renderer* renderer)
{
  board.clickInput(click, renderer);
  chat_window.clickInput(click, renderer);
  return false;
}
void GameScene::render(ASGE::Renderer* renderer)
{
  board.render(renderer);
  chat_window.render(renderer);
  background.render(renderer);
}
void GameScene::netInput(
  ASGE::Renderer* renderer, NetUtil::CommandID command_id, UserClient& origin,
  const std::string& message)
{
  if (command_id == NetUtil::CHAT_MESSAGE)
  {
    std::string message_string = origin.username + " > " + message;
    chat_window.addMessage(renderer, message_string);
  }
  if (command_id == NetUtil::DROP_COUNTER)
  {
    board.inputDrop(renderer, origin, std::stoi(message));
  }
  if (command_id == NetUtil::POP_OUT_COUNTER)
  {
    board.inputPop(renderer, origin, std::stoi(message));
  }
  if (command_id == NetUtil::IT_IS_YOUR_TURN_NOW)
  {
    board.is_it_my_turn = true;
  }
  if (command_id == NetUtil::WON_GAME)
  {
    scene_callback(Scene::SceneID::WIN_GAME);
  }
}
void GameScene::keyInput(const ASGE::KeyEvent* key)
{
  chat_window.keyInput(key);
}
void GameScene::update(float dt)
{
  board.update(dt);
}
void GameScene::mouseInput(const ASGE::MoveEvent* mouse)
{
  board.mouseInput(mouse);
}
