#include "game.h"
#include "imgui.h"
#include "imgui-SFML.h"
#include "SFML/System.hpp"
#include "b_loader.h"
#include "agent.h"
#include "voronoi.h"

Game::Game(){

  delta_time_ = 0.0f;
  pausedParabola = false;
  fixed_delta_time_ = fps.second_per_frame;

  fps.main_game = 60;
  fps.input_ = -1;
  fps.ai = 1;
  fps.world = 1;
  fps.draw_ = -1;

  fps.second_per_frame = 1/(float)fps.main_game;

  selectedAgentID = -1;
  targetRow = 0;
  possibleNextTarget = -1;
  startAddPattern = false;
  number_movement = 0;
  movement_type = Agent::PatternMovement::kPatternMovement_None;
}

Game::~Game() {

}

void Game::init(uint32_t w_width, uint32_t w_height) {

 // srand(time(NULL));
  w_width_ = w_width;
  w_height_ = w_height;
  voronoi.w = w_width_;
  voronoi.h = w_height_;
  //voronoi.init(10);
  //voronoi.calculateBisector();
  voronoi.calculateParabola();
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
  board_.units_[0].currentPos = 0;
  






}

void Game::input() {
  
  while(w_.pollEvent(events_)){
    ImGui::SFML::ProcessEvent(events_);

    if(events_.type == sf::Event::Closed ||
       ((events_.type == sf::Event::KeyPressed) && (events_.key.code == sf::Keyboard::Escape))) {
      w_.close();
    }

    
    if (sf::Mouse::isButtonPressed(sf::Mouse::Right)) {
      
      selectedAgentID = board_.getAgent(w_);

    }
    
        
  }
}

void Game::update(float delta_time) {
  if(pausedParabola){
    voronoi.d += 0.5f;

  }
}

void Game::fixedUpdate(float fixed_delta_time) {}


