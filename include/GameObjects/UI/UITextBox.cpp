//
// Created by hewis on 20/02/2021.
//

#include "UITextBox.h"
#include <iostream>
#include <utility>
UITextBox::UITextBox(
  ASGE::Renderer* renderer, TextBoxColour colour, ASGE::Point2D position, float width, float height,
  std::string default_text, size_t max_length, int font_index) :
  internal_string(std::move(default_text)),
  max_string_length(max_length)
{
  std::string file_path = "data/images/ui/textbox/";
  file_path += colour == BLUE     ? "blue/"
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
    background[i].getSprite()->setGlobalZOrder(1);
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
  text = TextComponent(
    renderer,
    internal_string,
    ASGE::Point2D(background[7].getPosition().x + 8, background[7].getPosition().y - 16),
    font_index,
    1,
    colour == FANCY ? ASGE::COLOURS::WHITE : ASGE::COLOURS::BLACK);
  text.getText().setZOrder(2);
}
bool UITextBox::clickInput(const ASGE::ClickEvent* clickEvent, ASGE::Renderer* /*renderer*/)
{
  if (clickEvent->action == ASGE::KEYS::KEY_PRESSED)
  {
    isSelected = background[4].isInside(
      ASGE::Point2D(static_cast<float>(clickEvent->xpos), static_cast<float>(clickEvent->ypos)));
    text.getText().setString(internal_string + (isSelected ? '_' : ' '));
    return isSelected;
  }
  return false;
}
void UITextBox::keyInput(const ASGE::KeyEvent* keyEvent)
{
  int key = keyEvent->key;
  if (key == ASGE::KEYS::KEY_TAB)
  {
    isSelected = false;
    text.getText().setString(internal_string + ' ');
  }
  else if (key == 340 || key == 344) /// SHIFT KEY
  {
    isShiftHeld = keyEvent->action != ASGE::KEYS::KEY_RELEASED;
  }
  else if (isSelected)
  {
    if (
      keyEvent->action == ASGE::KEYS::KEY_PRESSED && key >= ASGE::KEYS::KEY_SPACE &&
      key <= ASGE::KEYS::KEY_GRAVE_ACCENT && internal_string.length() < max_string_length)
    {
      int shift_offset = 0;
      if (isShiftHeld)
      {
        switch (key)
        {
          case ASGE::KEYS::KEY_1:
          case ASGE::KEYS::KEY_2:
          case ASGE::KEYS::KEY_4:
          case ASGE::KEYS::KEY_5:
          case ASGE::KEYS::KEY_7:
            shift_offset = -16;
            break;
          case ASGE::KEYS::KEY_9:
            shift_offset = -17;
            break;
          case ASGE::KEYS::KEY_0:
            shift_offset = -7;
            break;
          case ASGE::KEYS::KEY_6:
            shift_offset = 40;
            break;
          case ASGE::KEYS::KEY_8:
            shift_offset = -14;
            break;
          case ASGE::KEYS::KEY_MINUS:
            shift_offset = 50;
            break;
          case ASGE::KEYS::KEY_EQUAL:
            shift_offset = -18;
            break;
          case ASGE::KEYS::KEY_SEMICOLON:
            shift_offset = -1;
            break;
          case ASGE::KEYS::KEY_APOSTROPHE:
            shift_offset = 25;
            break;
          case ASGE::KEYS::KEY_COMMA:
          case ASGE::KEYS::KEY_PERIOD:
          case ASGE::KEYS::KEY_SLASH:
            shift_offset = 16;
            break;
          case ASGE::KEYS::KEY_SPACE:
            shift_offset = 0;
            break;
          default:
            shift_offset = 32;
            break;
        }
      }
      if (keyEvent->key >= ASGE::KEYS::KEY_A && keyEvent->key <= ASGE::KEYS::KEY_Z)
      {
        key += 32;
        shift_offset = -shift_offset;
      }
      internal_string += static_cast<char>(key + shift_offset);
      text.getText().setString(
        internal_string + (internal_string.length() == max_string_length ? ' ' : '_'));
    }
    if (
      keyEvent->key == ASGE::KEYS::KEY_BACKSPACE && keyEvent->action != ASGE::KEYS::KEY_RELEASED &&
      internal_string.length() > 0)
    {
      internal_string.pop_back();
      text.getText().setString(internal_string + '_');
    }
  }
}
void UITextBox::render(ASGE::Renderer* renderer)
{
  text.render(renderer);
  for (auto& bg : background)
  {
    bg.render(renderer);
  }
}
std::string UITextBox::getString()
{
  return internal_string;
}
bool UITextBox::getSelected() const
{
  return isSelected;
}
void UITextBox::setString(std::string string)
{
  internal_string = std::move(string);
  text.getText().setString(internal_string + (isSelected ? '_' : ' '));
}
