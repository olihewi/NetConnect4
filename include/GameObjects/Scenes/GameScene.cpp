//
// Created by Andrei on 21/02/2021.
//

#include "GameScene.h"

GameScene::GameScene(ASGE::Renderer* renderer, GCNetClient& _client) :
  client(_client), board(renderer, 7, 6, 1, client)
{
  boardGame(renderer);
  // board_space(renderer);
  playerTurn = TextComponent(
    renderer, "TURNS", ASGE::Point2D(500, 500), FONTS::CHAT_MESSAGE, 1, ASGE::COLOURS::GREEN);
}

void GameScene::boardGame(ASGE::Renderer* renderer)
{
  auto x_pos            = 0.0F;
  auto y_pos            = 0.0F;
  const int BOARD_Y_POS = 75;
  for (auto& board_tile : game_board)
  {
    board_tile = SpriteComponent(renderer, "data/images/connectblock.png", ASGE::Point2D(0, 0));
    board_tile.getSprite()->width(static_cast<float>(ASGE::SETTINGS.window_width) / 8.F);
    board_tile.getSprite()->height(124.0F);
    board_tile.getSprite()->xPos(x_pos);
    board_tile.getSprite()->yPos(y_pos + BOARD_Y_POS);
    x_pos += board_tile.getSprite()->width();
    board_tile.getSprite()->setGlobalZOrder(0);

    if (x_pos >= board_tile.getSprite()->width() * 8)
    {
      x_pos = 0;
      y_pos += board_tile.getSprite()->height();
    }
  }
  for (auto& click_grid : board_space)
  {
    click_grid = SpriteComponent(renderer, "data/images/empty_space.png", { 0, 0 });
    click_grid.getSprite()->width(static_cast<float>(ASGE::SETTINGS.window_width) / 8.F);
    click_grid.getSprite()->height(124.0F);
    click_grid.getSprite()->xPos(x_pos);
    click_grid.getSprite()->yPos(y_pos + BOARD_Y_POS);
    x_pos += click_grid.getSprite()->width();
    click_grid.getSprite()->setGlobalZOrder(1);

    if (x_pos >= click_grid.getSprite()->width() * 8)
    {
      x_pos = 0;
      y_pos += click_grid.getSprite()->height();
    }
  }
}

bool GameScene::clickInput(const ASGE::ClickEvent* click, ASGE::Renderer* renderer)
{
  board.clickInput(click, renderer);
  /*if (click->xpos >= 0 && click->xpos <= 1920)
  {
    game_board[0].loadSprite(renderer, "data/images/chips/red.png");
    return true;
  }*/
  return false;
}
void GameScene::render(ASGE::Renderer* renderer)
{
  /*for (auto& board_tile : game_board)
  {
    board_tile.render(renderer);
  }*/
  for (auto& board_item : board_space)
  {
    board_item.render(renderer);
  }
  board.render(renderer);
  playerTurn.render(renderer);
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
