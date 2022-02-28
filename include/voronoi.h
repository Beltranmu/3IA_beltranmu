#ifndef __VORONOI_H__
#define __VORONOI_H__ 1


#include <vector>
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



class Voronoi
{
public:
  Voronoi();
  ~Voronoi();

  int32_t w, h;

  float d;

  void init(int32_t nPoints);
  void draw(sf::RenderWindow* window);

  void calculateParabola();

  void calculateBisector();
  
  sf::Vector3<float> ecuationSystem(sf::Vector3<float>, sf::Vector3<float>);

  std::vector<sf::Vector2<float>> points;
  std::vector<sf::Vector2<float>> Mpoints;
  std::vector<sf::Vector2<float>> Spoints;
  std::vector<sf::Vector3<float>> parabole; // x = Ay^2 + By + C
  std::vector<sf::Vector2<float>> paraboleIPoints;
  std::vector<Bisector> bisector;
  std::vector<Line> lines;
  std::vector<Line> linesBisector;
  std::vector<Line> goodLinesBisector;

  bool drawAllLine;


};
#endif //__VORONOI_H__