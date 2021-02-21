//
// Created by hewis on 21/02/2021.
//

#include "ChatWindow.h"
#include "Utilities/FontManager.h"
ChatWindow::ChatWindow(ASGE::Renderer* renderer, GCNetClient& _client, ASGE::Point2D position) :
  client(_client), background(renderer, "data/images/ui/chat_background.png", position)
{
  auto window_height = static_cast<float>(ASGE::SETTINGS.window_height);
  text_box           = UITextBox(
    renderer,
    UITextBox::BLUE,
    ASGE::Point2D(position.x + 64, position.y + window_height - 62),
    600,
    50,
    "",
    48,
    FONTS::CHAT_MESSAGE);
  auto& bg_sprite = background.getSprite();
  bg_sprite->setGlobalZOrder(-1);
  addMessage(renderer, "Olihewi > This is a test message\nand its contents are top-secret!");
}
void ChatWindow::render(ASGE::Renderer* renderer)
{
  background.render(renderer);
  text_box.render(renderer);
  for (auto& message : messages)
  {
    message.render(renderer);
  }
}
void ChatWindow::keyInput(const ASGE::KeyEvent* keyEvent)
{
  text_box.keyInput(keyEvent);
  if (text_box.getSelected())
  {
    if (keyEvent->action == ASGE::KEYS::KEY_PRESSED && keyEvent->key == ASGE::KEYS::KEY_ENTER)
    {
      auto message = text_box.getString();
      if (message.length() > 0)
      {
        client.send(NetUtil::CHAT_MESSAGE, message);
        text_box.setString("");
      }
    }
  }
}
void ChatWindow::clickInput(const ASGE::ClickEvent* clickEvent)
{
  text_box.clickInput(clickEvent);
}
void ChatWindow::addMessage(ASGE::Renderer* renderer, std::string message)
{
  messages.emplace_back(TextComponent(
    renderer,
    message,
    ASGE::Point2D(background.getPosition().x + 64, background.getPosition().y + 920),
    FONTS::CHAT_MESSAGE,
    1,
    ASGE::COLOURS::BLACK));
}
