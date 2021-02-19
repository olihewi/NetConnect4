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
    MENU_GAME  = 1,
    GAME       = 2,
    LOBBY_GAME = 3,
    EXIT_GAME  = 4
  };

  MenuItem gameState = MenuItem::MENU_GAME;

 public:
  explicit ASGENetGame(const ASGE::GameSettings& settings);

  ~ASGENetGame() override;
  ASGENetGame(const ASGENetGame&) = delete;
  ASGENetGame& operator=(const ASGENetGame&) = delete;

  void keyHandler(ASGE::SharedEventData data);
  void update(const ASGE::GameTime& us) override;
  void render() override;
  void fixedUpdate(const ASGE::GameTime& us) override;
  // void disable(ASGE::Input* input);
  // void enable(ASGE::Input* input);

  bool init();

 private:
  std::vector<std::unique_ptr<GameComponent>> game_components;
  GCNetClient client;
  int key_callback_id = -1; /**< Key Input Callback ID. */
  std::string input_string;

  std::unique_ptr<SpriteComponent> background;
};
