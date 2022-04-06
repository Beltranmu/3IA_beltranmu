#ifndef __ASTAR_H__
#define __ASTAR_H__ 1

#include <stdint.h>"
#include <list>
#include <vector>

#include "SFML/Graphics.hpp"

class Board;


enum TypeDistanceUsedToCalculatePath{
  MANHATTAN_TYPE = 0,
  EUCLIDEAN_TYPE,
  CHEBYSHOV_TYPE,
  MAX_TYPE
};

struct ACell{
  uint32_t cellID;
  uint32_t parentCellID;
  float score;
  float g;

  // Same cellID and parentCellID -> init cell
};

struct TPath{
  std::vector<ACell> path;
  uint32_t origin, destination;
  bool draw = false;
  TypeDistanceUsedToCalculatePath type;
};

class Astar{
public:

  Astar();
  void calculatePath(Board* board, int initPostition, int endPosition);

  std::list<ACell> openList;
  std::list<ACell> closeList;
  std::vector<TPath> currentPaths;


  sf::Color pathColors[MAX_TYPE];

  bool manhattanD; 
  bool euclideanD; 
  bool chebyshovD;

};



#endif //__ASTAR_H__