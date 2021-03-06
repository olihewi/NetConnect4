//
// Created by Andrei on 21/02/2021.
//

#include "GameScene.h"

GameScene::GameScene(ASGE::Renderer* renderer, GCNetClient& _client) :
  client(_client), board(renderer, 7, 6, 1, client),
  chat_window(
    renderer, ASGE::Point2D(static_cast<float>(ASGE::SETTINGS.window_width) - 676, 0), _client)
{
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
}
void GameScene::keyInput(const ASGE::KeyEvent* key)
{
  chat_window.keyInput(key);
}
