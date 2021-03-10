//
// Created by hewis on 21/02/2021.
//

#ifndef ASGENETGAME_LOBBYSCENE_H
#define ASGENETGAME_LOBBYSCENE_H

#include <ASGENetLib/GCNetClient.hpp>
#include <GameObjects/Scenes/Scene.h>
#include <GameObjects/UI/ChatWindow.h>
#include <GameObjects/UI/UIButton.h>
#include <array>
class LobbyScene : public Scene
{
 public:
  LobbyScene(
    ASGE::Renderer* renderer, std::function<void(Scene::SceneID)> _scene_callback,
    GCNetClient& _client);
  void keyInput(const ASGE::KeyEvent* keyEvent) override;
  bool clickInput(const ASGE::ClickEvent* clickEvent, ASGE::Renderer* renderer) override;
  void render(ASGE::Renderer* renderer) override;
  void netInput(
    ASGE::Renderer* renderer, NetUtil::CommandID command_id, UserClient& origin,
    const std::string& message) override;

 private:
  void onReadyButton();
  void onDisconnectButton();
  // void onPopOutButton();

  std::function<void(Scene::SceneID)> scene_callback;
  GCNetClient& client;
  SpriteComponent background;
  SpriteComponent chat_box;

  ChatWindow chat_window;
  UIButton ready_button;
  UIButton disconnect_button;
  UIButton popout_button;
  UITextBox game_rules_box;
  TextComponent game_rules;
  std::array<SpriteComponent, 9> colour_selects;
};

#endif // ASGENETGAME_LOBBYSCENE_H
