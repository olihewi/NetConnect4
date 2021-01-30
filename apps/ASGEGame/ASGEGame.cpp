#include "ASGEGame.hpp"
#include <ASGENetLib/GCNetClient.hpp>

/// Initialises the game.
/// Setup your game and initialise the core components.
/// @param settings
ASGENetGame::ASGENetGame(const ASGE::GameSettings& settings) : OGLGame(settings)
{
  key_callback_id     = inputs->addCallbackFnc(ASGE::E_KEY, &ASGENetGame::keyHandler, this);
  inputs->use_threads = true;
  toggleFPS();

  auto client = std::make_unique<GCNetClient>();
  client->connect("127.0.0.1", 31276);
  game_components.emplace_back(std::move(client));
}

/// Destroys the game.
ASGENetGame::~ASGENetGame()
{
  this->inputs->unregisterCallback(static_cast<unsigned int>(key_callback_id));
}

/// Processes key inputs.
/// This function is added as a callback to handle the game's
/// keyboard input. For this game, calls to this function
/// are not thread safe, so you may alter the game's state
/// but your code needs to designed to prevent data-races.
/// @param data
/// @see KeyEvent
void ASGENetGame::keyHandler(ASGE::SharedEventData data)
{
  const auto* key = dynamic_cast<const ASGE::KeyEvent*>(data.get());

  if (key->key == ASGE::KEYS::KEY_ESCAPE)
  {
    signalExit();
  }
}

/// Updates your game and all it's components.
/// @param us
void ASGENetGame::update(const ASGE::GameTime& us)
{
  for (auto& gc : game_components)
  {
    gc->update(us.deltaInSecs());
  }
}

/// Render your game and its scenes here.
void ASGENetGame::render() {}

/// Calls to fixedUpdate use the same fixed timestep
/// irrespective of how much time is passed. This allows
/// calculations to resolve correctly and stop physics
/// simulations from imploding
///
/// https://gamedev.stackexchange.com/questions/1589/when-should-i-use-a-fixed-or-variable-time-step
/// "Use variable timesteps for your game and fixed steps for physics"
/// @param us
void ASGENetGame::fixedUpdate(const ASGE::GameTime& us)
{
  Game::fixedUpdate(us);
}
