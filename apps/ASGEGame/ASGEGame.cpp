#include "ASGEGame.hpp"
#include <Engine/FileIO.h>
#include <GameObjects/Scenes/GameScene.h>
#include <GameObjects/Scenes/LobbyScene.h>
#include <GameObjects/Scenes/TitleScreen.h>

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
  setScene(Scene::SceneID::LOBBY);
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
  current_scene->clickInput(click);
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
        renderer.get(), [this](auto&& PH1) { setScene(PH1); }, client);
      break;
    case Scene::SceneID::LOBBY:
      current_scene = std::make_unique<LobbyScene>(
        renderer.get(), [this](auto&& PH1) { setScene(PH1); }, client);
      break;
    case Scene::SceneID::GAME:
      current_scene = std::make_unique<GameScene>(renderer.get());
      break;
  }
}

void ASGENetGame::netInput(std::string message)
{
  auto command_id = static_cast<NetUtil::CommandID>(message[0]);
  message         = message.substr(message.find_last_of(':'));
  current_scene->netInput(renderer.get(), command_id, message);
}
