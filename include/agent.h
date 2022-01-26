#ifndef __AGENT_H__
#define __AGENT_H__ 1

#include <stdint.h>
class Board;

class Agent {

  public:
  typedef enum{
    kMovement_Random = 0,
    kMovement_Pattern,
    kMovement_Track,
    kMovement_None,
  } Movement;

  typedef enum{
    kPatternMovement_None = -1,
    kPatternMovement_Wait,
    kPatternMovement_Forward,
    kPatternMovement_Turn180,
    kPatternMovement_TurnLeft90,
    kPatternMovement_TurnRight90,
  }PatternMovement;

    Agent();
    ~Agent();

    void init();

    void moveUnit(Board* board);
    int randomMov(bool* canIMove);
    int patternMov(bool* canIMove);
    int pacManMovement(bool* canIMove, Board* board);
    void addMovement2Patern(PatternMovement p_m,int32_t n_m);
    void cleanMovementPatern();

    static const int32_t numMovements = 64;
    PatternMovement movementArray[numMovements];
    int32_t movementCounterArray[numMovements];
    int32_t i_movement;
    int32_t i_counterMov;
    int32_t next_mov;

    int32_t currentForwardX;
    int32_t currentForwardY;

    int32_t currentPos;
    float currentFPos;
    int32_t currentTarget;
    Movement movementType;
    uint32_t distanceToCatch;
    uint32_t speed;

    int32_t index_movementArray;

    uint32_t agentID;
    bool agentSelected;   

};

#endif //!__AGENT_H__