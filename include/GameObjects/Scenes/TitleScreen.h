//
// Created by hewis on 21/02/2021.
//

#ifndef ASGENETGAME_TITLESCREEN_H
#define ASGENETGAME_TITLESCREEN_H

#include "../../../apps/ASGEGame/ASGEGame.hpp"
#include <ASGENetLib/GCNetClient.hpp>
#include <GameComponents/SpriteComponent.hpp>
#include <GameObjects/Scenes/Scene.h>
#include <GameObjects/UI/UIButton.h>
#include <GameObjects/UI/UITextBox.h>
class TitleScreen : public Scene
{
 public:
  TitleScreen(ASGE::Renderer* renderer, ASGENetGame& main);
  void keyInput(const ASGE::KeyEvent* keyEvent) override;
  void clickInput(const ASGE::ClickEvent* clickEvent) override;
  void render(ASGE::Renderer* renderer) override;

 private:
  ASGENetGame& game;
  SpriteComponent background;
  UITextBox ip_address;
  UITextBox port;
  UITextBox username;
  UIButton connect;
};

#endif // ASGENETGAME_TITLESCREEN_H
