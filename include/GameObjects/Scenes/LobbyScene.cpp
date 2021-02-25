//
// Created by hewis on 21/02/2021.
//

#include "LobbyScene.h"
#include <Engine/FileIO.h>
#include <iostream>
LobbyScene::LobbyScene(ASGE::Renderer* renderer, ASGENetGame& main) :
  game(main), chat_window(
                renderer, main.getClient(),
                ASGE::Point2D(static_cast<float>(ASGE::SETTINGS.window_width) - 676, 0)),
  ready_button(renderer, UIButton::GREEN, ASGE::Point2D(0, 0), 300, 50, "READY")
{
  soloud.init();
  ASGE::FILEIO::File file;
  if (file.open("data/audio/8ball.wav"))
  {
    auto io_buffer = file.read();
    sample.loadMem(
      io_buffer.as_unsigned_char(), static_cast<unsigned int>(io_buffer.length), false, false);
  }
  sample.setLooping(true);
  soloud.play(sample);
}
void LobbyScene::render(ASGE::Renderer* renderer)
{
  chat_window.render(renderer);
  ready_button.render(renderer);
}
void LobbyScene::keyInput(const ASGE::KeyEvent* keyEvent)
{
  chat_window.keyInput(keyEvent);
}
void LobbyScene::clickInput(const ASGE::ClickEvent* clickEvent)
{
  chat_window.clickInput(clickEvent);
  ready_button.clickInput(clickEvent);
  if (ready_button.getClick())
  {
    game.setScene(ASGENetGame::SceneID::GAME);
  }
}
void LobbyScene::netInput(NetUtil::CommandID command_id, const std::string& message)
{
  if (command_id == NetUtil::CHANGE_COLOUR)
  {
    std::cout << "Changed colour " << message << std::endl;
  }
}
