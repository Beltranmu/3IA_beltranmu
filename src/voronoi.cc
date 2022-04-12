#include "voronoi.h"



Voronoi::Voronoi()
{
  horizontal = 0;
  w = 0;
  h = 0;
  d = 0;
  drawAllLine = false;
  showSitesInfo= false;
  reducedPoly = false;
  maxDistance = -1;
  firstSol = true;
  marginSamePoint = 0.15f;
  sameSolMargin = 4.0f;
  maxX = 0.0f;
  stepParabole = 0.005f;

 
}

Voronoi::~Voronoi()
{
}

void normalizeSFVec2(sf::Vector2<float>* v) {
  float mod = 1 / sqrtf((v->x * v->x) + (v->y * v->y));
  v->x *= mod;
  v->y *= mod;
}

void SwapListElements(std::vector<sf::Vector2<float>> *v, int position1, int position2) {
  sf::Vector2<float> data1 = (*v)[position1];
  sf::Vector2<float> data2 = (*v)[position2];

  (*v)[position1] = data2;
  (*v)[position2] = data1;


}


int Partition(std::vector<sf::Vector2<float>> *v, int first, int last, sf::Vector2<float> centralPoint) {
  sf::Vector2<float> tmpV = centralPoint - (*v)[last] ;
  normalizeSFVec2(&tmpV);
  float pivot = tmpV.x; // pivot value
  int i = first;  // Index of smaller element

  for (int j = first; j < last; j++)
  {
    tmpV = centralPoint - (*v)[j] ;
    normalizeSFVec2(&tmpV);
    float j_element = tmpV.x;
    if (j_element >= pivot) {
      SwapListElements(v, i, j);
      ++i;   // increment index of smaller element
    }
  }
  // Swap the pivot to its place
  SwapListElements(v, i, last);
  return i;
}


void QuickSorting(std::vector<sf::Vector2<float>> *v, int index_start, int index_end, sf::Vector2<float> centralPoint) {

 


  if (index_start < index_end) {
    int pivot_index = Partition(v, index_start, index_end, centralPoint);

    QuickSorting(v, index_start, pivot_index - 1, centralPoint);
    QuickSorting(v, pivot_index + 1, index_end, centralPoint);
  }
}



void Voronoi::customInit(){

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
  newLine.p1.y = (float)h - 1;
  newLine.p2.x = 0.0f;
  newLine.p2.y = (float)h - 1;
  lines.push_back(newLine);

  newLine.p1.x = 0.0f;
  newLine.p1.y = (float)h;
  newLine.p2.x = 0.0f;
  newLine.p2.y = 0.0f;
  lines.push_back(newLine);



  Cells site;
  sf::Vector2<float> newPoint;
  newPoint.x = (float)(595);
  newPoint.y = (float)(469);
  site.point = newPoint;
  site.perimetralLines.clear();
  site.color = sf::Color(rand() % 255, rand() % 255, rand() % 255, rand() % 255);
  points.push_back(newPoint);
  sites.push_back(site);
  AuxCell s;
  auxsites.push_back(s);
  auxsitesLittle.push_back(s);


  newPoint.x = (float)(267);
  newPoint.y = (float)(436);
  site.point = newPoint;
  site.perimetralLines.clear();
  site.color = sf::Color(rand() % 255, rand() % 255, rand() % 255, rand() % 255);
  points.push_back(newPoint);
  sites.push_back(site);

  auxsites.push_back(s);
  auxsitesLittle.push_back(s);



  newPoint.x = (float)(442);
  newPoint.y = (float)(181);
  site.point = newPoint;
  site.perimetralLines.clear();
  site.color = sf::Color(rand() % 255, rand() % 255, rand() % 255, rand() % 255);
  points.push_back(newPoint);
  sites.push_back(site);

  auxsites.push_back(s);
  auxsitesLittle.push_back(s);



}

