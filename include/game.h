


#ifndef __GAME_H__
#define __GAME_H__ 1

#include <stdint.h>
#include "SFML/Graphics.hpp"

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
      float main_game;
      float world;
      float input;
      float draw;
      float ai;
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


    float delta_time_;
    float fixed_delta_time_;
 
  private:
};

#endif //__GAME_H__