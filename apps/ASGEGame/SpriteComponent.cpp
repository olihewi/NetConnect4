//
// Created by Andrei on 11/02/2021.
//

#include "SpriteComponent.hpp"
#include <Engine/Renderer.h>

bool SpriteComponent::loadSprite(ASGE::Renderer* renderer, const std::string& file_path)
{
  sprite   = renderer->createUniqueSprite();
  occupied = false;
  return sprite->loadTexture(file_path);
}

std::unique_ptr<ASGE::Sprite>& SpriteComponent::getSprite()
{
  return sprite;
}

void SpriteComponent::render(ASGE::Renderer* renderer)
{
  renderer->renderSprite(*sprite);
}

SpriteComponent::SpriteComponent(ASGE::Renderer* renderer, const std::string& file_path)
{
  loadSprite(renderer, file_path);
}

bool SpriteComponent::vis() const
{
  return onTop;
}

bool SpriteComponent::setVisibility(bool invis)
{
  onTop = invis;
  return onTop;
}

void SpriteComponent::setGrid(int gridPos)
{
  gridPos_ = gridPos;
}

int SpriteComponent::getGrid() const
{
  return gridPos_;
}

void SpriteComponent::setxPos(float xPos)
{
  sprite->xPos(xPos);
}

void SpriteComponent::setyPos(float yPos)
{
  sprite->yPos(yPos);
}