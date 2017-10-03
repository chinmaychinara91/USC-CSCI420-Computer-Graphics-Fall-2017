// keyboard and mouse controls defined in this library

#include "stdafx.h"
#include <stdlib.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <pic.h>

// take the variables defined in the main code assign1.cpp
extern HeightField * heightField;//set up and initialized in our main init function
extern float rotation[3];// set up and initialized in main file
extern float translation[3];// set up and initialized in main file
extern float scale[3];// set up and initialized in main file
extern float cameraRotation[2];//load the current camera rotation for the point of view
extern drawdisplaytype::DisplayType displayType;//initialized in the main function this is what controls the wireframe, grayscale and points element and any further modes
extern unsigned int wireframeDensity;//this is the wireframe density
extern int screenshotFlag; // screen shot flag

namespace keyboardmouse {

	// initialize a type to help us determine which controlstate the user currently is in
	typedef enum {ROTATE, TRANSLATE, SCALE}	CONTROLSTATE;
	
	// initialize some integers for various menu options etc
	extern int g_iMenuId,
		g_vMousePos[2],
		g_iLeftMouseButton,
		g_iMiddleMouseButton,
		g_iRightMouseButton;

	extern int currentDisplay;//what the current display element consists of! 
	extern drawdisplaytype::DisplayType displayTypeMap[3];//this is a mapper of the currently available display types

	// mouse idle is useful for when the mouse is just sitting somewhere
	void mouseidle(int x, int y); 

	// mouse button will be used to handle button clicks from glut
	void mousebutton(int button, int state, int x, int y); 

	// implement a basic mousedrag listener
	// convert mouse drags into information about rotation / translation / scaling
	void mousedrag(int x, int y); 
	
	// basic menu functionality
	void menufunc(int value);

	// enable the keypress functionality for special cases etc
	void keyPressSpl(int key, int x, int y);

	// enable the keypress functionality etc
	void keyPress(unsigned char key, int x, int y);

	// initialize the menu
	void init();//initialize the menu

}

namespace keyboardmouse 
{

	// initialize the control state etc
	CONTROLSTATE g_ControlState;
		
	int g_iMenuId,
		// store the mouse position (x,y) as [x,y]
		g_vMousePos[2] = {0,0},	
		// store the mouse buttons each time to determine what is stored etc
		g_iLeftMouseButton = 0,
		g_iMiddleMouseButton = 0,
		g_iRightMouseButton = 0;

	// implement my own custom mapping system for switching between the display states etc
	int currentDisplay = 0;
	drawdisplaytype::DisplayType displayTypeMap[3] = {drawdisplaytype::GRAYSCALE, drawdisplaytype::POINT, drawdisplaytype::WIREFRAME};

	void mouseidle(int x, int y) {
	  g_vMousePos[0] = x;
	  g_vMousePos[1] = y;
	}

	// mouse button control
	void mousebutton(int button, int state, int x, int y) {

	  switch (button)
	  {
	    case GLUT_LEFT_BUTTON:
	      g_iLeftMouseButton = (state==GLUT_DOWN);
	      break;
	    case GLUT_MIDDLE_BUTTON:
	      g_iMiddleMouseButton = (state==GLUT_DOWN);
	      break;
	    case GLUT_RIGHT_BUTTON:
	      g_iRightMouseButton = (state==GLUT_DOWN);
	      break;
	  }
	 
	  switch(glutGetModifiers())
	  {
	    case GLUT_ACTIVE_CTRL:
	      g_ControlState = TRANSLATE;
		  cout << "\n CTRL pressed for TRANSLATE !!!" << endl;
	      break;
	    case GLUT_ACTIVE_SHIFT:
	      g_ControlState = SCALE;
		  cout << "\n SHIFT pressed for SCALE !!!" << endl;
	      break;
	    default:
	      g_ControlState = ROTATE;
	      break;
	  }

	  g_vMousePos[0] = x;
	  g_vMousePos[1] = y;
	}

