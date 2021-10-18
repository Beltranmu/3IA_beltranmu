#include "game.h"
#include "SFML/System.hpp"


Game::Game(){
  delta_time_ = 0.0f;
 
  fixed_delta_time_ = fps.second_per_frame;

  fps.main_game = 60.0f;
  fps.input = 1.0f;
  fps.ai = -1.0f;
  fps.world = 1.0f;
  fps.draw = 10.0f;

  fps.second_per_frame = 1.0f/(float)fps.main_game;

}

Game::~Game() {

}
void Game::init(uint32_t w_width, uint32_t w_height) {

  w_width_ = w_width;
  w_height_ = w_height;
  w_.create(sf::VideoMode(w_width_, w_height_), "AI WINDOW");

  if(!tex_.loadFromFile("../../deps/textures/ricky.png")){
    printf("Imagen no cargada");
  }
  sprite_ = sf::Sprite(tex_);
  sprite_.setPosition(100, 100);

 

}
void Game::input() {
  
  while(w_.pollEvent(events_)){
    if(events_.type == sf::Event::Closed ||
       events_.key.code == sf::Keyboard::Escape){
      w_.close();
    }

    switch(events_.key.code){
      case sf::Keyboard::Num1 :
        fps.ai++;
        break;

      case sf::Keyboard::Num2 :
        fps.ai--;
        break;

      case sf::Keyboard::Num3 :
        break;

      case sf::Keyboard::Num4 :
        break;
    }
  }
}


void Game::update(float delta_time) {
  
}

void Game::fixedUpdate(float fixed_delta_time) {}


void Game::draw() {

  w_.draw(sprite_);
  
}

void Game::end() {


}

void Game::mainLoop(){

  init(800, 600);
 
  sf::Clock sec_clock, main_clock, ia_clock, input_clock;
  sf::Clock world_clock, draw_clock;
  int frames=0;
  while(w_.isOpen()){

    main_clock.restart();
    w_.clear(sf::Color(0, 0, 0, 255));

    if (input_clock.getElapsedTime().asSeconds() > 1.0f / fps.input) {
      input_clock.restart();
      input();
      printf("Input\n");
    }
   
    
    
    if(ia_clock.getElapsedTime().asSeconds() > 1.0f/fps.ai || fps.ai == -1.0f){
      ia_clock.restart();
      printf("AI\n");
    }

    if (world_clock.getElapsedTime().asSeconds() > 1.0f / fps.world) {
      world_clock.restart();
      update(delta_time_);
      printf("World\n");
    }

   
    if (draw_clock.getElapsedTime().asSeconds() > 1.0f / fps.draw) {
      draw_clock.restart();
      draw();
      printf("Draw\n");
    }

    
    w_.display();
   
   
    if (sec_clock.getElapsedTime().asSeconds() > 1.0f) {
      printf("frames: %d\n", frames);
      frames = 0;
      sec_clock.restart();
      
    }
    frames++;
    do {
     // printf("%f\n", main_clock.getElapsedTime().asSeconds());
    } while (main_clock.getElapsedTime().asSeconds() < fps.second_per_frame);
   
  }
  
  end();
}