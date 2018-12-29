/*
 * GUI.cpp
 *
 *  Created on: 16/07/2014
 *      Author: paco
 *
 *  Copyright 2014 Francisco Martín
 *
 *  This file is part of ATCSim.
 *
 *  ATCSim is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  ATCSim is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with ATCSim.  If not, see <http://www.gnu.org/licenses/>.
 *  */


#include "GUI.h"

#ifdef __APPLE__
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#else
#include <GL/glu.h>
#include <GL/gl.h>
#endif

#include <iomanip>
#include <iostream>
#include <math.h>
#include "colours.h"
#include "Common.h"
//#include "Airport.h"
//#include "AirController.h"


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
const int GUI::wpt_size = 400; // Waypoint size (world units)
const float GUI::field_of_view_angle = 60;
const float GUI::x_near = 1.0f;
const float GUI::x_far = 40000.0f;

ATCDisplay::AirportInterfacePrx GUI::airportsim;
ATCDisplay::ATCDAirport GUI::airportinfo;

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


	ATCDisplay::ATCDFlights flights = airportsim->getFlights();
	ATCDisplay::ATCDFlights::iterator it;

	DrawAirport();

	for(it=flights.begin(); it!=flights.end(); ++it)
		DrawFlight(*it);

	ATCDisplay::ATCDStorm storm = airportsim->getStorm();
	DrawStorm(storm);

	textDisplay = TextDisplay::getInstance();

	textDisplay->calculateFramesPerSecond();
	textDisplay->displayFPS(30, win_height - 30, win_width, win_height, YELLOW);

	textDisplay->displayText((char*)(new std::string("ATCSim"))->c_str(), 15, 25, win_width, win_height, ORANGE);

	glutSwapBuffers();



}

ATCDisplay::ATCDFlight
GUI::getFlightFocused()
{
	ATCDisplay::ATCDFlights flights = airportsim->getFlights();
	std::vector<ATCDisplay::ATCDFlight>::iterator it;


	for(it=flights.begin(); it!=flights.end(); ++it)
			if((*it).focused)
				return (*it);
}


