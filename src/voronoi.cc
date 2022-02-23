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

  for (int p = 0; p < Spoints.size(); p++) {
    sf::RectangleShape rect;
    rect.setOutlineColor(sf::Color::Blue);
    rect.setFillColor(sf::Color::Blue);
    rect.setSize(sf::Vector2f(6.0f, 6.0f));

    rect.setPosition(sf::Vector2f(Spoints[p].x - 3, Spoints[p].y - 3));
    window->draw(rect);
  }
 /* for (int p = 0; p < bisector.size(); p++) {
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
  }*/

  for (int p = 0; p < linesBisector.size(); p++) {
    sf::RectangleShape rect;
    rect.setOutlineColor(sf::Color(188, 117, 255));
    rect.setFillColor(sf::Color(188, 117, 255));
    float size = 4.0f;
    rect.setSize(sf::Vector2f(size, size));
    rect.setPosition(sf::Vector2f(linesBisector[p].p1.x - size * 0.5f, linesBisector[p].p1.y - size * 0.5f));
    window->draw(rect);
    rect.setPosition(sf::Vector2f(linesBisector[p].p2.x - size * 0.5f, linesBisector[p].p2.y - size * 0.5f));
    window->draw(rect);

    sf::Vertex line[] =
    {
        linesBisector[p].p1,
        linesBisector[p].p2,
    };
    line[0].color = (sf::Color(255, 255, 0));
    line[1].color = (sf::Color(255, 255, 0));
    window->draw(line, 2, sf::Lines);
  }
}

float module(sf::Vector2<float> v){
  return sqrtf((v.x * v.x) + (v.y * v.y));
}

void normalizeSFVec2(sf::Vector2<float> *v){
  float mod = 1 / sqrtf((v->x * v->x) + (v->y * v->y));
  v->x *= mod;
  v->y *= mod;
}

float dotProtduct(sf::Vector2<float> v1, sf::Vector2<float> v2){


  float p = v1.x * v2.x + v1.y * v2.y;
  float m = sqrtf((v1.x * v1.x) + (v1.y * v1.y)) * sqrtf((v2.x * v2.x) + (v2.y * v2.y));
  return p / m;
}

bool compareMargin(float x, float y, float error) {
  return ((y - error <= x) && (x <= y + error));
}

