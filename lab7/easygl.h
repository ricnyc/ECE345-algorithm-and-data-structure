#ifndef EASYGL_H
#define EASYGL_H

#include <string>
#include "easygl_constants.h"
using namespace std;

class ShapeArray; 

class easygl 
{

private:
   // Singleton class.  This stores a pointer to the class so we can tell when its created and
   // avoid multiple object creation. 
   static easygl* object_ptr; 
   
   // Store a pointer to a shapeArray object, so callbacks can get at the
   // data and functions they need to draw everything.
   ShapeArray* shapeArray;   
                                  
public:

   // ************ Window initialization, closedown and event handling **************

   // Create a new window, with name (usually shown at the top) as given and a background
   // colour as given.  
   // Known bug:  cannot destroy and recreate the window on MS Windows --> error creating 2nd time.
   easygl (const char *window_name, int background_color_index);

   // Destroys the window and associated data.
   ~easygl ();

   // Get a pointer to this (singleton) class for use in callbacks.
   static easygl *get_object_ptr ();

   // Drawing to the main (user program controlled) part of the window will use the coordinate 
   // system from (xleft, ybottom) to (xright, ytop), which are called world coordinates.
   void set_world_coordinates (float xleft, float ybottom, float xright, float ytop);
   
   // Invokes the event loop, which will process user button clicks to pan, zoom, etc.
   // Control returns to the main program when the user presses the "Proceed" button.
   // gl_event_loop needs at least a drawscreen callback to redraw the graphics area
   // as it pans, zooms etc.  The passed in parameters control whether or not 
   // mouse movement and keyboard input results in callbacks to the user program.
   // (default:  neither type of input results in a callback).
   // Note:  the callbacks are defined below.
   // Passing in a pointer to the shapeArray data structure for use in callbacks.
   void gl_event_loop (ShapeArray* _shapeArray,
             bool enable_mouse_move_input = false, bool enable_keypress_input = false);

   // Sets the text that will be displayed in a subwindow at the bottom of the main window.
   void gl_set_window_message (const char *message);

   // Flushes the graphics queue to the screen.  Useful for animation, where you
   // are not waiting for and redrawing in response to events, and want to 
   // make sure graphics actually show up on the screen when you're done a frame,
   // rather than being buffered until the next event.
   // Not needed when you're using gl_event_loop (i.e. event-driven graphics).
   void gl_flush ();

   // *************** Graphics attribute setting routines ***********************

   // sets the color for subsequent drawing.  Colors defined in easygl_constants.h
   void gl_setcolor (int cindex);
   
   // sets color with a string name, instead of an enumerated constant
   void gl_setcolor (string cname); 

   /* Sets the line style to the specified line_style (SOLID or DASHED) */
   void gl_setlinestyle (int linestyle); 

   /* Sets the line width in pixels */
   void gl_setlinewidth (int linewidth);

   /* Sets the font size, in points, for text drawing */
   void gl_setfontsize (int pointsize);

   // *************** Graphics primitives ***********************
   // All use the current (last set) line width, style, color and 
   // (for text) font size.

   /* Clears the screen. Should normally be the first call in your 
    * screen redrawing function.
    */
   void gl_clearscreen (void);
   // Draws a line from (x1, y1) to (x2, y2) in world coordinates
   void gl_drawline (float x1, float y1, float x2, float y2);

   // Draws a rectangle from (x1, y1) to (x2, y2) in world coordinates
   void gl_drawrect (float x1, float y1, float x2, float y2);

   // Draws a filled rectangle 
   void gl_fillrect (float x1, float y1, float x2, float y2);

   // Draws a filled polygon, defined by the points array. 
   void gl_fillpoly (t_point *points, int npoints); 

   /* Outline (draw) or fill a circular arc, or an elliptical arc.  Angles in degrees.
    * startang measured from positive x-axis of Window.  Positive angextent means        
    * counterclockwise arc.                                                    
    */
   void gl_drawarc (float xcen, float ycen, float rad, float startang,
			  float angextent); 
   void gl_fillarc (float xcen, float ycen, float rad, float startang,
			  float angextent);
   void gl_drawellipticarc (float xc, float yc, float radx, float rady, float startang, float angextent);
   void gl_fillellipticarc (float xc, float yc, float radx, float rady, float startang, float angextent);

   /* x_clip_bound specifies horizontal bounding box.  If text won't fit in    
    * the space specified by x_clip_bound (world coordinates) text isn't drawn.
    * That avoids text going everywhere for high zoom levels.  Default the text
    * clipping to off (a huge bound).
    */
   #define HUGE_CLIP_BOUND 1.e20
   void gl_drawtext (float xcen, float ycen, const char *text, float x_clip_bound = HUGE_CLIP_BOUND);

   //********************** Callbacks to be written by the application programmer ******

   // To be defined by end user of this package.  These are callbacks that event_loop 
   // will call to process events.

   // Must be defined, and redraws the graphics area when called (due to panning, zooming, 
   // window being moved, etc).  Should only make calls to set graphics attributes and 
   // draw graphics primitives (no window management calls).
   static void drawscreen (void);

   // Called when a mouse button is pressed in the graphics area.  Can define an empty callback
   // if you don't want to do anything in this case.  Passed the x and y location where the mouse
   // click occured, in world coordinates. 
   static void act_on_mouse_button (float x, float y);

   // Called when a key is pressed and the window is active (selected) in the windowing 
   // system, if you asked for such events to be returned when you invoked gl_event_loop.
   // Can define an empty callback if you don't want to 
   // do anything in this case.
   static void act_on_keypress (char key_pressed);

   // Called when the mouse moves in the graphics area, if you asked for such events to be 
   // returned when you invoked gl_event_loop.  Parameters are the last mouse position, in 
   // world coordinates. Can define an empty callback if you don't want to 
   // do anything in this case.
   static void act_on_mouse_move (float x, float y);
};

// Note that more calls are available in the C-style interface defined by graphics.h, and 
// could be exported here if you ask me.  - VB
#endif // EASYGL_H