	// mouse drag changes mouse drags into information about scaling / rotation etc
	void mousedrag(int x, int y) 
	{
	  int vMouseDelta[2] = {x-g_vMousePos[0], y-g_vMousePos[1]};
	  
	  switch (g_ControlState)
	  {
	    case TRANSLATE:  
	      if (g_iLeftMouseButton)
	      {
	        translation[0] += vMouseDelta[0]*0.05;
			translation[1] -= vMouseDelta[1]*0.05;
	      }
	      if (g_iMiddleMouseButton)
	      {
			translation[2] += vMouseDelta[1]*0.01;
	      }
	      break;
	    case ROTATE:
	      if (g_iLeftMouseButton)
	      {
	        rotation[0] += vMouseDelta[1];
	        rotation[1] += vMouseDelta[0];
	      }
	      if (g_iMiddleMouseButton)
	      {
	        rotation[2] += vMouseDelta[1];
	      }
	      break;
	    case SCALE:
	      if (g_iLeftMouseButton)
	      {
	        scale[0] *= 1.0+vMouseDelta[0]*0.01;
	        scale[1] *= 1.0-vMouseDelta[1]*0.01;
	      }
	      if (g_iMiddleMouseButton)
	      {
	        scale[2] *= 1.0-vMouseDelta[1]*0.01;
	      }
	      break;
	  }
	  g_vMousePos[0] = x;
	  g_vMousePos[1] = y;
	}

	void keyPressSpl(int key, int x, int y) 
	{
		// change each time
		float delta = 10.0;

		// rotate counter clockwise / clockwise etc --- around the z axis
		if (key == GLUT_KEY_LEFT)
		{
			rotation[1] -= delta;
			cout << "\n Rotation clockwise !!!" << endl;
		}

		if (key == GLUT_KEY_RIGHT)
		{
			rotation[1] += delta;
			cout << "\n Rotation anti-clockwise !!!" << endl;
		}

		// rotate about the x axis this is into and out of the screen
		if (key == GLUT_KEY_UP) 
		{
			rotation[0] -= delta;
			cout << "\n Rotation upwards !!!" << endl;
		}

		if (key == GLUT_KEY_DOWN)
		{
			rotation[0] += delta;
			cout << "\n Rotation downwards !!!" << endl;
		}
		glutPostRedisplay();
	}

	void keyPressOthers(unsigned char key, int x, int y)
	{
		// start taking screenshots
		if(key == 's')
		{
			screenshotFlag = 1;
			cout << "\nScreenshot started !!!" << endl;
		}

		// stop taking screenshots
		if(key == 't')
		{
			screenshotFlag = 0;
			cout << "\nScreenshot ended !!!" << endl;
		}

		// render as grayscale
		if (key == 'g') 
		{
			displayType = drawdisplaytype::GRAYSCALE;
			cout << "\nRender type GRAYSCALE !!!" << endl;
		}

		//render as wireframe
		if (key == 'w') 
		{
			displayType = drawdisplaytype::WIREFRAME;
			cout << "\nRender type WIREFRAME !!!" << endl;
		}

		//render as wireframe over grayscale
		if (key == 'i') 
		{
			displayType = drawdisplaytype::GRAYSCALE;
			displayType1 = drawdisplaytype::WIREFRAME;
			cout << "\nRender type WIREFRAME over GRAYSCALE !!!" << endl;
		}

		// render as points
		if (key == 'p') 
		{
			displayType = drawdisplaytype::POINT;
			cout << "\nRender type POINT !!!" << endl;
		}

		// increase wireframe density
		if (key == '+' && wireframeDensity > 2)
		{
			wireframeDensity -= 2;
			cout << "\nWireframe density increased (lesser the value more the density) to: " << wireframeDensity << endl;
		}

		// decrease wireframe density
		if (key == '-' && wireframeDensity < float(heightField->getWidth()) *0.20)
		{
			wireframeDensity += 2;	
			cout << "\nWireframe density decreased (more the value less the density) to: " << wireframeDensity << endl;
		}

		glutPostRedisplay();
	}	
}