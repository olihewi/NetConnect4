#include "ASGEGame.hpp"
#include <GameObjects/Scenes/GameScene.h>
#include <GameObjects/Scenes/LobbyScene.h>
#include <GameObjects/Scenes/TitleScreen.h>
#include <Utilities/FontManager.h>
//#include <Utilities/NetUtil.h>
#include <Engine/FileIO.h>

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
  /// For some reason, ASGE only loads in sprites when it is first ran, so load all scenes...
  setScene(SceneID::LOBBY);
  setScene(SceneID::TITLE);
  key_callback_id   = inputs->addCallbackFnc(ASGE::E_KEY, &ASGENetGame::keyHandler, this);
  click_callback_id = inputs->addCallbackFnc(ASGE::E_MOUSE_CLICK, &ASGENetGame::clickHandler, this);
  mouse_callback_id = inputs->addCallbackFnc(ASGE::E_MOUSE_MOVE, &ASGENetGame::mouseHandler, this);
  scroll_callback_id =
    inputs->addCallbackFnc(ASGE::E_MOUSE_SCROLL, &ASGENetGame::scrollHandler, this);

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
void ASGENetGame::setScene(SceneID scene)
{
  switch (scene)
  {
    case SceneID::TITLE:
      current_scene = std::make_unique<TitleScreen>(renderer.get(), *this);
      break;
    case SceneID::LOBBY:
      current_scene = std::make_unique<LobbyScene>(renderer.get(), *this);
      break;
    case SceneID::GAME:
      current_scene = std::make_unique<GameScene>(renderer.get());
      break;
  }
}
GCNetClient& ASGENetGame::getClient()
{
  return client;
}

[[maybe_unused]] void
ASGENetGame::netInput(NetUtil::CommandID command_id, const std::string& message)
{
  current_scene->netInput(command_id, message);
}
