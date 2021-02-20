//
// Created by hewis on 20/02/2021.
//

#ifndef ASGENETGAME_UIBUTTON_H
#define ASGENETGAME_UIBUTTON_H

#include <GameComponents/SpriteComponent.hpp>
#include <GameObjects/GameObject.h>
#include <functional>
class UIButton : public GameObject
{
 public:
  UIButton(ASGE::Renderer* renderer, std::function<void()> event);
  void clickInput(const ASGE::ClickEvent* clickEvent, ASGE::Point2D position) override;
  void onClick();
  void render(ASGE::Renderer* renderer) override;
  SpriteComponent background;
  std::function<void()> callback;
};

#endif // ASGENETGAME_UIBUTTON_H
