//
// Created by huxy on 23/02/2020.
//

#pragma once

#include <ASGENetLib/GCNetClient.hpp>
#include <ASGENetLib/GComponent.hpp>
#include <Engine/OGLGame.h>
#include <GameObjects/Scenes/Scene.h>

#include "../../../cmake-build-debug/_deps/soloud-src/include/soloud.h"
#include "../../../cmake-build-debug/_deps/soloud-src/include/soloud_wav.h"

class ASGENetGame : public ASGE::OGLGame
{
 public:
  enum class SceneID
  {
    TITLE = 0,
    LOBBY = 1,
    GAME  = 2,
    //  EXIT_GAME  = 3
  };

  SceneID gameState = SceneID::TITLE;

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
  [[maybe_unused]] void netInput(NetUtil::CommandID command_id, const std::string& message);
  void render() override;
  void update(const ASGE::GameTime& us) override;

  void setScene(SceneID scene);
  bool init();
  GCNetClient& getClient();

 private:
  std::unique_ptr<Scene> current_scene;
  GCNetClient client;

  SoLoud::Soloud soloud;
  SoLoud::Wav sample;

  int key_callback_id    = -1; /**< Key Input Callback ID. */
  int click_callback_id  = -1; /**< Click Input Callback ID. */
  int mouse_callback_id  = -1; /**< Mouse Input Callback ID. */
  int scroll_callback_id = -1; /**< Scroll Input Callback ID. */
};
