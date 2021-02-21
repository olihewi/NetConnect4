//
// Created by huxy on 23/02/2020.
//

#pragma once

#include <ASGENetLib/GCNetClient.hpp>
#include <ASGENetLib/GComponent.hpp>
#include <Engine/OGLGame.h>
#include <GameComponents/SpriteComponent.hpp>
#include <GameObjects/GameObject.h>
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

  void fixedUpdate(const ASGE::GameTime& us) override;
  void keyHandler(ASGE::SharedEventData data);
  void clickHandler(ASGE::SharedEventData data);
  void mouseHandler(ASGE::SharedEventData data);
  void scrollHandler(ASGE::SharedEventData data);
  void render() override;
  void update(const ASGE::GameTime& us) override;

  bool init();

 private:
  std::vector<std::unique_ptr<GameComponent>> game_components;
  std::vector<std::unique_ptr<GameObject>> game_objects;
  GCNetClient client;

  int key_callback_id    = -1; /**< Key Input Callback ID. */
  int click_callback_id  = -1; /**< Click Input Callback ID. */
  int mouse_callback_id  = -1; /**< Mouse Input Callback ID. */
  int scroll_callback_id = -1; /**< Scroll Input Callback ID. */

  std::string input_string;
};
