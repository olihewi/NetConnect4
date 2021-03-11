//
// Created by hewis on 11/03/2021.
//

#ifndef ASGENETGAME_SPRITESCENE_H
#define ASGENETGAME_SPRITESCENE_H
#include <GameComponents/SpriteComponent.hpp>
#include <GameObjects/Scenes/Scene.h>
#include <vector>
/// This Scene is used to load all sprites, avoiding errors.
class SpriteScene : public Scene
{
 public:
  explicit SpriteScene(ASGE::Renderer* renderer);
  void render(ASGE::Renderer* renderer) override;
  std::vector<SpriteComponent> sprites;
};

#endif // ASGENETGAME_SPRITESCENE_H
