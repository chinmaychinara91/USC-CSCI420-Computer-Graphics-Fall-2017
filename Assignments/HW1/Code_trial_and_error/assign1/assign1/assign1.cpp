// CSCI-420 Assignment-1 
// Height Fields
// Code written by: Chinmay Chinara
// USC ID: 2527237452
// Due date: 25th September 2017
// This is the main entrypoint of the program

/* HEADER FILES */
#include "stdafx.h"
#include <pic.h>
#include <windows.h>
#include <stdlib.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <iostream>

#include "CreateHeightField.h"
#include "DrawDisplayType.h"
#include "CaptureScreenshot.h"
#include "DisplayFrames.h"
#include "KeyboardMouse.h"
using namespace std;

/* GLOBAL VARIABLES */
unsigned int wireframeDensity = 2;//wireframe density for the initial wireframe

drawdisplaytype::DisplayType displayType = drawdisplaytype::GRAYSCALE; //initialize the default type of rendering
drawdisplaytype::DisplayType displayType1 = drawdisplaytype::GRAYSCALE; //initialize the default type of rendering for overlay feature (extra credit)

// window variables
int windowHeight = 768, windowWidth = 1024;

// this flag controls whether to take a screenshot or not
int screenshotFlag = 0;

//rotation, translation and scaling
float rotation[3] = {0.0, 0.0, 0.0}; 
float translation[3] = {0.0, 0.0, -300.0};
float scale[3] = {0.9, 0.9, 1};

// this is the scalar that we will multiply by the rotation element
float cameraDistance = 50.0;

// we want to be able to rotate the camera around the x axis to go above and beyond or around the y element
float cameraRotation[2] = {0.0, 0.0};

// height field holder for this application
HeightField * heightField = NULL;

// define idle state
void doIdle()
{
  // make the screen update
  glutPostRedisplay();
}

// grab the jpeg data from a file and then initialize a height field object
void heightFieldInit(char *filename) 
{
	// initialize images etc
	Pic * image = jpeg_read(filename, NULL);

	// ensure that the file could be read etc
	if (!image) 
	{
		printf("Error reading file %s.\n", filename);
		exit(1);
	}

	unsigned int height = image->nx; // height of the image
	unsigned int width = image->ny; // width of the image
	unsigned int pixel_val; // current pixel intensity from 0 to 256

	// set up the height field object for global use
	heightField = new HeightField(height, width, GRAYSCALE);

	// for each pixel generate a height point 
	for (unsigned int y = 0; y < height; y++) 
	{
		for (unsigned int x = 0; x < width; x++) 
		{
			// the pixel intensity for each piece of the image 
			pixel_val = image->pix[y * width + x];

			// add the proper point into the height field object
			heightField->addHeightPoint(x, y, pixel_val);
		}
	}
	delete image;
}

int main(int argc, char** argv)
{
	//input check conditions to ensure that there is an input image
	if (argc<2)
	{  
		cout << "No input image provided !!!" << endl;
		cout << "Make sure to give input images for processing in the following method:" << endl;
		cout << "Method in Visual Studio Debugging section: <image whose height field is to be found>.jpg" << endl;
		exit(1);
	}
	
	// intialize the height field creation
	heightFieldInit(argv[1]);

	// initialize glut
	glutInit(&argc, argv);

	// initialize double buffer element
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH | GLUT_RGBA);

	// set up the window size 
	glutInitWindowSize(windowWidth, windowHeight);

	// set the window position
	glutInitWindowPosition(100, 100);

	// Name of the window 
	glutCreateWindow("Height Field Output");

	// set up the main display function
	glutDisplayFunc(displayframes::display);

	// set the various callbacks for the interaction with opengl
	glutIdleFunc(doIdle);
	glutSpecialFunc(keyboardmouse::keyPressSpl);//enable the keypress handling
	glutKeyboardFunc(keyboardmouse::keyPressOthers);//enable the keypress handling non-special

	// enable our mouse drag function for controlling the heightfield image
	glutMotionFunc(keyboardmouse::mousedrag);
	glutPassiveMotionFunc(keyboardmouse::mouseidle);
	glutMouseFunc(keyboardmouse::mousebutton);

	// enable 3d buffering / z-buffer
	glEnable(GL_DEPTH_TEST);

	// now enter the main glut loop 
	glutMainLoop();

	return(0);
}