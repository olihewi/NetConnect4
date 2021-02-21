//
// Created by hewis on 21/02/2021.
//

#include "TitleScreen.h"

#include <utility>

TitleScreen::TitleScreen(ASGE::Renderer* renderer, GCNetClient& _client) : client(_client)
{
  auto window_width  = static_cast<float>(ASGE::SETTINGS.window_width);
  auto window_height = static_cast<float>(ASGE::SETTINGS.window_height);
  background         = SpriteComponent(renderer, "data/images/background.png", ASGE::Point2D(0, 0));
  background.getSprite()->width(window_width);
  background.getSprite()->height(window_height);
  ip_address = UITextBox(
    renderer,
    UITextBox::RED,
    ASGE::Point2D(window_width / 2 - 226, window_height / 2 - 62),
    300,
    50,
    "127.0.0.1");
  port = UITextBox(
    renderer,
    UITextBox::YELLOW,
    ASGE::Point2D(window_width / 2 + 86, window_height / 2 - 62),
    128,
    50,
    "31276");
  username = UITextBox(
    renderer,
    UITextBox::BLUE,
    ASGE::Point2D(window_width / 2 - 226, window_height / 2),
    440,
    50,
    "Username");
  connect = UIButton(
    renderer,
    UIButton::GREEN,
    ASGE::Point2D(window_width / 2 - 150, window_height / 2 + 74),
    300,
    50,
    "CONNECT");
}
void TitleScreen::keyInput(const ASGE::KeyEvent* keyEvent)
{
  ip_address.keyInput(keyEvent);
  port.keyInput(keyEvent);
  username.keyInput(keyEvent);
}
void TitleScreen::clickInput(const ASGE::ClickEvent* clickEvent)
{
  ip_address.clickInput(clickEvent);
  port.clickInput(clickEvent);
  username.clickInput(clickEvent);
  connect.clickInput(clickEvent);
  if (connect.clicked)
  {
    client.connect(
      ip_address.getString(),
      static_cast<uint16_t>(std::stoi(port.getString())),
      username.getString());
    connect.clicked = false;
  }
}
void TitleScreen::render(ASGE::Renderer* renderer)
{
  background.render(renderer);
  ip_address.render(renderer);
  port.render(renderer);
  username.render(renderer);
  connect.render(renderer);
}
