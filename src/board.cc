#include "board.h"

Board::Board()
{
  w_cell = 0;
  h_cell = 0;
}

Board::~Board()
{
}

void Board::initBoard(uint32_t b_width, uint32_t b_height)
{
  w_cell = b_width / x_cell;
  h_cell = b_height / y_cell;
 


  for (int j = 0; j< y_cell; ++j)  {
    for(int i = 0; i< x_cell; ++i){
      int n = i + j * x_cell;
      rect_[n].setSize(sf::Vector2f(w_cell, h_cell));
      rect_[n].setOutlineColor(sf::Color::White);
      rect_[n].setFillColor(sf::Color::Transparent);
      rect_[n].setOutlineThickness(2);

      rect_[n].setPosition(sf::Vector2f(i * w_cell, j * h_cell));
    }
  }
  
}


