#include "ASGEGame.hpp"
#include <GameObjects/Scenes/GameScene.h>
#include <GameObjects/Scenes/TitleScreen.h>
#include <Utilities/FontManager.h>
//#include <Utilities/NetUtil.h>

/// Initialises the game.
ASGENetGame::ASGENetGame(const ASGE::GameSettings& settings) : OGLGame(settings)
{
  inputs->use_threads = true;
  toggleFPS();
  FontManager font_manager;
  font_manager.loadFonts(renderer.get());
  init();
  // client.connect("127.0.0.1", 31276, "Andrei");
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
  game_objects.emplace_back(std::make_unique<TitleScreen>(renderer.get(), client));
  // game_objects.emplace_back(std::make_unique<GameScene>(renderer.get()));
  key_callback_id   = inputs->addCallbackFnc(ASGE::E_KEY, &ASGENetGame::keyHandler, this);
  click_callback_id = inputs->addCallbackFnc(ASGE::E_MOUSE_CLICK, &ASGENetGame::clickHandler, this);
  mouse_callback_id = inputs->addCallbackFnc(ASGE::E_MOUSE_MOVE, &ASGENetGame::mouseHandler, this);
  scroll_callback_id =
    inputs->addCallbackFnc(ASGE::E_MOUSE_SCROLL, &ASGENetGame::scrollHandler, this);

  gameBoard();
  return false;
}

/// Processes key inputs.
void ASGENetGame::keyHandler(ASGE::SharedEventData data)
{
  const auto* key = dynamic_cast<const ASGE::KeyEvent*>(data.get());
  for (auto& game_object : game_objects)
  {
    game_object->keyInput(key);
  }

  if (key->key == ASGE::KEYS::KEY_ESCAPE)
  {
    signalExit();
  }
  if (gameState == MenuItem::MENU_GAME && key->key == ASGE::KEYS::KEY_ENTER)
  {
    gameState = MenuItem::GAME;
  }
  if (gameState == MenuItem::GAME)
  {
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
}
void ASGENetGame::clickHandler(ASGE::SharedEventData data)
{
  const auto* click = dynamic_cast<const ASGE::ClickEvent*>(data.get());
  for (auto& game_object : game_objects)
  {
    game_object->clickInput(click);
  }
}
void ASGENetGame::mouseHandler(ASGE::SharedEventData data)
{
  const auto* mouse = dynamic_cast<const ASGE::MoveEvent*>(data.get());
  for (auto& game_object : game_objects)
  {
    game_object->mouseInput(mouse);
  }
}
void ASGENetGame::scrollHandler(ASGE::SharedEventData data)
{
  const auto* scroll = dynamic_cast<const ASGE::ScrollEvent*>(data.get());
  for (auto& game_object : game_objects)
  {
    game_object->mouseScrollInput(scroll);
  }
}

void ASGENetGame::gameBoard() {}

/// Updates the game and all it's components.
void ASGENetGame::update(const ASGE::GameTime& us)
{
  auto dt = static_cast<float>(us.deltaInSecs());
  for (auto& gc : game_components)
  {
    gc->update(us.deltaInSecs());
  }
  for (auto& go : game_objects)
  {
    go->update(dt);
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
  for (auto& game_object : game_objects)
  {
    game_object->render(renderer.get());
  }
  for (auto& game_component : game_components)
  {
    game_component->render(renderer.get());
  }

  if (gameState == MenuItem::GAME)
  {
    renderer->renderText(input_string, 128, 128);
    gameRender();
  }
}
