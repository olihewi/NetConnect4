//
// Created by hewis on 21/02/2021.
//

#include "ChatWindow.h"

#include "Utilities/FontManager.h"
#include <utility>
ChatWindow::ChatWindow(ASGE::Renderer* renderer, ASGE::Point2D position, GCNetClient& _client) :
  client(_client), background(renderer, "data/images/ui/chatbox.png", position),
  text_box(
    renderer, UITextBox::BLUE,
    ASGE::Point2D(
      position.x + 64, position.y + static_cast<float>(ASGE::SETTINGS.window_height) - 62),
    600, 50, "", 48, FONTS::CHAT_MESSAGE)
{
  background.getSprite()->setGlobalZOrder(-1);
  addMessage(renderer, "This is the start of the chat.");
}
void ChatWindow::render(ASGE::Renderer* renderer)
{
  background.render(renderer);
  text_box.render(renderer);
  for (size_t i = 0; i < messages.size(); i++)
  {
    messages[i].render(renderer);
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
        client.send(NetUtil::CHAT_MESSAGE, text_box.getString());
        text_box.setString("");
      }
    }
  }
}
bool ChatWindow::clickInput(const ASGE::ClickEvent* clickEvent, ASGE::Renderer* renderer)
{
  text_box.clickInput(clickEvent, renderer);
  return true;
}
void ChatWindow::addMessage(ASGE::Renderer* renderer, std::string message)
{
  TextComponent this_message(
    renderer,
    std::move(message),
    ASGE::Point2D(background.getPosition().x + 64, background.getPosition().y + 920),
    FONTS::CHAT_MESSAGE,
    1,
    ASGE::COLOURS::BLACK);
  for (auto& each_message : messages)
  {
    each_message.getText().setPosition(ASGE::Point2D(
      each_message.getText().getPosition().x, each_message.getText().getPosition().y - 50));
  }
  messages.emplace_back(std::move(this_message));
}
