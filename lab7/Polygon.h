/* 
 * File:   Polygon.h
 * Author: lichuanr
 *
 * Created on November 25, 2013, 8:33 PM
 */

#ifndef POLYGON_H
#define	POLYGON_H
#include "Shape.h"
#include "easygl.h"

class Polygon : public Shape {
private:
   // t_point is a structure defined in easygl.h.  It has two members,
   // .x and .y, storing a 2D point.  We store 3 points in relVertex; 
   // each is the (x,y) offset of one triangle vertex from the shape 
   // center.
   t_point relVertex[100];   
   int n;
   // Private helper functions.
   t_point getVecBetweenPoints (t_point start, t_point end) const;
   float getCrossProduct (t_point vec1, t_point vec2) const;
   
public:
   Polygon (string _name, string _colour, float _xcen, float _ycen,
            float _xcoords[100], float _ycoords[100], int _n);
   
   // virtual keyword is optional in all the function declarations below, since
   // the base class Shape already declared them virtual. But it is good 
   // practice to repeat it again here, for clarity.
   virtual ~Polygon();
   
   
   virtual void print () const;
   virtual void scale (float scaleFac);
   virtual float computeArea () const;
   virtual float computePerimeter () const;
   virtual void draw (easygl* window) const;
   virtual bool pointInside (float x, float y) const;
};


#endif	/* POLYGON_H */