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
    
    //FrameControl
    struct FramesPerModule {
      int main_game;
      int world;
      int input_;
      int draw_;
      int ai;
      float second_per_frame;
    };

    FramesPerModule fps;

    //Window
    sf::RenderWindow w_;
    int32_t w_width_;
    int32_t w_height_;

    //Events
    sf::Event events_;

    //Texture
    sf::Texture tex_;
    sf::Sprite sprite_;

    
    //Board
    Board board_;
    sf::Texture map_texture_;
    sf::Sprite map_sprite_;

    float delta_time_;
    float fixed_delta_time_;
 
  private:
};

#endif //__GAME_H__