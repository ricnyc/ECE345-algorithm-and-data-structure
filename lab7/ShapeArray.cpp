/* 
 * File:   ShapeArray.cpp
 * Author: vaughn
 *
 * Created on November 20, 2012, 2:14 PM
 */

#include <iostream>
#include <string>
#include <sstream>
#include <assert.h>
#include <algorithm>
#include <string>
#include "easygl.h"
#include "ShapeArray.h"
using namespace std;
 
// Default constructor. Allocate a small amount of space for an array of 
// shapes. No valid shapes to start with.
ShapeArray::ShapeArray() {
   capacity = 1;
   shapes = new Shape*[capacity];
   nShape = 0;
   selectedShape = NULL; // Nothing clicked on.
   savedColour = "";
   
   window = NULL;   // No graphics window open yet.
}


ShapeArray::~ShapeArray() {
   for (int i = 0; i < nShape; i++) {
      delete shapes[i];  // Delete each shape.
   }
   delete[] shapes;  // Now delete the array of pointers to Shape objects.
   shapes = NULL;    // For safety only
   
   delete window;
   window = NULL;
}
   
   
// Insert the pointer to a newShape into the array of shapes.
// Create more space in the array if necessary.
void ShapeArray::addShape (Shape *newShape) {
   if (nShape == capacity) 
      resize (2 * capacity);  // Double array size if we're out of room.
   
   shapes[nShape] = newShape;
   nShape++;
}


// Helper routine to resize the shapes array (to get more storage).
void ShapeArray::resize (int newCapacity) {
   Shape **tmpArray = new Shape*[newCapacity];
   assert (newCapacity >= nShape);   // Ensure enough space for valid data.
   
   for (int i = 0; i < nShape; i++) // Copy over data.
      tmpArray[i] = shapes[i];
   
   delete[] shapes;
   shapes = tmpArray;
   capacity = newCapacity;
}


Shape* ShapeArray::findShape (string name) {
   for (int i = 0; i < nShape; i++) {
      if (shapes[i]->getName() == name) {
         return shapes[i];
      }
   }   
   
   return NULL;   // Not found
}


void ShapeArray::translate (stringstream& linestream) {
   string name;
   float xShift, yShift, xShape, yShape;
   
   linestream >> xShape >> yShape >> xShift >> yShift;
   if (linestream.fail()) {
      cout << "Error: invalid arguments\n";
      return;
   }
   
   Shape* shape = findShape (xShape, yShape);
   if (shape == NULL) {
      cout << "Error: could not find shape at (" << xShape << "," 
             << yShape << ")" << endl;
      return;
   }
   shape->setXcen (shape->getXcen() + xShift);
   shape->setYcen (shape->getYcen() + yShift);
   cout << "Success\n";
}


void ShapeArray::scale (stringstream& linestream) {
   string name;
   float scaleFac;
   
   linestream >> name >> scaleFac;
   if (linestream.fail()) {
      cout << "Error: invalid arguments\n";
      return;
   }
   
   if (scaleFac < 0) {
      cout << "Error: scaling factor must be nonnegative\n";
      return;
   }
   
   Shape* shape = findShape (name);
   if (shape == NULL) {
      cout << "Error: could not find shape with name " << name << endl;
      return;
   }   
   shape->scale (scaleFac);
   cout << "Success\n";
}


void ShapeArray::remove (stringstream& linestream) {
   string name;
   
   linestream >> name;
   if (linestream.fail()) {
      cout << "Error: invalid arguments\n";
      return;
   }
   
   int ifound = -1;
   for (int i = 0; i < nShape; i++) {
      if (shapes[i]->getName() == name) {
         ifound = i;
         break;
      }
   }
   
   if (ifound == -1) {
      cout << "Error: could not find shape with name " << name << endl;
      return;
   }
   
   delete shapes[ifound];   // Remove this shape.
   // Now shift all entries after ifound over by one, to remove the empty
   // spot in the array.
   for (int i = ifound + 1; i < nShape; i++)
      shapes[i-1] = shapes[i];
   
   nShape--;
   cout << "Success\n";
}


