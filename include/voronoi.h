#ifndef __VORONOI_H__
#define __VORONOI_H__ 1


#include <vector>
#include <map>
#include <stdint.h>
#include "SFML/Graphics.hpp"
#include "SFML/System/Vector2.hpp"



struct Bisector {
  sf::Vector2<float> Spoint;
  sf::Vector2<float> vDirector;
  sf::Vector2<float> p1;
  sf::Vector2<float> p2;
};

struct Line {
  sf::Vector2<float> mp, p1, p2;
};

struct Solution{
  sf::Vector2<float> point;
  uint32_t n = 0;
};


struct Cells{
  sf::Vector2<float> point;
  std::vector<sf::Vector2<float>> perimetralPoints;
};
class Voronoi
{
public:
  Voronoi();
  ~Voronoi();

  int32_t w, h;

  float horizontal, d;

  void init(int32_t nPoints);
  void draw(sf::RenderWindow* window);

  void calculateParabola();
  void calculateParabolaDraw();

  void calculateBisector();
  
  sf::Vector3<float> ecuationSystem(sf::Vector3<float>, sf::Vector3<float>);

  std::vector<sf::Vector2<float>> points;
  std::vector<sf::Vector2<float>> Mpoints;
  std::vector<sf::Vector2<float>> Spoints;
  std::vector<sf::Vector3<float>> parabole; // x = Ay^2 + By + C
  std::vector<sf::Vector3<float>> paraboleDraw; // x = Ay^2 + By + C
  std::vector<sf::Vector2<float>> paraboleIPoints;
  std::vector<Bisector> bisector;
  std::vector<Line> lines;
  std::vector<Line> linesBisector;
  std::vector<Line> goodLinesBisector;
  std::vector<Cells> sites;

  //std::map<sf::Vector2<float>, uint32_t> solutionsVoronoid;
  std::vector<Solution> solutions;
  std::vector<Solution> solutionsVoronoid;
  float maxDistance;

  bool drawAllLine;


};
#endif //__VORONOI_H__


