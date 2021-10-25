#ifndef __B_LOADER_H__
#define __B_LOADER_H__ 1

#include "SFML/Graphics.hpp"
#include "board.h"

typedef enum {
  kErrorCode_SRCNullPointer,
  kErrorCode_DataNullPointer,
  kErrorCode_File
} ErrorCode;

static ErrorCode BoardFromImage(Board* board, const char* filename)  {

  if (nullptr == filename) return kErrorCode_SRCNullPointer;
  if (nullptr == board) return kErrorCode_DataNullPointer;

  sf::Image boardImage;
 
  if (!boardImage.loadFromFile(filename)) return kErrorCode_File;

  sf::Vector2u imageSize = boardImage.getSize();
  sf::Color pixelColor(0);

  int t_width = imageSize.x;
  int t_height = imageSize.y;

  board->initBoard(t_width, t_height);

  for (int col = 0; col < t_width; ++col) {
    for (int row = 0; row < t_height; ++row) {

      pixelColor = boardImage.getPixel(col, row);     

      //White
      if (pixelColor == sf::Color::White){
        board->cell(row, col).value = kTileType_Normal;
      }
      //Black
      else if (pixelColor == sf::Color::Black) {
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