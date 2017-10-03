// library where the height field and all its related data gets created

#include "stdafx.h"
#include <stdlib.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <pic.h>

typedef enum {
	GRAYSCALE
} FieldType;

class HeightField {

	public: // constructors / destructors
		HeightField(unsigned int height, unsigned int width, FieldType type);
		~HeightField();		

	public: //access functions
		void addHeightPoint(unsigned int x, unsigned int y, unsigned int z);//add a point to this height map
		unsigned int getPoint(unsigned int x, unsigned int y);//return a single point's z value
		unsigned int getHeight();//returns the height of the image
		unsigned int getWidth();//returns the width
		unsigned int getMaxZ();//returns the maxZ
		unsigned int getMinZ();//returns the minZ
		float getGrayscaleColor(unsigned int x, unsigned int y);//return the color for that individual point
		void getRGBColor(unsigned int x, unsigned int y, float color[4]);
		GLfloat * getVertex(unsigned int x, unsigned int y);//grab a particular element

	private://variables and functions
		FieldType type;
		unsigned int width;//width of the element
		unsigned int height;//height of the map
		unsigned int maxZ;//maximum z field
		unsigned int minZ;//minimum z field 
		unsigned int size;//this is the size of the array that we are working with		
		unsigned int * data;//this is the data that we are storing for this particular image
		GLfloat (*vertices)[3];//this is an array of all the vertices we need for now
		// allow for quick index finding. This will make it easier to map our data structures to future elements
		unsigned int getIndex(unsigned int x, unsigned int y);//get the proper index for this data structure
};

HeightField::HeightField(unsigned int height, unsigned int width, FieldType type) : height(height), width(width), type(type) {

	// size of the array
	this->size = height * width;// in the future, when we want to work with things other than grayscale images, we can assume that 
	this->data = new unsigned int[size];//this is the data to store the correct points
	this->maxZ = 0;//initialize the maximum z value for now
	this->minZ = 255;//initialize the minimum value for z

	// initialize all elements
	this->vertices = new GLfloat[size][3];

}

HeightField::~HeightField() {

	delete this->data;//release the data!
	delete this->vertices;//release all vertices
}

void HeightField::addHeightPoint(unsigned int x, unsigned int y, unsigned int z) {

	// grab the index according to our algorithm
	unsigned int index = this->getIndex(x,y);

	// store the information in the global array -- useful for height information -- may be used later though
	this->data[index] = z;//

	// store the vertex information!
	this->vertices[index][0] = x;
	this->vertices[index][1] = y;
	this->vertices[index][2] = z;

	// make sure that we don't need to reset the current z value
	if (z > this->maxZ) 
		this->maxZ = z;

	// make sure that this is not less than the current minium z value
	if (z < this->minZ) 
		this->minZ = z;
	
}

// grab a vertex array from a certain position
GLfloat * HeightField::getVertex(unsigned int x, unsigned int y) {

	// grab the actual index using our algorithm
	unsigned int index = this->getIndex(x,y);

	// now return the actual vertex
	return this->vertices[index];

}

// get each point in image
unsigned int HeightField::getPoint(unsigned int x, unsigned int y) 
{
	return this->data[this->getIndex(x,y)];
}

// get height of image
unsigned int HeightField::getHeight() 
{
	return this->height;
}

// get width of image
unsigned int HeightField::getWidth() 
{
	return this->width;
}

// get the maximum value of height point Z
unsigned int HeightField::getMaxZ() 
{
	return this->maxZ;
}

// get the minimum value of height point Z
unsigned int HeightField::getMinZ() 
{
	return this->minZ;
}

// get the index for the particular element in the array
inline unsigned int HeightField::getIndex(unsigned int x, unsigned int y) 
{
	unsigned int index = (y * this->width) + x;
	return index;
}

// get the grayscale color
float HeightField::getGrayscaleColor(unsigned int x, unsigned int y) 
{
	float delta = this->maxZ - this->minZ;
	return float(this->getPoint(x,y)) / delta;
}