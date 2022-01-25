#include "game.h"
#include "imgui.h"
#include "imgui-SFML.h"
#include "SFML/System.hpp"
#include "b_loader.h"
#include "agent.h"

Game::Game(){

  delta_time_ = 0.0f;
 
  fixed_delta_time_ = fps.second_per_frame;

  fps.main_game = 60;
  fps.input_ = -1;
  fps.ai = 1;
  fps.world = 1;
  fps.draw_ = -1;

  fps.second_per_frame = 1/(float)fps.main_game;

  selectedAgentID = -1;
  targetRow = 0;
  targetCol = 0;
  possibleNextTarget = -1;
  startAddPattern = false;
  number_movement = 0;
  movement_type = Agent::PatternMovement::kPatternMovement_None;
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

 //initEnemy
 




  //board_.units_[1].addMovement2Patern(Agent::PatternMovement::kPatternMovement_Forward, 3);
  //board_.units_[1].addMovement2Patern(Agent::PatternMovement::kPatternMovement_Turn180, 1);
//   board_.units_[1].movementArray[0] = Agent::PatternMovement::kPatternMovement_Forward ;
//   board_.units_[1].movementCounterArray[0] = 3;
//   board_.units_[1].movementArray[1] = Agent::PatternMovement::kPatternMovement_Turn180;
//   board_.units_[1].movementCounterArray[1] = 1;
  
 /* board_.units_[3].movementArray[0] = Agent::PatternMovement::kPatternMovement_Forward;
  board_.units_[3].movementCounterArray[0] = 3;
  board_.units_[3].movementArray[1] = Agent::PatternMovement::kPatternMovement_Turn180;
  board_.units_[3].movementCounterArray[1] = 1;*/

}

void Game::input() {
  
  while(w_.pollEvent(events_)){
    ImGui::SFML::ProcessEvent(events_);

    if(events_.type == sf::Event::Closed ||
       ((events_.type == sf::Event::KeyPressed) && (events_.key.code == sf::Keyboard::Escape))) {
      w_.close();
    }

    switch(events_.key.code){

      case sf::Keyboard::Num1:
        board_.units_[3].movementType = Agent::Movement::kMovement_Random;
        break;

      case sf::Keyboard::Num2:
        board_.units_[3].movementType = Agent::Movement::kMovement_Pattern;
        board_.units_[3].currentForwardX = 0;
        board_.units_[3].currentForwardY = -1;
        break;

      case sf::Keyboard::Num3:
        board_.units_[3].movementType = Agent::Movement::kMovement_Track;
        break;
    }

    if (sf::Mouse::isButtonPressed(sf::Mouse::Right)) {
      
      selectedAgentID = board_.getAgent(w_);

    }
        
  }
}

void Game::update(float delta_time) {
  
}

void Game::fixedUpdate(float fixed_delta_time) {}


void Game::draw() {

  board_.drawBoard(&w_, possibleNextTarget);
  possibleNextTarget = -1;
  //board_.drawLBoard(&w_);
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
    if((ia_clock.getElapsedTime().asSeconds() > 1.0f/fps.ai || fps.ai == -1) 
      && (!startAddPattern)){
      ia_clock.restart();
      board_.unitMovement();
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

    ImGui::Begin("Agent Controller");

    if(selectedAgentID == -1){
      ImGui::TextColored(ImVec4(1, 0, 1, 1), "Agent: None");  // Agent
    }else{
      ImGui::TextColored(ImVec4(1, 0, 1, 1), "Agent: %d", selectedAgentID);  // Agent
      ImGui::SliderInt("Movement", (int*)&board_.units_[selectedAgentID].movementType, Agent::Movement::kMovement_Random, Agent::Movement::kMovement_Track);
      
      if (board_.units_[selectedAgentID].movementType == Agent::Movement::kMovement_Pattern) {
        if (ImGui::Button("Start Addition Pattern mode")){
          startAddPattern = true;
        }

        if(startAddPattern){
          if (ImGui::Button("Wait")) { movement_type = Agent::PatternMovement::kPatternMovement_Wait; }
          if (ImGui::Button("Forward")){ movement_type = Agent::PatternMovement::kPatternMovement_Forward;  }
          if (ImGui::Button("Turn 180")){ movement_type = Agent::PatternMovement::kPatternMovement_Turn180;  }
          if (ImGui::Button("Turn Left 90")){ movement_type = Agent::PatternMovement::kPatternMovement_TurnLeft90; }
          if (ImGui::Button("Turn Right 90")){ movement_type = Agent::PatternMovement::kPatternMovement_TurnRight90; }
          ImGui::SliderInt("Number Movements",&number_movement ,1,10);
          if (ImGui::Button("Add Pattern")) {
            board_.units_[selectedAgentID].addMovement2Patern(movement_type, number_movement);
            number_movement = 1;
          }
          if (ImGui::Button("End Addition Pattern mode")) {
            startAddPattern = false;
          }/*
           Show the current pattern
          for(int i = 0; i < board_.units_[selectedAgentID].index_movementArray; ++i){
       
          }*/
        }
        
      }

      if(board_.units_[selectedAgentID].movementType == Agent::Movement::kMovement_Track){

        ImGui::SliderInt("Target Row:", &targetRow, 0, board_.height_-1);
        ImGui::SliderInt("Target Col:", &targetCol, 0, board_.width_-1);
        board_.rowcol2Index(targetRow,targetCol, &possibleNextTarget);

        if(ImGui::Button("Confirm Tile"))
          board_.rowcol2Index(targetRow,targetCol, &board_.units_[selectedAgentID].currentTarget);
      }
    }
    
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