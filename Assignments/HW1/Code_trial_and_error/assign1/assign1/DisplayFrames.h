// initialize standard libraries needed if they were not already included

#include "stdafx.h"
#include <stdlib.h>
#include <math.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <pic.h>

// take the variables defined in the main code assign1.cpp
extern HeightField * heightField;//set up and initialized in our main init function
extern int windowHeight; // window height
extern int windowWidth; // window width
extern float rotation[3]; // set up and initialized in main file
extern float translation[3]; // set up and initialized in main file
extern float scale[3]; // set up and initialized in main file
extern float cameraRotation[2]; // grab the camera rotation from the main assign1.cpp
extern float cameraDistance; // this is how far away the camera is -- ie the radius of the sphere of view
extern int screenshotFlag; // the screen shot flag
extern drawdisplaytype::DisplayType displayType; // display type
extern drawdisplaytype::DisplayType displayType1;

namespace displayframes {

	// initialize image and basics of the application here
	void init();	
	// idle function called when nothing happening on machine
	void idle();
	// display is what is shown each time
	void display();

	// display controller is responsible for abstracting away the calls to our display elements
	void displayController();
}

// implement idle function -- responsible for working with the image on a consistent basis to continually ensure its integrity
void displayframes::idle() {

	// initialize other idle functionality here -- this could be a casual rotation or some sort of randomization of the translations etc
	glutPostRedisplay();//run the display segment again to update any changes that we may have
}

// display is for drawing out the elements using our scaled frame etc
void displayframes::display() {

	// rotate, scaling and translation should take place before this code in the future
	// draw a quick cube around the origin of the screen
	glViewport(0,0, windowWidth, windowHeight);	

	// start editing the modelview -- not the scenary
	glMatrixMode(GL_MODELVIEW);

	glLoadIdentity();

	// reset the matrix to a default state before rotating scaling etc
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	
	// clear the colors and make the background black
	glClearColor(0.0, 0.0, 0.0, 1.0);

	// reset the rotation of all axes to 0,0,0
	glTranslatef(translation[0], translation[1], translation[2]);

	// set up the proper scale each time!
	glScalef(scale[0], scale[1], scale[2]);


	// draw out each of the polygons needed for this object
	// now need to call the proper draw elements
	displayController();//this is responsible for initializing the correct display methods
					
	// initialize the gl_projection matrix -- this is useful for setting up perspective etc ...
	// initialize our matrix for the final viewing using projection ... 
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	// fov angle, aspect ratio = width / height, near z, far z
	gluPerspective(10.0f, windowWidth / windowHeight, 0.01, 1000.0);

	// swap the buffers and bring the second one out from hiding
	glutSwapBuffers();

	if(screenshotFlag == 1)
		capturescreenshot::TakeScreenshot();
}

// display controller is where special cases in the future can go
void displayframes::displayController() {

	// push a matrix to rotate our element so that z will actually be drawn as y so we don't have to worry about this!
	glPushMatrix();

	// by rotating around the x axis by 90.0
	// when we draw a z value, it will look like a y value and we don't need to worry about that particular case
	// multiply the current matrix by 90, but only around the x axis
	glTranslatef(0,0,-100);
	glScalef(0.1,0.1,0.1);

	// set up the proper rotations
	glRotatef(rotation[0], 1.0, 0.0,0.0);
	glRotatef(rotation[1], 0.0, 1.0,0.0);
	glRotatef(rotation[2], 0.0, 0.0,1.0);
		
	// now that we have drawn out the element, lets rotate it about the z axis to help
	glRotatef(90, -1, 0,0);

	// now translate the rotated object down to the left to center it
	glTranslatef(int(heightField->getWidth())*-0.5, 0, int(heightField->getHeight()) * -0.25);

	//now we want to rotate the field so we can see it a little bit better than before etc	
	glRotatef(30, 1, 0, 0);

	// scale our image for a second
	// checkout our current display type and then call the correct display from the display namespace
	if (displayType == drawdisplaytype::GRAYSCALE)
	{
		if(displayType1 == drawdisplaytype::WIREFRAME)
		{
			drawdisplaytype::drawGrayscale();
			glPolygonOffset (1.0f, 10.0f);
			drawdisplaytype::drawWireframe();
		}
		else
			drawdisplaytype::drawGrayscale();
	}
		
	else if (displayType == drawdisplaytype::WIREFRAME)
		drawdisplaytype::drawWireframe();

	else if (displayType == drawdisplaytype::POINT)
		drawdisplaytype::drawPoints();

	// initialize any other elements etc	
	glPopMatrix();//stop the z/y reversing here
}