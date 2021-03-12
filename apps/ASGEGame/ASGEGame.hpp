//
// Created by huxy on 23/02/2020.
//

#pragma once

#include <ASGENetLib/GCNetClient.hpp>
#include <ASGENetLib/GComponent.hpp>
#include <Engine/OGLGame.h>
#include <GameObjects/Scenes/Scene.h>
#include <soloud.h>
#include <soloud_wav.h>

class ASGENetGame : public ASGE::OGLGame
{
 public:
  explicit ASGENetGame(const ASGE::GameSettings& settings);
  ASGENetGame(const ASGENetGame&) = delete;
  ASGENetGame& operator=(const ASGENetGame&) = delete;
  ~ASGENetGame() override;

  bool init();

  void keyHandler(ASGE::SharedEventData data);
  void clickHandler(ASGE::SharedEventData data);
  void mouseHandler(ASGE::SharedEventData data);
  void scrollHandler(ASGE::SharedEventData data);

  void update(const ASGE::GameTime& us) override;
  void fixedUpdate(const ASGE::GameTime& us) override;

  void netInput(const char* message);

  void render() override;

  void setScene(Scene::SceneID scene);

 private:
  std::unique_ptr<Scene> current_scene;

  GCNetClient client;
  SoLoud::Soloud soloud;
  SoLoud::Wav eight_ball;
  SoLoud::Wav counter_drop;
  SoLoud::Wav counter_pop;
  SoLoud::Wav door_bell;
  SoLoud::Wav game_over;
  SoLoud::Wav door_closed;

  int key_callback_id    = -1; /**< Key Input Callback ID. */
  int click_callback_id  = -1; /**< Click Input Callback ID. */
  int mouse_callback_id  = -1; /**< Mouse Input Callback ID. */
  int scroll_callback_id = -1; /**< Scroll Input Callback ID. */
};
