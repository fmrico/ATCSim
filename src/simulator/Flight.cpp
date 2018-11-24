/*
 * Flight.cpp
 *
 *  Created on: 15/07/2014
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
 */

#include "Flight.h"

#ifdef __APPLE__
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#else
#include <GL/glu.h>
#include <GL/gl.h>
#endif

#include "Common.h"

#include <iostream>
#include <string>
#include <math.h>

Flight::~Flight() {
	// TODO Auto-generated destructor stub
}

Flight::Flight(std::string _id, Position _pos, float _bearing, float _inclination, float _speed)
{
	id = _id;
	pos = _pos;
	bearing = _bearing;
	inclination = _inclination;
	//speed = _speed;
	setSpeed(_speed);	// Through set in order to limit speeds

	route.clear();
	inStorm = false;

	focused = false;
	points = INIT_FLIGHT_POINTS;

	w_speed = 0.0f;
}

void
Flight::update(float delta_t)
{
	float trans;
	Position CPpos;

	if(routed())
	{
		float goal_bearing, diff_bearing, new_w;

		CPpos = route.front().pos;
		pos.angles(CPpos, goal_bearing, inclination);

		goal_bearing = normalizePi(goal_bearing + M_PI);
		diff_bearing = normalizePi(goal_bearing - bearing);
		new_w = diff_bearing;

		if(fabs(new_w)>MAX_FLIFGT_W) new_w = (fabs(new_w)/new_w) * MAX_FLIFGT_W;

		//std::cout<<"["<<id<<"]angle = "<<bearing<<"\tnew = "<<goal_bearing<<"\t["<<diff_bearing<<"]\tideal w = "<<new_w<<" -> "<<new_w_b<<std::endl;

		bearing = bearing + new_w*delta_t;

		float goal_speed, diff_speed, acc;

		goal_speed = checkSpeedLimits(route.front().speed);
		acc = (goal_speed - speed);

		if(fabs(acc)>MAX_ACELERATION) acc = (acc/fabs(acc))*MAX_ACELERATION;

		speed = speed + acc*delta_t;

		//std::cout<<"["<<id<<"]speed = "<<speed<<"\tnew = "<<goal_speed<<"\t["<<acc<<"]\t"<<std::endl;

	}else
		inclination = 0.0;

	last_pos = pos;

	trans = speed * delta_t;


	pos.set_x(pos.get_x() + trans * cos(bearing) * cos(inclination));
	pos.set_y(pos.get_y() + trans * sin(bearing) * cos(inclination));
	pos.set_z(pos.get_z() + ( trans * sin(inclination)));

//	if(pos.distance(last_pos) > pos.distance(CPpos))
//		route.pop_front();

	if(pos.distance(CPpos)<DIST_POINT)
		route.pop_front();

	if(inStorm)
	{
		//std::cout<<"["<<id<<"]In Storm"<<std::endl;
		points = points - 2*delta_t;
	}
	else
		points = points - delta_t;



}


float Flight::checkSpeedLimits(float tgt_speed){
	return (tgt_speed > CRASH_SPEED_MAX ? CRASH_SPEED_MAX : tgt_speed);
}

