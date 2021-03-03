//
// Created by hewis on 20/02/2021.
//

#ifndef ASGENETGAME_GAMEOBJECT_H
#define ASGENETGAME_GAMEOBJECT_H

#include <Engine/InputEvents.h>
#include <Engine/Renderer.h>
#include <vector>
class GameObject
{
 public:
  virtual ~GameObject() = default;
  virtual void update(float /*dt*/) {}
  virtual void keyInput(const ASGE::KeyEvent* /*keyEvent*/) {}
  virtual bool clickInput(const ASGE::ClickEvent* /*clickEvent*/, ASGE::Renderer* /*renderer*/)
  {
    return false;
  }
  virtual void mouseInput(const ASGE::MoveEvent* /*moveEvent*/) {}
  virtual void mouseScrollInput(const ASGE::ScrollEvent* /*scrollEvent*/) {}
  virtual void render(ASGE::Renderer* /*renderer*/) {}

 private:
};

#endif // ASGENETGAME_GAMEOBJECT_H
