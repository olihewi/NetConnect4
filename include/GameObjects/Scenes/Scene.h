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
  virtual void netInput(NetUtil::CommandID /*command_id*/, const std::string& /*message*/) {}
};

#endif // ASGENETGAME_SCENE_H
