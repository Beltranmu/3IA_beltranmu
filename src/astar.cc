#include "astar.h"
#include "board.h"
// 1. Put the starting square in the open list.
// 2. Repeat until the open list is empty :
// 
//    1. Get the square on the open list which has the lowest score.Let�s call this
//    square S.
//    2. Remove S from the open list and add S to the closed list.
//    3. For each square T in S�s walkable adjacent tiles :
// 
//      1. If T is in the closed list : Ignore it.
//      2. If T is not in the open list : Add it and compute its score.
//      3. If T is already in the open list : Check if the F score is lower when
//         we use the current generated path to get there.If it is, update its
//         score and update its parent as well.


// F = G + H

Astar::Astar(){

  ManhattanD = true;
  EuclideanD = false;

}

void Astar::calculatePath(Board* board, int initPostition, int endPosition){
  if (initPostition == endPosition)
  {
    printf("Choose another position\n");
  }
  if(ManhattanD == false && EuclideanD == false){
    printf("Choose a type to calculate the distance\n");
    return;
  }
  if(ManhattanD == true && EuclideanD == true){
    printf("ALl distance types chosen, choose only one, pls :D\n");
    return;
  }
  for(int i = 0; i<(int) currentPaths.size(); ++i){
    bool samePath = currentPaths[i].destination == endPosition;
    samePath = samePath && currentPaths[i].origin == initPostition;
    if(samePath){
      printf("Path already calculated\n");
      return;
    }
  }


  ACell initCell;
  openList.clear();
  closeList.clear();

  initCell.cellID = initPostition;
  initCell.parentCellID = initPostition;
  initCell.g = 0;
  
  if(ManhattanD){ initCell.score = initCell.g + board->manhantanDistance(initPostition, endPosition); }
  if(EuclideanD){ initCell.score = initCell.g + board->euclidianDistance(initPostition, endPosition); }
  uint32_t parentID = initPostition;
  bool pathFound = initPostition == endPosition;
  
  openList.push_back(initCell);
 
  ACell lowestScoreCell;
  uint32_t lowestScoreCellIndex = 0;
  while(!openList.empty() && !pathFound){
    //Get the one with lowest F in the openList
    uint32_t index = 0;
    uint32_t lowestScore = 9999;
    std::list<ACell>::iterator it = openList.begin();
    for(it; it != openList.end(); ++it ){
      uint32_t score = it->score;
      /*CALCULAR SCORE*/
      if(score < lowestScore){
        lowestScore = score;
        lowestScoreCell = *it;
        lowestScoreCellIndex = index;
        parentID = it->cellID;
      }
      index++;
    }

    //Remove from the open list
    it = openList.begin();
    advance(it, lowestScoreCellIndex);
    openList.erase(it);
    //Add it in the close list
    closeList.push_front(lowestScoreCell);

    //Check Square
    uint32_t neighbourdCells[4];
    neighbourdCells[0] = board->north(lowestScoreCell.cellID); //North
    neighbourdCells[1] = board->south(lowestScoreCell.cellID); //South
    neighbourdCells[2] = board->west(lowestScoreCell.cellID);  //West
    neighbourdCells[3] = board->east(lowestScoreCell.cellID);  //East

    for(int j = 0; j< 4 && !pathFound; j++){
      if(board->checkUnitMovement(neighbourdCells[j])){
        bool isInCloseList = false;
        bool isInOpenList = false;
        //Search in the closeList
        it = closeList.begin();
        for(it; it != closeList.end() && !isInCloseList; ++it){
          if(it->cellID == neighbourdCells[j]){
            isInCloseList = true;
          }
        }

        if(!isInCloseList){

          for (int q = 0; q < openList.size(); ++q) {
            it = openList.begin();
            advance(it, q);
            if (it->cellID == neighbourdCells[j]) {
              isInOpenList = true;
            }
          }
          

          uint32_t GScore = lowestScoreCell.g + 1; 
          uint32_t HScore = 0;
         
          if (ManhattanD) { HScore = initCell.g + board->manhantanDistance(neighbourdCells[j], endPosition); }
          if (EuclideanD) { HScore = initCell.g + board->euclidianDistance(neighbourdCells[j], endPosition); }
          uint32_t FScore = GScore + HScore;
          if (!isInOpenList) {
            ACell newCell;
            newCell.cellID = neighbourdCells[j];
            newCell.parentCellID = parentID;
            newCell.g = GScore;
            newCell.score = FScore;
            openList.push_front(newCell);
          }
          //Already in the openList
          else {
            if(FScore < it->score){
              it->score = FScore;
              it->g = GScore;
              it->parentCellID = parentID;
            }
          
          }
          if(HScore == 0){
            pathFound = true;
            ACell newCell;
            newCell.cellID = neighbourdCells[j];
            newCell.parentCellID = parentID;
            newCell.g = GScore;
            newCell.score = FScore;
            closeList.push_front(newCell);
          }
        }
      }
    }
  }

  // Get the path
  if(pathFound){
    std::list<ACell>::iterator it = closeList.begin();
    std::list<uint32_t> path;
    path.clear();
    //Camino esta en la closeList
    bool endPath = false;
    bool endAdded = false;
    uint32_t endCellID = endPosition;
    //path.push_front(closeList.begin()->cellID);
    for(it; it != closeList.end() && !endPath; ){

      if(it->cellID == it->parentCellID){
        endPath = true;
        path.push_front(it->cellID);
      }

      if(it->cellID == endCellID && !endPath){
       // endAdded = true;
        endCellID = it->parentCellID;
        path.push_front(it->cellID);
        it = closeList.begin();
      }else{
        ++it;
      }

      
    }
    std::list<uint32_t>::iterator it2 = path.begin();
    int sizePath = path.size();
    TPath newPath;
    newPath.origin = initPostition;
    newPath.destination = endPosition;
    //newPath.path = (uint32_t*)malloc(sizeof(uint32_t) * sizePath);
    //Eliminar la lista para el path
    int i = 0;
    for (it2; it2 != path.end(); ++it2) {
      newPath.path.push_back(*it2) ;
      i++;
    }
    currentPaths.push_back(newPath);

  }
}
