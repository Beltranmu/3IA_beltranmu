#include "agent.h"
#include <stdio.h>

  Agent::Agent(){

    currentForwardX = 1;
    currentForwardY = 0;

    currentPos = 0;
    i_movement = 0;
    i_counterMov = 0;
    next_mov = 0;
    tileTarget = -1;
    currentTarget = 0;
  }

  Agent::~Agent(){

  }

  void Agent::init(){

    for(int i = 0; i < numMovements ; ++i){
      movementArray[i] = kPatternMovement_None;
      movementCounterArray[i] = 0;
    }
    movementType = kMovement_Random;
    i_movement = 0;
  }

  int Agent::patternMov(bool *canIMove){
    //Should I move?

    if (movementArray[i_movement] == kPatternMovement_None) {
      i_movement = 0;
    }
/*
    printf("Data Before:\n");
    printf("i_movement: %d\n", i_movement);
    printf("movementArray[%d]%d",  i_movement, movementArray[i_movement]);
    printf("i_counterMov: %d\n", i_counterMov);
    printf("movementCounterArray[%d]%d\n",  i_movement, movementCounterArray[i_movement]);*/
      
    switch (movementArray[i_movement])
    {
      case kPatternMovement_Forward:
        *canIMove = true;  break;

      case kPatternMovement_Turn180:
        currentForwardX *= -1;
        currentForwardY *= -1;
      break;

      case kPatternMovement_TurnLeft90:
        if(currentForwardY == 0){
          currentForwardY = -1 * currentForwardX;
          currentForwardX = 0;
        }else{
          currentForwardX = currentForwardY;
          currentForwardY = 0;
        }
      break;

      case kPatternMovement_TurnRight90:
        if (currentForwardY == 0) {
          currentForwardY = currentForwardX;
          currentForwardX = 0;
        }
        else {
          currentForwardX = -1 * currentForwardY;
          currentForwardY = 0;
        }
      break;
    }
    
    
    ++i_counterMov;
    if (i_counterMov >= movementCounterArray[i_movement]) {
      i_movement++;
      i_movement &= 63;
      i_counterMov = 0;
    }
/*
    printf("Data After:\n");
    printf("i_movement: %d\n", i_movement);
    printf("movementArray[%d]%d", i_movement, movementArray[i_movement]);
    printf("i_counterMov: %d\n", i_counterMov);
    printf("movementCounterArray[%d]%d\n\n", i_movement, movementCounterArray[i_movement]);
*/
    //Translate the movement
    next_mov = 0;
    if (currentForwardX == 0 && currentForwardY == 1) { next_mov = 1; }   // South
    if (currentForwardX == 1 && currentForwardY == 0) { next_mov = 2; }   // Right
    if (currentForwardX == -1 && currentForwardY == 0) { next_mov = 3; }  // Left

    
    return next_mov;
  }

  int Agent::pacmanMov() {

    

    return 0;
  }