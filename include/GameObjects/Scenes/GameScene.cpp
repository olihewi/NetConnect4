//
// Created by Andrei on 21/02/2021.
//

#include "GameScene.h"

GameScene::GameScene(ASGE::Renderer* renderer)
{
  boardGame(renderer);
}

void GameScene::render(ASGE::Renderer* renderer)
{
  for (auto& board : game_board)
  {
    board.render(renderer);
  }
}

void GameScene::boardGame(ASGE::Renderer* renderer)
{
  auto x_pos            = 0.0F;
  auto y_pos            = 0.0F;
  const int BOARD_Y_POS = 75;

  for (auto& board : game_board)
  {
    board = SpriteComponent(renderer, "data/connectblock.png", ASGE::Point2D(0, 0));
    board.getSprite()->width(static_cast<float>(ASGE::SETTINGS.window_width) / 8.F);
    board.getSprite()->height(124.0F);
    board.getSprite()->xPos(x_pos);
    board.getSprite()->yPos(y_pos + BOARD_Y_POS);
    x_pos += board.getSprite()->width();

    if (x_pos >= board.getSprite()->width() * 8)
    {
      x_pos = 0;
      y_pos += board.getSprite()->height();
    }
  }
}
