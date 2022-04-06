#include "board.h"


Board::Board(){

  targetColD = 0;
  targetColI = 0;
  targetRowD = 0;
  targetRowI = 0;


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


  //Init Agents
  for(int c = 0; c <  kBoardMaxSize; ++c){
    units_[c].init(); // No units here;
    units_[c].currentPos = -1; // No units here;
    units_[c].agentID = c;
  }


  width_tile_  = 8;
  height_tile_ = 8;
  desp_x_tile_ = 4;
  desp_y_tile_ = 4;

  mt.loadFromFile("../../data/gfx/maps/map_03_960x704_layout ABGS.png");
  board_sprite = sf::Sprite(mt);

  agent_t_.loadFromFile("../../data/gfx/agents/allied_soldier.bmp");
  agent_s_ = sf::Sprite(agent_t_);

  agent_t2_.loadFromFile("../../data/gfx/agents/axis_soldier.bmp");
  agent_not_selected_ = sf::Sprite(agent_t2_);

  player_t.loadFromFile("../../data/gfx/agents/player.png");
  player_s = sf::Sprite(player_t);

}

void Board::initUnits(){

  for (int i = 0; i < kBoardMaxUnits; ++i) {

    int unit_pos = randomWalkableCell();
    units_[i].currentPos = unit_pos;

  }

  treasureLocation = randomWalkableCell();
  treasureLocation = 120 * 60;
  //Character
  units_[0].currentTarget = treasureLocation;
  units_[0].movementType = Agent::Movement::kMovement_Track;
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

void Board::checkAndMove(Agent* a, int id_end_cell){

  // Can move
  if(cell_[id_end_cell].value >= kTileType_Normal){
    //Need to be changed

    a->currentPos = id_end_cell;

    // Graphically move the unit
    //units_[id_origin_cell] = -1;

  }

}

void Board::checkForPlayer(uint32_t playerToSearch, Agent* e){
    
    units_[playerToSearch].been_chased = false;
  if(manhantanDistance(units_[playerToSearch].currentPos, e->currentPos) < e->distanceToCatch){
    e->movementType = Agent::Movement::kMovement_Track;
    e->currentTarget = units_[playerToSearch].currentPos;
    units_[playerToSearch].speed += 0.5f;
  }
  
}

void Board::killUnit(int target_idx){ units_[target_idx].currentPos = -1;}

void Board::unitMovement() {
  units_[0].speed = 1;
  for (int i = 0; i < kBoardMaxUnits; ++i) {

    units_[i].moveUnit(this);
  }
}

void Board::randomMove(){

//   for(int i = 0; i < kBoardMaxUnits; ++i){
// 
//     int mov = rand() % 4;
// 
//     int next_tile ;
// 
//     switch (mov) {
//       case 0:
//         next_tile = north(units_[i].currentPos);
//         break;
//       case 1:
//         next_tile = south(units_[i].currentPos);
//         break;
//       case 2:
//         next_tile = west(units_[i].currentPos);
//         break;
//       case 3:
//         next_tile = east(units_[i].currentPos);
//         break;
//     }
// 
//     checkAndMove(units_[i].currentPos, next_tile);
//   
//   }

}

int Board::pacmanMovement(int32_t org_cell, int32_t target_cell, int32_t* fwX, int32_t* fwY) {
  

  if(target_cell == org_cell){
    return-1;
  }
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
      
     return dst_desp;
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
    return dst_desp;
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

      if (euclideanDistance > euclidianDistance(target_cell, north(org_cell))) {
        euclideanDistance = euclidianDistance(target_cell, north(org_cell));

        *fwX = 0;
        *fwY = -1;
        dst_desp = 0;
      }
    }
    return dst_desp;
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

  for (int i = 0; i < kBoardMaxUnits; ++i) {

    int row = 0, col = 0;
    index2RowCol(&row, &col, units_[i].currentPos);
    float posx = col * width_tile_ + desp_x_tile_;
    float posy = row * height_tile_ + desp_y_tile_;
    agent_s_.setPosition(posx, posy);
    window->draw(agent_s_);

  }

}

