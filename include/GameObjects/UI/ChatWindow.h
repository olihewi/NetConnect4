//
// Created by hewis on 21/02/2021.
//

#ifndef ASGENETGAME_CHATWINDOW_H
#define ASGENETGAME_CHATWINDOW_H
#include "UITextBox.h"
#include <ASGENetLib/GCNetClient.hpp>
#include <GameObjects/GameObject.h>
class ChatWindow : public GameObject
{
 public:
  ChatWindow(ASGE::Renderer* renderer, ASGE::Point2D position, GCNetClient& _client);
  void render(ASGE::Renderer* renderer) override;
  void keyInput(const ASGE::KeyEvent* keyEvent) override;
  void clickInput(const ASGE::ClickEvent* clickEvent, ASGE::Renderer* renderer) override;
  void addMessage(ASGE::Renderer* renderer, std::string message);

 private:
  GCNetClient& client;
  SpriteComponent background;
  UITextBox text_box;
  std::vector<TextComponent> messages;
};

#endif // ASGENETGAME_CHATWINDOW_H
