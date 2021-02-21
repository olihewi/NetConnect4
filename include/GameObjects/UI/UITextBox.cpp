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
  file_path += colour == BLUE ? "blue/" : colour == RED ? "red/" : "yellow/";
  for (size_t i = 0; i < background.size(); i++)
  {
    std::string this_file_path = file_path;
    this_file_path += i / 3 == 0 ? "u" : i / 3 == 1 ? "m" : "b";
    this_file_path += i % 3 == 0 ? "l" : i % 3 == 1 ? "m" : "r";
    this_file_path += ".png";
    int y_index   = static_cast<int>(i) / 3;
    float x_pos   = static_cast<float>(i % 3) * 6 + (i % 3 == 2 ? width - 6 : 0);
    float y_pos   = static_cast<float>(y_index) * 6 + (i / 3 == 2 ? height - 6 : 0);
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
    background[i].getSprite()->setGlobalZOrder(1);
  }
  text = TextComponent(
    renderer,
    internal_string,
    ASGE::Point2D(background[7].getPosition().x + 8, background[7].getPosition().y - 16),
    font_index,
    1,
    ASGE::COLOURS::BLACK);
  text.getText().setZOrder(2);
}
void UITextBox::clickInput(const ASGE::ClickEvent* clickEvent)
{
  if (clickEvent->action == ASGE::KEYS::KEY_PRESSED)
  {
    isSelected = background[4].isInside(
      ASGE::Point2D(static_cast<float>(clickEvent->xpos), static_cast<float>(clickEvent->ypos)));
    text.getText().setString(internal_string + (isSelected ? '_' : ' '));
  }
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
      text.getText().setString(internal_string + '_');
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
