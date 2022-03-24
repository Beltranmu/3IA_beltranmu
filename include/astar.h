#ifndef __ASTAR_H__
#define __ASTAR_H__ 1

#include <stdint.h>"
#include <list>
#include <vector>

class Board;

struct ACell{
  uint32_t cellID;
  uint32_t parentCellID;
  uint32_t score;
  uint32_t g;

  // Same cellID and parentCellID -> init cell
};

struct TPath{
  std::vector<uint32_t> path;
  uint32_t origin, destination;
  bool draw = false;
};

class Astar{
public:
  void calculatePath(Board* board, int initPostition, int endPosition);

  std::list<ACell> openList;
  std::list<ACell> closeList;
  std::vector<TPath> currentPaths;

};



#endif //__ASTAR_H__