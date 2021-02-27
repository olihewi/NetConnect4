//
// Created by hewis on 20/02/2021.
//

#include "UIButton.h"
#include "Utilities/FontManager.h"

UIButton::UIButton(
  ASGE::Renderer* renderer, ButtonColour colour, ASGE::Point2D position, float width, float height,
  const std::string& button_text)
{
  std::string file_path = "data/images/ui/button/";
  file_path += colour == BLUE    ? "blue/"
               : colour == GREEN ? "green/"
               : colour == RED   ? "red/"
                                 : "yellow/";
  for (size_t i = 0; i < background.size(); i++)
  {
    std::string this_file_path = file_path;
    this_file_path += i / 3 == 0 ? "u" : i / 3 == 1 ? "m" : "b";
    this_file_path += i % 3 == 0 ? "l" : i % 3 == 1 ? "m" : "r";
    this_file_path += ".png";
    int y_index   = static_cast<int>(i) / 3;
    float x_pos   = static_cast<float>(i % 3) * 6 + (i % 3 == 2 ? width - 6 : 0);
    float y_pos   = y_index == 2 ? height + 6 : y_index == 1 ? 6 : 0;
    background[i] = SpriteComponent(
      renderer, this_file_path, ASGE::Point2D(position.x + x_pos, position.y + y_pos));
    if (i % 3 == 1)
    {
      background[i].getSprite()->width(width);
    }
    if (i / 3 == 1)
    {
      background[i].getSprite()->height(height);
    }
  }
  text = TextComponent(
    renderer,
    button_text,
    ASGE::Point2D(background[7].getPosition().x + 8, background[7].getPosition().y - 16),
    FONTS::HANDWRITING,
    1,
    ASGE::COLOURS::WHITE);
}
void UIButton::clickInput(const ASGE::ClickEvent* clickEvent)
{
  if (clickEvent->action == ASGE::KEYS::KEY_PRESSED)
  {
    if (background[4].isInside(ASGE::Point2D(
          static_cast<float>(clickEvent->xpos), static_cast<float>(clickEvent->ypos))))
    {
      clicked = true;
    }
  }
}

void UIButton::render(ASGE::Renderer* renderer)
{
  for (auto& bg : background)
  {
    bg.render(renderer);
  }
  text.render(renderer);
}
bool UIButton::getClick()
{
  bool return_val = clicked;
  clicked         = false;
  return return_val;
}
