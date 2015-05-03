/* 
 * File:   Rectangle.cpp
 * Author: lichuanr
 * 
 * Created on November 25, 2013, 8:30 PM
 */

#include "Rectangle.h"
#include <iostream>
#include <cmath>
#include "easygl.h"

using namespace std;


// Constructor. First set up base class (Shape), then store the 
// vertices, which are 3 (x,y) points giving offsets from the Shape center 
// to each triangle vertex.
Rectangle::Rectangle (string _name, string _colour, float _xcen, float _ycen,
             float _width, float _height) 
              : Shape (_name, _colour, _xcen, _ycen) 
{
    width = _width;
    height = _height;
}


Rectangle::~Rectangle() {
   // No dynamic memory to delete
}


void Rectangle::print () const {
   Shape::print();
      cout << "rectangle width: " << width << " height: " << height << endl;

}


void Rectangle::scale (float scaleFac) {

      width *= scaleFac;
      height *= scaleFac;

}
   

float Rectangle::computeArea () const {
   // 1/2 * base * height
   // The height requires some trigonometry to compute, for an arbitrary triangle.
   // Some manipulation gives a simpler formula to use in this case, which I use below.
   // Compute two vectors, from one vertex to each of the other two.
   // Then use the formula below to get area.
   float area;   
   area = abs (width*height);
   return area;
}


float Rectangle::computePerimeter () const {
   //calculate the total area
    float perimeter = 0;
   perimeter = (width+height)*2;
   return perimeter;
}


void Rectangle::draw (easygl* window) const {
   // Load up the data structure needed by easygl, and draw the triangle
   // using the easygl::draw_polygon call.
   // This data type is in easygl_constants.h
    float xleft, xright, ytop, ybottom;
      xleft = getXcen() - width/2;
      xright = getXcen() + width/2;
      ytop = getYcen() + height/2;
      ybottom = getYcen() - height/2;
      
   window->gl_setcolor(getColour());
   window->gl_fillrect(xleft, ybottom, xright, ytop);
}


bool Rectangle::pointInside (float x, float y) const {
   // Make a point that corresponds to where you clicked. Since all my
   // vertices are relative to the triangle center, it is more convenient
   // to also shift the click point so it is an offset from the triangle 
   // center.
   t_point click;
   click.x = x - getXcen();//distance between x and x-center
   click.y = y - getYcen();
   
   // The test is that the cross product between the vector along an 
   // edge (from a vertex to the next vertex), and the vector from that 
   // start vertex to the click point, must have
   // the same sign (+ve or -ve) for all 3 vertices.  That guarantees the
   // click point is on the "inside" of all 3 triangle sides, and hence is 
   // in the triangle.
   
   //for triangle only +++ and --- means the click inside triangle area can return true
   t_point vecToClick, vecOfSide;
   if(click.x >= -width / 2 && click.x <= width/2 && click.y >= - height / 2 && click.y <= height/2)//make sure the point inside the rectangle
   {
       return true;
   }
   else
   {
       return false;
   }

}


// Private helper functions below.  Working out triangle area etc. 
// requires some vector math, so these helper functions are useful.

// Return the (x,y) vector between start and end points.
t_point Rectangle::getVecBetweenPoints (t_point start, t_point end) const {
   t_point vec;
   vec.x = end.x - start.x;
   vec.y = end.y - start.y;
   return (vec);
}


// Return vec1 x vec2, where vec1 and vec2 are 2D vectors, and 
// hence the cross product is a single (z-directed) number.
float Rectangle::getCrossProduct (t_point vec1, t_point vec2) const {
   return (vec1.x * vec2.y - vec1.y * vec2.x);
}

