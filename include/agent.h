#ifndef __AGENT_H__
#define __AGENT_H__ 1

#include <stdint.h>

class Agent {

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
  } PatternMovement;

  public:
    Agent();
    ~Agent();

    void init();
    void chooseMovement();

    static const int32_t numMovements = 100;
    int32_t movementArray[numMovements];
    int32_t movementCounterArray[numMovements];

    int32_t currentDir;
    Movement movementType;
    PatternMovement nextDir;

};

#endif //!__AGENT_H__