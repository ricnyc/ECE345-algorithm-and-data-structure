#include <iostream>
#include <cmath>
#include "easygl.h"
#include "Circle.h"
using namespace std;


// Constructor. First set up base class (Shape), then store the 
// vertices, which are 3 (x,y) points giving offsets from the Shape center 
// to each triangle vertex.
Circle::Circle(string _name, string _colour, float _xcen, float _ycen,
            float _radius) 
              : Shape (_name, _colour, _xcen, _ycen)
{
    radius = _radius;
}


Circle::~Circle () {
   // No dynamic memory to delete
}


void Circle::print () const {
   Shape::print();//
   cout << "circle radius: " << radius << endl;
}


void Circle::scale (float scaleFac) {

      radius *= scaleFac;

}
   

float Circle::computeArea () const {
   // 1/2 * base * height
   // The height requires some trigonometry to compute, for an arbitrary triangle.
   // Some manipulation gives a simpler formula to use in this case, which I use below.
   // Compute two vectors, from one vertex to each of the other two.
   // Then use the formula below to get area.
   float area;
   area = radius*radius*PI;
   return area;
}


float Circle::computePerimeter () const {
   float perimeter = 0;
   perimeter = 2*PI*radius; 
   return perimeter;
}


void Circle::draw (easygl* window) const {
   // Load up the data structure needed by easygl, and draw the triangle
   // using the easygl::draw_polygon call.
   float xcen = getXcen();
   float ycen =getYcen();
   window->gl_setcolor(getColour());
   window->gl_fillarc(xcen, ycen, radius, 0, 360);
}


bool Circle::pointInside (float x, float y) const {
   // Make a point that corresponds to where you clicked. Since all my
   // vertices are relative to the triangle center, it is more convenient
   // to also shift the click point so it is an offset from the triangle 
   // center.
   t_point click;
   click.x = x - getXcen();
   click.y = y - getYcen();
   
   
   if(click.x <= radius && click.y <= radius)//distance from center point less than radius (inside the graph)
   {
       return true;
   }
   else 
   {
       return false;
   }
}