void
GUI::keyboard(unsigned char key, int mousePositionX, int mousePositionY )
{
	float dlin, dlat;
	float despx, despy, despz;
	dlin = dlat = 0.0f;

	ATCDisplay::ATCDFlight flight;

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
    	airportsim->UpdateSimT(INC_SIMTIME);
    	//Airport::getInstance()->UpdateSimTime(INC_SIMTIME);
        break;
    case '-':
    	airportsim->UpdateSimT(-INC_SIMTIME);
        //Airport::getInstance()->UpdateSimTime(-INC_SIMTIME);
        break;
	case 'c':
		cam_alpha = INIT_CAM_A;
		cam_beta = INIT_CAM_B;
		cam_x = INIT_CAM_X;
		cam_y = INIT_CAM_Y;
		cam_z = INIT_CAM_Z;

		break;
	case '\t':
		airportsim->NextFocus();
		break;
	case 'f':

		flight = getFlightFocused();

		cam_x = flight.pos.x - 2000.0;
		cam_y = flight.pos.y;
		cam_z = flight.pos.z;

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
GUI::init(ATCDisplay::AirportInterfacePrx as)
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

	airportsim = as;

	airportinfo = airportsim->getAirportInfo();
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

void
GUI::DrawStorm(ATCDisplay::ATCDStorm storm)
{
	//std::cerr<<"("<<storm.pos.x<<", "<<storm.pos.y<<", "<<storm.pos.z<<") ["<<storm.height<<","<<storm.radious<<", "<<storm.speed<<"]"<<std::endl;

	//Podemos pintar muchas esferas, o polígonos
	glPushMatrix();
	glColor3f(1.0f,1.0f,1.0f);
	glTranslatef(storm.pos.x, storm.pos.y, storm.pos.z);

	glutWireTorus(storm.height, storm.radious-storm.height/2.0, 30, 30);
	glPopMatrix();
}

void
GUI::DrawFlight(ATCDisplay::ATCDFlight flight)
{

	glPushMatrix();

	//Draw Aeroplane
	glTranslatef(flight.pos.x, flight.pos.y, flight.pos.z);
	glRotatef(toDegrees(flight.bearing), 0.0f, 0.0f, 1.0f);
	glRotatef(toDegrees(-flight.inclination), 0.0f, 1.0f, 0.0f);
	glBegin(GL_POLYGON);
	glColor3f(0.0f,1.0f,0.0f);

	//glVertex3f( 30.0f, 0.0f, 0.0f);
	//glVertex3f( -30.0f, 32.0f, 0.0f);
	//glVertex3f( -30.0f, -32.0f, 0.0f);
	glVertex3f( 45.0f, 0.0f, -2.0f);
	glVertex3f( 35.0f, -5.0f, -2.0f);
	glVertex3f( -22.64f, -5.0f, -2.0f);
	glVertex3f( -32.64f, 0.0f, -2.0f);
	glVertex3f( -22.64f, 5.0f, -2.0f);
	glVertex3f( 35.0f, 5.0f, -2.0f);
	glEnd();



	glBegin(GL_POLYGON);
	glColor3f(1.0f,0.0f,1.0f);

	glVertex3f( 3.0f, -5.0f, -2.0f);
	glVertex3f( -12.0f, -40.0f, -2.0f);
	glVertex3f( -18.0f, -40.0f, -2.0f);
	glVertex3f( -15.0f, -30.0f, -2.0f);
	glVertex3f( -13.0f, -5.0f, -2.0f);
	glVertex3f( -13.0f, 5.0f, -2.0f);
	glVertex3f( -15.0f, 30.0f, -2.0f);
	glVertex3f( -18.0f, 40.0f, -2.0f);
	glVertex3f( -12.0f, 40.0f, -2.0f);
	glVertex3f( 3.0f, 5.0f, -2.0f);

	glEnd();

	glBegin(GL_POLYGON);
	glColor3f(1.0f,1.0f,1.0f);

	glVertex3f( -38.0f, 0.0f, 12.0f);
	glVertex3f( -46.0f, -12.0f, 12.0f);
	glVertex3f( -53.0f, -12.0f, 12.0f);
	glVertex3f( -48.0f, 0.0f, 12.0f);
	glVertex3f( -53.0f, 12.0f, 12.0f);
	glVertex3f( -46.0f, 12.0f, 12.0f);

	glEnd();


	glBegin(GL_POLYGON);
	glColor3f(0.0f,0.0f,1.0f);

	glVertex3f( 35.0f, 0.0f, 5.0f);
	glVertex3f( 45.0f, 0.0f, -2.0f);
	glVertex3f( 35.0f, 0.0f, -5.0f);
	glVertex3f( -23.0f, 0.0f, -5.0f);
	glVertex3f( -45.0f, 0.0f, 2.0f);
	glVertex3f( -33.0f, 0.0f, 5.0f);

	glEnd();

	glBegin(GL_POLYGON);
	glColor3f(0.0f,1.0f,1.0f);

	glVertex3f( -45.0f, 0.0f, 2.0f);
	glVertex3f( -48.0f, 0.0f, 12.0f);
	glVertex3f( -38.0f, 0.0f, 12.0f);
	glVertex3f( -33.0f, 0.0f, 5.0f);

	glEnd();


	//Draw Collision sphere

	if(flight.focused)
		glColor4f(1.0f, 0.0f, 0.0f, 0.4f);
	else
		glColor4f(1.0f,1.0f,1.0f, 0.2f);


	GLUquadric *quadratic = gluNewQuadric();
	gluQuadricNormals(quadratic, GLU_SMOOTH);
	gluQuadricTexture(quadratic, GL_TRUE);
	gluSphere( quadratic, COLLISION_DISTANCE/2.0f, 32, 32);
	glPopMatrix();

	if(flight.focused)
	{
		ATCDisplay::ATCDRoute route = flight.flightRoute;

		std::vector<ATCDisplay::ATCDPosition>::iterator it;
		it = route.begin();
		TextDisplay *textDisplay = TextDisplay::getInstance();
		char pos_str[255];

		textDisplay->displayText((char*)flight.id.c_str(), 15, 75, GUI::win_width, GUI::win_height, LIGHTBLUE, GLUT_BITMAP_HELVETICA_18);
		snprintf(pos_str, 255, "Points: %5.5lf ", flight.points);
		textDisplay->displayText(pos_str, 15, 95, GUI::win_width, GUI::win_height, YELLOW, GLUT_BITMAP_HELVETICA_12);

		snprintf(pos_str, 255, "Position: (%lf, %lf, %lf) m", flight.pos.x, flight.pos.y, flight.pos.z);
		textDisplay->displayText(pos_str, 15, 115, GUI::win_width, GUI::win_height, WHITE, GLUT_BITMAP_HELVETICA_12);
		snprintf(pos_str, 255, "Bearing: %lf deg", toDegrees(flight.bearing));
		textDisplay->displayText(pos_str, 15, 135, GUI::win_width, GUI::win_height, WHITE, GLUT_BITMAP_HELVETICA_12);
		snprintf(pos_str, 255, "Inclination: %lf deg", toDegrees(flight.inclination));
		textDisplay->displayText(pos_str, 15, 155, GUI::win_width, GUI::win_height, WHITE, GLUT_BITMAP_HELVETICA_12);
		snprintf(pos_str, 255, "Speed: %lf m/sec", flight.speed);
		textDisplay->displayText(pos_str, 15, 175, GUI::win_width, GUI::win_height, WHITE, GLUT_BITMAP_HELVETICA_12);


		if(!route.empty())
		{

			glColor4f(0.0f,0.0f,1.0f, 1.0f);
			glBegin(GL_LINES);

			float aux_alt;
			glVertex3f(flight.pos.x, flight.pos.y, flight.pos.z);
			for(it = route.begin(); it!=route.end(); ++it)
			{
				// If point of route has no altitude, draw last altitude
				if((*it).z > MAINTAIN_ALT)
					aux_alt = (*it).z;

				glVertex3f((*it).x, (*it).y, aux_alt);
				glVertex3f((*it).x, (*it).y, aux_alt);
			}
			glEnd();


			for(it = route.begin(); it!=route.end(); ++it)
			{
				// If point of route has no altitude, draw last altitude
				if((*it).z > MAINTAIN_ALT)
					aux_alt = (*it).z;

				glColor4f(0.0f,0.0f,1.0f, 1.0f);
				glPushMatrix();
				glTranslatef((*it).x, (*it).y, aux_alt);
				GLUquadric *quadratic = gluNewQuadric();
				gluQuadricNormals(quadratic, GLU_SMOOTH);
				gluQuadricTexture(quadratic, GL_TRUE);
				gluSphere( quadratic, 50.0f, 32, 32);
				glPopMatrix();

				if(it->name != "")
				{
					glBegin(GL_POLYGON);
					glColor3f(0.6f, 0.6f, 0.6f);
					glVertex3f(-0.5*wpt_size + (*it).x, (*it).y, 1.0f);
					glVertex3f( 0.5*wpt_size + (*it).x, -0.5*wpt_size + (*it).y, 1.0f);
					glVertex3f( 0.5*wpt_size + (*it).x,  0.5*wpt_size + (*it).y, 1.0f);
					glEnd();

					std::string wpt_name = (*it).name;
					glRasterPos2i((*it).x + 1.5*wpt_size, (*it).y - 0.5*wpt_name.length()*0.5*wpt_size);	//TODO: center text
					for(std::string::iterator i = wpt_name.begin(); i != wpt_name.end(); i++){
						char c = *i;
						glColor3d(1.0, 1.0, 1.0);
						glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, c);
					}//for

				}//if

			}//for


			textDisplay->displayText((char *)"Route", 15, 230, GUI::win_width, GUI::win_height, BLUE, GLUT_BITMAP_HELVETICA_12);

			int c = 0;
			std::string z_str;
			for(it = route.begin(); it!=route.end(); ++it)
			{
				char* charAux = new char[4];		// Two decimal places

				if((*it).z < 0)
					z_str = "=.==";
				else
				{
					//z_str = std::to_string((*it).z);
					std::stringstream ss;
					ss << std::fixed << std::setprecision(2) << (*it).z;
					z_str = ss.str();
				}

				strcpy(charAux, z_str.c_str());

				if((*it).name == ""){
					snprintf(pos_str, 255, "Position: (%.2lf, %.2lf, %s) m", (*it).x, (*it).y, charAux);
				}else{
					std::string nameStr = (*it).name;
					char* charStr = new char[nameStr.length()+1];
					strcpy(charStr, nameStr.c_str());
					//snprintf(pos_str, 255, "Wpt: %s (%.2lf, %.2lf) m @ %.2f m", charStr, (*it).wpt.lat, (*it).wpt.lon, (*it).alt);
					snprintf(pos_str, 255, "Waypoint: %s @ %s m", charStr, charAux);
				}

				textDisplay->displayText(pos_str, 25, 250+(20*c), GUI::win_width, GUI::win_height, WHITE, GLUT_BITMAP_HELVETICA_12);
				c++;
			}

		}

	}


}

