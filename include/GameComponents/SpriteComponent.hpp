//
// Created by Andrei on 11/02/2021.
//

#ifndef ASGENETGAME_SPRITECOMPONENT_HPP
#define ASGENETGAME_SPRITECOMPONENT_HPP
#pragma once
#include <ASGENetLib/GComponent.hpp>
#include <Engine/Renderer.h>
#include <Engine/Sprite.h>
#include <vector>

class SpriteComponent : public GameComponent
{
 public:
  SpriteComponent();
  SpriteComponent(ASGE::Renderer* renderer, const std::string& file_path, ASGE::Point2D position);

  bool loadSprite(ASGE::Renderer* renderer, const std::string& file_path);
  std::unique_ptr<ASGE::Sprite>& getSprite();

  void update(double /* dt */) override {}
  void render(ASGE::Renderer* renderer) override;

  [[nodiscard]] bool getVisibility() const;
  void setVisibility(bool _visibility);

  ASGE::Point2D getPosition();
  void setPosition(ASGE::Point2D _position);
  void translate(ASGE::Point2D _translation);

  bool isInside(ASGE::Point2D position);

 private:
  std::unique_ptr<ASGE::Sprite> sprite = nullptr;
  bool visible                         = true;
};

#endif // ASGENETGAME_SPRITECOMPONENT_HPP