void Game::draw() {

  board_.drawBoard(&w_, possibleNextTarget);
  //possibleNextTarget = -1;
  //board_.drawLBoard(&w_);
  //voronoi.draw(&w_);
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
    //voronoi.calculateParabolaDraw();
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
    ImGui::TextColored(ImVec4(1, 1, 1, 1), "Position %d",board_.units_[0].currentPos);
    ImGui::TextColored(ImVec4(1, 1, 1, 1), "Target %d",board_.units_[0].currentTarget);
    ImGui::SliderInt("InitPosRow", &board_.targetRowI, 0, board_.height_ - 1);
    ImGui::SliderInt("InitPosCol", &board_.targetColI, 0, board_.width_ - 1);

    ImGui::SliderInt("DstPosRow", &board_.targetRowD, 0, board_.height_ - 1);
    ImGui::SliderInt("DstPosCol", &board_.targetColD, 0, board_.width_ - 1);
    ImGui::Checkbox("Manhattan Distance", &board_.aPath_.ManhattanD);
    ImGui::Checkbox("Euclidean Distance", &board_.aPath_.EuclideanD);

    if (ImGui::Button("Check A Star")) {
      int origin = board_.targetColI + board_.targetRowI * board_.width_;
      int dst = board_.targetColD + board_.targetRowD * board_.width_;
      if(origin != dst){
        printf("Calculate Path From %d -> %d\n", origin, dst);
        board_.aPath_.calculatePath(&board_, origin,dst);
      }
    }
    //ImGui::BeginChild("Paths");
    for (int i = 0; i < (int)board_.aPath_.currentPaths.size(); ++i) {
      ImGui::BeginChild("Path");
      ImGui::TextColored(ImVec4(1, 1, 1, 1), "Path From %d -> %d", board_.aPath_.currentPaths[i].origin, 
        board_.aPath_.currentPaths[i].destination);
      char name[255];
      sprintf(name, "Draw %d", i);
      ImGui::Checkbox(name, &board_.aPath_.currentPaths[i].draw);
      for(int p = 0; p< (int)board_.aPath_.currentPaths[i].path.size(); ++p){

        ImGui::TextColored(ImVec4(1, 0, 1, 1), "%d : %d", p,
          board_.aPath_.currentPaths[i].path[p]);

      }
      ImGui::EndChild();
    }
   // ImGui::EndChild();
    ImGui::BeginChild("Scrolling");
    /*ImGui::Checkbox("Lines", &voronoi.drawAllLine);
    ImGui::Checkbox("Sectors", &voronoi.drawSectors);
    if (ImGui::Button("Check Parbole")) {
      voronoi.calculateParabola();
    } if (ImGui::Button("Clear Parbole")) {
      for (int i = 0; i < (int)voronoi.sites.size(); ++i) {
        voronoi.sites[i].perimetralLines.clear();
      };
        voronoi.solutionsVoronoi.clear();
    }
    if (ImGui::Button("Pause Parabola")) {
      pausedParabola = !pausedParabola;
    }
    for(int i = 0; i< (int)voronoi.paraboleDraw.size(); ++i){
      ImGui::TextColored(ImVec4(1, 1, 1, 1), "Ecuacion: x = %fy^2 %fy %f", voronoi.paraboleDraw[i].x, voronoi.paraboleDraw[i].y, voronoi.paraboleDraw[i].z);
    }
    ImGui::SliderFloat("Direztriz line", &voronoi.d, 0, 1500);
    ImGui::SliderFloat("Horizontal line", &voronoi.horizontal, 0, 704);
    if (ImGui::Button("Check Voronoi")) {
      voronoi.calculateBisector();
    }
    for (int n = 0; n < (int)voronoi.sites.size(); n++) {
     
      float red = ((float)n+1.0f) / (float)voronoi.sites.size();
      ImGui::TextColored(ImVec4(1, red, red, 1), "Point: %d", n);
      char name[255];
      sprintf(name, "PositionX % d", n);
      ImGui::SliderFloat(name, &voronoi.sites[n].point.x, 0, 960);
      sprintf(name, "PositionY % d", n);
      ImGui::SliderFloat(name, &voronoi.sites[n].point.y, 0, 704);
    }*/
    ImGui::EndChild();
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
          ImGui::SliderInt("Number Movements",&number_movement ,1,20);
          if (ImGui::Button("Add Pattern")) {
            board_.units_[selectedAgentID].addMovement2Patern(movement_type, number_movement);
            number_movement = 1;
            movement_type = Agent::PatternMovement::kPatternMovement_None;
          }
          if (ImGui::Button("End Addition Pattern mode")) {
            startAddPattern = false;
          }
          const char* name_movement = "NONE";
          switch (movement_type)
          {
          case Agent::PatternMovement::kPatternMovement_Wait: name_movement = "WAIT"; break;
          case Agent::PatternMovement::kPatternMovement_Forward: name_movement = "FORWARD"; break;
          case Agent::PatternMovement::kPatternMovement_Turn180: name_movement = "TURN180"; break;
          case Agent::PatternMovement::kPatternMovement_TurnLeft90: name_movement = "TURNLEFT90"; break;
          case Agent::PatternMovement::kPatternMovement_TurnRight90: name_movement = "TURNRIGHT90"; break;
          }
          ImGui::TextColored(ImVec4(1, 0, 0, 1), "PATTERN TO ADD:");
          ImGui::Text("Movement Type: %s || Steps: %d", name_movement, number_movement);


          //Show the current pattern
          ImGui::TextColored(ImVec4(0, 1, 0, 1), "CURRENT PATTERN");
          const char* name_mov = "NONE";
      
          for(int i = 0; i < board_.units_[selectedAgentID].index_movementArray; ++i){
            switch (board_.units_[selectedAgentID].movementArray[i])
            {
              case Agent::PatternMovement::kPatternMovement_Wait: name_mov = "WAIT"; break;
              case Agent::PatternMovement::kPatternMovement_Forward: name_mov = "FORWARD"; break;
              case Agent::PatternMovement::kPatternMovement_Turn180: name_mov = "TURN180"; break;
              case Agent::PatternMovement::kPatternMovement_TurnLeft90: name_mov = "TURNLEFT90"; break;
              case Agent::PatternMovement::kPatternMovement_TurnRight90: name_mov = "TURNRIGHT90"; break;
            }
            //ImGui::Text("Movement Type: %s || Steps: %d", name_mov, board_.units_[selectedAgentID].movementCounterArray[i]);
            ImGui::TextColored(ImVec4(1, 1, 0, 1), "Movement Type: %s || Steps: %d", name_mov, board_.units_[selectedAgentID].movementCounterArray[i]);
          }
          
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