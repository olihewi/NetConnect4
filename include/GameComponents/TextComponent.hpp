//
// Created by hewis on 12/02/2021.
//

#ifndef ASGENETGAME_TEXTCOMPONENT_H
#define ASGENETGAME_TEXTCOMPONENT_H
#include "ASGENetLib/GComponent.hpp"
#include <Engine/Renderer.h>
class TextComponent : public GameComponent
{
 public:
  TextComponent();
  TextComponent(
    ASGE::Renderer* renderer, std::string text, ASGE::Point2D position, int font_index, float scale,
    ASGE::Colour colour);
  ASGE::Text& getText();
  void update(double /* dt */) override {}
  void render(ASGE::Renderer* renderer) override;

 private:
  bool visible = true;
  ASGE::Text thisText{};
};

#endif // ASGENETGAME_TEXTCOMPONENT_H
