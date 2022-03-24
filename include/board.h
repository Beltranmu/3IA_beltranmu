#ifndef __BOARD_H__
#define __BOARD_H__ 1

#include <stdint.h>
#include "SFML/Graphics.hpp"
#include "agent.h"
#include "astar.h"

const int kBoardMaxSize = 128;
const int kBoardMinSize = 16;
const int kBoardMaxUnits = 10;  // EVEN PLEASE

enum TileType {
  //Non-Walkables
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

    bool checkUnitMovement(int id_end_cell);
    //void moveUnit(int unit_id, int id_origin_cell, int id_end_cell);
    void checkAndMove(Agent* a, int id_end_cell);
    void checkForPlayer(uint32_t playerToSearch, Agent* e); ///> true if there is a player near otherwise false
    void killUnit(int target_idx);

    void unitMovement();
    void randomMove();
    int pacmanMovement(int32_t org_cell, int32_t target_cell, int32_t* fwX, int32_t* fwY);

    void drawLBoard(sf::RenderWindow* window);
    void drawBoard(sf::RenderWindow* window, int selected_cell);

    int32_t manhantanDistance(int32_t origin_cell, int32_t dst_cell);
    float euclidianDistance(int32_t origin_cell, int32_t dst_cell);

    int32_t getAgent(sf::RenderWindow& window);

    Cell cell_[kBoardMaxSize * kBoardMaxSize];
    Agent units_[kBoardMaxSize];

    int32_t treasureLocation;

    Astar aPath_;

    int width_;
    int height_;

    int width_tile_;
    int height_tile_;
    int desp_x_tile_;
    int desp_y_tile_;



    int32_t targetRowI;
    int32_t targetColI;
    int32_t targetRowD;
    int32_t targetColD;


    sf::Texture mt;
    sf::Sprite board_sprite;

    sf::Texture agent_t_;
    sf::Sprite agent_s_;
    sf::Texture agent_t2_;
    sf::Sprite agent_not_selected_;

    sf::Texture player_t;
    sf::Sprite player_s;

  protected:
   
  private:
};

#endif //__BOARD_H__