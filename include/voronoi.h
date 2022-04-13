#ifndef __VORONOI_H__
#define __VORONOI_H__ 1


#include <vector>
#include <map>
#include <stdint.h>
#include "SFML/Graphics.hpp"
#include "SFML/System/Vector2.hpp"

const int kwidthStreet = 20;

struct Size{
  float width, height;
};

struct Map{
  Size size;
  float widthStreets;
};

struct Bisector {
  sf::Vector2<float> Spoint;
  sf::Vector2<float> vDirector;
  sf::Vector2<float> p1;
  sf::Vector2<float> p2;
};

struct Line {
  sf::Vector2<float> mp, p1, p2;
};
struct LineP {
  sf::Vector2<float> p1, p2;
  // p1-> Point, p2-> NextPoint,
};

struct Solution{
  sf::Vector2<float> point;
  uint32_t n = 0;
  std::vector<int> parentSites;
  int sites[3] = { -1,-1,-1 };
};


struct Parabole {
  sf::Vector3<float> parabole; // x = Ay^2 + By + C
  int parentPoint;
};

struct Cells{
  sf::Vector2<float> point;
  std::vector<LineP> perimetralLines;
  sf::Color color;
};

struct AuxCell {
  
  std::vector<sf::Vector2<float>> upperPoints;
  std::vector<sf::Vector2<float>> bottonPoints;
};
class Voronoi
{
public:
  Voronoi();
  ~Voronoi();

  int32_t w, h;

  float horizontal, d;
  bool reducedPoly;

  void customInit();
  void customInit2();
  void init(int32_t nPoints);
  void draw(sf::RenderWindow* window);
  void clear();
  void calculateParabola();
  void calculateParabolaDraw();

  void calculateBisector();

  bool isBeachLine(sf::Vector2<float> p);
  
  sf::Vector3<float> ecuationSystem(sf::Vector3<float>, sf::Vector3<float>);

  std::vector<sf::Vector2<float>> points;
  std::vector<sf::Vector2<float>> Mpoints;
  std::vector<sf::Vector2<float>> Spoints;
  std::vector<sf::Vector3<float>> paraboleDraw; // x = Ay^2 + By + C
  std::vector<Solution> paraboleIPoints;
  std::vector<Bisector> bisector;
  std::vector<Line> lines;
  std::vector<Line> linesBisector;
  std::vector<Line> goodLinesBisector;
  std::vector<Solution> solutionsVoronoi2;
  


  //std::map<sf::Vector2<float>, uint32_t> solutionsVoronoid;
  std::vector<Solution> solutions;
  std::vector<Solution> solutionsVoronoi;



  // Good one
  std::vector<Cells> sites;
  std::vector<AuxCell> auxsitesLittle;
  std::vector<AuxCell> auxsites;
  std::vector<Parabole> parabole; // x = Ay^2 + By + C

  void calculateSites();

  void intersectionParaboleHLine(Parabole p, float y);
  void intersectionParaboleVLine(Parabole p, float x);
  void addSolution(float x, float y,  int32_t paraboleIndex, int32_t parabole2Index = -1);
  void intersectionParaboleParabole(Parabole p, Parabole q);


  float stepParabole;
  float maxX;
  bool firstSol;

  float maxDistance;
  Map map;
  bool drawAllLine;
  bool drawSectors;
  bool drawIPoints;

  bool showSitesInfo;
  float marginSamePoint;
  float sameSolMargin;


};
#endif //__VORONOI_H__