void ShapeArray::printAll (stringstream& linestream) {
   for (int i = 0; i < nShape; i++) {
      shapes[i]->print();
   }
}


void ShapeArray::computeArea (stringstream& linestream) {
   double totalArea = 0;
   for (int i = 0; i < nShape; i++) {
      totalArea += shapes[i]->computeArea();
   }
   cout.precision (1);
   cout.setf (ios::fixed);
   cout << "Total area: " << totalArea << endl;
}


void ShapeArray::computePerimeter (stringstream& linestream) {
   double totalPerimeter = 0;
   for (int i = 0; i < nShape; i++) {
      totalPerimeter += shapes[i]->computePerimeter();
   }
   cout.precision (1);
   cout.setf (ios::fixed);
   cout << "Total perimeter: " << totalPerimeter << endl;
}


void ShapeArray::handleDraw(stringstream& linestream) {
   
   // Create the graphics window, if it doesn't exist already.
   if (window == NULL)
      window = new easygl ("Shape class program", WHITE);
   
   selectedShape = NULL;  // Nothing clicked on
   
   // Figure out a reasonable coordinate system to draw in, based on the
   // centers of the shape objects. 
   float xmin = 0, ymin = 0, xmax = 0, ymax = 0;
   for (int i = 0; i < nShape; i++) {
      xmin = min (xmin, shapes[i]->getXcen() );
      xmax = max (xmax, shapes[i]->getXcen() );
      ymin = min (ymin, shapes[i]->getYcen() );
      ymax = max (ymax, shapes[i]->getYcen() );
   }
   
   // Expand the drawable area a bit, since we just made something that 
   // covers the center of all the objects, not the edges.
   xmin -= (xmax - xmin) * .1;
   xmax += (xmax - xmin) * .1;
   ymin -= (ymax - ymin) * .1;
   ymax += (ymax - ymin) * .1;
   // Avoid making a coordinate system that is too small.
   if (xmin == xmax) {
      xmax++;
   }
   if (ymin == ymax) {
      ymax++;
   }
   
   // Sets the coordinate system such that these coordinates define the 
   // edges of the window.  The user can still zoom and zoom out after.
   window->set_world_coordinates(xmin, ymin, xmax, ymax);
   cout << "Passing control to graphics window. Click Proceed to return control to this command window\n";
   reDraw();  // Make any graphics changes show up right away.
   window->gl_flush();  // Ensure the graphics get displayed right away.
   window->gl_event_loop(this, false, false);
   cout << "Control returned to command window\n";
}


void ShapeArray::reDraw () {
   window->gl_clearscreen ();
   for (int i = 0; i < nShape; i++) {
      shapes[i]->draw(window);
   }
}


// Callback function used to highlight and move shapes around in 
// response to mouse clicks in the graphics window.
// 1. First click:  highlight the shape clicked on, at (x,y).
// 2. Second click: move the shape to the specified (x,y).
void ShapeArray::clickHighlight (float x, float y) {
   
   if (selectedShape != NULL) {
      // Second mouse click --> move the shape.
      // Move the selected shape to x,y and unhighlight it.
      selectedShape->setXcen (x);
      selectedShape->setYcen (y);
      selectedShape->setColour (savedColour);
      selectedShape = NULL;  // Unselected now.
   }
   else {
      // First mouse click: find the shape and highlight it
      selectedShape = findShape (x, y);
      if (selectedShape != NULL) {
         savedColour = selectedShape->getColour();
         if (savedColour != "red") {
            selectedShape->setColour("red");
         }
         else {
            selectedShape->setColour("green");
         }
      }
   }

   // Redraw the graphics and flush the graphics to make sure the screen is 
   // updated.
   reDraw();
   window->gl_flush();
}


// Look through shapes in reverse order, checking to see if we clicked
// inside a shape. We go in reverse order so we check the shape on top 
// (draw last) first.  
Shape* ShapeArray::findShape (float x, float y) {
   
   for (int i = nShape-1; i >= 0; i--) {
      if (shapes[i]->pointInside(x, y)) {
         return (shapes[i]);
      }
   }
   
   return NULL;   // Not found
}
