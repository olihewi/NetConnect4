//
// Created by hewis on 21/02/2021.
//

#include "TitleScreen.h"

#include <Engine/FileIO.h>
#include <utility>

TitleScreen::TitleScreen(
  ASGE::Renderer* renderer, std::function<void(Scene::SceneID)> _scene_callback,
  GCNetClient& _client) :
  scene_callback(std::move(_scene_callback)),
  client(_client), background(renderer, "data/images/background.png", ASGE::Point2D(0, 0))
{
  auto window_width  = static_cast<float>(ASGE::SETTINGS.window_width);
  auto window_height = static_cast<float>(ASGE::SETTINGS.window_height);
  auto& bg_sprite    = background.getSprite();
  bg_sprite->width(window_width);
  bg_sprite->height(window_height);
  bg_sprite->setGlobalZOrder(-1);

  ip_address = UITextBox(
    renderer,
    UITextBox::RED,
    ASGE::Point2D(window_width / 2 - 226, window_height / 2 - 62),
    300,
    50,
    "127.0.0.1",
    15);
  port = UITextBox(
    renderer,
    UITextBox::YELLOW,
    ASGE::Point2D(window_width / 2 + 86, window_height / 2 - 62),
    128,
    50,
    "31276",
    5);
  username = UITextBox(
    renderer,
    UITextBox::BLUE,
    ASGE::Point2D(window_width / 2 - 226, window_height / 2 + 4),
    440,
    50,
    "Username",
    24);
  connect = UIButton(
    renderer,
    UIButton::GREEN,
    ASGE::Point2D(window_width / 2 - 150, window_height / 2 + 74),
    300,
    50,
    "CONNECT");
  exit_game = UIButton(
    renderer,
    UIButton::YELLOW,
    ASGE::Point2D(window_width / 2 - 150, window_height / 2 + 144t),
    300,
    50,
    "QUIT GAME");
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
  if (connect.getClick())
  {
    client.connect(
      ip_address.getString(),
      static_cast<uint16_t>(std::stoi(port.getString())),
      username.getString());
    scene_callback(Scene::SceneID::LOBBY);
  }
  /*  if(exit_game.getClick())
    {

    } */
}
void TitleScreen::render(ASGE::Renderer* renderer)
{
  background.render(renderer);
  ip_address.render(renderer);
  port.render(renderer);
  username.render(renderer);
  connect.render(renderer);
  exit_game.render(renderer);
}
