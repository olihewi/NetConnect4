//
// Created by hewis on 21/02/2021.
//

#ifndef ASGENETGAME_TITLESCREEN_H
#define ASGENETGAME_TITLESCREEN_H

#include <ASGENetLib/GCNetClient.hpp>
#include <GameComponents/SpriteComponent.hpp>
#include <GameObjects/Scenes/Scene.h>
#include <GameObjects/UI/UIButton.h>
#include <GameObjects/UI/UITextBox.h>
#include <functional>

class TitleScreen : public Scene
{
 public:
  TitleScreen(
    ASGE::Renderer* renderer, std::function<void(Scene::SceneID)> _scene_callback,
    GCNetClient& _client, std::function<void()> _signal_exit);
  void keyInput(const ASGE::KeyEvent* keyEvent) override;
  bool clickInput(const ASGE::ClickEvent* clickEvent, ASGE::Renderer* renderer) override;
  void render(ASGE::Renderer* renderer) override;

  void onConnectButton();

 private:
  std::function<void(Scene::SceneID)> scene_callback;
  GCNetClient& client;
  SpriteComponent background;
  UITextBox ip_address;
  UITextBox port;
  UITextBox username;
  UIButton connect;
  UIButton exit_game;
};

#endif // ASGENETGAME_TITLESCREEN_H
