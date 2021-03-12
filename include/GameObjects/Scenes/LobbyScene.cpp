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
    renderer, UIButton::GREEN, ASGE::Point2D(675, 100), 400, 125, "Ready",
    [this]() { onReadyButton(); }),
  disconnect_button(
    renderer, UIButton::RED, ASGE::Point2D(675, 400), 400, 125, "Disconnect",
    [this]() { onDisconnectButton(); }),
  popout_button(
    renderer, UIButton::YELLOW, ASGE::Point2D(675, 250), 400, 125, "Pop-Out Enabled", []() {}),
  game_rules(
    renderer,
    "How To Play: \n \n Each player takes turns to place counters into the board.\n "
    "In order to win, a player must achieve a row of 4 counters.\n"
    "This can be horizontally, vertically or diagonally.\n\n"
    "When playing with the The Pop-Out Ruleset,\n"
    "players can pop their counters from the bottom row of the board.",
    ASGE::Point2D(50, 650), FONTS::FANCY, 1, ASGE::COLOURS::WHITE),
  select_colour(
    renderer, "Select your Colour:", ASGE::Point2D(50, 75), FONTS::FANCY, 1, ASGE::COLOURS::WHITE),
  colour_selects(std::array<SpriteComponent, 9>{
    SpriteComponent(renderer, "data/images/chips/red.png", ASGE::Point2D(50, 100)),
    SpriteComponent(renderer, "data/images/chips/orange.png", ASGE::Point2D(200, 100)),
    SpriteComponent(renderer, "data/images/chips/yellow.png", ASGE::Point2D(350, 100)),
    SpriteComponent(renderer, "data/images/chips/green.png", ASGE::Point2D(50, 250)),
    SpriteComponent(renderer, "data/images/chips/blue.png", ASGE::Point2D(200, 250)),
    SpriteComponent(renderer, "data/images/chips/purple.png", ASGE::Point2D(350, 250)),
    SpriteComponent(renderer, "data/images/chips/pink.png", ASGE::Point2D(50, 400)),
    SpriteComponent(renderer, "data/images/chips/black.png", ASGE::Point2D(200, 400)),
    SpriteComponent(renderer, "data/images/chips/white.png", ASGE::Point2D(350, 400)) })
{
  background.getSprite()->setGlobalZOrder(-2);
}
void LobbyScene::render(ASGE::Renderer* renderer)
{
  chat_window.render(renderer);
  ready_button.render(renderer);
  popout_button.render(renderer);
  disconnect_button.render(renderer);
  game_rules.render(renderer);
  background.render(renderer);
  select_colour.render(renderer);
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
    if (popout_button.isInside(ASGE::Point2D(
          static_cast<float>(clickEvent->xpos), static_cast<float>(clickEvent->ypos))))
    {
      client.send(NetUtil::SET_BOARD_POP_OUT, pop_out ? "0" : "1");
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
  else if (command_id == NetUtil::SET_BOARD_POP_OUT)
  {
    pop_out = (message[0] == '1');
    popout_button.setText(pop_out ? "Pop-Out Enabled" : "Pop-Out Disabled");
    popout_button.changeColour(renderer, pop_out ? UIButton::YELLOW : UIButton::BLUE);
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
