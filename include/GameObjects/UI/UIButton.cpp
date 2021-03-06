//
// Created by hewis on 20/02/2021.
//

#include "UIButton.h"

UIButton::UIButton(
  ASGE::Renderer* renderer, ButtonColour colour, ASGE::Point2D position, float width, float height,
  const std::string& button_text, std::function<void()> _callback, int font_index) :
  callback(std::move(_callback))
{
  std::string file_path = "data/images/ui/button/";
  file_path += colour == BLUE     ? "blue/"
               : colour == GREEN  ? "green/"
               : colour == RED    ? "red/"
               : colour == YELLOW ? "yellow/"
                                  : "fancy/";
  for (size_t i = 0; i < background.size(); i++)
  {
    std::string this_file_path = file_path;
    this_file_path += i / 3 == 0 ? "u" : i / 3 == 1 ? "m" : "b";
    this_file_path += i % 3 == 0 ? "l" : i % 3 == 1 ? "m" : "r";
    this_file_path += ".png";
    background[i] =
      SpriteComponent(renderer, this_file_path, ASGE::Point2D(position.x, position.y));
  }
  for (size_t i = 1; i < 8; i += 3) /// Positioning middle column
  {
    background[i].getSprite()->xPos(
      background[i - 1].getSprite()->xPos() + background[i - 1].getSprite()->width());
    background[i].getSprite()->width(
      width - background[0].getSprite()->width() - background[2].getSprite()->width());
  }
  for (size_t i = 2; i < 9; i += 3) /// Positioning right column
  {
    background[i].getSprite()->xPos(
      background[i - 1].getSprite()->xPos() + background[i - 1].getSprite()->width());
  }
  for (size_t i = 3; i < 6; i++) /// Positioning middle row
  {
    background[i].getSprite()->yPos(
      background[i - 3].getSprite()->yPos() + background[i - 3].getSprite()->height());
    background[i].getSprite()->height(
      height - background[0].getSprite()->height() - background[6].getSprite()->height());
  }
  for (size_t i = 6; i < 9; i++) /// Positioning bottom row
  {
    background[i].getSprite()->yPos(
      background[i - 3].getSprite()->yPos() + background[i - 3].getSprite()->height());
  }
  text =
    TextComponent(renderer, button_text, ASGE::Point2D(0, 0), font_index, 1, ASGE::COLOURS::WHITE);
  text.getText().setPosition(ASGE::Point2D(
    background[4].getPosition().x + background[4].getSprite()->width() / 2 -
      text.getText().getWidth() / 2,
    background[4].getPosition().y + background[4].getSprite()->height() / 2 + 8));
}
bool UIButton::clickInput(const ASGE::ClickEvent* clickEvent, ASGE::Renderer* /*renderer*/)
{
  if (clickEvent->action == ASGE::KEYS::KEY_PRESSED)
  {
    if (background[4].isInside(ASGE::Point2D(
          static_cast<float>(clickEvent->xpos), static_cast<float>(clickEvent->ypos))))
    {
      callback();
      return true;
    }
  }
  return false;
}

void UIButton::render(ASGE::Renderer* renderer)
{
  for (auto& bg : background)
  {
    bg.render(renderer);
  }
  text.render(renderer);
}
