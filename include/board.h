#ifndef __BOARD_H__
#define __BOARD_H__ 1

#include <stdint.h>
#include "SFML/Graphics.hpp"

const int kBoardMaxSize = 128;
const int kBoardMinSize = 16;
const int kBoardMaxUnits = 10;  // EVEN PLEASE

enum TileType {
  //Non Walkables
  kTileType_Void = 0, 
  kTileType_Wall,
  //Walkables
  kTileType_Normal, 
  kTileType_Door, 
  kTileType_End, 
};

/**/


struct Cell{
  int value;
  int height;
};

class Board
{
  public:

    Board();
    ~Board();
   
    void initBoard(int width = kBoardMaxSize/4, int height = kBoardMaxSize / 4);
    void initUnits();
    
    //Utils row,col to index and viceversa
    void index2RowCol(int *row, int *col, int id);
    void rowcol2Index(int  row, int  col, int *id);

    //Return the cell with row and col you tell
    Cell& cell(int row, int col);
    // Return the index of a cell
    int north(int id);
    int south(int id);
    int west(int id);
    int east(int id);
    int randomWalkableCell();
    //Return true if the type of the cell is the same that the one you give
    uint8_t cellType(int id, int cell_type);

    bool checkUnitMovement(int unit_id, int id_origin_cell, int id_end_cell);
    void moveUnit(int unit_id, int id_origin_cell, int id_end_cell);
    void checkAndMove(int unit_id, int id_origin_cell, int id_end_cell);
    void killUnit(int target_idx);

    void randomMove();

    void drawLBoard(sf::RenderWindow* window);
    void drawBoard(sf::RenderWindow* window);


    Cell cell_[kBoardMaxSize * kBoardMaxSize];
    int units_[kBoardMaxSize * kBoardMaxSize];
    int width_;
    int height_;

    int width_tile_;
    int height_tile_;
    int desp_x_tile_;
    int desp_y_tile_;

    sf::Texture mt;
    sf::Sprite board_sprite;

    sf::Texture agent_t_;
    sf::Sprite agent_s_;
  protected:
   
  private:
};

#endif //__BOARD_H__