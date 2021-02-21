//
// Created by hewis on 20/02/2021.
//

#ifndef ASGENETGAME_UITEXTBOX_H
#define ASGENETGAME_UITEXTBOX_H

#include "GameObjects/GameObject.h"
#include <GameComponents/SpriteComponent.hpp>
#include <GameComponents/TextComponent.hpp>
class UITextBox : public GameObject
{
 public:
  enum TextBoxColour
  {
    BLUE,
    RED,
    YELLOW
  };
  UITextBox() = default;
  UITextBox(
    ASGE::Renderer* renderer, TextBoxColour colour, ASGE::Point2D position, float width,
    float height, std::string default_text = "", size_t max_length = 16);
  void keyInput(const ASGE::KeyEvent* keyEvent) override;
  void clickInput(const ASGE::ClickEvent* clickEvent) override;
  void render(ASGE::Renderer* renderer) override;
  std::string getString();

 private:
  bool isSelected  = false;
  bool isShiftHeld = false;
  TextComponent text;
  std::string internal_string;
  size_t max_string_length;
  std::array<SpriteComponent, 9> background;
};

#endif // ASGENETGAME_UITEXTBOX_H
