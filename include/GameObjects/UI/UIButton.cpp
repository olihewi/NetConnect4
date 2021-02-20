//
// Created by hewis on 20/02/2021.
//

#include "UIButton.h"
#include <GameComponents/SpriteComponent.hpp>
#include <GameComponents/TextComponent.hpp>
#include <iostream>

void UIButton::clickInput(const ASGE::ClickEvent* clickEvent)
{
  if (clickEvent->action == ASGE::KEYS::KEY_PRESSED)
  {
    if (background.isInside(ASGE::Point2D(
          static_cast<float>(clickEvent->xpos), static_cast<float>(clickEvent->ypos))))
    {
      onClick();
    }
  }
}
void UIButton::onClick()
{
  std::cout << "Test" << std::endl;
}
UIButton::UIButton(ASGE::Renderer* renderer, std::function<void()> event, ASGE::Point2D position)
{
  background = SpriteComponent(renderer, "data/background.png", position);
  callback   = std::move(event);
}
void UIButton::render(ASGE::Renderer* renderer)
{
  background.render(renderer);
}
