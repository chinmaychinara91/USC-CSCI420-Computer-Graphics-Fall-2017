// CSCI-420 Assignment-1 
// Height Fields
// Code written by: Chinmay Chinara
// USC ID: 2527237452
// Due date: 25th September 2017
========================================================================
My code is entirely in Windows, tried and tested
========================================================================
STEPS TO COMPILE AND RUN CODE FROM SCRATCH
========================================================================
1. 	The complete project needs to be built using Microsoft Visual Studio

2. 	Create an Empty project using Microsoft Visual Studio with the project name as 
	"assign1"

3.	Copy all the files and folders present in this folder where this README.txt is to
	the "assign1" folder created inside "assign1" project. Along with it make sure that
	all image files are also copied in this folder. Make an additional folder by the
	name "Screenshot" where all the screen shots will be saved (if required)

4. 	Once the Project window loads, in the Solution Explorer do the following:
--> 	In Header Files section add: CaptureScreenshot.h, CreateHeightField.h, DisplayFrames.h, 
	DrawDisplayType.h, KeyboardMouse.h, stdafx.h, targetver.h
--> 	In Source Files section add: assign1.cpp, stdafx.cpp

5. 	In the Project -> assign1 Properties -> Configuration Properties -> VC++ Directories -> Include Directories, add 
	path for "glut-3.7.6-bin" and "picLibrary" folders

6. 	In the Project -> assign1 Properties -> Configuration Properties -> C/C++ -> General -> Additional Include 
	Directories, add path for "glut-3.7.6-bin" and "picLibrary" folders

7.	In the Project -> assign1 Properties -> Configuration Properties -> Linker -> General -> Additional Include Directories, 
	add "glut-3.7.6-bin" and "picLibrary"

8.	In the Project -> assign1 Properties -> Configuration Properties -> Linker -> Input -> Additional Dependencies, 
	add libjpeg.lib, libtiff.lib, picLibrary.lib, glut32.lib

9.	The Project is now all set. Before running make sure an input image is given. Else the code will throw
	a message how to rectify and re-run the code. For doing that, go to Project -> assign1 Properties -> Configuration
	Properties -> Debugging ->  Command Arguments and add the path of the file with name (just name if image file present
	in the same folder)

10.	Press CTRL+F5 to run the code.

========================================================================
INTERACTION FUNCTIONALITIES (USING MOUSE AND KEYBOARD)
========================================================================
1.	Left Key for clockwise rotation

2.	Right key for anti-clockwise rotation

3.	Up key for upward rotation

4.	Down key for downward rotation

5.	's' key for screenshot capture start (at max 300 screenshots)

6.	't' key for screenshot capture stop

7.	'g' key for rendering as GRAYSCALE

8.	'w' key for rendering as WIREFRAME

9.	'p' key for rendering as POINTS

10.	'+' key for increasing wireframe density

11.	'-' key for decreasing wireframe density

12. 	Hold left mouse button and scroll around the image to rotate it about in 3D

13.	Hold middle mouse button and scroll around the image to rotate it about in 2D around y-axis

14.	Keep pressing CTRL key and hold left mouse button and scroll around the image to TRANSLATE

15.	Keep pressing SHIFT key and hold left mouse button and scroll around the image to SCALE

========================================================================
OTHER POINTS / EXTRA CREDITS
========================================================================
1.	All screenshots taken by me for all the 156x156 images given in Starter Code folder
	are in the respective folders

2.	My default screen size for the display is 1024 (width) and 768 (height). It can be changed
	in the assign1.cpp code in line number 27.

3. 	My code works for any type of image size (tried and tested). I used 256 x 256 for 
	faster results for submission.

4. 	Be able to render the height field as points, lines("wireframe"), or solid triangles 
	(with keys for the user to switch between the three as defined in above section) 

5.	Render as a perspective view, utilizing GL's depth buffer for hidden surface removal
	
6.	Input from the mouse to spin the heightfield around using glRotate

7.	Input from the mouse to move the heightfield around using glTranslate

8.	Input from the mouse to change the dimensions of the heightfield using glScale

9.	The vertices colored using some smooth gradient (red).