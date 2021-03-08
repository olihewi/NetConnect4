//
// Created by hewis on 21/02/2021.
//

#include "LobbyScene.h"
#include <Engine/FileIO.h>
#include <iostream>
#include <utility>
LobbyScene::LobbyScene(
  ASGE::Renderer* renderer, std::function<void(Scene::SceneID)> _scene_callback,
  GCNetClient& _client) :
  scene_callback(std::move(_scene_callback)),
  client(_client), background(renderer, "data/images/background3.png", ASGE::Point2D(0, 0)),
  chat_window(
    renderer, ASGE::Point2D(static_cast<float>(ASGE::SETTINGS.window_width) - 676, 0), _client),
  ready_button(
    renderer, UIButton::GREEN, ASGE::Point2D(0, 0), 300, 50, "READY",
    [this]() { onReadyButton(); }),
  disconnect_button(
    renderer, UIButton::RED, ASGE::Point2D(500, 0), 300, 50, "DISCONNECT",
    [this]() { onDisconnectButton(); }),
  game_rules(
    renderer,
    "RULES OF CONNECT FOUR \n \n EACH PLAYER HAS A TURN WHERE THEY ARE ABLE TO DROP A CHIP INTO "
    "THE BOARD. \n TO WIN THE GAME ONE PLAYER WOULD, \n HAVE TO ACHIEVE A DIAGONAL FOUR "
    "COMBINATION OF THE CHIPS.\n",
    ASGE::Point2D(0, 800), 1, 1, ASGE::COLOURS::BLACK),
  colour_selects(std::array<SpriteComponent, 9>{
    SpriteComponent(renderer, "data/images/chips/red.png", ASGE::Point2D(50, 200)),
    SpriteComponent(renderer, "data/images/chips/orange.png", ASGE::Point2D(200, 200)),
    SpriteComponent(renderer, "data/images/chips/yellow.png", ASGE::Point2D(350, 200)),
    SpriteComponent(renderer, "data/images/chips/green.png", ASGE::Point2D(500, 200)),
    SpriteComponent(renderer, "data/images/chips/blue.png", ASGE::Point2D(50, 350)),
    SpriteComponent(renderer, "data/images/chips/purple.png", ASGE::Point2D(200, 350)),
    SpriteComponent(renderer, "data/images/chips/pink.png", ASGE::Point2D(350, 350)),
    SpriteComponent(renderer, "data/images/chips/black.png", ASGE::Point2D(500, 350)),
    SpriteComponent(renderer, "data/images/chips/white.png", ASGE::Point2D(650, 350)) })
{
  background.getSprite()->setGlobalZOrder(-2);
}
void LobbyScene::render(ASGE::Renderer* renderer)
{
  chat_window.render(renderer);
  ready_button.render(renderer);
  disconnect_button.render(renderer);
  game_rules.render(renderer);
  background.render(renderer);
  for (auto& colour_select : colour_selects)
  {
    colour_select.render(renderer);
  }
}
void LobbyScene::keyInput(const ASGE::KeyEvent* keyEvent)
{
  chat_window.keyInput(keyEvent);
}
bool LobbyScene::clickInput(const ASGE::ClickEvent* clickEvent, ASGE::Renderer* renderer)
{
  chat_window.clickInput(clickEvent, renderer);
  if (ready_button.clickInput(clickEvent, renderer))
  {
    return true;
  }
  if (disconnect_button.clickInput(clickEvent, renderer))
  {
    return false;
  }
  if (clickEvent->action == ASGE::KEYS::KEY_PRESSED)
  {
    for (size_t i = 0; i < colour_selects.size(); i++)
    {
      if (colour_selects[i].isInside(ASGE::Point2D(
            static_cast<float>(clickEvent->xpos), static_cast<float>(clickEvent->ypos))))
      {
        client.send(NetUtil::CHANGE_COLOUR, std::string(1, static_cast<char>(i + 64)));
      }
    }
  }
  return true;
}

void LobbyScene::netInput(
  ASGE::Renderer* renderer, NetUtil::CommandID command_id, UserClient& origin,
  const std::string& message)
{
  if (command_id == NetUtil::CHAT_MESSAGE)
  {
    std::string message_string = origin.username + " > " + message;
    std::cout << message_string << std::endl;
    chat_window.addMessage(renderer, message_string);
  }
  else if (command_id == NetUtil::CHANGE_USERNAME)
  {
    chat_window.addMessage(renderer, origin.username + " joined the lobby.");
  }
  else if (command_id == NetUtil::CHANGE_COLOUR)
  {
    chat_window.addMessage(
      renderer,
      origin.username + " changed their colour to " + UserClient::getColourName(origin.colour));
  }
  else if (command_id == NetUtil::DISCONNECTED)
  {
    chat_window.addMessage(renderer, origin.username + " has disconnected.");
  }
}
void LobbyScene::onReadyButton()
{
  scene_callback(SceneID::GAME);
}
void LobbyScene::onDisconnectButton()
{
  client.disconnect();
  scene_callback(SceneID::TITLE);
}
