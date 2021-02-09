#include "ASGEGame.hpp"

/// Initialises the game.
ASGENetGame::ASGENetGame(const ASGE::GameSettings& settings) : OGLGame(settings)
{
  key_callback_id     = inputs->addCallbackFnc(ASGE::E_KEY, &ASGENetGame::keyHandler, this);
  inputs->use_threads = true;
  toggleFPS();

  client.connect("127.0.0.1", 31276);
}

/// Destroys the game.
ASGENetGame::~ASGENetGame()
{
  this->inputs->unregisterCallback(static_cast<unsigned int>(key_callback_id));
}

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
        client.send(input_string);
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

/// Render your game and its scenes here.
void ASGENetGame::render()
{
  renderer->renderText(input_string, 128, 128);
}

/// "Use fixed steps for physics"
void ASGENetGame::fixedUpdate(const ASGE::GameTime& us)
{
  Game::fixedUpdate(us);
}
