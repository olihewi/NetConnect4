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
  client(_client), background(renderer, "data/images/background4.png", ASGE::Point2D(0, 0))
{
  auto window_width  = static_cast<float>(ASGE::SETTINGS.window_width);
  auto window_height = static_cast<float>(ASGE::SETTINGS.window_height);
  auto& bg_sprite    = background.getSprite();
  bg_sprite->width(window_width);
  bg_sprite->height(window_height);
  bg_sprite->setGlobalZOrder(-1);
  replay_button = UIButton(
    renderer,
    UIButton::FANCY,
    ASGE::Point2D(window_width / 2 - 150, window_height / 2 - 135),
    300,
    70,
    "REPLAY",
    [this]() { onReplayButton(); });

  lobby_button = UIButton(
    renderer,
    UIButton::FANCY,
    ASGE::Point2D(window_width / 2 - 150, window_height / 2 + 14),
    300,
    70,
    "RETURN TO LOBBY",
    [this]() { onLobbyButton(); });
  title_button = UIButton(
    renderer,
    UIButton::FANCY,
    ASGE::Point2D(window_width / 2 - 150, window_height / 2 + 160),
    300,
    70,
    "TITLE SCREEN",
    [this]() { onTitleButton(); });
}

bool WinScene::clickInput(const ASGE::ClickEvent* clickEvent, ASGE::Renderer* renderer)
{
  if (replay_button.clickInput(clickEvent, renderer))
  {
    return true;
  }
  if (title_button.clickInput(clickEvent, renderer))
  {
    return false;
  }
  if (lobby_button.clickInput(clickEvent, renderer))
  {
    return false;
  }

  return true;
}

void WinScene::render(ASGE::Renderer* renderer)
{
  background.render(renderer);
  replay_button.render(renderer);
  lobby_button.render(renderer);
  title_button.render(renderer);
}

void WinScene::onLobbyButton()
{
  scene_callback(SceneID::LOBBY);
}

void WinScene::onReplayButton()
{
  scene_callback(SceneID::GAME);
}

void WinScene::onTitleButton()
{
  client.disconnect();
  scene_callback(SceneID::TITLE);
}
