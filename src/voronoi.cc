#include "voronoi.h"



Voronoi::Voronoi()
{

}

Voronoi::~Voronoi()
{
}




void Voronoi::init(int32_t nPoints){

  Line newLine;
  newLine.p1.x = 0.0f;
  newLine.p1.y = 0.0f;
  newLine.p2.x = (float)w;
  newLine.p2.y = 0.0f;
  lines.push_back(newLine);

  newLine.p1.x = (float)w;
  newLine.p1.y = 0.0f;
  newLine.p2.x = (float)w;
  newLine.p2.y = (float)h;
  lines.push_back(newLine);

  newLine.p1.x = (float)w;
  newLine.p1.y = (float)h-1;
  newLine.p2.x = 0.0f;
  newLine.p2.y = (float)h-1;
  lines.push_back(newLine);

  newLine.p1.x = 0.0f;
  newLine.p1.y = (float)h;
  newLine.p2.x = 0.0f;
  newLine.p2.y = 0.0f;
  lines.push_back(newLine);


  for(int i = 0; i < nPoints; i++){

    sf::Vector2<float> newPoint;
    newPoint.x = (float)(rand() % w);
    newPoint.y = (float)(rand() % h);

    points.push_back(newPoint);
  }

}


void Voronoi::draw(sf::RenderWindow* window){
  for (int l = 0; l < lines.size(); l++) {
    sf::Vertex line[] =
    {
        sf::Vertex(lines[l].p1),
        sf::Vertex(lines[l].p2),

    };
    line[0].color = (sf::Color(150, 50, 250));
    line[1].color = (sf::Color(150, 50, 250));
    window->draw(line, 2, sf::Lines);
  }

  for(int p = 0; p < points.size(); p++){
    sf::RectangleShape rect;
    rect.setOutlineColor(sf::Color::White);
    rect.setFillColor(sf::Color::White);
    rect.setSize(sf::Vector2f(2.0f, 2.0f));

    rect.setPosition(sf::Vector2f(points[p].x, points[p].y));
    window->draw(rect);


  } 
  
  for (int p = 0; p < Mpoints.size(); p++) {
    sf::RectangleShape rect;
    rect.setOutlineColor(sf::Color::Red);
    rect.setFillColor(sf::Color::Red);
    rect.setSize(sf::Vector2f(6.0f, 6.0f));

    rect.setPosition(sf::Vector2f(Mpoints[p].x-3, Mpoints[p].y-3));
    window->draw(rect);
  }
  for (int p = 0; p < bisector.size(); p++) {
    sf::RectangleShape rect;
    rect.setOutlineColor(sf::Color::Green);
    rect.setFillColor(sf::Color::Green);
    float size = 4.0f;
    rect.setSize(sf::Vector2f(size, size));
    rect.setPosition(sf::Vector2f(bisector[p].Spoint.x-size*0.5f, bisector[p].Spoint.y - size * 0.5f));
    window->draw(rect);

    sf::Vertex line[] =
    {
        sf::Vertex(bisector[p].Spoint + bisector[p].vDirector),
        sf::Vertex(bisector[p].Spoint - bisector[p].vDirector),

    };
    line[0].color = (sf::Color(255, 143, 36));
    line[1].color = (sf::Color(255, 143, 36));
    window->draw(line, 2, sf::Lines);

   /* sf::Vertex line2[] =
    {
        sf::Vertex(bisector[p].Spoint),
        sf::Vertex(bisector[p].Spoint - bisector[p].vDirector),

    };
    line2[0].color = (sf::Color(255, 143, 36));
    line2[1].color = (sf::Color(255, 143, 36));
    window->draw(line2, 2, sf::Lines);*/
    
    
  }


}

void normalizeSFVec2(sf::Vector2<float> *v){
  float mod = 1 / sqrtf((v->x * v->x) + (v->y * v->y));
  v->x *= mod;
  v->y *= mod;
}
void Voronoi::calculateBisector()
{
  int p = 0;
  int j = 1;

  for (int p = 0; p < points.size(); p++) {
    for(int j = 0; j < points.size(); j++){

      if(p!=j){
        sf::Vector2<float> newPoint;
        sf::Vector2<float> vDirector = points[j] - points[p];
        newPoint = points[p] + vDirector*0.5f;
        Mpoints.push_back(newPoint);

        Bisector n;
        n.Spoint = newPoint;
        n.vDirector = { vDirector.y, -vDirector.x };
        //bisector.push_back(n);

        for(int l = 0; l < lines.size(); l++){
          sf::Vector3<float> e1, e2, sol;
          sf::Vector2<float> vdir1 = { -vDirector.y, vDirector.x };
          normalizeSFVec2(&vdir1);
          sf::Vector2<float> vdir2 = lines[l].p2 - lines[l].p1;
          normalizeSFVec2(&vdir2);
         // MATR::Vec2 vdir1 = MATR::RestaDeVec2(a2, a1), vdir2 = MATR::RestaDeVec2(b2, b1);
          //int cont = 0;
          float m = 0;
          if(vdir1.x !=0){
             m = vdir1.y / vdir1.x;
          }
          
          e1.x = -m;
          e1.y = 1;

          e1.z = -m * newPoint.x + newPoint.y;

          if (vdir2.x != 0) {
            m = vdir2.y / vdir2.x;
            e2.x = -m;
            e2.y = 1;

            e2.z = -m * lines[l].p1.x + lines[l].p1.y;
          }else{
            e2.x = 1;
            e2.y = 0;

            e2.z =  lines[l].p1.y;
          }

         

            sol = ecuationSystem(e1, e2);
          if (sol.z == 1) {
            Bisector n;
            n.Spoint.x = sol.x;
            n.Spoint.y = sol.y;
            n.vDirector = {vdir1.x * 1000, vdir1.y * 1000 };
            bisector.push_back(n);
          }
      
          
        }
        
        
      }
   }
    
  }

}

sf::Vector3<float> Voronoi::ecuationSystem(sf::Vector3<float> ec1, sf::Vector3<float> ec2)
{
  float aux = 1;
  sf::Vector3<float> sol = { 0.0f, 0.0f, -1.0f };
  if (ec1.x == ec2.x && ec1.y == ec2.y)
  {
    if (ec1.z == ec2.z)//Las rectas son la misma
    {
      sol.y = 0.5;
      sol.x = 0.5;
      sol.z = 0.5f;
    }
    else {// las rectas son parelesas no hay sol
      sol.y = 100.0;
      sol.x = 100.0;
      sol.z = 100.0;
    }
  }
  else {

    aux = (-1) * (ec2.x / ec1.x);
    ec2.x = ec1.x * aux + ec2.x;
    ec2.y = ec1.y * aux + ec2.y;
    ec2.z = ec1.z * aux + ec2.z;



    sol.y = ec2.z / ec2.y;
    sol.x = (ec1.z - sol.y * ec1.y) / ec1.x;
    sol.z = 1;

    //printf("X= %f, Y= %f", sol.x,sol.y);
  }
  return sol;
}
