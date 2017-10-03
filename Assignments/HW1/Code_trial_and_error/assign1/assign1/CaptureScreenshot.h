// this library will handle the screenshots that needs to be taken
	
#include "stdafx.h"
#include <stdlib.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <pic.h>


// take the variables defined in the main code assign1.cpp
extern Pic *currentImage;
extern int windowHeight, windowWidth;

// local variables being used when to take screenshots
int count = 0; // count to keep track of updates (take 1 screenshot every 30 updates)
int fid = 0; // file id count to be appended to name of each file being saved

namespace capturescreenshot {
	void saveScreenshot (char * filename); // take the screenshot
	void TakeScreenshot(); // save the screenshot
}

void capturescreenshot::saveScreenshot (char * filename) 
{
	int x, y;
	Pic * image = NULL;

	// ensure that our filename is given
	if (filename == NULL) return;

	// create a picture buffer for storing the image pixels etc
	// allocate a picture object the size of our screen
	// pic_alloc(int nx, int ny, int bpp, pic) -- will then return our image that we need
	image = pic_alloc(windowWidth, windowHeight, 3, NULL);

	printf("File to save to: %s\n", filename);

	// loop from the top left down to the bottom right for creating the pixels 
	// we want to only grab one row at at time starting from the top
	for (y = windowHeight-1 ; y >= 0; y--) 
	{
		// grab the image data, one row at a time from top to bottom
		// draw a row at a time
		glReadPixels(0, windowHeight-1-y, windowWidth, 1, GL_RGB, GL_UNSIGNED_BYTE, &image->pix[y*image->nx*image->bpp]);
	}

	if (jpeg_write(filename, image))
		printf("\nFile %s saved successfully.\n", filename);
	else
		printf("Could not save image");
	pic_free(image);
}

void capturescreenshot::TakeScreenshot() 
{
	// logic to capture screenshot every 30 updates
	char fname[2048];
	count++;
	if(count == 30 && fid <= 300)
	{
		sprintf(fname, "Screenshot/screen.%04d.jpg", fid);
		capturescreenshot::saveScreenshot(fname);
		count = 0;
		fid++;
	}
}