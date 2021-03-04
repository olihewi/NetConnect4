//
// Created by Andrei on 21/02/2021.
//

#include "GameScene.h"

GameScene::GameScene(ASGE::Renderer* renderer, GCNetClient& _client) :
  client(_client), board(renderer, 7, 6, 1, client)
{
}

bool GameScene::clickInput(const ASGE::ClickEvent* click, ASGE::Renderer* renderer)
{
  board.clickInput(click, renderer);
  return false;
}
void GameScene::render(ASGE::Renderer* renderer)
{
  board.render(renderer);
}
void GameScene::netInput(
  ASGE::Renderer* renderer, NetUtil::CommandID command_id, UserClient& origin,
  const std::string& message)
{
  if (command_id == NetUtil::DROP_COUNTER)
  {
    board.inputDrop(renderer, origin, std::stoi(message));
  }
}
