//
// Created by hewis on 20/02/2021.
//

#ifndef ASGENETGAME_UIBUTTON_H
#define ASGENETGAME_UIBUTTON_H

#include <GameComponents/SpriteComponent.hpp>
#include <GameComponents/TextComponent.hpp>
#include <GameObjects/GameObject.h>
class UIButton : public GameObject
{
 public:
  enum ButtonColour
  {
    BLUE,
    GREEN,
    RED,
    YELLOW
  };
  UIButton() = default;
  UIButton(
    ASGE::Renderer* renderer, ButtonColour colour, ASGE::Point2D position, float width,
    float height, const std::string& button_text);
  void clickInput(const ASGE::ClickEvent* clickEvent) override;
  void render(ASGE::Renderer* renderer) override;
  bool getClick();

 private:
  std::array<SpriteComponent, 9> background;
  TextComponent text;
  bool clicked = false;
};

#endif // ASGENETGAME_UIBUTTON_H
