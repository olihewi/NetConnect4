//
// Created by hewis on 21/02/2021.
//

#ifndef ASGENETGAME_LOBBYSCENE_H
#define ASGENETGAME_LOBBYSCENE_H

#include "../../../apps/ASGEGame/ASGEGame.hpp"

#include "../../../cmake-build-debug/_deps/soloud-src/include/soloud.h"
#include "../../../cmake-build-debug/_deps/soloud-src/include/soloud_wav.h"
#include <ASGENetLib/GCNetClient.hpp>
#include <GameObjects/Scenes/Scene.h>
#include <GameObjects/UI/ChatWindow.h>
#include <GameObjects/UI/UIButton.h>
class LobbyScene : public Scene
{
 public:
  LobbyScene(ASGE::Renderer* renderer, ASGENetGame& main);
  void keyInput(const ASGE::KeyEvent* keyEvent) override;
  void clickInput(const ASGE::ClickEvent* clickEvent) override;
  void render(ASGE::Renderer*) override;
  void netInput(NetUtil::CommandID command_id, const std::string& message) override;

 private:
  ASGENetGame& game;
  ChatWindow chat_window;
  UIButton ready_button;
  SoLoud::Soloud soloud;
  SoLoud::Wav sample;
};

#endif // ASGENETGAME_LOBBYSCENE_H
