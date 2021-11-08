#include "game.h"
#include "imgui.h"
#include "imgui-SFML.h"
#include "SFML/System.hpp"
#include "b_loader.h"

Game::Game(){

  delta_time_ = 0.0f;
 
  fixed_delta_time_ = fps.second_per_frame;

  fps.main_game = 60;
  fps.input_ = 1;
  fps.ai = 1;
  fps.world = 1;
  fps.draw_ = -1;

  fps.second_per_frame = 1/(float)fps.main_game;

}

Game::~Game() {

}

void Game::init(uint32_t w_width, uint32_t w_height) {

  w_width_ = w_width;
  w_height_ = w_height;
  w_.create(sf::VideoMode(w_width_, w_height_), "AI WINDOW");
  srand(time(NULL));

  if(!tex_.loadFromFile("../../data/textures/ricky.png")){
    printf("Failed to load image\n");
  }

  sprite_ = sf::Sprite(tex_);
  sprite_.setPosition(100, 100);
  ImGui::SFML::Init(w_);

  map_texture_.loadFromFile("../../data/gfx/maps/map_03_960x704_layout ABGS.png");
  map_sprite_ = sf::Sprite(map_texture_);
  //Board
  BoardFromImage(&board_, "../../data/gfx/maps/map_03_120x88_cost.png");

  int c1 = rand()%(120*88);
  int c2 = rand()%(120*88);
  printf("C1: %d C2: %d", c1, c2);
  printf("Distance Manhatan distance: %d  and euclidean: %f", board_.manhantanDistance(c1, c2), board_.euclidianDistance(c1, c2));
  

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

  board_.drawBoard(&w_);
    
}

void Game::end() {

  ImGui::SFML::Shutdown();
}

void Game::mainLoop(){

  init(960, 704);

  sf::Clock sec_clock, main_clock, ia_clock, input_clock;
  sf::Clock world_clock, draw_clock, imgui_clock;

  int frames=0;
  int imguifps = 0;

  while(w_.isOpen()){

    main_clock.restart();

    // Input Update
    if (input_clock.getElapsedTime().asSeconds() > 1.0f / fps.input_ || fps.input_ == -1) {
      input_clock.restart();
      input();
    }
   
    // IA Update
    if(ia_clock.getElapsedTime().asSeconds() > 1.0f/fps.ai || fps.ai == -1){
      ia_clock.restart();
      board_.randomMove();
    }

    // World Update
    if (world_clock.getElapsedTime().asSeconds() > 1.0f / fps.world|| fps.world == -1) {
      world_clock.restart();
      update(delta_time_);      
    }

    ImGui::SFML::Update(w_, imgui_clock.restart());
    ImGui::Begin("FPS Controller");
 
    ImGui::TextColored(ImVec4(1, 1, 1, 1),"FPS panel");
    ImGui::TextColored(ImVec4(1, 0, 1, 1),"FPS:%d", imguifps);
    ImGui::SliderInt("Input", &fps.input_, -1, 60);
    if (fps.input_ == 0) fps.input_ = -1;
    ImGui::SliderInt("AI", &fps.ai, -1, 60.0f);
    if (fps.ai== 0) fps.ai = -1;
    ImGui::SliderInt("World", &fps.world, -1, 60);
    if (fps.world == 0) fps.world = -1;
    ImGui::SliderInt("Draw", &fps.draw_, -1, 60);
    if(fps.draw_ == 0)
      fps.draw_ = -1;

    ImGui::End();

    //Draw
    if (draw_clock.getElapsedTime().asSeconds() > 1.0f / (float)fps.draw_ || fps.draw_ == -1) {
      draw_clock.restart();
      w_.clear(sf::Color(0, 0, 0, 255));
      draw();
    }

    ImGui::SFML::Render(w_);
    w_.display();   
   
    if (sec_clock.getElapsedTime().asSeconds() > 1 ) {
      imguifps = frames;
      frames = 0;
      sec_clock.restart();      
    }

    frames++;

    do {
    } while (main_clock.getElapsedTime().asSeconds() < fps.second_per_frame);
   
  }
  
  end();
}