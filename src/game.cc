#include "game.h"
#include "imgui.h"
#include "imgui-SFML.h"
#include "SFML/System.hpp"
#include "b_loader.h"

Game::Game(){
  delta_time_ = 0.0f;
 
  fixed_delta_time_ = fps.second_per_frame;

  fps.main_game = 60.0f;
  fps.input = 1.0f;
  fps.ai = 1.0f;
  fps.world = 1.0f;
  fps.draw = -1.0f;

  fps.second_per_frame = 1.0f/(float)fps.main_game;

}

Game::~Game() {

}

void Game::init(uint32_t w_width, uint32_t w_height) {

  w_width_ = w_width;
  w_height_ = w_height;
  w_.create(sf::VideoMode(w_width_, w_height_), "AI WINDOW");
  srand(time(NULL));
  if(!tex_.loadFromFile("../../data/textures/ricky.png")){
    printf("Imagen no cargada");
  }
  sprite_ = sf::Sprite(tex_);
  sprite_.setPosition(100, 100);
  ImGui::SFML::Init(w_);

  map_texture_.loadFromFile("../../data/gfx/maps/map_03_960x704_layout ABGS.png");
  map_sprite_ = sf::Sprite(map_texture_);
  //Board
  BoardFromImage(&board_, "../../data/gfx/maps/map_03_120x88_cost.png");
  

}
void Game::input() {
  
  while(w_.pollEvent(events_)){
    ImGui::SFML::ProcessEvent(events_);

    if(events_.type == sf::Event::Closed ||
       events_.key.code == sf::Keyboard::Escape){
      w_.close();
    }

    
  }
}


void Game::update(float delta_time) {
  
}

void Game::fixedUpdate(float fixed_delta_time) {}


void Game::draw() {

  //w_.draw(sprite_);
  //board_.drawLBoard(&w_);
  //w_.draw(map_sprite_);
  board_.drawBoard(&w_);
  
}

void Game::end() {

  ImGui::SFML::Shutdown();
}

void Game::mainLoop(){

  init(960, 704);
  //float my_values[3];
  sf::Clock sec_clock, main_clock, ia_clock, input_clock;
  sf::Clock world_clock, draw_clock, imgui_clock;
  int frames=0;
  int imguifps = 0;
  while(w_.isOpen()){

    main_clock.restart();

    if (input_clock.getElapsedTime().asSeconds() > 1.0f / fps.input ||
        fps.input == -1.0f) {
      input_clock.restart();
      input();
      //printf("Input\n");
    }
   
    if(ia_clock.getElapsedTime().asSeconds() > 1.0f/fps.ai || 
       fps.ai == -1.0f){
      ia_clock.restart();
      board_.randomMove();
    }

    if (world_clock.getElapsedTime().asSeconds() > 1.0f / fps.world|| 
        fps.world == -1.0f) {
      world_clock.restart();
      update(delta_time_);
      //printf("World\n");
    }

    ImGui::SFML::Update(w_, imgui_clock.restart());
    ImGui::Begin("HOLAAA");
 
    ImGui::TextColored(ImVec4(1, 1, 1, 1),"FPS panel");
    ImGui::TextColored(ImVec4(1, 0, 1, 1),"FPS:%d", imguifps);
    ImGui::SliderFloat("Input", &fps.input, -1.0f, 60.0f);
    ImGui::SliderFloat("AI", &fps.ai, -1.0f, 60.0f);
    ImGui::SliderFloat("World", &fps.world, -1.0f, 60.0f);
    ImGui::SliderFloat("Draw", &fps.draw, -1.0f, 61.0f);
   


    ImGui::End();



    //Draw
    w_.clear(sf::Color(0, 0, 0, 255));
    if (draw_clock.getElapsedTime().asSeconds() > 1.0f / fps.draw || 
        fps.draw == -1.0f) {
      draw_clock.restart();
      draw();
      //printf("Draw\n");
    }

   
    ImGui::SFML::Render(w_);
    w_.display();
   
   
    if (sec_clock.getElapsedTime().asSeconds() > 1.0f ) {
      printf("frames: %d\n", frames);
      imguifps = frames;
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