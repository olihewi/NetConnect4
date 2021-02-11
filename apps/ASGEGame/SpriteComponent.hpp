//
// Created by Andrei on 11/02/2021.
//

#ifndef ASGENETGAME_SPRITECOMPONENT_HPP
#define ASGENETGAME_SPRITECOMPONENT_HPP
#pragma once
#include <Engine/Renderer.h>
#include <Engine/Sprite.h>
#include <memory>
#include <vector>

class SpriteComponent
{
 public:
  SpriteComponent(ASGE::Renderer* renderer, const std::string& file_path);
  // ~SpriteComponent() = default;

  [[maybe_unused]] bool loadSprite(ASGE::Renderer* renderer, const std::string& file_path);

  std::unique_ptr<ASGE::Sprite>& getSprite();

  void render(ASGE::Renderer* renderer);

  void update(double /* dt */) {}

  bool setVisibility(bool invis);

  [[nodiscard]] bool vis() const;

  bool onTop    = false;
  bool occupied = false;

  void setGrid(int gridPosition);

  [[nodiscard]] int getGrid() const;

  void setxPos(float xPos);

  void setyPos(float yPos);

 private:
  std::unique_ptr<ASGE::Sprite> sprite = nullptr;
  int gridPos_{};
};

#endif // ASGENETGAME_SPRITECOMPONENT_HPP
