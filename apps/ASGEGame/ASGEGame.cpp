#include "ASGEGame.hpp"
#include <Engine/FileIO.h>
#include <GameObjects/Scenes/GameScene.h>
#include <GameObjects/Scenes/LobbyScene.h>
#include <GameObjects/Scenes/SpriteScene.h>
#include <GameObjects/Scenes/TitleScreen.h>
#include <GameObjects/Scenes/WinScene.h>
#include <iostream>

/// Initialises the game.
ASGENetGame::ASGENetGame(const ASGE::GameSettings& settings) : OGLGame(settings)
{
  // toggleFPS();
  inputs->use_threads = true;
  FontManager font_manager;
  font_manager.loadFonts(renderer.get());
  init();
}

/// Destroys the game.
ASGENetGame::~ASGENetGame()
{
  this->inputs->unregisterCallback(static_cast<unsigned int>(key_callback_id));
  this->inputs->unregisterCallback(static_cast<unsigned int>(click_callback_id));
  this->inputs->unregisterCallback(static_cast<unsigned int>(mouse_callback_id));
  this->inputs->unregisterCallback(static_cast<unsigned int>(scroll_callback_id));
}

/// Initialise Components.
bool ASGENetGame::init()
{
  soloud.init();
  client.setCallback([this](auto&& PH1) { netInput(PH1); });
  /// For some reason, ASGE only loads in sprites when it is first ran, so load all scenes...
  setScene(Scene::SceneID::SPRITE_DEBUG);
  setScene(Scene::SceneID::TITLE);

  key_callback_id   = inputs->addCallbackFnc(ASGE::E_KEY, &ASGENetGame::keyHandler, this);
  click_callback_id = inputs->addCallbackFnc(ASGE::E_MOUSE_CLICK, &ASGENetGame::clickHandler, this);
  mouse_callback_id = inputs->addCallbackFnc(ASGE::E_MOUSE_MOVE, &ASGENetGame::mouseHandler, this);
  scroll_callback_id =
    inputs->addCallbackFnc(ASGE::E_MOUSE_SCROLL, &ASGENetGame::scrollHandler, this);

  ASGE::FILEIO::File file;
  if (file.open("data/audio/8ball.wav"))
  {
    auto io_buffer = file.read();
    eight_ball.loadMem(
      io_buffer.as_unsigned_char(), static_cast<unsigned int>(io_buffer.length), false, false);
    eight_ball.setLooping(true);
  }
  if (file.open("data/audio/counter_drop.wav"))
  {
    auto io_buffer = file.read();
    counter_drop.loadMem(
      io_buffer.as_unsigned_char(), static_cast<unsigned int>(io_buffer.length), false, false);
  }
  if (file.open("data/audio/counter_pop.wav"))
  {
    auto io_buffer = file.read();
    counter_pop.loadMem(
      io_buffer.as_unsigned_char(), static_cast<unsigned int>(io_buffer.length), false, false);
  }
  if (file.open("data/audio/door_bell.wav"))
  {
    auto io_buffer = file.read();
    door_bell.loadMem(
      io_buffer.as_unsigned_char(), static_cast<unsigned int>(io_buffer.length), false, false);
  }
  if (file.open("data/audio/game_over.wav"))
  {
    auto io_buffer = file.read();
    game_over.loadMem(
      io_buffer.as_unsigned_char(), static_cast<unsigned int>(io_buffer.length), false, false);
  }
  if (file.open("data/audio/door_closed.wav"))
  {
    auto io_buffer = file.read();
    door_closed.loadMem(
      io_buffer.as_unsigned_char(), static_cast<unsigned int>(io_buffer.length), false, false);
  }
  soloud.play(eight_ball);
  return false;
}

/// Processes key inputs.
void ASGENetGame::keyHandler(ASGE::SharedEventData data)
{
  const auto* key = dynamic_cast<const ASGE::KeyEvent*>(data.get());
  current_scene->keyInput(key);
}
void ASGENetGame::clickHandler(ASGE::SharedEventData data)
{
  const auto* click = dynamic_cast<const ASGE::ClickEvent*>(data.get());
  current_scene->clickInput(click, renderer.get());
}
void ASGENetGame::mouseHandler(ASGE::SharedEventData data)
{
  const auto* mouse = dynamic_cast<const ASGE::MoveEvent*>(data.get());
  current_scene->mouseInput(mouse);
}
void ASGENetGame::scrollHandler(ASGE::SharedEventData data)
{
  const auto* scroll = dynamic_cast<const ASGE::ScrollEvent*>(data.get());
  current_scene->mouseScrollInput(scroll);
}

/// Updates the game and all it's components.
void ASGENetGame::update(const ASGE::GameTime& us)
{
  auto dt = static_cast<float>(us.deltaInSecs());
  current_scene->update(dt);
}

/// "Use fixed steps for physics"
void ASGENetGame::fixedUpdate(const ASGE::GameTime& us)
{
  Game::fixedUpdate(us);
}

/// Render your game and its scenes here.
void ASGENetGame::render()
{
  renderer->setFont(0);
  current_scene->render(renderer.get());
}

void ASGENetGame::setScene(Scene::SceneID scene)
{
  switch (scene)
  {
    case Scene::SceneID::TITLE:
      current_scene = std::make_unique<TitleScreen>(
        renderer.get(), [this](auto&& PH1) { setScene(PH1); }, client, [this]() { signalExit(); });
      break;
    case Scene::SceneID::LOBBY:
      current_scene = std::make_unique<LobbyScene>(
        renderer.get(), [this](auto&& PH1) { setScene(PH1); }, client);
      break;
    case Scene::SceneID::GAME:
      current_scene =
        std::make_unique<GameScene>(renderer.get(), client, [this](auto&& PH1) { setScene(PH1); });
      break;
    case Scene::SceneID::WIN_GAME:
      current_scene = std::make_unique<WinScene>(
        renderer.get(), [this](auto&& PH1) { setScene(PH1); }, client);
      break;
    case Scene::SceneID::SPRITE_DEBUG:
      current_scene = std::make_unique<SpriteScene>(renderer.get());
      break;
  }
}

void ASGENetGame::netInput(const char* message)
{
  auto command_id = static_cast<NetUtil::CommandID>(message[0]);
  auto& user      = client.getPlayer(static_cast<size_t>(message[1] - 64));
  std::string message_string(message);
  message_string = message_string.substr(message_string.find_last_of(':') + 1);
  current_scene->netInput(renderer.get(), command_id, user, message_string);
  if (command_id == NetUtil::DROP_COUNTER)
  {
    soloud.play(counter_drop);
  }
  else if (command_id == NetUtil::POP_OUT_COUNTER)
  {
    soloud.play(counter_pop);
  }
  else if (command_id == NetUtil::ASSIGN_PLAYER_ID)
  {
    soloud.play(door_bell);
  }
  else if (command_id == NetUtil::WON_GAME)
  {
    soloud.play(game_over);
  }
  else if (command_id == NetUtil::DISCONNECTED)
  {
    soloud.play(door_closed);
  }
}
