//
// Created by hewis on 21/02/2021.
//

#ifndef ASGENETGAME_SCENE_H
#define ASGENETGAME_SCENE_H
#include "GameObjects/GameObject.h"
#include "Utilities/NetUtil.h"
class Scene : public GameObject
{
 public:
  enum class SceneID
  {
    TITLE = 0,
    LOBBY = 1,
    GAME  = 2,
    //  EXIT_GAME  = 3
  };
  virtual void netInput(
    ASGE::Renderer* /*renderer*/, NetUtil::CommandID /*command_id*/, const std::string& /*message*/)
  {
  }
};

#endif // ASGENETGAME_SCENE_H
