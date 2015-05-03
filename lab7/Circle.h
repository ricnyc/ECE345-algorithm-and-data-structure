/* 
 * File:   Circle.h
 * Author: lichuanr
 *
 * Created on November 25, 2013, 8:32 PM
 */

#include "Shape.h"
#include "easygl.h"

#ifndef CIRCLE_H
#define	CIRCLE_H

class Circle : public Shape {
private:
   // t_point is a structure defined in easygl.h.  It has two members,
   // .x and .y, storing a 2D point.  We store 3 points in relVertex; 
   // each is the (x,y) offset of one triangle vertex from the shape 
   // center.
    float radius;
   
   // Private helper functions.

   
public:

   Circle (string _name, string _colour, float _xcen, float _ycen,
            float _radius);
   
   // virtual keyword is optional in all the function declarations below, since
   // the base class Shape already declared them virtual. But it is good 
   // practice to repeat it again here, for clarity.
   virtual ~Circle();
   
   
   virtual void print () const;
   virtual void scale (float scaleFac);
   virtual float computeArea () const;
   virtual float computePerimeter () const;
   virtual void draw (easygl* window) const;
   virtual bool pointInside (float x, float y) const;
};

#endif	/* TRIANGLE_H */