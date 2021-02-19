#include "ASGEGame.hpp"
#include <Utilities/NetUtil.h>

/// Initialises the game.
ASGENetGame::ASGENetGame(const ASGE::GameSettings& settings) : OGLGame(settings)
{
  inputs->use_threads = true;
  toggleFPS();
  init();
  client.connect("127.0.0.1", 31276, "Andrei");
}

ASGENetGame::~ASGENetGame()
{
  this->inputs->unregisterCallback(static_cast<unsigned int>(key_callback_id));
}

/// Initialise Components.
bool ASGENetGame::init()
{
  key_callback_id = inputs->addCallbackFnc(ASGE::E_KEY, &ASGENetGame::keyHandler, this);
  background      = std::make_unique<SpriteComponent>(
    renderer.get(), "data/background.png", ASGE::Point2D(1920, 1080));
  return false;
}

/// Destroys the game.

/// Processes key inputs.
void ASGENetGame::keyHandler(ASGE::SharedEventData data)
{
  const auto* key = dynamic_cast<const ASGE::KeyEvent*>(data.get());

  if (key->key == ASGE::KEYS::KEY_ESCAPE)
  {
    signalExit();
  }
  if (key->action == ASGE::KEYS::KEY_PRESSED)
  {
    if (key->key >= ASGE::KEYS::KEY_SPACE && key->key <= ASGE::KEYS::KEY_GRAVE_ACCENT)
    {
      input_string += static_cast<char>(key->key);
    }
    if (input_string.length() > 0)
    {
      if (key->key == ASGE::KEYS::KEY_BACKSPACE)
      {
        input_string.pop_back();
      }
      if (key->key == ASGE::KEYS::KEY_ENTER)
      {
        client.send(NetUtil::CHAT_MESSAGE, input_string);
        input_string = "";
      }
    }
  }
}

/// Updates the game and all it's components.
void ASGENetGame::update(const ASGE::GameTime& us)
{
  for (auto& gc : game_components)
  {
    gc->update(us.deltaInSecs());
  }
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
  if (gameState == MenuItem::MENU_GAME)
  {
    background->render(renderer.get());
  }
  if (gameState == MenuItem::GAME)
  {
    renderer->renderText(input_string, 128, 128);
  }
}
