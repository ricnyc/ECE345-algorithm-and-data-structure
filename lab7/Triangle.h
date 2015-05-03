/* 
 * File:   Triangle.h
 * Author: vaughn
 *
 * Created on November 21, 2012, 7:36 PM
 */

#ifndef TRIANGLE_H
#define	TRIANGLE_H

#include "Shape.h"
#include "easygl.h"

class Triangle : public Shape {
private:
   // t_point is a structure defined in easygl.h.  It has two members,
   // .x and .y, storing a 2D point.  We store 3 points in relVertex; 
   // each is the (x,y) offset of one triangle vertex from the shape 
   // center.
   t_point relVertex[3];   
   
   // Private helper functions.
   t_point getVecBetweenPoints (t_point start, t_point end) const;
   float getCrossProduct (t_point vec1, t_point vec2) const;
   
public:
   Triangle (string _name, string _colour, float _xcen, float _ycen,
            float _xcoords[3], float _ycoords[3]);
   
   // virtual keyword is optional in all the function declarations below, since
   // the base class Shape already declared them virtual. But it is good 
   // practice to repeat it again here, for clarity.
   virtual ~Triangle();
   
   
   virtual void print () const;
   virtual void scale (float scaleFac);
   virtual float computeArea () const;
   virtual float computePerimeter () const;
   virtual void draw (easygl* window) const;
   virtual bool pointInside (float x, float y) const;
};

#endif	/* TRIANGLE_H */
