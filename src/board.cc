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
  }
  for(int c = 0; c <  kBoardMaxSize; ++c){
    units_[c].init(); // No units here;
    units_[c].currentPos = -1; // No units here;
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
    units_[i].currentPos = unit_pos;

  }

}

void Board::index2RowCol(int* row, int* col, int id){

  *row = id / width_;
  *col = id % width_;

}

void Board::rowcol2Index(int row, int col, int* id){ *id = row * width_ + col;}

Cell& Board::cell(int row, int col){ return cell_[row * width_ + col];}

int Board::north(int id){

  int col = 0;
  int row = 0;

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

bool Board::checkUnitMovement(int id_end_cell) {
  return (cell_[id_end_cell].value >= kTileType_Normal);
}

void Board::checkAndMove(int unit_id, int id_origin_cell, int id_end_cell){

  // Can move
  if(cell_[id_end_cell].value >= kTileType_Normal){

    units_[unit_id].currentPos = id_end_cell;

    // Graphically move the unit
    //units_[id_origin_cell] = -1;

  }

}

void Board::killUnit(int target_idx){ units_[target_idx].currentPos = -1;}

void Board::unitMovement() {
  for (int i = 0; i < kBoardMaxUnits; ++i) {
    int mov = 0;
    int next_tile;
    bool will_move = false;

    switch (units_[i].movementType) {
      case Agent::kMovement_Random: mov = rand() % 4;  will_move = true; break;;
      case Agent::kMovement_Pattern: mov = units_[i].patternMov(&will_move); break;
      case Agent::kMovement_Track: mov = pacmanMovement(units_[i].currentPos, 
      units_[i].currentTarget,
      &units_[i].currentForwardX,
        &units_[i].currentForwardY);/*units_[i].trackMov();*/
        will_move = true; 
        break;
    }
    if (will_move) {
      switch (mov) {
      case 0:
        next_tile = north(units_[i].currentPos);
        break;
      case 1:
        next_tile = south(units_[i].currentPos);
        break;
      case 2:
        next_tile = west(units_[i].currentPos);
        break;
      case 3:
        next_tile = east(units_[i].currentPos);
        break;
      }

      checkAndMove(i, units_[i].currentPos, next_tile);
    }
  }
}

void Board::randomMove(){

  for(int i = 0; i < kBoardMaxUnits; ++i){

    int mov = rand() % 4;

    int next_tile ;

    switch (mov) {
      case 0:
        next_tile = north(units_[i].currentPos);
        break;
      case 1:
        next_tile = south(units_[i].currentPos);
        break;
      case 2:
        next_tile = west(units_[i].currentPos);
        break;
      case 3:
        next_tile = east(units_[i].currentPos);
        break;
    }

    checkAndMove(i, units_[i].currentPos, next_tile);
  
  }

}

int Board::pacmanMovement(int32_t org_cell, int32_t target_cell, int32_t* fwX, int32_t* fwY) {
  
  float euclideanDistance = 99999.f;
  int dst_desp = 0;
  // South
  if(*fwX == 0 && *fwY == 1){
    if(checkUnitMovement(south(org_cell))){

      euclideanDistance = euclidianDistance(target_cell, south(org_cell));
      dst_desp = 1;
    }
    if (checkUnitMovement(east(org_cell))) {

      if(euclideanDistance > euclidianDistance(target_cell, east(org_cell))){
        euclideanDistance = euclidianDistance(target_cell, east(org_cell));

        *fwX = 1;
        *fwY = 0;
        dst_desp = 3;
      }

    }
    if (checkUnitMovement(west(org_cell))) {

      if (euclideanDistance > euclidianDistance(target_cell, west(org_cell))){
        euclideanDistance = euclidianDistance(target_cell, west(org_cell));

        *fwX = -1;
        *fwY = 0;
        dst_desp = 2;
      }

    }
  }

  // North
  if (*fwX == 0 && *fwY == -1) {
    if (checkUnitMovement(north(org_cell))) {

      euclideanDistance = euclidianDistance(target_cell, north(org_cell));
      dst_desp = 0;
    }
    if (checkUnitMovement(east(org_cell))) {

      if (euclideanDistance > euclidianDistance(target_cell, east(org_cell))) {
        euclideanDistance = euclidianDistance(target_cell, east(org_cell));

        *fwX = 1;
        *fwY = 0;
        dst_desp = 3;
      }

    }
    if (checkUnitMovement(west(org_cell))) {

      if (euclideanDistance > euclidianDistance(target_cell, west(org_cell))) {
        euclideanDistance = euclidianDistance(target_cell, west(org_cell));

        *fwX = -1;
        *fwY = 0;
        dst_desp = 2;
      }

    }
  }

  // East
  if (*fwX == 1 && *fwY == 0) {
    if (checkUnitMovement(east(org_cell))) {

      euclideanDistance = euclidianDistance(target_cell, east(org_cell));
      dst_desp = 3;
    }
    if (checkUnitMovement(south(org_cell))) {

      if (euclideanDistance > euclidianDistance(target_cell, south(org_cell))) {
        euclideanDistance = euclidianDistance(target_cell, south(org_cell));

        *fwX = 0;
        *fwY = 1;
        dst_desp = 1;
      }

    }
    if (checkUnitMovement(north(org_cell))) {

      if (euclideanDistance > euclidianDistance(org_cell, north(org_cell))) {
        euclideanDistance = euclidianDistance(org_cell, north(org_cell));

        *fwX = 0;
        *fwY = -1;
        dst_desp = 0;
      }

    }
  }

  // West
  if (*fwX == -1 && *fwY == 0) {
    if (checkUnitMovement(west(org_cell))) {

      euclideanDistance = euclidianDistance(target_cell, west(org_cell));
      dst_desp = 2;
    }
    if (checkUnitMovement(south(org_cell))) {

      if (euclideanDistance > euclidianDistance(target_cell, south(org_cell))) {
        euclideanDistance = euclidianDistance(target_cell, south(org_cell));

        *fwX = 0;
        *fwY = 1;
        dst_desp = 1;
      }

    }
    if (checkUnitMovement(north(org_cell))) {

      if (euclideanDistance > euclidianDistance(target_cell, north(org_cell))) {
        euclideanDistance = euclidianDistance(target_cell, north(org_cell));

        *fwX = 0;
        *fwY = -1;
        dst_desp = 0;
      }

    }
  }
   return dst_desp;
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
    index2RowCol(&row, &col, units_[i].currentPos);
    float posx = col * width_tile_ + desp_x_tile_;
    float posy = row * height_tile_ + desp_y_tile_;
    agent_s_.setPosition(posx, posy);
    window->draw(agent_s_);

  }
   
}

int32_t Board::manhantanDistance(int32_t origin_cell, int32_t dst_cell){
  int r1, r2, c1, c2;
  index2RowCol(&r1, &c1, origin_cell);
  index2RowCol(&r2, &c2, dst_cell);

  return (abs(r2 - r1) + abs(c2 - c1));
}

float Board::euclidianDistance(int32_t origin_cell, int32_t dst_cell){
  int r1, r2, c1, c2;
  index2RowCol(&r1, &c1, origin_cell);
  index2RowCol(&r2, &c2, dst_cell);

  int dx = (r2 - r1) * width_tile_;
  int dy = (c2 - c1) * height_tile_;
  
  return sqrt(dx * dx + dy * dy);
}