#include "board.h"

Board::Board(){

}

Board::~Board(){
}

void Board::initBoard(int width, int height){

  width_ = width;
  height_ = height;

  for (int col = 0; col < kBoardMaxSize * kBoardMaxSize; ++col){
    cell_[col].height = 0;
    cell_[col].value = kTileType_Void;
    units_[col] = -1; // No units here;
  } 

  width_tile_  = 8;
  height_tile_ = 8;
  desp_x_tile_ = 4;
  desp_y_tile_ = 4;

  mt.loadFromFile("../../data/gfx/maps/map_03_960x704_layout ABGS.png");
  board_sprite = sf::Sprite(mt);

  agent_t_.loadFromFile("../../data/gfx/agents/allied_soldier.bmp");
  agent_s_ = sf::Sprite(agent_t_);

}

void Board::initUnits(){

  for (int i = 0; i < kBoardMaxUnits; ++i) {

    int unit_pos = randomWalkableCell();
    units_[i] = unit_pos;

  }

}

void Board::index2RowCol(int* row, int* col, int id){

  *row = id / width_;
  *col = id % width_;

}

void Board::rowcol2Index(int row, int col, int* id){ *id = row * width_ + col;}

Cell& Board::cell(int row, int col){ return cell_[row * width_ + col];}

int Board::north(int id){

  int col =0;
  int row =0;

  index2RowCol(&row, &col, id);

  //Not on the first row
  if(0 != row)
    id -= width_;

  return id;
}

int Board::south(int id){

  int col = 0;
  int row = 0;

  index2RowCol(&row, &col, id);

  //Not on the last row
  if ((height_-1) != row)
    id += width_;

  return id;
}

int Board::west(int id){

  int col = 0;
  int row = 0;

  index2RowCol(&row, &col, id);
  
  //Not on the first column
  if (0 != col)
    --id;

  return id;
}


int Board::east(int id){
  
  int col = 0;
  int row = 0;
  
  index2RowCol(&row, &col, id);
  
  //Not on the last column
  if ((width_ - 1) != col)
    id++;

  return id;
}

int Board::randomWalkableCell(){

  int rc = rand()%(width_ * height_);

  while (cell_[rc].value < kTileType_Normal) { rc = rand()%(width_ * height_);}

  return rc;
}


uint8_t Board::cellType(int id, int cell_type){ return cell_[id].value == cell_type;}

void Board::checkAndMove(int unit_id, int id_origin_cell, int id_end_cell){

  // Can move
  if(cell_[id_end_cell].value >= kTileType_Normal){

    units_[unit_id] = id_end_cell;
    // Graphically move the unit
    //units_[id_origin_cell] = -1;

  }

}

void Board::killUnit(int target_idx){ units_[target_idx] = -1;}

void Board::randomMove(){

  for(int i = 0; i < kBoardMaxUnits; ++i){

    int mov = rand() % 4;
    int next_tile ;

    switch (mov) {
      case 0:
        next_tile = north(units_[i]);
        break;
      case 1:
        next_tile = south(units_[i]);
        break;
      case 2:
        next_tile = west(units_[i]);
        break;

      case 3:
        next_tile = east(units_[i]);
        break;
    }

    checkAndMove(i, units_[i], next_tile);
  
  }

}

void Board::drawLBoard(sf::RenderWindow* window){

  sf::RectangleShape rect;
  rect.setOutlineColor(sf::Color::Black);
  rect.setSize(sf::Vector2f(8.0f, 8.0f));

  for (int i = 0; i < width_ * height_; ++i) {

    //window->draw();
    rect.setFillColor(sf::Color::Red);
    if(cell_[i].value == kTileType_Normal)
      rect.setFillColor(sf::Color::Green);

    int x = (i % width_) * 8;
    int y = (i / width_) * 8;

    rect.setPosition(sf::Vector2f(x, y));
    window->draw(rect);

  }

}

void Board::drawBoard(sf::RenderWindow* window){

  window->draw(board_sprite);

  for(int i = 0; i < kBoardMaxUnits; ++i){

    int row = 0, col = 0;
    index2RowCol(&row, &col, units_[i]);
    float posx = col * width_tile_ + desp_x_tile_;
    float posy = row * height_tile_ + desp_y_tile_;
    agent_s_.setPosition(posx, posy);
    window->draw(agent_s_);

  }
   
}


