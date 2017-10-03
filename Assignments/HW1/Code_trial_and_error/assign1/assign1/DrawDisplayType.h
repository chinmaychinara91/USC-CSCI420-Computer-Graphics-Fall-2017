// library to draw Grayscale, Wireframe, Points

#include "stdafx.h"
#include <pic.h>
#include <windows.h>
#include <stdlib.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <iostream>

using namespace std;

// take the variables defined in the main code assign1.cpp
extern HeightField * heightField;
extern unsigned int wireframeDensity;
extern int windowHeight, windowWidth;

namespace drawdisplaytype {
	// declare a type that is useful for the toggling of what type of display we want
	typedef enum {
		GRAYSCALE,//draw out a grayscale image
		WIREFRAME,//draw out a wireframe -- currently not working
		POINT,//draw out only points	
	} DisplayType;

	// draw points is useful for drawing the map by simply drawing out elements
	void drawPoints();

	// draw out grayscale gradient for this particular element
	void drawGrayscale();
	void grayscalePlot(int x, int y);//responsible for drawing out a single vertex etc for this element

	// void draw wireframe of the mesh etc
	void drawWireframe();
}

// draw points instead of lines. These can be edited later to make them smoother etc
void drawdisplaytype::drawPoints() {

	// initialize points
	glBegin(GL_POINTS);	

	// initialize the point size etc	
	glPointSize(30.0);//set the point size for each dot drawn

	// cache a color array
	float color;

	// loop through each element and draw the correct point
	for (int x = int(heightField->getWidth()) - 1; x >= 0; --x) {

		// loop through each y value
		for (int y = int(heightField->getHeight()) -1; y >= 0; --y) {

			// grab the proper color from the heightfield
			color = heightField->getGrayscaleColor(x,y);

			// now that the color has been determined, draw it out
			glColor4f(color,0,0,10.0);

			// grab the vertice and draw it on screen	
			glVertex3fv(heightField->getVertex(x,y));//draw the proper vertex on screen	
		}
	} //end of the y for loop

	glEnd();//end the points drawing
}

void drawdisplaytype::drawWireframe() {

	// cache height / width etc of this element
	int height = int(heightField->getHeight()), width = int(heightField->getWidth());	

	// make sure that we are drawing a reds wireframe
	glColor4f(0,1.0,0,10.0);

	// want to loop through each row, stopping one from the bottom
	for (int y = height - wireframeDensity -1; y >= wireframeDensity; y = y-wireframeDensity ) {
		// we want to circle for each element in the next for loop and counter-clockwise add our vertices to the point
		for (int x = wireframeDensity + 1; x < width - wireframeDensity; x = x + wireframeDensity) {

			// draw out the top loops
			glBegin(GL_LINE_LOOP);

				glVertex3f(x,y,heightField->getPoint(x,y));
				glVertex3f(x-wireframeDensity, y, heightField->getPoint(x-wireframeDensity,y));
				glVertex3f(x-wireframeDensity, y+ wireframeDensity, heightField->getPoint(x-wireframeDensity,y+wireframeDensity));	

			glEnd();
		}
	}
}

void drawdisplaytype::grayscalePlot(int x, int y) 
{
	// responsible for drawing out and initializing an individual point for this drawing etc
	int z = heightField->getPoint(x,y);
	float color = heightField->getGrayscaleColor(x,y);

	// actually draw out the element and change the points accordingly
	glColor4f(color,0,0,10.0);
	glVertex3f(x,y,z);
}	

void drawdisplaytype::drawGrayscale() {

	// cache the height / width elements for this particular looping system
	int height = heightField->getHeight(), width = heightField->getWidth(), tempZ;

	// a color variable so that we can dynamically change the vertex each time
	float tempColor;

	// start a matrix to help us if we need any transformations
	glPushMatrix();

		for (int y = height - 2; y >= 1; --y) 
		{
			// initialize the drawing of the top triangle strip
			glBegin(GL_TRIANGLE_STRIP);

			for (int x = 1; x < width - 2; ++x) 
			{
				// drawing of each of the different elements
				grayscalePlot(x-1, y);
				grayscalePlot(x-1, y+1);
				grayscalePlot(x,y);
				grayscalePlot(x,y+1);
				grayscalePlot(x+1, y+1);
				grayscalePlot(x+1, y);

				// drawing of the bottom strip
				grayscalePlot(x-1, y);
				grayscalePlot(x-1, y-1);
				grayscalePlot(x,y);
				grayscalePlot(x,y-1);
				grayscalePlot(x+1, y-1);
				grayscalePlot(x+1, y);
			}	
			glEnd();
		}
	glPopMatrix();
}