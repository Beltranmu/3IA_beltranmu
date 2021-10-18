


#ifndef __GAME_H__
#define __GAME_H__ 1

#include <stdint.h>
#include "SFML/Graphics.hpp"
#include "board.h"


class Game
{
  public:
    void mainLoop();
    Game();
    ~Game();
  protected:
   
    void init(uint32_t w_width, uint32_t w_height);
    void input();
    void update(float delta_time);
    void fixedUpdate(float fixed_delta_time);
    void draw();
    void end();
    
    //Window
    sf::RenderWindow w_;
    int32_t w_width_;
    int32_t w_height_;
  
    //Board
    Board board_;

    //Events
    sf::Event events_;

    //Texture
    sf::Texture tex_;
    sf::Sprite sprite_;

    //Shape
    sf::RectangleShape rect_;
    float x_;
    float y_;
    int mode_mov;

    float delta_time_;
    float fixed_delta_time_;
    int32_t fps;
    float second_per_frame_;
  private:
};

#endif //__GAME_H__