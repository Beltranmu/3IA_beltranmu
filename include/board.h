#ifndef __BOARD_H__
#define __BOARD_H__ 1

#include <stdint.h>
#include "SFML/Graphics.hpp"

const int kBoardMaxSize = 128;
const int kBoardMinSize = 16;
//const int kBoardMaxUnits = 48;  // EVEN PLEASE

typedef enum TileType {
  //Non Walkables
  kTileType_Void = 0, 
  kTileType_Wall,
  //Walkables
  kTileType_Normal, 
  kTileType_Door, 
  kTileType_End, 
};

/**/


typedef struct Cell{
  int value;
  int height;
};

class Board
{
  public:

    Board();
    ~Board();
    int width_;
    int height_;
   
    void initBoard(int width = kBoardMaxSize/4, int height = kBoardMaxSize / 4);

    Cell& cell(int row, int col);

    Cell cell_[kBoardMaxSize * kBoardMaxSize];

    void drawLogic(sf::RenderWindow* window);
    void drawBoard(sf::RenderWindow* window);
  protected:
   
  private:
};

#endif //__BOARD_H__