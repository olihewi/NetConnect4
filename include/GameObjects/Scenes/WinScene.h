//
// Created by Andrei on 03/03/2021.
//

#ifndef ASGENETGAME_WINSCENE_H
#define ASGENETGAME_WINSCENE_H
#include <ASGENetLib/GCNetClient.hpp>
#include <GameObjects/Scenes/Scene.h>
#include <GameObjects/UI/ChatWindow.h>
#include <GameObjects/UI/UIButton.h>

class WinScene : public Scene
{
 public:
  WinScene(
    ASGE::Renderer* renderer, std::function<void(Scene::SceneID)> _scene_callback,
    GCNetClient& _client);

  bool clickInput(const ASGE::ClickEvent* clickEvent, ASGE::Renderer* renderer) override;
  void render(ASGE::Renderer* renderer) override;
  void onReplayButton();
  void onLobbyButton();
  void onTitleButton();

 private:
  std::function<void(Scene::SceneID)> scene_callback;
  GCNetClient& client;
  SpriteComponent background;
  UIButton replay_button;
  UIButton lobby_button;
  UIButton title_button;
};

#endif // ASGENETGAME_WINSCENE_H
