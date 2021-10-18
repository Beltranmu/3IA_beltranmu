#include "game.h"
#include "SFML/System.hpp"


Game::Game(){
  delta_time_ = 0.0f;
  //fixed_delta_time_ = 0.0f;
  fps = 60;
  second_per_frame_ = 1.0f/(float)fps;
  fixed_delta_time_ = second_per_frame_;
}

Game::~Game() {

}
void Game::init(uint32_t w_width, uint32_t w_height) {

  w_width_ = w_width;
  w_height_ = w_height;
  w_.create(sf::VideoMode(w_width_, w_height_), "AI WINDOW");
  board_.initBoard(w_width_, w_height_);

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
    if(events_.type == sf::Event::Closed ||
       events_.key.code == sf::Keyboard::Escape){
      w_.close();
    }

    switch(events_.key.code){
      case sf::Keyboard::A :
        mode_mov = 1;
        break;

      case sf::Keyboard::D:
        mode_mov = 2;
        break;

      case sf::Keyboard::W:
        mode_mov = 3;
        break;

      case sf::Keyboard::S:
        mode_mov = 4;
        break;
     
    }
  }
}


void Game::update(float delta_time) {
  float des_x = 0;
  float des_y = 0;
  const float desp = 5000.0f;
  switch (mode_mov) {
  case 1:
    des_x = -desp;
    break;

  case 2: 
    des_x = desp;
    break;

  case 3:
    des_y = -desp;
    break;

  case 4:
    des_y = desp;
    break;
  }

  x_ += (des_x * delta_time);
  y_ += (des_y * delta_time);
  rect_.setPosition(sf::Vector2f(x_, y_ ));
  mode_mov = 0;
}

void Game::fixedUpdate(float fixed_delta_time) {}


void Game::draw() {

  w_.draw(rect_);
  //w_.draw(sprite_);
  int n = board_.x_cell * board_.y_cell;

  for (int i = 0; i < n; ++i) {
    w_.draw(board_.rect_[i]);
  }
}

void Game::end() {


}

void Game::mainLoop(){

  init(800, 600);
 
  sf::Time t1, t2;
  sf::Clock sec_clock, main_clock;
  int frames=0;
  while(w_.isOpen()){
    main_clock.restart();
    delta_time_ = main_clock.getElapsedTime().asSeconds();
  
    w_.clear(sf::Color(0, 0, 0, 255));
    input();
    printf("T1 : %f\n", t1.asSeconds());
    delta_time_ = (main_clock.getElapsedTime()).asSeconds();
    
    
    update(delta_time_);
  

    main_clock.restart();
    do{
      fixedUpdate(fixed_delta_time_);
    } while (main_clock.getElapsedTime().asSeconds() < fixed_delta_time_);

    draw();

    frames++;
    if(sec_clock.getElapsedTime().asSeconds() > 1.0f){
      printf("frames: %d\n", frames);
      frames = 0;
      sec_clock.restart();
    }
    w_.display();
  }
  
  end();
}