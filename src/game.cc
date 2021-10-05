#include "game.h"
#include "SFML/System.hpp"


Game::Game(){
  delta_time_ = 0.0f;
  fixed_delta_time_ = 0.0f;
  fps = 60;
  second_per_frame_ = 1.0f/(float)fps;
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

  rect_.setSize(sf::Vector2f(100,100));
  rect_.setOutlineColor(sf::Color::Red);
  rect_.setFillColor(sf::Color::Cyan);
  rect_.setOutlineThickness(2);
  x_ = 100;
  y_ = 100;
  rect_.setPosition(sf::Vector2f(x_, y_));

}
void Game::input() {
  
  while(w_.pollEvent(events_)){
    if(events_.type == sf::Event::Closed){
      w_.close();
    }
  }
}


void Game::update(float delta_time) {
 

}

void Game::fixedUpdate(float fixed_delta_time) {}


void Game::draw() {

  w_.draw(sprite_);
  w_.draw(rect_);
}

void Game::end() {


}

void Game::mainLoop(){

  init(800, 600);
 
  sf::Time t1, t2;
  sf::Clock main_clock;
  while(w_.isOpen()){
    main_clock.restart();
    t1 = main_clock.getElapsedTime();
    w_.clear(sf::Color(0, 0, 0, 255));
    input();
    delta_time_ = (t1 - main_clock.getElapsedTime()).asSeconds();
    
    
    //main_clock.restart();
    

    update(delta_time_);
    fixedUpdate(fixed_delta_time_);
    draw();

  
    w_.display();
  }
  
  end();
}