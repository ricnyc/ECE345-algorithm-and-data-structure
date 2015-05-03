/* 
 * File:   ShapeArray.h
 * Author: vaughn
 *
 * Created on November 20, 2012, 2:41 PM
 */

#ifndef SHAPEARRAY_H
#define	SHAPEARRAY_H

#include <sstream>
#include "Shape.h"
#include "easygl.h"
using namespace std;

class ShapeArray {
private:
   // Array of pointers to Shape objects
   // From [0..nShape-1] have valid data, and there is storage for data from [0..capacity-1]
   Shape** shapes;  
   int nShape;          // Number of valid shape objects
   int capacity;        // Capacity (allocated size) of shapeArray
   
   Shape* selectedShape;  // Pointer to any "clicked on" shape.
   string savedColour;    // Original colour of selected shape.
   
   easygl* window;      // pointer to the graphics window object (for drawing)
   
   /*******  Miscellaneous helper functions. *******************/
   void resize (int newCapacity);  // Resizes shapes to the new capacity.
   
   // Returns a pointer to the Shape (in shapes) with the specified name,
   // or NULL if no shape with that name is in the array.
   Shape* findShape (string name);
   
   // Returns a pointer the Shape covering the specified (x,y) location,
   // or NULL if no shape covers thats spot.  If multiple shapes cover that
   // spot, the one on top (last drawn) is returned.
   Shape* findShape (float x, float y);
      
public:
   ShapeArray();
   ~ShapeArray();

   // Adds newShape to the shapes array, creating more storage if necessary.
   void addShape (Shape *newShape);  
   
   // Functions which each parse and execute a specific command.
   // They all take a stringstream argument, which contains a single input
   // line. The command has already been extracted; the arguments are left.
   void translate (stringstream& linestream);
   void scale (stringstream& linestream);
   void remove (stringstream& linestream);
   void printAll (stringstream& linestream);
   void computeArea (stringstream& linestream);
   void computePerimeter (stringstream& linestream);
   void handleDraw(stringstream& linestream);
   
   // Function that redraws all the graphics; used in callbacks after a 
   // window events.
   void reDraw ();
   
   // Function that checks where a mouse click was, and highlights the shape
   // clicked on (if any).  Used in callbacks.
   void clickHighlight (float x, float y);
};

#endif	/* SHAPEARRAY_H */
