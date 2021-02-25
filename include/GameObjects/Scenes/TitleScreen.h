//
// Created by hewis on 21/02/2021.
//

#ifndef ASGENETGAME_TITLESCREEN_H
#define ASGENETGAME_TITLESCREEN_H

#include "../../../cmake-build-debug/_deps/soloud-src/include/soloud.h"
#include "../../../cmake-build-debug/_deps/soloud-src/include/soloud_wav.h"
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
    GCNetClient& _client);
  void keyInput(const ASGE::KeyEvent* keyEvent) override;
  void clickInput(const ASGE::ClickEvent* clickEvent) override;
  void render(ASGE::Renderer* renderer) override;

 private:
  std::function<void(Scene::SceneID)> scene_callback;
  GCNetClient& client;
  SpriteComponent background;
  UITextBox ip_address;
  UITextBox port;
  UITextBox username;
  UIButton connect;
};

#endif // ASGENETGAME_TITLESCREEN_H
