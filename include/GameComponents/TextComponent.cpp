//
// Created by hewis on 12/02/2021.
//

#include "TextComponent.hpp"
TextComponent::TextComponent(
  ASGE::Renderer* renderer, std::string text, ASGE::Point2D position, int font_index, float scale,
  ASGE::Colour colour) :
  GameComponent(GameComponent::ID::TEXT)
{
  thisText.setString(text);
  thisText.setFont(renderer->getFont(font_index));
  thisText.setColour(colour);
  thisText.setScale(scale);
  thisText.setPosition(position);
  thisText.setZOrder(1);
}
ASGE::Text& TextComponent::getText()
{
  return thisText;
}
void TextComponent::render(ASGE::Renderer* renderer)
{
  if (visible)
  {
    renderer->renderText(thisText);
  }
}
TextComponent::TextComponent() : GameComponent(GameComponent::ID::TEXT) {}
