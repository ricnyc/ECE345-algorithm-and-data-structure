/* 
 * File:   Shape.h
 * Author: vaughn
 *
 * Created on November 21, 2012, 5:07 PM
 * Base class for shapes. Stores data and methods (functions) common for all
 * shapes. This is an abstract base class -- it cannot be instantiated since
 * it just the common parts of real shapes (circles, rectangles, etc.) and
 * a common interface to access those real shapes.
 */

#ifndef SHAPE_H
#define	SHAPE_H

#define PI 3.141593   // This constant may be useful to you
#include <string>
#include "easygl.h"   // To get at graphics.
using namespace std;

class Shape {
private:
   string name;    // Name of this shape, can be used as its identifier
   
   // A string giving the colour of the shape. Valid values are:
   // "white", "black", "grey55", "grey75" "blue", "green", "yellow", 
   // "cyan", "red", "darkgreen", "magenta"
   string colour;
   
   float xcen, ycen;  // x and y coordinates of the center of the shape.

public:
   // Accessor and mutator functions implemented by Shape
   string getName () const;
   void setName (string _name);
   string getColour () const;
   void setColour (string _colour);
   float getXcen () const;
   void setXcen (float _xcen);
   float getYcen () const;
   void setYcen (float _ycen);
   
   // Shift the object's center by the specified amount. Derived classes 
   // should be defined so that shifting the object center shifts where the
   // whole object is drawn.
   // Implemented by Shape.
   void translate (float xShift, float yShift);
   
   // Below are virtual interface functions; these *must* be implemented in each
   // class derived from Shape.
   
   // Print out the object. Shape::print() will print the basic info contained
   // in the Shape base class. Made virtual so you get the right print method
   // (print extra info) for derived classes.
   virtual void print () const;
   
   // Scale the object size by the specified factor.
   // E.g. a scaleFac of 1 would change nothing, 0.5 would shrink the object
   // to half its original size, and 2 would grow the object to twice its
   // original size. The object stays centered at the same xcen, ycen point.
   virtual void scale (float scaleFac) = 0;
   
   // Returns the area of the Shape.
   virtual float computeArea () const = 0;
   
   // Returns the perimeter of the Shape.
   virtual float computePerimeter () const = 0;
   
   // Draws the object, using the easygl drawing commands.
   virtual void draw (easygl* window) const = 0;
   
   // Returns true if the given (x,y) point is inside the Shape.
   // Otherwise returns false.
   virtual bool pointInside (float x, float y) const = 0;
   
   // virtual destructor, in case we have different data to clean up in 
   // different derived classes.
   virtual ~Shape ();
   
protected:
   // Constructors protected, so they can only be invoked from Derived 
   // classes as part of building a Derived object.  No other classes can 
   // create a Shape anyway, since it is an abstract base class (cannot be
   // instantiated).
   Shape ();
   Shape (string _name, string _colour, float _xcen, float _ycen);
};

#endif	/* SHAPE_H */

