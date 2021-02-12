//
// Created by Andrei on 11/02/2021.
//

#include "GameComponents/SpriteComponent.hpp"

SpriteComponent::SpriteComponent(
  ASGE::Renderer* renderer, const std::string& file_path, ASGE::Point2D position) :
  GameComponent(GameComponent::ID::SPRITE)
{
  loadSprite(renderer, file_path);
  setPosition(position);
}

bool SpriteComponent::loadSprite(ASGE::Renderer* renderer, const std::string& file_path)
{
  sprite = renderer->createUniqueSprite();
  return sprite->loadTexture(file_path);
}

std::unique_ptr<ASGE::Sprite>& SpriteComponent::getSprite()
{
  return sprite;
}

void SpriteComponent::render(ASGE::Renderer* renderer)
{
  if (visible)
  {
    renderer->renderSprite(*sprite);
  }
}

bool SpriteComponent::getVisibility() const
{
  return visible;
}
void SpriteComponent::setVisibility(bool _visibility)
{
  visible = _visibility;
}

ASGE::Point2D SpriteComponent::getPosition()
{
  return ASGE::Point2D(sprite->xPos(), sprite->yPos());
}
void SpriteComponent::setPosition(ASGE::Point2D _position)
{
  sprite->xPos(_position.x);
  sprite->yPos(_position.y);
}
void SpriteComponent::translate(ASGE::Point2D _translation)
{
  sprite->xPos(sprite->xPos() + _translation.x);
  sprite->yPos(sprite->yPos() + _translation.y);
}
