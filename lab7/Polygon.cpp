
#include <iostream>
#include <cmath>
#include "easygl.h"
#include "Polygon.h"
using namespace std;


// Constructor. First set up base class (Shape), then store the 
// vertices, which are 3 (x,y) points giving offsets from the Shape center 
// to each triangle vertex.
Polygon::Polygon(string _name, string _colour, float _xcen, float _ycen,
            float xcoords[100], float ycoords[100], int _n) 
              : Shape (_name, _colour, _xcen, _ycen) {
    n = _n;//set n to total number of sides
   for (int i = 0; i < n; i++) {
      relVertex[i].x = xcoords[i];
      relVertex[i].y = ycoords[i];
   }
}


Polygon::~Polygon () {
   // No dynamic memory to delete
}


void Polygon::print () const {
   Shape::print();//

   cout << "polygon";
   for (int i = 0; i < n; i++) {
      cout << " (" << relVertex[i].x+getXcen() << "," << relVertex[i].y+getYcen() << ")";
   }
   cout << endl;
}


void Polygon::scale (float scaleFac) {
   for (int i = 0; i < n; i++) {
      relVertex[i].x *= scaleFac;
      relVertex[i].y *= scaleFac;
       
//      relVertex[i] = (relVertex[i].x + getXcen())*scaleFac;
//      relVertex[i] = (relVertex[i].y +getYcen())* scaleFac;
   }
}
   

float Polygon::computeArea () const {
   // 1/2 * base * height
   // The height requires some trigonometry to compute, for an arbitrary triangle.
   // Some manipulation gives a simpler formula to use in this case, which I use below.
   // Compute two vectors, from one vertex to each of the other two.
   // Then use the formula below to get area.
    
  float temp1, temp2;  
  float area = 0;         // Accumulates area in the loop
  int j = n-1;  // The last vertex is the 'previous' one to the first
  for (int i=0; i<n; i++)
    { 
      temp1 =relVertex[j].x+relVertex[i].x;
      temp2 = relVertex[j].y-relVertex[i].y;
      area = area + temp1*temp2; 
      j = i;  //j is previous vertex to i
    }
  return abs(area/2);//calculate the abs value for final value

}


float Polygon::computePerimeter () const {
   float perimeter = 0;
   float sideLength;
   int endIndex;
   t_point dist;
   
   for (int i = 0; i < n; i++) {
      endIndex = (i + 1) % n;
      dist = getVecBetweenPoints (relVertex[i], relVertex[endIndex]);
      sideLength = sqrt (dist.x * dist.x + dist.y * dist.y);
      perimeter += sideLength;
   }
   return perimeter;
}


void Polygon::draw (easygl* window) const {
   // Load up the data structure needed by easygl, and draw the triangle
   // using the easygl::draw_polygon call.
   t_point coords[n];  // This data type is in easygl_constants.h
   for (int i = 0; i < n; i++) {
      coords[i].x = getXcen() + relVertex[i].x;
      coords[i].y = getYcen() + relVertex[i].y;
   }
   window->gl_setcolor(getColour());
   window->gl_fillpoly(coords, n);
}


bool Polygon::pointInside (float x, float y) const {
   // Make a point that corresponds to where you clicked. Since all my
   // vertices are relative to the triangle center, it is more convenient
   // to also shift the click point so it is an offset from the triangle 
   // center.
   t_point click;
   click.x = x - getXcen();
   click.y = y - getYcen();
   
   // The test is that the cross product between the vector along an 
   // edge (from a vertex to the next vertex), and the vector from that 
   // start vertex to the click point, must have
   // the same sign (+ve or -ve) for all 3 vertices.  That guarantees the
   // click point is on the "inside" of all 3 triangle sides, and hence is 
   // in the triangle.
   
   //for triangle only +++ and --- means the click inside triangle area can return true
   t_point vecToClick, vecOfSide;
   float crossProduct;
   bool allNeg = true, allPos = true;
   int endIndex;
   
   for (int i = 0; i < n; i++) {
      vecToClick = getVecBetweenPoints (relVertex[i], click);
      endIndex = (i + 1) % n; // Next vertex after i
      vecOfSide = getVecBetweenPoints (relVertex[i], relVertex[endIndex]);
      crossProduct = getCrossProduct (vecOfSide, vecToClick);
      if (crossProduct <= 0) 
         allPos = false;
      else
         allNeg = false;
   }
   return (allPos || allNeg);
}


// Private helper functions below.  Working out triangle area etc. 
// requires some vector math, so these helper functions are useful.

// Return the (x,y) vector between start and end points.
t_point Polygon::getVecBetweenPoints (t_point start, t_point end) const {
   t_point vec;
   vec.x = end.x - start.x;
   vec.y = end.y - start.y;
   return (vec);
}


// Return vec1 x vec2, where vec1 and vec2 are 2D vectors, and 
// hence the cross product is a single (z-directed) number.
float Polygon::getCrossProduct (t_point vec1, t_point vec2) const {
   return (vec1.x * vec2.y - vec1.y * vec2.x);
}