#include <iostream>
#include <cstdlib>
#include "easygl.h"
#include "graphics.h"
#include "ShapeArray.h"
using namespace std;


easygl *easygl::object_ptr = NULL;

// see easygl.h and easygl_constants.h for details on how to call these
// functions.  This class is a thin wrapper around the easygl C-style
// interface to allow everything to be encapsulated in one object, if you
// so desire.


// **************** Window management functions ********************

easygl::easygl (const char *window_name, int background_color_index)
{
   if (easygl::object_ptr != NULL) 
   {
      cerr << "Error:  multiple windows not supported. Aborting program.\n";
      exit (1);
   }
   init_graphics (window_name, background_color_index);
   gl_set_window_message ("Not checking for events; window will not respond.");
   easygl::object_ptr = this;
}


easygl::~easygl () 
{
   close_graphics ();
   easygl::object_ptr = NULL;
}



void easygl::set_world_coordinates (float xleft, float ybottom, float xright, float ytop)
{
   init_world (xleft, ytop, xright, ybottom);
}


easygl * easygl::get_object_ptr ()
{

   return (easygl::object_ptr);
}


void easygl::gl_set_window_message(const char *message) 
{
   update_message (message);
}


void easygl::gl_event_loop (ShapeArray* _shapeArray, 
        bool enable_mouse_move_input, bool enable_keypress_input) 
{
   
   shapeArray = _shapeArray;  // Store for callbacks.
   set_mouse_move_input (enable_mouse_move_input);
   set_keypress_input (enable_keypress_input);
   gl_set_window_message ("Window active: (1) click on a shape, then (2) click to move its center");
   event_loop (act_on_mouse_button, act_on_mouse_move, act_on_keypress, drawscreen);
   gl_set_window_message ("Not checking for events; window will not respond.\n");
}


void easygl::gl_flush () {
   flushinput ();
}


// **************** Call back functions to fill in if you want them ***************

// Stubs for user calls.
void easygl::drawscreen (void) {
   easygl* window = easygl::get_object_ptr();
   ShapeArray* shapeArrayPtr = window->shapeArray;
   shapeArrayPtr->reDraw ();
}


void easygl::act_on_mouse_button (float x, float y) {
   easygl* window = easygl::get_object_ptr();
   ShapeArray* shapeArrayPtr = window->shapeArray;
   shapeArrayPtr->clickHighlight (x, y);
}


void easygl::act_on_keypress (char key_pressed) { }
void easygl::act_on_mouse_move (float x, float y) { }


// ****************** Graphics Attribute functions ***************************

void easygl::gl_setcolor (int cindex)
{
   setcolor (cindex);
}


void easygl::gl_setcolor (string cname) {
   setcolor (cname);   
}


/* Sets the line style to the specified line_style (SOLID or DASHED) */
void easygl::gl_setlinestyle (int linestyle)
{
   setlinestyle (linestyle);
}


/* Sets the line width in pixels */
void easygl::gl_setlinewidth (int linewidth)
{
   setlinewidth (linewidth);
}


// Sets the font size, in points, for text drawing 
void easygl::gl_setfontsize (int pointsize)   
{ 
   setfontsize (pointsize);
}


// *************** Graphics primitives ***********************
// All use the current (last set) line width, style, color and 
// (for text) font size.

// Clears the screen. Should normally be the first call in your 
// screen redrawing function.
void easygl::gl_clearscreen (void)
{
   clearscreen ();
}


// Draws a line from (x1, y1) to (x2, y2) in world coordinates
void easygl::gl_drawline (float x1, float y1, float x2, float y2)
{   
   drawline (x1, y1, x2, y2);
}


// Draws a rectangle from (x1, y1) to (x2, y2) in world coordinates
void easygl::gl_drawrect (float x1, float y1, float x2, float y2)
{
   drawrect (x1, y1, x2, y2);
}


// Draws a filled rectangle 
void easygl::gl_fillrect (float x1, float y1, float x2, float y2)
{
   fillrect (x1, y1, x2, y2);
}


// Draws a filled polygon, defined by the points array. 
void easygl::gl_fillpoly (t_point *points, int npoints)
{
   fillpoly (points, npoints);
}


// Outline (draw) or fill a circular arc, or an elliptical arc.  Angles in degrees.
// startang measured from positive x-axis of Window.  Positive angextent means        
// counterclockwise arc.                                                    
void easygl::gl_drawarc (float xcen, float ycen, float rad, float startang,
			  float angextent) 
{  
   drawarc (xcen, ycen, rad, startang, angextent);
}


void easygl::gl_fillarc (float xcen, float ycen, float rad, float startang,
			  float angextent) 
{    
   fillarc (xcen, ycen, rad, startang, angextent);
}


void easygl::gl_drawellipticarc (float xc, float yc, float radx, float rady, float startang, float angextent) 
{
  drawellipticarc (xc, yc, radx, rady, startang, angextent);
}


void easygl::gl_fillellipticarc (float xc, float yc, float radx, float rady, float startang, float angextent)
{
   fillellipticarc (xc, yc, radx, rady, startang, angextent);
}


// x_clip_bound specifies horizontal bounding box.  If text won't fit in    
// the space specified by x_clip_bound (world coordinates) text isn't drawn.
// That avoids text going everywhere for high zoom levels.

void easygl::gl_drawtext (float xcen, float ycen, const char *text, 
      float x_clip_bound) 
{
   drawtext (xcen, ycen, text, x_clip_bound);
}


