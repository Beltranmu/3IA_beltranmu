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
    cell_[col].value = 0;
  }
  // Init position of the players and agents
}

Cell& Board::cell(int row, int col){
  return cell_[row * width_ + col];
}

void Board::drawLogic(sf::RenderWindow* window){
  sf::RectangleShape rect;
  rect.setOutlineColor(sf::Color::Black);
  rect.setSize(sf::Vector2f(8.0f, 8.0f));

  for (int i = 0; i < width_ * height_; ++i) {
    //window->draw();
    rect.setFillColor(sf::Color::Red);
    if(cell_[i].value == kTileType_Normal){
      rect.setFillColor(sf::Color::Green);
    }
    int x = (i % width_) * 8;
    int y = (i / width_) * 8;
    rect.setPosition(sf::Vector2f(x, y));
    window->draw(rect);
  }
}