void Voronoi::customInit2(){
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
  newLine.p1.y = (float)h - 1;
  newLine.p2.x = 0.0f;
  newLine.p2.y = (float)h - 1;
  lines.push_back(newLine);

  newLine.p1.x = 0.0f;
  newLine.p1.y = (float)h;
  newLine.p2.x = 0.0f;
  newLine.p2.y = 0.0f;
  lines.push_back(newLine);

  

    Cells site;
    sf::Vector2<float> newPoint;
    newPoint.x = (float)(159);
    newPoint.y = (float)(533);
    site.point = newPoint;
    site.perimetralLines.clear();
    site.color = sf::Color(rand() % 255, rand() % 255, rand() % 255, rand() % 255);
    points.push_back(newPoint);
    sites.push_back(site);
    AuxCell s;
    auxsites.push_back(s);
    auxsitesLittle.push_back(s);

 
    newPoint.x = (float)(663);
    newPoint.y = (float)(323);
    site.point = newPoint;
    site.perimetralLines.clear();
    site.color = sf::Color(rand() % 255, rand() % 255, rand() % 255, rand() % 255);
    points.push_back(newPoint);
    sites.push_back(site);
    
    auxsites.push_back(s);
    auxsitesLittle.push_back(s);



    newPoint.x = (float)(717);
    newPoint.y = (float)(367);
    site.point = newPoint;
    site.perimetralLines.clear();
    site.color = sf::Color(rand() % 255, rand() % 255, rand() % 255, rand() % 255);
    points.push_back(newPoint);
    sites.push_back(site);

    auxsites.push_back(s);
    auxsitesLittle.push_back(s);
 
    newPoint.x = (float)(218);
    newPoint.y = (float)(27);
    site.point = newPoint;
    site.perimetralLines.clear();
    site.color = sf::Color(rand() % 255, rand() % 255, rand() % 255, rand() % 255);
    points.push_back(newPoint);
    sites.push_back(site);

    auxsites.push_back(s);
    auxsitesLittle.push_back(s);

    newPoint.x = (float)(578);
    newPoint.y = (float)(464);
    site.point = newPoint;
    site.perimetralLines.clear();
    site.color = sf::Color(rand() % 255, rand() % 255, rand() % 255, rand() % 255);
    points.push_back(newPoint);
    sites.push_back(site);

    auxsites.push_back(s);
    auxsitesLittle.push_back(s);


    newPoint.x = (float)(714);
    newPoint.y = (float)(91);
    site.point = newPoint;
    site.perimetralLines.clear();
    site.color = sf::Color(rand() % 255, rand() % 255, rand() % 255, rand() % 255);
    points.push_back(newPoint);
    sites.push_back(site);

    auxsites.push_back(s);
    auxsitesLittle.push_back(s);

    newPoint.x = (float)(937);
    newPoint.y = (float)(514);
    site.point = newPoint;
    site.perimetralLines.clear();
    site.color = sf::Color(rand() % 255, rand() % 255, rand() % 255, rand() % 255);
    points.push_back(newPoint);
    sites.push_back(site);

    auxsites.push_back(s);
    auxsitesLittle.push_back(s);

    newPoint.x = (float)(826);
    newPoint.y = (float)(438);
    site.point = newPoint;
    site.perimetralLines.clear();
    site.color = sf::Color(rand() % 255, rand() % 255, rand() % 255, rand() % 255);
    points.push_back(newPoint);
    sites.push_back(site);

    auxsites.push_back(s);
    auxsitesLittle.push_back(s);

    newPoint.x = (float)(485);
    newPoint.y = (float)(650);
    site.point = newPoint;
    site.perimetralLines.clear();
    site.color = sf::Color(rand() % 255, rand() % 255, rand() % 255, rand() % 255);
    points.push_back(newPoint);
    sites.push_back(site);

    auxsites.push_back(s);
    auxsitesLittle.push_back(s);

    newPoint.x = (float)(710);
    newPoint.y = (float)(137);
    site.point = newPoint;
    site.perimetralLines.clear();
    site.color = sf::Color(rand() % 255, rand() % 255, rand() % 255, rand() % 255);
    points.push_back(newPoint);
    sites.push_back(site);

    auxsites.push_back(s);
    auxsitesLittle.push_back(s);


    newPoint.x = (float)(701);
    newPoint.y = (float)(3);
    site.point = newPoint;
    site.perimetralLines.clear();
    site.color = sf::Color(rand() % 255, rand() % 255, rand() % 255, rand() % 255);
    points.push_back(newPoint);
    sites.push_back(site);

    auxsites.push_back(s);
    auxsitesLittle.push_back(s);

    newPoint.x = (float)(158);
    newPoint.y = (float)(694);
    site.point = newPoint;
    site.perimetralLines.clear();
    site.color = sf::Color(rand() % 255, rand() % 255, rand() % 255, rand() % 255);
    points.push_back(newPoint);
    sites.push_back(site);

    auxsites.push_back(s);
    auxsitesLittle.push_back(s);

    newPoint.x = (float)(458);
    newPoint.y = (float)(592);
    site.point = newPoint;
    site.perimetralLines.clear();
    site.color = sf::Color(rand() % 255, rand() % 255, rand() % 255, rand() % 255);
    points.push_back(newPoint);
    sites.push_back(site);

    auxsites.push_back(s);
    auxsitesLittle.push_back(s);

    newPoint.x = (float)(720);
    newPoint.y = (float)(386);
    site.point = newPoint;
    site.perimetralLines.clear();
    site.color = sf::Color(rand() % 255, rand() % 255, rand() % 255, rand() % 255);
    points.push_back(newPoint);
    sites.push_back(site);

    auxsites.push_back(s);
    auxsitesLittle.push_back(s);

    newPoint.x = (float)(548);
    newPoint.y = (float)(351);
    site.point = newPoint;
    site.perimetralLines.clear();
    site.color = sf::Color(rand() % 255, rand() % 255, rand() % 255, rand() % 255);
    points.push_back(newPoint);
    sites.push_back(site);

    auxsites.push_back(s);
    auxsitesLittle.push_back(s);
}

void Voronoi::init(int32_t nPoints){

  Line newLine;
  newLine.p1.x = 0.0f;
  newLine.p1.y = 0.0f;
  newLine.p2.x = (float)map.size.width;
  newLine.p2.y = 0.0f;
  lines.push_back(newLine);

  newLine.p1.x = (float)map.size.width;
  newLine.p1.y = 0.0f;
  newLine.p2.x = (float)map.size.width;
  newLine.p2.y = (float)map.size.height;
  lines.push_back(newLine);

  newLine.p1.x = (float)map.size.width;
  newLine.p1.y = (float)map.size.height-1;
  newLine.p2.x = 0.0f;
  newLine.p2.y = (float)map.size.height -1;
  lines.push_back(newLine);

  newLine.p1.x = 0.0f;
  newLine.p1.y = (float)map.size.height;
  newLine.p2.x = 0.0f;
  newLine.p2.y = 0.0f;
  lines.push_back(newLine);


  for(int i = 0; i < nPoints; i++){

    Cells site;
    sf::Vector2<float> newPoint;
    newPoint.x = (float)(rand() % (int)map.size.width);
    newPoint.y = (float)(rand() % (int)map.size.height);
    site.point = newPoint;  
    site.perimetralLines.clear();
    site.color = sf::Color((rand() % 155 )+100, (rand() % 155) + 100, (rand() % 155) + 100, (rand() % 155) + 100);
    points.push_back(newPoint);
    sites.push_back(site);
    AuxCell s;
    auxsites.push_back(s);
    auxsitesLittle.push_back(s);
  }

  maxX = map.size.width + 500.0f;
  
}