void
GUI::DrawAirport()
{

	glBegin(GL_QUADS);
	glColor3f(0.2f,0.2f,0.2f);
	glVertex3f( -airportinfo.radious, airportinfo.radious, 0.0f);
	glVertex3f(  airportinfo.radious, airportinfo.radious, 0.0f);
	glVertex3f(  airportinfo.radious,-airportinfo.radious, 0.0f);
	glVertex3f( -airportinfo.radious,-airportinfo.radious, 0.0f);
	glEnd();

	ATCDisplay::ATCDLandStrip lstrip= (*airportinfo.airportLandstrips.begin());

	glBegin(GL_QUADS);
	glColor3f(1.0f,1.0f,0.0f);
	glVertex3f(  0.0f, -(lstrip.width/2.0), 0.01f);
	glVertex3f(  0.0f,  lstrip.width, 0.01f);
	glVertex3f( -lstrip.length, lstrip.width, 0.01f);
	glVertex3f( -lstrip.length, -lstrip.width, 0.01f);
	glEnd();

	glPushMatrix();
	glTranslatef(1.0f, 0.0f, 25.0f);
	GLUquadric *quadratic = gluNewQuadric();
	gluQuadricNormals(quadratic, GLU_SMOOTH);
	gluQuadricTexture(quadratic, GL_TRUE);
	gluSphere( quadratic, 25.0f, 32, 32);
	glPopMatrix();

	TextDisplay *textDisplay = TextDisplay::getInstance();
	char points_txt[255];
	snprintf(points_txt, 255, "Level: %d\t\tPoints: %d ", airportsim->getMaxFlights(), airportsim->getPoints());

	textDisplay->displayText(points_txt, GUI::win_width-300, 25, GUI::win_width, GUI::win_height, WHITE, GLUT_BITMAP_TIMES_ROMAN_24);

	snprintf(points_txt, 255, "Time speed: x%3.1f", airportsim->getSimT());
	textDisplay->displayText(points_txt, 10, GUI::win_height-5, GUI::win_width, GUI::win_height, WHITE, GLUT_BITMAP_HELVETICA_12);
	char help_txt[255];
	strcpy(help_txt, "Press Mouse3 and move mouse to change orientation");
	textDisplay->displayText(help_txt, GUI::win_width-310, GUI::win_height-5, GUI::win_width, GUI::win_height, WHITE, GLUT_BITMAP_HELVETICA_12);
	strcpy(help_txt, "<Tab> Change flight info");
	textDisplay->displayText(help_txt, GUI::win_width-160, GUI::win_height-200, GUI::win_width, GUI::win_height, WHITE, GLUT_BITMAP_HELVETICA_12);
	strcpy(help_txt, "<w>Move camera forward");
	textDisplay->displayText(help_txt, GUI::win_width-160, GUI::win_height-180, GUI::win_width,
GUI::win_height, WHITE, GLUT_BITMAP_HELVETICA_12);
	strcpy(help_txt, "<+>Speed up time");
	textDisplay->displayText(help_txt, GUI::win_width-160, GUI::win_height-160, GUI::win_width,
GUI::win_height, WHITE, GLUT_BITMAP_HELVETICA_12);
	strcpy(help_txt, "<->Slow down time");
	textDisplay->displayText(help_txt, GUI::win_width-160, GUI::win_height-140, GUI::win_width, GUI::win_height, WHITE, GLUT_BITMAP_HELVETICA_12);
	strcpy(help_txt, "<s>Move camera backward");
	textDisplay->displayText(help_txt, GUI::win_width-160, GUI::win_height-120, GUI::win_width, GUI::win_height, WHITE, GLUT_BITMAP_HELVETICA_12);
	strcpy(help_txt, "<a>Move camera side left");
	textDisplay->displayText(help_txt, GUI::win_width-160, GUI::win_height-100, GUI::win_width, GUI::win_height, WHITE, GLUT_BITMAP_HELVETICA_12);
	strcpy(help_txt, "<d>Move camera side right");
	textDisplay->displayText(help_txt, GUI::win_width-160, GUI::win_height-80, GUI::win_width, GUI::win_height, WHITE, GLUT_BITMAP_HELVETICA_12);
	strcpy(help_txt, "<c>Reset camera position");
	textDisplay->displayText(help_txt, GUI::win_width-160, GUI::win_height-60, GUI::win_width, GUI::win_height, WHITE, GLUT_BITMAP_HELVETICA_12);
	strcpy(help_txt, "<f>Center camera in flight");
	textDisplay->displayText(help_txt, GUI::win_width-160, GUI::win_height-40, GUI::win_width, GUI::win_height, WHITE, GLUT_BITMAP_HELVETICA_12);
	strcpy(help_txt, "<esc>Finish");
	textDisplay->displayText(help_txt, GUI::win_width-160, GUI::win_height-20, GUI::win_width, GUI::win_height, WHITE, GLUT_BITMAP_HELVETICA_12);

}
