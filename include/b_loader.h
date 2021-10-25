#ifndef __B_LOADER_H__
#define __B_LOADER_H__ 1

//#include <stdint.h>
#include "SFML/Graphics.hpp"
#include "board.h"

static void BoardFromImage(Board* board, const char* filename)  {
  if (nullptr == filename) { /*return kErrorCode_SRCNullPointer; */}
  if (nullptr == board) {/*return kErrorCode_DataNullPointer;*/ }
  sf::Texture tex;
  sf::Sprite sprite;
 
  if (!tex.loadFromFile(filename)) {
    printf("Imagen no cargada");
  }
  sprite = sf::Sprite(tex);
  int t_width = tex.getSize().x;
  int t_height = tex.getSize().y;

  board->initBoard(t_width, t_height);

  sf::Color pixelColor(0);
  for (int col = 0; col < t_width; ++col) {
    for (int row = 0; row < t_height; ++row) {
      pixelColor = tex.copyToImage().getPixel(col, row);
     

      //White
      if ((pixelColor.r == 0xFF) &&
          (pixelColor.g == 0xFF) &&
          (pixelColor.b == 0xFF)) {
        board->cell(row, col).value = kTileType_Normal;
      }
      //Black
      else if ((pixelColor.r == 0x00) &&
               (pixelColor.g == 0x00) &&
               (pixelColor.b == 0x00)) {
        board->cell(row, col).value = kTileType_Wall;
      }
      else {
        board->cell(row, col).value = kTileType_Wall;
      }
    }
  }
  board->initUnits();
}

#endif //__B_LOADER_H__