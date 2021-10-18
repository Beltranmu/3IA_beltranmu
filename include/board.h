


#ifndef __BOARD_H__
#define __BOARD_H__ 1

#include <stdint.h>
#include "SFML/Graphics.hpp"

class Board
{
  public:

    Board();
    ~Board();

    const uint32_t x_cell = 8;
    const uint32_t y_cell = 6;
    uint32_t w_cell ;
    uint32_t h_cell ;
    sf::RectangleShape rect_[8 * 6];
    void initBoard(uint32_t b_width, uint32_t b_height);
  protected:
   
  private:
};

#endif //__GAME_H__