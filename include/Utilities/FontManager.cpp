//
// Created by hewis on 20/02/2021.
//

#include "FontManager.h"
#include <Engine/FileIO.h>
#include <iostream>
int FontManager::loadFont(ASGE::Renderer* renderer, const std::string& file_path, int font_size)
{
  ASGE::FILEIO::File font_file = ASGE::FILEIO::File();
  if (font_file.open(file_path))
  {
    ASGE::FILEIO::IOBuffer file_buffer = font_file.read();
    if (file_buffer.length != 0U)
    {
      return renderer->loadFontFromMem(
        file_path.c_str(),
        file_buffer.as_unsigned_char(),
        static_cast<unsigned int>(file_buffer.length),
        font_size);
    }
  }
  return -1;
}
void FontManager::loadFonts(ASGE::Renderer* renderer)
{
  loadFont(renderer, "data/fonts/sriracha.ttf", 32);
  loadFont(renderer, "data/fonts/kanit.ttf", 72);
  loadFont(renderer, "data/fonts/playfair.ttf", 24);
  loadFont(renderer, "data/fonts/comic.ttf", 32);
}
