//
// Created by Andrei on 03/03/2021.
//

#include "WinScene.h"
#include <Engine/FileIO.h>
#include <iostream>
#include <utility>

WinScene::WinScene(
  ASGE::Renderer* renderer, std::function<void(Scene::SceneID)> _scene_callback,
  GCNetClient& _client) :
  scene_callback(std::move(_scene_callback)),
  client(_client), background(renderer, "/data/images/background3.png", ASGE::Point2D(0, 0))
{
  auto window_width  = static_cast<float>(ASGE::SETTINGS.window_width);
  auto window_height = static_cast<float>(ASGE::SETTINGS.window_height);
  auto& bg_sprite    = background.getSprite();
  bg_sprite->width(window_width);
  bg_sprite->height(window_height);
  bg_sprite->setGlobalZOrder(-1);
  replay_button = UIButton(
    renderer,
    UIButton::GREEN,
    ASGE::Point2D(window_width / 2 - 150, window_height / 2 + 74),
    300,
    50,
    "REPLAY",
    [this]() { onReplayButton(); });

  menu_button = UIButton(
    renderer,
    UIButton::RED,
    ASGE::Point2D(window_width / 2 - 150, window_height / 2 + 144),
    300,
    50,
    "RETURN TO MENU",
    [this]() { onMenuButton(); });
  exit_button = UIButton(
    renderer,
    UIButton::RED,
    ASGE::Point2D(window_width / 2 - 150, window_height / 2 + 44),
    300,
    50,
    "EXIT GAME",
    [this]() { onExitButton(); });
}

bool WinScene::clickInput(const ASGE::ClickEvent* clickEvent, ASGE::Renderer* renderer)
{
  replay_button.clickInput(clickEvent, renderer);
  menu_button.clickInput(clickEvent, renderer);
  exit_button.clickInput(clickEvent, renderer);
  return true;
}

void WinScene::render(ASGE::Renderer* renderer)
{
  background.render(renderer);
  replay_button.render(renderer);
  menu_button.render(renderer);
  exit_button.render(renderer);
}

void WinScene::onMenuButton()
{
  client.disconnect();
  scene_callback(SceneID::TITLE);
}

void WinScene::onReplayButton()
{
  scene_callback(SceneID::GAME);
}

void WinScene::onExitButton()
{
  client.disconnect();
  scene_callback(SceneID::LOBBY);
}
