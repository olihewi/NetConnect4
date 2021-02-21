//
// Created by hewis on 21/02/2021.
//

#ifndef ASGENETGAME_TITLESCREEN_H
#define ASGENETGAME_TITLESCREEN_H

#include <ASGENetLib/GCNetClient.hpp>
#include <GameComponents/SpriteComponent.hpp>
#include <GameObjects/GameObject.h>
#include <GameObjects/UI/UIButton.h>
#include <GameObjects/UI/UITextBox.h>
class TitleScreen : public GameObject
{
 public:
  TitleScreen(ASGE::Renderer* renderer, GCNetClient& _client);
  void keyInput(const ASGE::KeyEvent* keyEvent) override;
  void clickInput(const ASGE::ClickEvent* clickEvent) override;
  void render(ASGE::Renderer* renderer) override;

 private:
  GCNetClient& client;
  SpriteComponent background;
  UITextBox ip_address;
  UITextBox port;
  UITextBox username;
  UIButton connect;
};

#endif // ASGENETGAME_TITLESCREEN_H