void Voronoi::draw(sf::RenderWindow* window) {
  sf::Vector2<float> p1 = { (float)d, 0.0f };
  sf::Vector2<float> p2 = { (float)d, (float)h };
  sf::Vertex directriz[] =
  {
      sf::Vertex(p1),
      sf::Vertex(p2)

  };

  window->draw(directriz, 2, sf::Lines);

  sf::Vector2<float> p3 = { 0.0f, horizontal };
  sf::Vector2<float> p4 = { (float)w,horizontal };
  sf::Vertex ho[] =
  {
      sf::Vertex(p3),
      sf::Vertex(p4)

  };

  window->draw(ho, 2, sf::Lines);

  for (int p = 0; p < (int)paraboleDraw.size(); ++p) {
    for (int x = 0; x < w; x++) {
      float a = paraboleDraw[p].x;
      float b = paraboleDraw[p].y;
      float c = paraboleDraw[p].z - x;
      float denominator = 2.0f * a;
      float insideSqrt = (b * b) - (4.0f * a * c);
      if (insideSqrt < 0) {
        insideSqrt = 0;
      }
      float y1 = (-b + sqrt(insideSqrt)) / denominator;
      float y2 = (-b - sqrt(insideSqrt)) / denominator;

      a = paraboleDraw[p].x;
      b = paraboleDraw[p].y;
      c = paraboleDraw[p].z - x - 1;
      denominator = 2.0f * a;
      insideSqrt = (b * b) - (4.0f * a * c);
      if (insideSqrt < 0) {
        insideSqrt = 0;
      }
      float y3 = (-b + sqrt(insideSqrt)) / denominator;
      float y4 = (-b - sqrt(insideSqrt)) / denominator;
      sf::Vector2<float> p1 = { (float)x,  y1 };
      sf::Vector2<float> p2 = { (float)x + 1, y3 };
      sf::Vertex linepp[] =
      {
          sf::Vertex(p1),
          sf::Vertex(p2)

      };

      sf::Vector2<float> p3 = { (float)x,  y2 };
      sf::Vector2<float> p4 = { (float)x + 1, y4 };
      sf::Vertex linepn[] =
      {
          sf::Vertex(p3),
          sf::Vertex(p4)

      };

      window->draw(linepp, 2, sf::Lines);
      window->draw(linepn, 2, sf::Lines);
    }

  }

  for (int l = 0; l < (int)lines.size(); l++) {
    sf::Vertex line[] =
    {
        sf::Vertex(lines[l].p1),
        sf::Vertex(lines[l].p2),
    };
    line[0].color = (sf::Color(150, 50, 250));
    line[1].color = (sf::Color(150, 50, 250));
    window->draw(line, 2, sf::Lines);
  }

  for (int p = 0; p < (int)sites.size(); p++) {
    sf::RectangleShape rect;
    rect.setOutlineColor(sf::Color::White);
    rect.setFillColor(sf::Color::White);
    rect.setSize(sf::Vector2f(2.0f, 2.0f));

    rect.setPosition(sf::Vector2f(sites[p].point.x, sites[p].point.y));
    window->draw(rect);

    for (int l = 0; l < (int)sites[p].perimetralLines.size(); ++l) {
      if (drawSectors) {
        sf::Vertex triangle[] =
        {
            sites[p].perimetralLines[l].p1,
            sites[p].perimetralLines[l].p2,
            sites[p].point
        };

        triangle[0].color = sites[p].color;
        triangle[1].color = sites[p].color;
        triangle[2].color = sites[p].color;
        window->draw(triangle, 3, sf::Triangles);
      }
      sf::Vertex line[] =
      {
          sites[p].perimetralLines[l].p1,
          sites[p].perimetralLines[l].p2
      };

      line[0].color = sites[p].color;
      line[1].color = sites[p].color;
      window->draw(line, 2, sf::Lines);


    }

  }
  if (drawIPoints) {
    for (int p = 0; p < (int)solutionsVoronoi.size(); p++) {
      sf::RectangleShape rect;
      rect.setOutlineColor(sf::Color::Green);
      rect.setFillColor(sf::Color::Green);
      rect.setSize(sf::Vector2f(6.0f, 6.0f));

      rect.setPosition(sf::Vector2f(solutionsVoronoi[p].point.x - 3, solutionsVoronoi[p].point.y - 3));
      window->draw(rect);


    }
  }

 /* for (int p = 0; p < (int)paraboleIPoints.size(); p++) {
    sf::RectangleShape rect;
    rect.setOutlineColor(sf::Color::Red);
    rect.setFillColor(sf::Color::Red);
    rect.setSize(sf::Vector2f(4.0f, 4.0f));

    rect.setPosition(sf::Vector2f(paraboleIPoints[p].point.x - 2, paraboleIPoints[p].point.y -2));
    window->draw(rect);


  }*/



 if(drawAllLine){

    for (int p = 0; p < (int)linesBisector.size(); p++) {
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


}

void Voronoi::clear()
{
  points.clear();
  Mpoints.clear();
  Spoints.clear();
  parabole.clear();
  paraboleDraw.clear();
  paraboleIPoints.clear();
  bisector.clear();
  lines.clear();
  linesBisector.clear();
  goodLinesBisector.clear();
  int c = 0;
  for (c; c < (int)sites.size(); c++) {
    sites[c].perimetralLines.clear();
  }
  sites.clear();

  for (c = 0; c < (int)auxsitesLittle.size(); c++) {
    auxsitesLittle[c].upperPoints.clear();
    auxsitesLittle[c].bottonPoints.clear();
  }
  auxsitesLittle.clear();

  for (c = 0; c < (int)auxsites.size(); c++) {
    auxsites[c].upperPoints.clear();
    auxsites[c].bottonPoints.clear();
  }
  auxsites.clear();


  solutions.clear();
  solutionsVoronoi.clear();


}

inline bool compareMargin(float x, float y, float error) {
  return ((y - error <= x) && (x <= y + error));
}


float module(sf::Vector2<float> v){
  return sqrtf((v.x * v.x) + (v.y * v.y));
}


void Voronoi::calculateParabolaDraw()
{
  float di = d;
  
  paraboleDraw.clear();
  
  for (int p = 0; p < (int)points.size(); p++) {
    if (points[p].x < di) {
      //Creo parabola  
      sf::Vector3<float> newParabole;

      float mp = ((float)di - points[p].x) * 0.5f;
      sf::Vector2<float> V = { points[p].x + mp, points[p].y };
      float h = V.x;
      float k = V.y;
      float xp = (4.0f * h * mp);
      newParabole.x = 1.0f;
      newParabole.y = -2.0f * k;
      newParabole.z = (k * k) - xp;

      newParabole /= -4.0f * mp;


      paraboleDraw.push_back(newParabole);
    }
  }
}


 void Voronoi::calculateParabola() {

    bool firstSol = true;
    bool not = true;


    for (int i = 0; i < (int)sites.size(); ++i) {
      sites[i].perimetralLines.clear();
    }for (int i = 0; i < (int)auxsites.size(); ++i) {
      auxsites[i].bottonPoints.clear();
      auxsites[i].upperPoints.clear();
      auxsitesLittle[i].upperPoints.clear();
      auxsitesLittle[i].upperPoints.clear();
    }
    solutionsVoronoi.clear();
    paraboleIPoints.clear();
    float di = 378.3f;
   // for (di = 0; di < w + 1000; di += 0.005f) {
      parabole.clear();

      solutions.clear();
      for (int p = 0; p < (int)sites.size(); p++) {
        float dist = di - sites[p].point.x;
        if (sites[p].point.x < di) {
          //Creo parabola  
          Parabole newParabole;

          float mp = ((float)di - sites[p].point.x) * 0.5f;
          sf::Vector2<float> V = { sites[p].point.x + mp, sites[p].point.y };
          float h = V.x;
          float k = V.y;
          float xp = (4.0f * h * mp);
          newParabole.parentPoint = p;
          newParabole.parabole.x = 1.0f;
          newParabole.parabole.y = -2.0f * k;
          newParabole.parabole.z = (k * k) - xp;

          newParabole.parabole /= -4.0f * mp;


          parabole.push_back(newParabole);
        }
      }
      int pp = 1;
      // Calcular puntos de corte 
      for (int p = 0; p < (int)parabole.size(); ++p) {
        //Corte con los cuatro bordes
        { //x = 0
          {
            float x1 = 0;
            float a = parabole[p].parabole.x;
            float b = parabole[p].parabole.y;
            float c = parabole[p].parabole.z - x1;
            float denominator = 2.0f * a;
            float insideSqrt = (b * b) - (4.0f * a * c);

            float y1 = (-b + sqrt(insideSqrt)) / denominator;
            float y2 = (-b - sqrt(insideSqrt)) / denominator;

            bool solutionXInRange = ((x1 >= -1) && (x1 <= 960));
            bool solutionYInRange = ((y1 >= -1) && (y1 <= 704));
            bool validSolution = ((solutionXInRange) && (solutionYInRange) && (isBeachLine({ x1,y1 })));
            if (validSolution) {
              if (firstSol) {
                Solution newSol;
                newSol.n = 1;
                newSol.point = { x1,y1 };
                newSol.sites[0] = parabole[p].parentPoint;
                solutions.push_back(newSol);
                firstSol = false;
              }
              else {
                bool alreadySol = false;
                for (int s = 0; s < (int)solutions.size() && !alreadySol; ++s) {
                  float x = solutions[s].point.x;
                  float y = solutions[s].point.y;
                  bool sameSol = (compareMargin(x1, x, marginSamePoint) && compareMargin(y1, y, marginSamePoint));
                  if (sameSol) {
                    solutions[s].n++;
                    if (solutions[s].sites[0] != parabole[p].parentPoint && solutions[s].sites[1] != parabole[p].parentPoint) {
                      solutions[s].sites[2] = parabole[p].parentPoint;
                    }
                    else {
                      solutions[s].sites[1] = parabole[p].parentPoint;
                    }

                    alreadySol = true;
                  }
                }
                if (!alreadySol) {
                  Solution newSol;
                  newSol.n = 1;
                  newSol.sites[0] = parabole[p].parentPoint;
                  newSol.point = { x1,y1 };
                  solutions.push_back(newSol);
                }
              }
            }
            solutionXInRange = ((x1 >= -1) && (x1 <= 960));
            solutionYInRange = ((y2 >= -1) && (y2 <= 704));
            validSolution = ((solutionXInRange) && (solutionYInRange) && (isBeachLine({ x1,y2 })));
            if (validSolution) {
              if (firstSol) {
                Solution newSol;
                newSol.n = 1;
                newSol.point = { x1,y2 };
                newSol.sites[0] = parabole[p].parentPoint;
                solutions.push_back(newSol);
                firstSol = false;
              }
              else {
                bool alreadySol = false;
                for (int s = 0; s < (int)solutions.size() && !alreadySol; ++s) {
                  float x = solutions[s].point.x;
                  float y = solutions[s].point.y;
                  bool sameSol = (compareMargin(x1, x, marginSamePoint) && compareMargin(y2, y, marginSamePoint));
                  if (sameSol) {
                    solutions[s].n++;
                    if (solutions[s].sites[0] != parabole[p].parentPoint && solutions[s].sites[1] != parabole[p].parentPoint) {
                      solutions[s].sites[2] = parabole[p].parentPoint;
                    }
                    else {
                      solutions[s].sites[1] = parabole[p].parentPoint;
                    }
                    alreadySol = true;
                  }
                }
                if (!alreadySol) {
                  Solution newSol;
                  newSol.n = 1;
                  newSol.sites[0] = parabole[p].parentPoint;
                  newSol.point = { x1,y2 };
                  solutions.push_back(newSol);
                }
              }
            }
          }
          // x = 960
          {
            float x1 = 960;
            float a = parabole[p].parabole.x;
            float b = parabole[p].parabole.y;
            float c = parabole[p].parabole.z - x1;
            float denominator = 2.0f * a;
            float insideSqrt = (b * b) - (4.0f * a * c);

            float y1 = (-b + sqrt(insideSqrt)) / denominator;
            float y2 = (-b - sqrt(insideSqrt)) / denominator;

            bool solutionXInRange = ((x1 >= -1) && (x1 <= 960));
            bool solutionYInRange = ((y1 >= -1) && (y1 <= 704));
            bool validSolution = ((solutionXInRange) && (solutionYInRange) && (isBeachLine({ x1,y1 })));
            if (validSolution) {
              if (firstSol) {
                Solution newSol;
                newSol.n = 1;
                newSol.sites[0] = parabole[p].parentPoint;
                newSol.point = { x1,y1 };
                solutions.push_back(newSol);
                firstSol = false;
              }
              else {
                bool alreadySol = false;
                for (int s = 0; s < (int)solutions.size() && !alreadySol; ++s) {
                  float x = solutions[s].point.x;
                  float y = solutions[s].point.y;
                  bool sameSol = (compareMargin(x1, x, marginSamePoint) && compareMargin(y1, y, marginSamePoint));
                  if (sameSol) {
                    solutions[s].n++;
                    if (solutions[s].sites[0] != parabole[p].parentPoint && solutions[s].sites[1] != parabole[p].parentPoint) {
                      solutions[s].sites[2] = parabole[p].parentPoint;
                    }
                    else {
                      solutions[s].sites[1] = parabole[p].parentPoint;
                    }
                    alreadySol = true;
                  }
                }
                if (!alreadySol) {
                  Solution newSol;
                  newSol.n = 1;
                  newSol.sites[0] = parabole[p].parentPoint;
                  newSol.point = { x1,y1 };
                  solutions.push_back(newSol);
                }
              }
            }
            solutionXInRange = ((x1 >= -1) && (x1 <= 960));
            solutionYInRange = ((y2 >= -1) && (y2 <= 704));
            validSolution = ((solutionXInRange) && (solutionYInRange) && (isBeachLine({ x1,y2 })));
            if (validSolution) {
              if (firstSol) {
                Solution newSol;
                newSol.n = 1;
                newSol.sites[0] = parabole[p].parentPoint;
                newSol.point = { x1,y2 };
                solutions.push_back(newSol);
                firstSol = false;
              }
              else {
                bool alreadySol = false;
                for (int s = 0; s < (int)solutions.size() && !alreadySol; ++s) {
                  float x = solutions[s].point.x;
                  float y = solutions[s].point.y;
                  bool sameSol = (compareMargin(x1, x, marginSamePoint) && compareMargin(y2, y, marginSamePoint));
                  if (sameSol) {
                    if (solutions[s].sites[0] != parabole[p].parentPoint && solutions[s].sites[1] != parabole[p].parentPoint) {
                      solutions[s].sites[2] = parabole[p].parentPoint;;
                    }
                    else {
                      solutions[s].sites[1] = parabole[p].parentPoint;;
                    }
                    solutions[s].n++;
                    alreadySol = true;
                  }
                }
                if (!alreadySol) {
                  Solution newSol;
                  newSol.n = 1;
                  newSol.sites[0] = parabole[p].parentPoint;;
                  newSol.point = { x1,y2 };
                  solutions.push_back(newSol);
                }
              }
            }
          }
          // y = 0 y = 704
          {
            float y1 = 0;
            float y2 = 704;
            float x1 = y1 * y1 * parabole[p].parabole.x + y1 * parabole[p].parabole.y + parabole[p].parabole.z;
            float x2 = y2 * y2 * parabole[p].parabole.x + y2 * parabole[p].parabole.y + parabole[p].parabole.z;

            bool solutionXInRange = ((x1 >= -1) && (x1 <= 960));
            bool solutionYInRange = ((y1 >= -1) && (y1 <= 704));
            bool validSolution = ((solutionXInRange) && (solutionYInRange) && (isBeachLine({ x1,y1 })));
            if (validSolution) {
              if (firstSol) {
                Solution newSol;
                newSol.n = 1;
                newSol.sites[0] = parabole[p].parentPoint;;
                newSol.point = { x1,y1 };
                solutions.push_back(newSol);
                firstSol = false;
              }
              else {
                bool alreadySol = false;
                for (int s = 0; s < (int)solutions.size() && !alreadySol; ++s) {
                  float x = solutions[s].point.x;
                  float y = solutions[s].point.y;
                  bool sameSol = (compareMargin(x1, x, marginSamePoint) && compareMargin(y1, y, marginSamePoint));
                  if (sameSol) {
                    if (solutions[s].sites[0] != parabole[p].parentPoint && solutions[s].sites[1] != parabole[p].parentPoint) {
                      solutions[s].sites[2] = parabole[p].parentPoint;;
                    }
                    else {
                      solutions[s].sites[1] = parabole[p].parentPoint;;
                    }
                    solutions[s].n++;
                    alreadySol = true;
                  }
                }
                if (!alreadySol) {
                  Solution newSol;
                  newSol.n = 1;
                  newSol.sites[0] = parabole[p].parentPoint;;
                  newSol.point = { x1,y1 };
                  solutions.push_back(newSol);
                }
              }
            }
            solutionXInRange = ((x2 >= -1) && (x2 <= 960));
            solutionYInRange = ((y2 >= -1) && (y2 <= 704));
            validSolution = ((solutionXInRange) && (solutionYInRange) && (isBeachLine({ x2,y2 })));
            if (validSolution) {
              if (firstSol) {
                Solution newSol;
                newSol.n = 1;
                newSol.sites[0] = parabole[p].parentPoint;;
                newSol.point = { x2,y2 };
                solutions.push_back(newSol);
                firstSol = false;
              }
              else {
                bool alreadySol = false;
                for (int s = 0; s < (int)solutions.size() && !alreadySol; ++s) {
                  float x = solutions[s].point.x;
                  float y = solutions[s].point.y;
                  bool sameSol = (compareMargin(x2, x, marginSamePoint) && compareMargin(y2, y, marginSamePoint));
                  if (sameSol) {
                    if (solutions[s].sites[0] != parabole[p].parentPoint && solutions[s].sites[1] != parabole[p].parentPoint) {
                      solutions[s].sites[2] = parabole[p].parentPoint;;
                    }
                    else {
                      solutions[s].sites[1] = parabole[p].parentPoint;;
                    }
                    solutions[s].n++;
                    alreadySol = true;
                  }
                }
                if (!alreadySol) {
                  Solution newSol;
                  newSol.n = 1;
                  newSol.sites[0] = parabole[p].parentPoint;;
                  newSol.point = { x2,y2 };
                  solutions.push_back(newSol);
                }
              }
            }
          }
        }

        // Corte con parablolas
        for (int p1 = pp; p1 < (int)parabole.size(); ++p1) {

          if (p != p1) {
            float a = parabole[p].parabole.x - parabole[p1].parabole.x;
            float b = parabole[p].parabole.y - parabole[p1].parabole.y;
            float c = parabole[p].parabole.z - parabole[p1].parabole.z;
            float denominator = 2.0f * a;
            float insideSqrt = (b * b) - (4.0f * a * c);
            float y1 = (-b + sqrt(insideSqrt)) / denominator;
            float y2 = (-b - sqrt(insideSqrt)) / denominator;

            a = parabole[p].parabole.x * y1 * y1;
            b = parabole[p].parabole.y * y1;
            c = parabole[p].parabole.z;
            float x1 = a + b + c;

            a = parabole[p].parabole.x * y2 * y2;
            b = parabole[p].parabole.y * y2;
            float x2 = a + b + c;

            bool solutionXInRange = ((x1 >= -1) && (x1 <= 961));
            bool solutionYInRange = ((y1 >= -1) && (y1 <= 705));
            bool validSolution = ((solutionXInRange) && (solutionYInRange) && (isBeachLine({ x1,y1 })));

            if (validSolution) {
              if (firstSol) {
                Solution newSol;
                newSol.n = 1;
                newSol.point = { x1,y1 };
                newSol.sites[0] = parabole[p].parentPoint;
                newSol.sites[1] = parabole[p1].parentPoint;
                solutions.push_back(newSol);
                firstSol = false;
              }
              else {
                bool alreadySol = false;
                for (int s = 0; s < (int)solutions.size() && !alreadySol; ++s) {
                  float x = solutions[s].point.x;
                  float y = solutions[s].point.y;
                  bool sameSol = (compareMargin(x1, x, marginSamePoint) && compareMargin(y1, y, marginSamePoint));
                  if (sameSol) {
                    if (solutions[s].sites[0] != parabole[p].parentPoint && solutions[s].sites[1] != parabole[p].parentPoint) {
                      solutions[s].sites[2] = parabole[p].parentPoint;
                    }
                    else {
                      solutions[s].sites[2] = parabole[p1].parentPoint;
                    }


                    solutions[s].n++;
                    alreadySol = true;
                  }
                }
                if (!alreadySol) {
                  Solution newSol;
                  newSol.n = 1;
                  newSol.point = { x1,y1 };
                  newSol.sites[0] = parabole[p].parentPoint;
                  newSol.sites[1] = parabole[p1].parentPoint;
                  solutions.push_back(newSol);
                }
              }
            }
            solutionXInRange = ((x2 >= -1) && (x2 <= 961));
            solutionYInRange = ((y2 >= -1) && (y2 <= 705));
            validSolution = ((solutionXInRange) && (solutionYInRange) && (isBeachLine({ x2,y2 })));
            if (validSolution) {
              if (firstSol) {
                Solution newSol;
                newSol.n = 1;
                newSol.sites[0] = parabole[p].parentPoint;
                newSol.sites[1] = parabole[p1].parentPoint;
                newSol.point = { x2,y2 };
                solutions.push_back(newSol);
                firstSol = false;
              }
              else {
                bool alreadySol = false;
                for (int s = 0; s < (int)solutions.size() && !alreadySol; ++s) {
                  float x = solutions[s].point.x;
                  float y = solutions[s].point.y;
                  bool sameSol = (compareMargin(x2, x, marginSamePoint) && compareMargin(y2, y, marginSamePoint));
                  if (sameSol) {

                    if (solutions[s].sites[0] != parabole[p].parentPoint && solutions[s].sites[1] != parabole[p].parentPoint) {
                      solutions[s].sites[2] = parabole[p].parentPoint;
                    }
                    else {
                      solutions[s].sites[2] = parabole[p1].parentPoint;
                    }
                    solutions[s].n++;
                    alreadySol = true;
                  }
                }
                if (!alreadySol) {
                  Solution newSol;
                  newSol.n = 1;
                  newSol.sites[0] = parabole[p].parentPoint;
                  newSol.sites[1] = parabole[p1].parentPoint;
                  newSol.point = { x2,y2 };
                  solutions.push_back(newSol);
                }
              }
            }
          }
        }
        pp++;
      }
      // Check for a valid sol
      for (int i = 0; i < (int)solutions.size(); ++i) {
        if (solutions[i].n >= 2) {
          paraboleIPoints.push_back(solutions[i]);
        }

      }

    //}

    // Delete unecessary points

    for (int i = 0; i < (int)paraboleIPoints.size(); ++i) {

      if (solutionsVoronoi2.empty()) {
        solutionsVoronoi2.push_back(paraboleIPoints[i]);
      }
      else {
        bool samePoint = false;
        for (int j = 0; j < (int)solutionsVoronoi2.size() && !samePoint; ++j) {
          bool sameX = compareMargin(solutionsVoronoi2[j].point.x, paraboleIPoints[i].point.x, sameSolMargin);
          bool sameY = compareMargin(solutionsVoronoi2[j].point.y, paraboleIPoints[i].point.y, sameSolMargin);
          samePoint = sameX && sameY;
        }
        if (!samePoint) {
          solutionsVoronoi2.push_back(paraboleIPoints[i]);
        }
      }
    }
}



void Voronoi::addSolution(float x, float y, uint32_t paraboleIndex, uint32_t parabole2Index){


  bool solutionXInRange = ((x >= -1) && (x <= 960));
  bool solutionYInRange = ((y >= -1) && (y <= 704));
  bool validSolution = ((solutionXInRange) && (solutionYInRange) && (isBeachLine({ x,y })));
  if (validSolution) {
    if (firstSol) {
      Solution newSol;
      newSol.n = 1;
      newSol.point = { x,y };
      if(paraboleIndex != -1){
        newSol.parentSites.push_back(paraboleIndex);
      }
      if(parabole2Index != -1){
        newSol.parentSites.push_back(parabole2Index);
      }
      solutions.push_back(newSol);
      firstSol = false;
    }
    else {
      bool alreadySol = false;
      for (int s = 0; s < (int)solutions.size() && !alreadySol; ++s) {
        float tmpx = solutions[s].point.x;
        float tmpy = solutions[s].point.y;
        bool sameSol = (compareMargin(x, tmpx, marginSamePoint) && compareMargin(y,tmpy, marginSamePoint));
        if (sameSol) {
          solutions[s].n++;
          //Need to be changed
          int a;
          bool noParentSiteAlready = true;
          bool noParent2SiteAlready = true;
          for (a = 0; a < solutions[s].parentSites.size() && (noParentSiteAlready || noParent2SiteAlready); ++a){
            if (solutions[s].parentSites[a] == paraboleIndex) {
              noParentSiteAlready = false;
            }
            if(
               solutions[s].parentSites[a] == parabole2Index){
              noParent2SiteAlready = false;
            }
          }
          if (noParentSiteAlready) {
            if (paraboleIndex != -1) {
              solutions[s].parentSites.push_back(paraboleIndex);
            }
          }
          if(noParent2SiteAlready){
            if (parabole2Index != -1) {
              solutions[s].parentSites.push_back(parabole2Index);
            }
          }

          alreadySol = true;
        }
      }
      if (!alreadySol) {
        Solution newSol;
        newSol.n = 1;
        if (paraboleIndex != -1) {
          newSol.parentSites.push_back(paraboleIndex);
        }
        if (parabole2Index != -1) {
          newSol.parentSites.push_back(parabole2Index);
        }
        newSol.point = { x,y };
        solutions.push_back(newSol);
      }
    }
  }
}


void Voronoi::intersectionParaboleHLine(Parabole p, float y){

  float x1 = y ;
  float a = p.parabole.x;
  float b = p.parabole.y;
  float c = p.parabole.z - x1;
  float denominator = 2.0f * a;
  float insideSqrt = (b * b) - (4.0f * a * c);

  float y1 = (-b + sqrt(insideSqrt)) / denominator;
  float y2 = (-b - sqrt(insideSqrt)) / denominator;
  addSolution(x1, y1, p.parentPoint);
  addSolution(x1, y2, p.parentPoint);
}

void Voronoi::intersectionParaboleVLine(Parabole p, float x){ }

void Voronoi::intersectionParaboleParabole(Parabole p, Parabole q){

  float a = p.parabole.x - q.parabole.x;
  float b = p.parabole.y - q.parabole.y;
  float c = p.parabole.z - q.parabole.z;
  float denominator = 2.0f * a;
  float insideSqrt = (b * b) - (4.0f * a * c);
  float y1 = (-b + sqrt(insideSqrt)) / denominator;
  float y2 = (-b - sqrt(insideSqrt)) / denominator;

  a = p.parabole.x * y1 * y1;
  b = p.parabole.y * y1;
  c = p.parabole.z;
  float x1 = a + b + c;

  a = p.parabole.x * y2 * y2;
  b = p.parabole.y * y2;
  float x2 = a + b + c;

  addSolution(x1, y1,p.parentPoint, q.parentPoint);
  addSolution(x2, y2,p.parentPoint, q.parentPoint);

  


}

void Voronoi::calculateSites(){


  for (int i = 0; i < (int)sites.size(); ++i) {
    sites[i].perimetralLines.clear();
  }for (int i = 0; i < (int)auxsites.size(); ++i) {
    auxsites[i].bottonPoints.clear();
    auxsites[i].upperPoints.clear();
    auxsitesLittle[i].upperPoints.clear();
    auxsitesLittle[i].upperPoints.clear();
  }
  solutionsVoronoi.clear();
  paraboleIPoints.clear();

  
  float directrizLine = 378.3f;
 // for (directrizLine = 0.0f; directrizLine < maxX; directrizLine += stepParabole) {
    solutions.clear();
    parabole.clear();
    firstSol = false;
    int i;
    //Calculate the parabole for each point
    for (i = 0; i < (int)sites.size(); ++i) {

      bool pointLeftParabole = sites[i].point.x < directrizLine;
      if(pointLeftParabole){
        //Can calculate the parabolas a its possible intersection
        Parabole newParabole;

        float mp = ((float)directrizLine - sites[i].point.x) * 0.5f;
        sf::Vector2<float> V = { sites[i].point.x + mp, sites[i].point.y };
        float h = V.x;
        float k = V.y;
        float xp = (4.0f * h * mp);
        newParabole.parentPoint = i;
        newParabole.parabole.x = 1.0f;
        newParabole.parabole.y = -2.0f * k;
        newParabole.parabole.z = (k * k) - xp;

        newParabole.parabole /= -4.0f * mp;


        parabole.push_back(newParabole);
      }
    }

    // Once parabole are calculated, we have to calculate each possible intersection point
    int p, pp;
    for(p = 0; p <parabole.size(); ++p){

    //Border of the map
      {
        intersectionParaboleHLine(parabole[p], 0);
        intersectionParaboleHLine(parabole[p], map.size.width);
        intersectionParaboleVLine(parabole[p], 0);
        intersectionParaboleVLine(parabole[p], map.size.height);
      }
      //Parabole with the other paraboles
      {
        for(pp = p+1; pp < parabole.size(); ++pp){
          intersectionParaboleParabole(parabole[p], parabole[pp]);
        }
      }
    }

    for (int i = 0; i < (int)solutions.size(); ++i) {
      if (solutions[i].n >= 2) {
        paraboleIPoints.push_back(solutions[i]);
      }

    }
 // }
  






// Delete unecessary points

for (int i = 0; i < (int)paraboleIPoints.size(); ++i) {

  if (solutionsVoronoi.empty()) {
    solutionsVoronoi.push_back(paraboleIPoints[i]);
  }
  else {
    bool samePoint = false;
    for (int j = 0; j < (int)solutionsVoronoi.size() && !samePoint; ++j) {
      bool sameX = compareMargin(solutionsVoronoi[j].point.x, paraboleIPoints[i].point.x, sameSolMargin);
      bool sameY = compareMargin(solutionsVoronoi[j].point.y, paraboleIPoints[i].point.y, sameSolMargin);
      samePoint = sameX && sameY;
    }
    if (!samePoint) {
      solutionsVoronoi.push_back(paraboleIPoints[i]);
    }
  }
}

  
}


float dotProtduct(sf::Vector2<float> v1, sf::Vector2<float> v2){


  float p = v1.x * v2.x + v1.y * v2.y;
  float m = sqrtf((v1.x * v1.x) + (v1.y * v1.y)) * sqrtf((v2.x * v2.x) + (v2.y * v2.y));
  return p / m;
}


void Voronoi::calculateBisector()
{
  int p = 0;
  //int j = 1;
  bisector.clear();
  Mpoints.clear();
  Spoints.clear();
  linesBisector.clear();
  goodLinesBisector.clear();
  int ii = 1;
  for (int p = 0; p < (int)points.size(); p++) {
    for(int j = ii; j < (int)points.size(); j++){

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
        for(int l = 0; l < (int)lines.size(); l++){
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
              goodLinesBisector.push_back(newBisector);
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
  for(int i = 0; i < (int)linesBisector.size(); ++ i){

    for(int j = ii; j < (int)linesBisector.size(); ++ j){

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
            if (module(goodLinesBisector[i].p1 - goodLinesBisector[i].p2) >= module(p - goodLinesBisector[i].p2)) {
              //Cambiamos
              goodLinesBisector[i].p1 = p;
            }
          }else if(compareMargin(dotvalue, -1.0f, 0.1f)){
            //Cambiar el 2
            if (module(goodLinesBisector[i].p1 - goodLinesBisector[i].p2) >= module(p - goodLinesBisector[i].p1)) {
              //Cambiamos
              goodLinesBisector[i].p2 = p;
            }
          }

          V1 = linesBisector[j].mp - linesBisector[j].p1;
          V2 = linesBisector[j].mp - p;
          dotvalue = dotProtduct(V1, V2);

          if (compareMargin(dotvalue, 1.0f, 0.1f)) {
            //Cambiar el 1
            if (module(goodLinesBisector[j].p1 - goodLinesBisector[j].p2) >= module(p - goodLinesBisector[j].p2)) {
              //Cambiamos
              goodLinesBisector[j].p1 = p;
            }
          }
          else if (compareMargin(dotvalue, -1.0f, 0.1f)) {
            //Cambiar el 2
            if (module(goodLinesBisector[j].p1 - goodLinesBisector[j].p2) >= module(p - goodLinesBisector[j].p1)) {
              //Cambiamos
              goodLinesBisector[j].p2 = p;
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

bool Voronoi::isBeachLine(sf::Vector2<float> p)
{

  for (int i = 0; i < (int)parabole.size() ; ++i) {
    sf::Vector2<float> p2;

    p2.y = p.y;
    p2.x = p2.y * p2.y * parabole[i].parabole.x + p2.y * parabole[i].parabole.y + parabole[i].parabole.z;

    if(compareMargin(p.y, p2.y, 0.1f) && p2.x > (p.x+0.1f) ){
      return false;
    }
  }
   
  return true;
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