//
//void
//Flight::draw()
//{
//
//
//
//	glPushMatrix();
//
//	//Draw Aeroplane
//	glTranslatef(pos.get_x(), pos.get_y(), pos.get_z());
//	glRotatef(toDegrees(bearing), 0.0f, 0.0f, 1.0f);
//	glRotatef(toDegrees(-inclination), 0.0f, 1.0f, 0.0f);
//	glBegin(GL_POLYGON);
//	glColor3f(1.0f,0.0f,0.0f);
//
//	glVertex3f( 30.0f, 0.0f, 0.0f);
//	glVertex3f( -30.0f, 32.0f, 0.0f);
//	glVertex3f( -30.0f, -32.0f, 0.0f);
//	glEnd();
//
//	glBegin(GL_POLYGON);
//	glColor3f(0.0f,0.0f,1.0f);
//
//	glVertex3f( -10.0f, 0.0f, 0.0f);
//	glVertex3f( -30.0f, 0.0f, 0.0f);
//	glVertex3f( -30.0f, 0.0f, 21.0f);
//	glEnd();
//
//
//	//Draw Collision sphere
//
//	if(focused)
//		glColor4f(1.0f, 0.0f, 0.0f, 0.4f);
//	else
//		glColor4f(1.0f,1.0f,1.0f, 0.2f);
//
//
//	GLUquadric *quadratic = gluNewQuadric();
//	gluQuadricNormals(quadratic, GLU_SMOOTH);
//	gluQuadricTexture(quadratic, GL_TRUE);
//	gluSphere( quadratic, COLLISION_DISTANCE/2.0f, 32, 32);
//	glPopMatrix();
//
//	if(focused)
//	{
//		std::list<Route>::iterator it;
//
//		TextDisplay *textDisplay = TextDisplay::getInstance();
//		char pos_str[255];
//
//		textDisplay->displayText((char*)id.c_str(), 15, 75, GUI::win_width, GUI::win_height, LIGHTBLUE, GLUT_BITMAP_HELVETICA_18);
//		snprintf(pos_str, 255, "Points: %5.5lf ", points);
//		textDisplay->displayText(pos_str, 15, 95, GUI::win_width, GUI::win_height, YELLOW, GLUT_BITMAP_HELVETICA_12);
//
//		snprintf(pos_str, 255, "Position: (%lf, %lf, %lf) m", pos.get_x(), pos.get_y(), pos.get_z());
//		textDisplay->displayText(pos_str, 15, 115, GUI::win_width, GUI::win_height, WHITE, GLUT_BITMAP_HELVETICA_12);
//		snprintf(pos_str, 255, "Bearing: %lf deg", toDegrees(bearing));
//		textDisplay->displayText(pos_str, 15, 135, GUI::win_width, GUI::win_height, WHITE, GLUT_BITMAP_HELVETICA_12);
//		snprintf(pos_str, 255, "Inclination: %lf deg", toDegrees(inclination));
//		textDisplay->displayText(pos_str, 15, 155, GUI::win_width, GUI::win_height, WHITE, GLUT_BITMAP_HELVETICA_12);
//		snprintf(pos_str, 255, "Speed: %lf m/sec", speed);
//		textDisplay->displayText(pos_str, 15, 175, GUI::win_width, GUI::win_height, WHITE, GLUT_BITMAP_HELVETICA_12);
//
//
//		if(!route.empty())
//		{
//
//			glColor4f(0.0f,0.0f,1.0f, 1.0f);
//			glBegin(GL_LINES);
//
//			glVertex3f(pos.get_x(), pos.get_y(), pos.get_z());
//			for(it = route.begin(); it!=route.end(); ++it)
//			{
//				glVertex3f((*it).pos.get_x(), (*it).pos.get_y(), (*it).pos.get_z());
//				glVertex3f((*it).pos.get_x(), (*it).pos.get_y(), (*it).pos.get_z());
//			}
//			glEnd();
//
//			for(it = route.begin(); it!=route.end(); ++it)
//			{
//				glPushMatrix();
//				glTranslatef((*it).pos.get_x(), (*it).pos.get_y(),(*it).pos.get_z());
//				GLUquadric *quadratic = gluNewQuadric();
//				gluQuadricNormals(quadratic, GLU_SMOOTH);
//				gluQuadricTexture(quadratic, GL_TRUE);
//				gluSphere( quadratic, 50.0f, 32, 32);
//				glPopMatrix();
//			}
//
//
//			textDisplay->displayText((char *)"Route", 15, 230, GUI::win_width, GUI::win_height, BLUE, GLUT_BITMAP_HELVETICA_12);
//
//			int c = 0;
//			for(it = route.begin(); it!=route.end(); ++it)
//			{
//				snprintf(pos_str, 255, "Position: (%lf, %lf, %lf) m", (*it).pos.get_x(), (*it).pos.get_y(), (*it).pos.get_z());
//				textDisplay->displayText(pos_str, 25, 250+(20*c), GUI::win_width, GUI::win_height, WHITE, GLUT_BITMAP_HELVETICA_12);
//				c++;
//			}
//
//		}
//
//	}
//
//
//
//
//}
