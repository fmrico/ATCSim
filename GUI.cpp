/*
 * GUI.cpp
 *
 *  Created on: 16/07/2014
 *      Author: paco
 */

#include "GUI.h"

#ifdef __APPLE__
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#else
#include <GL/glu.h>
#include <GL/gl.h>
#endif

#include <iostream>
#include <math.h>
#include "Common.h"
#include "Airport.h"
#include "AirController.h"


//#define INIT_CAM_X -20000.0f;
//#define INIT_CAM_Y 0.0f;
//#define INIT_CAM_Z 5000.0f;
//#define INIT_CAM_A M_PI;
//#define INIT_CAM_B -M_PI/2.0f;

#define INIT_CAM_X 0.0f;
#define INIT_CAM_Y 0.0f;
#define INIT_CAM_Z 20000.0f;
#define INIT_CAM_A M_PI;
#define INIT_CAM_B -M_PI;

int GUI::mousebutton = 0;
int GUI::mousestate = 0;
int GUI::mousex = 0;
int GUI::mousey = 0;
float GUI::cam_alpha = INIT_CAM_A;
float GUI::cam_beta = INIT_CAM_B;
float GUI::cam_x = INIT_CAM_X;
float GUI::cam_y = INIT_CAM_Y;
float GUI::cam_z = INIT_CAM_Z;
const int GUI::win_width  = 1024;
const int GUI::win_height = 768;
const float GUI::field_of_view_angle = 60;
const float GUI::x_near = 1.0f;
const float GUI::x_far = 40000.0f;

GUI::GUI(int argc, char *argv[]) {

	glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH );  // Display Mode
	glutInitWindowSize(win_width,win_height);					// set window size
	glutCreateWindow("ATCSim");									// create Window
	glutDisplayFunc(GUI::step);									// register Display Function
	glutIdleFunc( GUI::render );									// register Idle Function
	glutMouseFunc(GUI::processMouseFunc);
	glutMotionFunc(GUI::processMouseMotion);
	glutKeyboardFunc( GUI::keyboard );								// register Keyboard Handler

}

GUI::~GUI() {
	// TODO Auto-generated destructor stub
}

void
GUI::render()
{
	float vcam_x, vcam_y, vcam_z;
	TextDisplay *textDisplay;

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();


	vcam_x = cam_x + (cos(cam_alpha) * sin (cam_beta));
	vcam_y = cam_y + (sin(cam_alpha) * sin (cam_beta));
	vcam_z = cam_z + cos(cam_beta);

	gluLookAt(cam_x, cam_y, cam_z, vcam_x, vcam_y, vcam_z, 0.0, 0.0, 1.0);

	Airport::getInstance()->draw();
	Airport::getInstance()->step();

	AirController::getInstance()->doWork();

	textDisplay = TextDisplay::getInstance();

	textDisplay->calculateFramesPerSecond();
	textDisplay->displayFPS(30, win_height - 30, win_width, win_height, YELLOW);

	textDisplay->displayText((char*)(new std::string("ATCSim"))->c_str(), 15, 25, win_width, win_height, ORANGE);

	glutSwapBuffers();



}

void
GUI::keyboard(unsigned char key, int mousePositionX, int mousePositionY )
{
	float dlin, dlat;
	float despx, despy, despz;
	dlin = dlat = 0.0f;

	float desp = 100.0f;
	switch ( key )
	{
	case KEY_ESCAPE:
		exit ( 0 );
		break;
	case 'w':
	dlin += desp;
	break;
	case 's':
		dlin -= desp;
		break;
	case 'a':
		dlat += desp;
		break;
	case 'd':
		dlat -= desp;
		break;
    case '+':
        Airport::getInstance()->UpdateSimTime(INC_SIMTIME);
        break;
    case '-':
        Airport::getInstance()->UpdateSimTime(-INC_SIMTIME);
        break;
	case 'c':
		cam_alpha = INIT_CAM_A;
		cam_beta = INIT_CAM_B;
		cam_x = INIT_CAM_X;
		cam_y = INIT_CAM_Y;
		cam_z = INIT_CAM_Z;

		break;
	case '\t':
		Airport::getInstance()->NextFocus();
		break;
	case 'f':

		cam_x = Airport::getInstance()->getFocused()->getPosition().get_x() - 2000.0;
		cam_y = Airport::getInstance()->getFocused()->getPosition().get_y();
		cam_z = Airport::getInstance()->getFocused()->getPosition().get_z();

		cam_alpha = M_PI;
		cam_beta = -M_PI/2.0f;

		break;
	default:
		std::cerr<<"Key: "<<key<<std::endl;
		break;
	}

	cam_x = cam_x + (dlin * cos(cam_alpha) * sin (cam_beta));
	cam_y = cam_y + (dlin * sin(cam_alpha) * sin (cam_beta));
	cam_z = cam_z + dlin * cos(cam_beta);

	cam_x = cam_x + (dlat * cos(cam_alpha+(M_PI/2.0)) * sin (cam_beta));
	cam_y = cam_y + (dlat * sin(cam_alpha+(M_PI/2.0)) * sin (cam_beta));
	//cam_z = cam_z + dlat * cos(cam_beta);


}

void
GUI::processMouseFunc(int _button, int _state, int _x, int _y) {

	mousebutton = _button;
	mousex = _x;
	mousey = _y;
}

void
GUI::processMouseMotion(int _x, int _y) {

	int deltax, deltay;

	deltax = _x - mousex;
	deltay = _y - mousey;

	mousex = _x;
	mousey = _y;


	if((mousebutton == GLUT_RIGHT_BUTTON) && (mousestate == GLUT_DOWN ))
	{
		cam_alpha = normalizePi(cam_alpha - toRadians(deltax));
		cam_beta = normalizePi(cam_beta - toRadians(deltay));
	}

}

void
GUI::init()
{

	GLfloat aspect = (GLfloat) win_width / win_height;

	glMatrixMode(GL_PROJECTION);												// select projection matrix
	glViewport(0, 0, win_width, win_height);									// set the viewport
	glMatrixMode(GL_PROJECTION);												// set matrix mode
	glLoadIdentity();															// reset projection matrix
	gluPerspective(field_of_view_angle, aspect, x_near, x_far);				// set up a perspective projection matrix
	glMatrixMode(GL_MODELVIEW);													// specify which matrix is the current matrix
	glShadeModel( GL_SMOOTH );
	glClearDepth( 1.0f );														// specify the clear value for the depth buffer
	glEnable( GL_DEPTH_TEST );
	glDepthFunc( GL_LEQUAL );
	glHint( GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST );						// specify implementation-specific hints
	glClearColor(0.0, 0.0, 0.0, 1.0);											// specify clear values for the color buffers
	glEnable (GL_BLEND);
	glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);



}

void
GUI::run()
{
	glutMainLoop();
}

void
GUI::step()
{

}

