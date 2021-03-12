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
  background(renderer, "data/images/background3.png", ASGE::Point2D(0, 0)),
  forfeit(
    renderer, UIButton::FANCY,
    ASGE::Point2D(static_cast<float>(ASGE::SETTINGS.window_width) - 676, 0), 676, 75, "Forfeit",
    [this]() { client.send(NetUtil::FORFEIT, "1"); }, FONTS::FANCY)
{
  background.getSprite()->setGlobalZOrder(-2);
}

bool GameScene::clickInput(const ASGE::ClickEvent* click, ASGE::Renderer* renderer)
{
  board.clickInput(click, renderer);
  chat_window.clickInput(click, renderer);
  forfeit.clickInput(click, renderer);
  return false;
}
void GameScene::render(ASGE::Renderer* renderer)
{
  board.render(renderer);
  chat_window.render(renderer);
  background.render(renderer);
  forfeit.render(renderer);
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
  else if (command_id == NetUtil::DROP_COUNTER)
  {
    board.inputDrop(renderer, origin, std::stoi(message));
  }
  else if (command_id == NetUtil::POP_OUT_COUNTER)
  {
    board.inputPop(renderer, origin, std::stoi(message));
  }
  else if (command_id == NetUtil::WON_GAME || command_id == NetUtil::FORFEIT)
  {
    chat_window.addMessage(renderer, origin.username + " has won!");
    scene_callback(Scene::SceneID::WIN_GAME);
  }
  else if (command_id == NetUtil::FILL_ENTIRE_BOARD)
  {
    board.fillBoard(renderer, message);
  }
  else if (command_id == NetUtil::SET_BOARD_POP_OUT)
  {
    board.pop_out = message[0] == '1';
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
