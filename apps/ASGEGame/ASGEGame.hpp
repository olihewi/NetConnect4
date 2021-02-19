//
// Created by huxy on 23/02/2020.
//

#pragma once

#include <ASGENetLib/GCNetClient.hpp>
#include <ASGENetLib/GComponent.hpp>
#include <Engine/OGLGame.h>
#include <GameComponents/SpriteComponent.hpp>
#include <vector>

class ASGENetGame : public ASGE::OGLGame
{
 public:
  enum class MenuItem
  {
    MENU_GAME = 0,
    GAME      = 1,
    //  LOBBY_GAME = 2,
    //  EXIT_GAME  = 3
  };

  MenuItem gameState = MenuItem::MENU_GAME;

 public:
  explicit ASGENetGame(const ASGE::GameSettings& settings);

  ~ASGENetGame() override;

  ASGENetGame(const ASGENetGame&) = delete;

  ASGENetGame& operator=(const ASGENetGame&) = delete;

  // void disable(ASGE::Input* input);
  // void enable(ASGE::Input* input);
  void fixedUpdate(const ASGE::GameTime& us) override;
  void gameBoard();
  void gameRender();
  void keyHandler(ASGE::SharedEventData data);
  void render() override;
  void update(const ASGE::GameTime& us) override;

  bool init();

 private:
  std::vector<std::unique_ptr<GameComponent>> game_components;
  GCNetClient client;

  int key_callback_id = -1; /**< Key Input Callback ID. */

  float window_height = static_cast<float>(ASGE::SETTINGS.window_height);
  float window_width  = static_cast<float>(ASGE::SETTINGS.window_width);
  float BOARD_HEIGHT  = 124.0F;
  float BOARD_WIDTH   = window_width / 8;

  std::string input_string;
  std::unique_ptr<SpriteComponent> background;
  std::array<std::unique_ptr<SpriteComponent>, 32 * 2> game_board;
};
