//
// Created by hewis on 11/03/2021.
//

#include "SpriteScene.h"
SpriteScene::SpriteScene(ASGE::Renderer* renderer)
{
  sprites.emplace_back(SpriteComponent(renderer, "data/images/background.png", ASGE::Point2D()));
  sprites.emplace_back(SpriteComponent(renderer, "data/images/background2.png", ASGE::Point2D()));
  sprites.emplace_back(SpriteComponent(renderer, "data/images/background3.png", ASGE::Point2D()));
  sprites.emplace_back(SpriteComponent(renderer, "data/images/background4.png", ASGE::Point2D()));
  sprites.emplace_back(SpriteComponent(renderer, "data/images/empty_space.png", ASGE::Point2D()));
  sprites.emplace_back(SpriteComponent(renderer, "data/images/board/pop_out.png", ASGE::Point2D()));
  sprites.emplace_back(SpriteComponent(renderer, "data/images/board/regular.png", ASGE::Point2D()));
  sprites.emplace_back(SpriteComponent(renderer, "data/images/chips/black.png", ASGE::Point2D()));
  sprites.emplace_back(SpriteComponent(renderer, "data/images/chips/blue.png", ASGE::Point2D()));
  sprites.emplace_back(SpriteComponent(renderer, "data/images/chips/green.png", ASGE::Point2D()));
  sprites.emplace_back(SpriteComponent(renderer, "data/images/chips/orange.png", ASGE::Point2D()));
  sprites.emplace_back(SpriteComponent(renderer, "data/images/chips/pink.png", ASGE::Point2D()));
  sprites.emplace_back(SpriteComponent(renderer, "data/images/chips/purple.png", ASGE::Point2D()));
  sprites.emplace_back(SpriteComponent(renderer, "data/images/chips/red.png", ASGE::Point2D()));
  sprites.emplace_back(SpriteComponent(renderer, "data/images/chips/white.png", ASGE::Point2D()));
  sprites.emplace_back(SpriteComponent(renderer, "data/images/chips/yellow.png", ASGE::Point2D()));
  sprites.emplace_back(
    SpriteComponent(renderer, "data/images/ui/chat_background.png", ASGE::Point2D()));
  sprites.emplace_back(SpriteComponent(renderer, "data/images/ui/chatbox.png", ASGE::Point2D()));
  sprites.emplace_back(
    SpriteComponent(renderer, "data/images/ui/button/blue/bl.png", ASGE::Point2D()));
  sprites.emplace_back(
    SpriteComponent(renderer, "data/images/ui/button/blue/bm.png", ASGE::Point2D()));
  sprites.emplace_back(
    SpriteComponent(renderer, "data/images/ui/button/blue/br.png", ASGE::Point2D()));
  sprites.emplace_back(
    SpriteComponent(renderer, "data/images/ui/button/blue/ml.png", ASGE::Point2D()));
  sprites.emplace_back(
    SpriteComponent(renderer, "data/images/ui/button/blue/mm.png", ASGE::Point2D()));
  sprites.emplace_back(
    SpriteComponent(renderer, "data/images/ui/button/blue/mr.png", ASGE::Point2D()));
  sprites.emplace_back(
    SpriteComponent(renderer, "data/images/ui/button/blue/ul.png", ASGE::Point2D()));
  sprites.emplace_back(
    SpriteComponent(renderer, "data/images/ui/button/blue/um.png", ASGE::Point2D()));
  sprites.emplace_back(
    SpriteComponent(renderer, "data/images/ui/button/blue/ur.png", ASGE::Point2D()));
  sprites.emplace_back(
    SpriteComponent(renderer, "data/images/ui/button/fancy/bl.png", ASGE::Point2D()));
  sprites.emplace_back(
    SpriteComponent(renderer, "data/images/ui/button/fancy/bm.png", ASGE::Point2D()));
  sprites.emplace_back(
    SpriteComponent(renderer, "data/images/ui/button/fancy/br.png", ASGE::Point2D()));
  sprites.emplace_back(
    SpriteComponent(renderer, "data/images/ui/button/fancy/ml.png", ASGE::Point2D()));
  sprites.emplace_back(
    SpriteComponent(renderer, "data/images/ui/button/fancy/mm.png", ASGE::Point2D()));
  sprites.emplace_back(
    SpriteComponent(renderer, "data/images/ui/button/fancy/mr.png", ASGE::Point2D()));
  sprites.emplace_back(
    SpriteComponent(renderer, "data/images/ui/button/fancy/ul.png", ASGE::Point2D()));
  sprites.emplace_back(
    SpriteComponent(renderer, "data/images/ui/button/fancy/um.png", ASGE::Point2D()));
  sprites.emplace_back(
    SpriteComponent(renderer, "data/images/ui/button/fancy/ur.png", ASGE::Point2D()));
  sprites.emplace_back(
    SpriteComponent(renderer, "data/images/ui/button/green/bl.png", ASGE::Point2D()));
  sprites.emplace_back(
    SpriteComponent(renderer, "data/images/ui/button/green/bm.png", ASGE::Point2D()));
  sprites.emplace_back(
    SpriteComponent(renderer, "data/images/ui/button/green/br.png", ASGE::Point2D()));
  sprites.emplace_back(
    SpriteComponent(renderer, "data/images/ui/button/green/ml.png", ASGE::Point2D()));
  sprites.emplace_back(
    SpriteComponent(renderer, "data/images/ui/button/green/mm.png", ASGE::Point2D()));
  sprites.emplace_back(
    SpriteComponent(renderer, "data/images/ui/button/green/mr.png", ASGE::Point2D()));
  sprites.emplace_back(
    SpriteComponent(renderer, "data/images/ui/button/green/ul.png", ASGE::Point2D()));
  sprites.emplace_back(
    SpriteComponent(renderer, "data/images/ui/button/green/um.png", ASGE::Point2D()));
  sprites.emplace_back(
    SpriteComponent(renderer, "data/images/ui/button/green/ur.png", ASGE::Point2D()));
  sprites.emplace_back(
    SpriteComponent(renderer, "data/images/ui/button/red/bl.png", ASGE::Point2D()));
  sprites.emplace_back(
    SpriteComponent(renderer, "data/images/ui/button/red/bm.png", ASGE::Point2D()));
  sprites.emplace_back(
    SpriteComponent(renderer, "data/images/ui/button/red/br.png", ASGE::Point2D()));
  sprites.emplace_back(
    SpriteComponent(renderer, "data/images/ui/button/red/ml.png", ASGE::Point2D()));
  sprites.emplace_back(
    SpriteComponent(renderer, "data/images/ui/button/red/mm.png", ASGE::Point2D()));
  sprites.emplace_back(
    SpriteComponent(renderer, "data/images/ui/button/red/mr.png", ASGE::Point2D()));
  sprites.emplace_back(
    SpriteComponent(renderer, "data/images/ui/button/red/ul.png", ASGE::Point2D()));
  sprites.emplace_back(
    SpriteComponent(renderer, "data/images/ui/button/red/um.png", ASGE::Point2D()));
  sprites.emplace_back(
    SpriteComponent(renderer, "data/images/ui/button/red/ur.png", ASGE::Point2D()));
  sprites.emplace_back(
    SpriteComponent(renderer, "data/images/ui/button/yellow/bl.png", ASGE::Point2D()));
  sprites.emplace_back(
    SpriteComponent(renderer, "data/images/ui/button/yellow/bm.png", ASGE::Point2D()));
  sprites.emplace_back(
    SpriteComponent(renderer, "data/images/ui/button/yellow/br.png", ASGE::Point2D()));
  sprites.emplace_back(
    SpriteComponent(renderer, "data/images/ui/button/yellow/ml.png", ASGE::Point2D()));
  sprites.emplace_back(
    SpriteComponent(renderer, "data/images/ui/button/yellow/mm.png", ASGE::Point2D()));
  sprites.emplace_back(
    SpriteComponent(renderer, "data/images/ui/button/yellow/mr.png", ASGE::Point2D()));
  sprites.emplace_back(
    SpriteComponent(renderer, "data/images/ui/button/yellow/ul.png", ASGE::Point2D()));
  sprites.emplace_back(
    SpriteComponent(renderer, "data/images/ui/button/yellow/um.png", ASGE::Point2D()));
  sprites.emplace_back(
    SpriteComponent(renderer, "data/images/ui/button/yellow/ur.png", ASGE::Point2D()));
  sprites.emplace_back(
    SpriteComponent(renderer, "data/images/ui/textbox/blue/bl.png", ASGE::Point2D()));
  sprites.emplace_back(
    SpriteComponent(renderer, "data/images/ui/textbox/blue/bm.png", ASGE::Point2D()));
  sprites.emplace_back(
    SpriteComponent(renderer, "data/images/ui/textbox/blue/br.png", ASGE::Point2D()));
  sprites.emplace_back(
    SpriteComponent(renderer, "data/images/ui/textbox/blue/ml.png", ASGE::Point2D()));
  sprites.emplace_back(
    SpriteComponent(renderer, "data/images/ui/textbox/blue/mm.png", ASGE::Point2D()));
  sprites.emplace_back(
    SpriteComponent(renderer, "data/images/ui/textbox/blue/mr.png", ASGE::Point2D()));
  sprites.emplace_back(
    SpriteComponent(renderer, "data/images/ui/textbox/blue/ul.png", ASGE::Point2D()));
  sprites.emplace_back(
    SpriteComponent(renderer, "data/images/ui/textbox/blue/um.png", ASGE::Point2D()));
  sprites.emplace_back(
    SpriteComponent(renderer, "data/images/ui/textbox/blue/ur.png", ASGE::Point2D()));
  sprites.emplace_back(
    SpriteComponent(renderer, "data/images/ui/textbox/fancy/bl.png", ASGE::Point2D()));
  sprites.emplace_back(
    SpriteComponent(renderer, "data/images/ui/textbox/fancy/bm.png", ASGE::Point2D()));
  sprites.emplace_back(
    SpriteComponent(renderer, "data/images/ui/textbox/fancy/br.png", ASGE::Point2D()));
  sprites.emplace_back(
    SpriteComponent(renderer, "data/images/ui/textbox/fancy/ml.png", ASGE::Point2D()));
  sprites.emplace_back(
    SpriteComponent(renderer, "data/images/ui/textbox/fancy/mm.png", ASGE::Point2D()));
  sprites.emplace_back(
    SpriteComponent(renderer, "data/images/ui/textbox/fancy/mr.png", ASGE::Point2D()));
  sprites.emplace_back(
    SpriteComponent(renderer, "data/images/ui/textbox/fancy/ul.png", ASGE::Point2D()));
  sprites.emplace_back(
    SpriteComponent(renderer, "data/images/ui/textbox/fancy/um.png", ASGE::Point2D()));
  sprites.emplace_back(
    SpriteComponent(renderer, "data/images/ui/textbox/fancy/ur.png", ASGE::Point2D()));
  sprites.emplace_back(
    SpriteComponent(renderer, "data/images/ui/textbox/red/bl.png", ASGE::Point2D()));
  sprites.emplace_back(
    SpriteComponent(renderer, "data/images/ui/textbox/red/bm.png", ASGE::Point2D()));
  sprites.emplace_back(
    SpriteComponent(renderer, "data/images/ui/textbox/red/br.png", ASGE::Point2D()));
  sprites.emplace_back(
    SpriteComponent(renderer, "data/images/ui/textbox/red/ml.png", ASGE::Point2D()));
  sprites.emplace_back(
    SpriteComponent(renderer, "data/images/ui/textbox/red/mm.png", ASGE::Point2D()));
  sprites.emplace_back(
    SpriteComponent(renderer, "data/images/ui/textbox/red/mr.png", ASGE::Point2D()));
  sprites.emplace_back(
    SpriteComponent(renderer, "data/images/ui/textbox/red/ul.png", ASGE::Point2D()));
  sprites.emplace_back(
    SpriteComponent(renderer, "data/images/ui/textbox/red/um.png", ASGE::Point2D()));
  sprites.emplace_back(
    SpriteComponent(renderer, "data/images/ui/textbox/red/ur.png", ASGE::Point2D()));
  sprites.emplace_back(
    SpriteComponent(renderer, "data/images/ui/textbox/yellow/bl.png", ASGE::Point2D()));
  sprites.emplace_back(
    SpriteComponent(renderer, "data/images/ui/textbox/yellow/bm.png", ASGE::Point2D()));
  sprites.emplace_back(
    SpriteComponent(renderer, "data/images/ui/textbox/yellow/br.png", ASGE::Point2D()));
  sprites.emplace_back(
    SpriteComponent(renderer, "data/images/ui/textbox/yellow/ml.png", ASGE::Point2D()));
  sprites.emplace_back(
    SpriteComponent(renderer, "data/images/ui/textbox/yellow/mm.png", ASGE::Point2D()));
  sprites.emplace_back(
    SpriteComponent(renderer, "data/images/ui/textbox/yellow/mr.png", ASGE::Point2D()));
  sprites.emplace_back(
    SpriteComponent(renderer, "data/images/ui/textbox/yellow/ul.png", ASGE::Point2D()));
  sprites.emplace_back(
    SpriteComponent(renderer, "data/images/ui/textbox/yellow/um.png", ASGE::Point2D()));
  sprites.emplace_back(
    SpriteComponent(renderer, "data/images/ui/textbox/yellow/ur.png", ASGE::Point2D()));
}
void SpriteScene::render(ASGE::Renderer* renderer)
{
  for (auto& sprite : sprites)
  {
    sprite.render(renderer);
  }
}