void Board::drawBoard(sf::RenderWindow* window, int selected_cell){

  window->draw(board_sprite);

  for (int i = 0; i < kBoardMaxUnits; ++i) {

    int row = 0, col = 0;
    index2RowCol(&row, &col, units_[i].currentPos);
    float posx = col * width_tile_ + desp_x_tile_;
    float posy = row * height_tile_ + desp_y_tile_;
    agent_s_.setPosition(posx, posy);
    if (i > 0) {
      if (!units_[i].agentSelected) {
        window->draw(agent_s_);
      }
      else {
        agent_not_selected_.setPosition(posx, posy);
        window->draw(agent_not_selected_);
      }
    }
    else{
      player_s.setPosition(posx, posy);
      window->draw(player_s);
    }
//     Draw forward
//         int r_forward = 0;
//         int c_forward = 0;
//         if(units_[i].currentForwardX == 0){
//           if(units_[i].currentForwardY == 1){//South
//             index2RowCol(&r_forward, &c_forward, south(units_[i].currentPos));
//           }else{ //North
//             index2RowCol(&r_forward, &c_forward, north(units_[i].currentPos));
//           }
//         }
//         else if(units_[i].currentForwardX == 1){
//           index2RowCol(&r_forward, &c_forward, east(units_[i].currentPos));
//         }
//         else{
//           index2RowCol(&r_forward, &c_forward, west(units_[i].currentPos));
//         }
//         sf::RectangleShape rect;
//         rect.setOutlineColor(sf::Color::Blue);
//         rect.setFillColor(sf::Color::Blue);
//         rect.setSize(sf::Vector2f(10.0f, 10.0f));
//     
//         int x = c_forward * 8;
//         int y = r_forward * 8;
//     
//         rect.setPosition(sf::Vector2f(x, y));
//         window->draw(rect);
  }
  if (selected_cell >= 0) {
    sf::RectangleShape rect;
    rect.setOutlineColor(sf::Color::Green);
    rect.setFillColor(sf::Color::Green);
    rect.setSize(sf::Vector2f(8.0f, 8.0f));

    int x = (selected_cell % width_) * 8;
    int y = (selected_cell / width_) * 8;

    rect.setPosition(sf::Vector2f(x, y));
    window->draw(rect);
  }

  //Draw Treasure

  sf::RectangleShape treasure;
  treasure.setOutlineColor(sf::Color::Red);
  treasure.setFillColor(sf::Color::Red);
  treasure.setSize(sf::Vector2f(8.0f, 8.0f));

  int xt = (treasureLocation % width_) * 8;
  int yt = (treasureLocation / width_) * 8;

  treasure.setPosition(sf::Vector2f(xt, yt));
  window->draw(treasure);



  //Draw Origin and destination for the A*
  sf::RectangleShape origin;
  sf::RectangleShape destination;


  origin.setOutlineColor(sf::Color::Green);
  origin.setFillColor(sf::Color::Green);
  origin.setSize(sf::Vector2f(8.0f, 8.0f));

  destination.setOutlineColor(sf::Color::Red);
  destination.setFillColor(sf::Color::Red);
  destination.setSize(sf::Vector2f(8.0f, 8.0f));

  int xo = targetColI * 8;
  int yo = targetRowI * 8;
  int xd = targetColD * 8;
  int yd = targetRowD * 8;

  origin.setPosition(sf::Vector2f(xo, yo));
  destination.setPosition(sf::Vector2f(xd, yd));
  window->draw(origin);
  window->draw(destination);

  //**Draw Path for A*
  for (int p = 0; p < aPath_.currentPaths.size(); ++p) {

    if(aPath_.currentPaths[p].draw){
      for(int c = 0; c < (int) aPath_.currentPaths[p].path.size(); ++c){
        sf::RectangleShape cellPath;
        cellPath.setOutlineColor(sf::Color::Black);
        cellPath.setFillColor(aPath_.pathColors[aPath_.currentPaths[p].type]);
        cellPath.setSize(sf::Vector2f(8.0f, 8.0f));

        int xc = (aPath_.currentPaths[p].path[c] % width_) * 8;
        int yc = (aPath_.currentPaths[p].path[c] / width_) * 8;

        cellPath.setPosition(sf::Vector2f(xc, yc));
        window->draw(cellPath);
      }
    }

  }
   
}

uint32_t Board::manhantanDistance(int32_t origin_cell, int32_t dst_cell){
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


uint32_t Board::chebyshovDistance(int32_t origin_cell, int32_t dst_cell){
  int r1, r2, c1, c2;
  index2RowCol(&r1, &c1, origin_cell);
  index2RowCol(&r2, &c2, dst_cell);
  uint32_t dr = abs(r2 - r1);
  uint32_t dc = abs(c2 - c1);
  return  dr > dc ? dr : dc ;
}

int32_t Board::getAgent(sf::RenderWindow& window) {

  sf::Vector2i mousePosition = sf::Mouse::getPosition(window);

  int mpX = mousePosition.x / 8;
  int mpY = mousePosition.y / 8;

  int32_t cell = -1;

  rowcol2Index(mpY, mpX, &cell);

  int32_t tmpAgentID = -1;

  for(int i = 0; i < kBoardMaxUnits; ++i){

    if(north(west(units_[i].currentPos)) == cell || north(units_[i].currentPos) == cell || north(east(units_[i].currentPos)) == cell ||
       west(units_[i].currentPos) == cell || units_[i].currentPos == cell || east(units_[i].currentPos) == cell ||
       south(west(units_[i].currentPos)) == cell || south(units_[i].currentPos) == cell || south(east(units_[i].currentPos)) == cell){

      units_[i].agentSelected = true;
      tmpAgentID = i;

    }else{

      units_[i].agentSelected = false;

    }

  }
  
  return tmpAgentID;

}