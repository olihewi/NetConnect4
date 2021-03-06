//
// Created by hewis on 21/02/2021.
//

#include "TitleScreen.h"

#include <Engine/FileIO.h>
#include <iostream>
#include <utility>

TitleScreen::TitleScreen(
  ASGE::Renderer* renderer, std::function<void(Scene::SceneID)> _scene_callback,
  GCNetClient& _client, std::function<void()> _signal_exit) :
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
    UITextBox::FANCY,
    ASGE::Point2D(window_width / 2 - 226, window_height / 2 - 150),
    300,
    100,
    "127.0.0.1",
    15,
    FONTS::FANCY);
  port = UITextBox(
    renderer,
    UITextBox::FANCY,
    ASGE::Point2D(window_width / 2 + 86, window_height / 2 - 150),
    128,
    100,
    "31276",
    5,
    FONTS::FANCY);
  username = UITextBox(
    renderer,
    UITextBox::FANCY,
    ASGE::Point2D(window_width / 2 - 226, window_height / 2 + -35),
    440,
    100,
    "Username",
    24,
    FONTS::FANCY);
  connect = UIButton(
    renderer,
    UIButton::FANCY,
    ASGE::Point2D(window_width / 2 - 150, window_height / 2 + 75),
    300,
    75,
    "CONNECT",
    [this]() { onConnectButton(); },
    FONTS::FANCY);
  exit_game = UIButton(
    renderer,
    UIButton::FANCY,
    ASGE::Point2D(window_width / 2 - 150, window_height / 2 + 175),
    300,
    75,
    "QUIT GAME",
    std::move(_signal_exit),
    FONTS::FANCY);
  falling_counters.emplace_back(
    SpriteComponent(renderer, "data/images/chips/black.png", ASGE::Point2D(0, 0)));
  falling_counters.emplace_back(
    SpriteComponent(renderer, "data/images/chips/blue.png", ASGE::Point2D(200, 100)));
  falling_counters.emplace_back(
    SpriteComponent(renderer, "data/images/chips/green.png", ASGE::Point2D(400, 600)));
  falling_counters.emplace_back(
    SpriteComponent(renderer, "data/images/chips/orange.png", ASGE::Point2D(600, 300)));
  falling_counters.emplace_back(
    SpriteComponent(renderer, "data/images/chips/pink.png", ASGE::Point2D(800, 1000)));
  falling_counters.emplace_back(
    SpriteComponent(renderer, "data/images/chips/purple.png", ASGE::Point2D(1000, 800)));
  falling_counters.emplace_back(
    SpriteComponent(renderer, "data/images/chips/red.png", ASGE::Point2D(1200, 200)));
  falling_counters.emplace_back(
    SpriteComponent(renderer, "data/images/chips/white.png", ASGE::Point2D(1400, 500)));
  falling_counters.emplace_back(
    SpriteComponent(renderer, "data/images/chips/yellow.png", ASGE::Point2D(1600, 900)));
  for (auto& falling_counter : falling_counters)
  {
    falling_counter.getSprite()->setGlobalZOrder(-1);
  }
}
void TitleScreen::keyInput(const ASGE::KeyEvent* keyEvent)
{
  ip_address.keyInput(keyEvent);
  port.keyInput(keyEvent);
  username.keyInput(keyEvent);
}
bool TitleScreen::clickInput(const ASGE::ClickEvent* clickEvent, ASGE::Renderer* renderer)
{
  ip_address.clickInput(clickEvent, renderer);
  port.clickInput(clickEvent, renderer);
  username.clickInput(clickEvent, renderer);
  connect.clickInput(clickEvent, renderer);
  return true;
}
void TitleScreen::render(ASGE::Renderer* renderer)
{
  background.render(renderer);
  ip_address.render(renderer);
  port.render(renderer);
  username.render(renderer);
  connect.render(renderer);
  exit_game.render(renderer);
  for (auto& falling_counter : falling_counters)
  {
    falling_counter.render(renderer);
  }
}
void TitleScreen::onConnectButton()
{
  client.connect(
    ip_address.getString(),
    static_cast<uint16_t>(std::stoi(port.getString())),
    username.getString());
  scene_callback(Scene::SceneID::LOBBY);
}
void TitleScreen::update(float dt)
{
  for (auto& falling_counter : falling_counters)
  {
    falling_counter.translate(ASGE::Point2D(0, 1000 * dt));
    auto window_height = static_cast<float>(ASGE::SETTINGS.window_height);
    if (falling_counter.getPosition().y > window_height)
    {
      falling_counter.translate(ASGE::Point2D(0, -window_height));
    }
  }
}
