//
// Created by hewis on 20/02/2021.
//

#ifndef ASGENETGAME_UIBUTTON_H
#define ASGENETGAME_UIBUTTON_H

#include <GameComponents/SpriteComponent.hpp>
#include <GameComponents/TextComponent.hpp>
#include <GameObjects/GameObject.h>
#include <functional>
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
    float height, const std::string& button_text, std::function<void()> _callback);
  bool clickInput(const ASGE::ClickEvent* clickEvent, ASGE::Renderer* /*renderer*/) override;
  void render(ASGE::Renderer* renderer) override;

 private:
  std::array<SpriteComponent, 9> background;
  TextComponent text;
  std::function<void()> callback;
};

#endif // ASGENETGAME_UIBUTTON_H
