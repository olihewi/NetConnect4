//
// Created by hewis on 21/02/2021.
//

#ifndef ASGENETGAME_SCENE_H
#define ASGENETGAME_SCENE_H
#include "GameObjects/GameObject.h"
#include "Utilities/NetUtil.h"
#include "Utilities/UserClient.h"
class Scene : public GameObject
{
 public:
  enum class SceneID
  {
    TITLE    = 0,
    LOBBY    = 1,
    GAME     = 2,
    WIN_GAME = 3
  };
  virtual void netInput(
    ASGE::Renderer* /*renderer*/, NetUtil::CommandID /*command_id*/, UserClient& /*origin*/,
    const std::string& /*message*/)
  {
  }
};

#endif // ASGENETGAME_SCENE_H
