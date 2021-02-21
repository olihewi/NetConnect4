//
// Created by hewis on 20/02/2021.
//

#ifndef ASGENETGAME_FONTMANAGER_H
#define ASGENETGAME_FONTMANAGER_H

#include <Engine/Renderer.h>
#include <string>
class FontManager
{
 public:
  int loadFont(ASGE::Renderer* renderer, const std::string& file_path, int font_size);
  void loadFonts(ASGE::Renderer* renderer);
};
namespace FONTS
{
  constexpr int HANDWRITING  = 1;
  constexpr int TITLING      = 2;
  constexpr int FANCY        = 3;
  constexpr int COMIC_SANS   = 4;
  constexpr int CHAT_MESSAGE = 5;
}

#endif // ASGENETGAME_FONTMANAGER_H
