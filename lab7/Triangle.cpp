#include <iostream>
#include <cmath>
#include "easygl.h"
#include "Triangle.h"
using namespace std;


// Constructor. First set up base class (Shape), then store the 
// vertices, which are 3 (x,y) points giving offsets from the Shape center 
// to each triangle vertex.
Triangle::Triangle (string _name, string _colour, float _xcen, float _ycen,
            float xcoords[3], float ycoords[3]) 
              : Shape (_name, _colour, _xcen, _ycen) {
   
   for (int i = 0; i < 3; i++) {
      relVertex[i].x = xcoords[i];
      relVertex[i].y = ycoords[i];
   }
}


Triangle::~Triangle () {
   // No dynamic memory to delete
}


void Triangle::print () const {
   Shape::print();//
   cout << "triangle";
   for (int i = 0; i < 3; i++) {
      cout << " (" << relVertex[i].x << "," << relVertex[i].y << ")";
   }
   cout << endl;
}


void Triangle::scale (float scaleFac) {
   for (int i = 0; i < 3; i++) {
      relVertex[i].x *= scaleFac;
      relVertex[i].y *= scaleFac;
   }
}
   

float Triangle::computeArea () const {
   // 1/2 * base * height
   // The height requires some trigonometry to compute, for an arbitrary triangle.
   // Some manipulation gives a simpler formula to use in this case, which I use below.
   // Compute two vectors, from one vertex to each of the other two.
   // Then use the formula below to get area.
   float area;
   t_point vec1, vec2;
   vec1 = getVecBetweenPoints (relVertex[0], relVertex[1]);
   vec2 = getVecBetweenPoints (relVertex[0], relVertex[2]);
   
   area = 0.5 * abs (vec1.x * vec2.y - vec2.x * vec1.y);
   return area;
}


float Triangle::computePerimeter () const {
   float perimeter = 0;
   float sideLength;
   int endIndex;
   t_point dist;
   
   for (int i = 0; i < 3; i++) {
      endIndex = (i + 1) % 3;
      dist = getVecBetweenPoints (relVertex[i], relVertex[endIndex]);
      sideLength = sqrt (dist.x * dist.x + dist.y * dist.y);
      perimeter += sideLength;
   }
   return perimeter;
}


void Triangle::draw (easygl* window) const {
   // Load up the data structure needed by easygl, and draw the triangle
   // using the easygl::draw_polygon call.
   t_point coords[3];  // This data type is in easygl_constants.h
   for (int i = 0; i < 3; i++) {
      coords[i].x = getXcen() + relVertex[i].x;
      coords[i].y = getYcen() + relVertex[i].y;
   }
   window->gl_setcolor(getColour());
   window->gl_fillpoly(coords, 3);
}


bool Triangle::pointInside (float x, float y) const {
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
   
   for (int i = 0; i < 3; i++) {
      vecToClick = getVecBetweenPoints (relVertex[i], click);
      endIndex = (i + 1) % 3; // Next vertex after i
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
t_point Triangle::getVecBetweenPoints (t_point start, t_point end) const {
   t_point vec;
   vec.x = end.x - start.x;
   vec.y = end.y - start.y;
   return (vec);
}


// Return vec1 x vec2, where vec1 and vec2 are 2D vectors, and 
// hence the cross product is a single (z-directed) number.
float Triangle::getCrossProduct (t_point vec1, t_point vec2) const {
   return (vec1.x * vec2.y - vec1.y * vec2.x);
}