void Voronoi::calculateBisector()
{
  int p = 0;
  //int j = 1;
  bisector.clear();
  Mpoints.clear();
  Spoints.clear();
  linesBisector.clear();
  int ii = 1;
  for (int p = 0; p < points.size(); p++) {
    for(int j = ii; j < points.size(); j++){

      if(p!=j){
        sf::Vector2<float> newPoint;
        sf::Vector2<float> vDirector = points[j] - points[p];
        newPoint = points[p] + vDirector*0.5f;
        Mpoints.push_back(newPoint);

        Bisector n;
        n.Spoint = newPoint;
        n.vDirector = { vDirector.y, -vDirector.x };
        //bisector.push_back(n);
        bool firstPoint = false;
        Line newBisector;
        newBisector.mp = newPoint;
        sf::Vector2<float> vdir1 = { -vDirector.y, vDirector.x };
        sf::Vector3<float> e1, e2, sol;
        normalizeSFVec2(&vdir1);
      
        float m = 0;
        if(vdir1.x !=0){
            m = vdir1.y / vdir1.x;
            e1.x = -m;
            e1.y = 1;

            e1.z = -m * newPoint.x + newPoint.y;
        }else {
          e1.x = 1;
          e1.y = 0;

          e1.z = newPoint.y;
        }
        for(int l = 0; l < lines.size(); l++){
          sf::Vector2<float> vdir2 = lines[l].p2 - lines[l].p1;
          normalizeSFVec2(&vdir2);


          if (vdir2.x != 0) {
            m = vdir2.y / vdir2.x;
            e2.x = -m;
            e2.y = 1;

            e2.z = -m * lines[l].p1.x + lines[l].p1.y;
          }else{
            e2.x = 1;
            e2.y = 0;

            e2.z =  lines[l].p1.x;
          }

          sol = ecuationSystem(e1, e2);
          bool solutionXInRange = ((sol.x >= -1) && (sol.x <= 961));
          bool solutionYInRange = ((sol.y >= -1) && (sol.y <= 705));
          bool validSolution = ((sol.z == 1) && (solutionXInRange) && (solutionYInRange));

          if (validSolution) {
            if(!firstPoint){
              firstPoint = true;
              newBisector.p1 = { sol.x, sol.y };
            }else{

              newBisector.p2 = { sol.x, sol.y };
              linesBisector.push_back(newBisector);
            }
            Bisector n;
            n.Spoint.x = sol.x;
            n.Spoint.y = sol.y;
            n.vDirector = {vdir1.x * 2000, vdir1.y * 2000 };
            bisector.push_back(n);
          }
      
          
        }
        
        
      }
   }
    ii++;
  }

   ii = 1;
  for(int i = 0; i < linesBisector.size(); ++ i){
    for(int j = ii; j < linesBisector.size(); ++ j){

      if (i != j) {
        sf::Vector3<float> e1, e2, sol;
        sf::Vector2<float> vdir1 = linesBisector[i].p2 - linesBisector[i].p1;
        normalizeSFVec2(&vdir1);
        sf::Vector2<float> vdir2 = linesBisector[j].p2 - linesBisector[j].p1;
        normalizeSFVec2(&vdir2);

        float m = 0;
        if (vdir1.x != 0) {
          m = vdir1.y / vdir1.x;
          e1.x = -m;
          e1.y = 1;

          e1.z = -m * linesBisector[i].p1.x + linesBisector[i].p1.y;
        }
        else {
          e1.x = 1;
          e1.y = 0;

          e1.z = linesBisector[i].p1.x;;
        }

        if (vdir2.x != 0) {
          m = vdir2.y / vdir2.x;
          e2.x = -m;
          e2.y = 1;

          e2.z = -m * linesBisector[j].p1.x + linesBisector[j].p1.y;
        }
        else {
          e2.x = 1;
          e2.y = 0;

          e2.z = linesBisector[j].p1.x;
        }

        sol = ecuationSystem(e1, e2);
        bool solutionXInRange = ((sol.x >= -1) && (sol.x <= 961));
        bool solutionYInRange = ((sol.y >= -1 ) && (sol.y <= 705));
        bool validSolution = ((sol.z == 1) && (solutionXInRange) && (solutionYInRange));

        if (validSolution) {
          //Line i
          sf::Vector2<float> V1, V2, p;
          p.x = sol.x;
          p.y = sol.y;
          V1 = linesBisector[i].mp - linesBisector[i].p1;
          V2 = linesBisector[i].mp - p;
          float dotvalue = dotProtduct(V1,V2);

          if (compareMargin(dotvalue, 1.0f, 0.1f)){
            //Cambiar el 1
            if (module(linesBisector[i].p1 - linesBisector[i].p2) >= module(p - linesBisector[i].p2)) {
              //Cambiamos
              linesBisector[i].p1 = p;
            }
          }else if(compareMargin(dotvalue, -1.0f, 0.1f)){
            //Cambiar el 2
            if (module(linesBisector[i].p1 - linesBisector[i].p2) >= module(p - linesBisector[i].p1)) {
              //Cambiamos
              linesBisector[i].p2 = p;
            }
          }

          V1 = linesBisector[j].mp - linesBisector[j].p1;
          V2 = linesBisector[j].mp - p;
          dotvalue = dotProtduct(V1, V2);

          if (compareMargin(dotvalue, 1.0f, 0.1f)) {
            //Cambiar el 1
            if (module(linesBisector[j].p1 - linesBisector[j].p2) >= module(p - linesBisector[j].p2)) {
              //Cambiamos
              linesBisector[j].p1 = p;
            }
          }
          else if (compareMargin(dotvalue, -1.0f, 0.1f)) {
            //Cambiar el 2
            if (module(linesBisector[j].p1 - linesBisector[j].p2) >= module(p - linesBisector[j].p1)) {
              //Cambiamos
              linesBisector[j].p2 = p;
            }
          }



          //Line j
          Spoints.push_back({ sol.x, sol.y });
          //Change segments
        }
      }
    }
    ii++;
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
