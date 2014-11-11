/*
 * Airport.cpp
 *
 *  Created on: 17/07/2014
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

#include "Airport.h"

#include <sys/time.h>
#include <stdio.h>

#include "GUI.h"

#ifdef __APPLE__
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#else
#include <GL/glu.h>
#include <GL/gl.h>
#endif

#include <cstdlib>

Airport::Airport() {

	flights.clear();

	gettimeofday(&last_ts, NULL);
	crono = last_ts.tv_sec*1000000 + last_ts.tv_usec;

	final_pos.set_x(LANDING_POS_X);
	final_pos.set_y(LANDING_POS_Y);
	final_pos.set_z(LANDING_POS_Z);

	srand (time(NULL));
	sec = 0;
	points = INIT_POINTS;
	max_flights = INIT_MAX_FLIGHTS;
    SimTimeMod = 1.0;
}

Airport::~Airport() {
	std::list<Flight*>::iterator it;
	for(it = flights.begin(); it!=flights.end(); ++it)
		delete(*it);
	flights.clear();
}

void
Airport::generate_flight()
{

	float angle, x, y, z;
	float bear, inc;
	char id[6];

	angle = toRadians((float)(rand() % 360 - 180));

	x = 20000.0f * cos(angle);
	y = 20000.0f * sin(angle);
	z = 2000.0f + (float)(rand() % 2000);

	Position ipos(x, y, z);
	Position pos0(0.0, 0.0, 0.0);

	pos0.angles(ipos, bear, inc);

	sprintf(id, "IB%4.4d", sec++);
	Flight *aux;
	aux = new Flight(id, ipos, bear, 0.0, 200.0);
	flights.push_back(aux);

	if(flights.size() == 1)
		NextFocus();
}


void
Airport::NextFocus()
{
	if(flights.empty()) return;

	if(flights.size() == 1)
	{
		focus = flights.begin();
		(*focus)->setFocused(true);
	}

	if(flights.size() > 1)
	{
		(*focus)->setFocused(false);

		if(++focus == flights.end())
			focus =  flights.begin();
	}else
		focus =  flights.begin();

	(*focus)->setFocused(true);
}


void
Airport::step()
{
	float delta_t;
	struct timeval tv;
	std::list<Flight*>::iterator it;
	long ta, tb;

	gettimeofday(&tv, NULL);

	ta = tv.tv_sec*1000000 + tv.tv_usec;
	tb = last_ts.tv_sec*1000000 + last_ts.tv_usec;

	delta_t = ((float)(ta-tb)) /1000000.0;
	last_ts = tv;

	if((ta-crono)>INC_DIFF)
	{
		max_flights += INC_PEN;
		std::cerr<<"Increase flights in "<<INC_PEN<<" to "<<max_flights<<std::endl;
		crono = ta;
	}

	if(!flights.empty())
		for(it = flights.begin(); it!=flights.end(); ++it)
		{
			(*it)->update(SimTimeMod * delta_t);
			(*it)->draw();
		}

	checkLandings();
	checkCollisions();
	checkCrashes();

	if(flights.size()<max_flights)
		generate_flight();
}


std::list<Flight*>::iterator
Airport::removeFlight(std::string id)
{
	std::list<Flight*>::iterator it;

	it=flights.begin();

	while(it !=  flights.end())
	{
		if((*it)->getId().compare(id) == 0)
		{
			if((*it)==(*focus))
			{
				delete(*it);
				focus = flights.erase(it);
				(*focus)->setFocused(true);
				return focus;
			}else
			{
				delete(*it);
				it = flights.erase(it);
				return it;
			}
		}
			it++;
	}
	return flights.begin();

}

void
Airport::checkCollisions()
{
	std::list<Flight*>::iterator i,j;
	bool removed = false;


	i =  flights.begin();

	while(i != flights.end())
	{
		j = i;

		if(j!=flights.end()) j++;

		while(j != flights.end())
		{
			if( (*i)->getPosition().distance((*j)->getPosition()) < COLLISION_DISTANCE)
			{
				std::cerr<<"Collision between "<<(*i)->getId()<<" and "<<(*j)->getId()<<std::endl;
				i = removeFlight((*i)->getId());
				j = removeFlight((*j)->getId());
				points += COLLISION_POINTS;
				return; //Avoid not valid iterator. Only one collision per cycle
			}
			j++;
		}
		i++;
	}
}


void
Airport::checkCrashes()
{
	std::list<Flight*>::iterator it;

	it = flights.begin();
	while(it != flights.end())
	{
		if((*it)->getPosition().get_z()<CRASH_Z)
		{
			std::cerr<<"[PoZ]Crash of "<<(*it)->getId()<<std::endl;
			it=removeFlight((*it)->getId());
			points += CRASH_HEIGHT_POINTS;
		}else if(toDegrees(fabs((*it)->getInclination())) > CRASH_INC)
		{
			std::cerr<<"[Inc] Crash of "<<(*it)->getId()<<std::endl;
			it = removeFlight((*it)->getId());
			points += CRASH_INC_POINTS;
		}else if( (*it)->getSpeed()<CRASH_SPEED)
		{
			std::cerr<<"[Spd] Crash of "<<(*it)->getId()<<std::endl;
			it = removeFlight((*it)->getId());
			points += CRASH_SPEED_POINTS;
		}else
			it++;
	}
}

void
Airport::checkLandings()
{
	std::list<Flight*>::iterator it;

	it = flights.begin();

	while(it != flights.end())
	{

		if((final_pos.distance((*it)->getPosition()) < LANDING_DIST) &&
				(toDegrees(normalizePi(fabs((*it)->getBearing() - toRadians(LANDING_BEAR))))<LANDING_BEAR_MAX_ERROR) &&
				((*it)->getSpeed()<LANDING_SPEED))
		{

			std::cerr<<"Flight "<<(*it)->getId()<<" landed"<<std::endl;
			it = removeFlight((*it)->getId());

			points += (int)(*it)->getPoints();
		}else
			it++;
	}

}

void
Airport::UpdateSimTime(float inc)
{
    SimTimeMod = SimTimeMod + inc;
    
    if(SimTimeMod < 0) SimTimeMod = 0;
}

void
Airport::draw()
{
	glBegin(GL_QUADS);
	glColor3f(0.2f,0.2f,0.2f);
	glVertex3f( -10000.0f, 10000.0f, 0.0f);
	glVertex3f(  10000.0f, 10000.0f, 0.0f);
	glVertex3f(  10000.0f,-10000.0f, 0.0f);
	glVertex3f( -10000.0f,-10000.0f, 0.0f);
	glEnd();

	glBegin(GL_QUADS);
	glColor3f(1.0f,1.0f,0.0f);
	glVertex3f(  0.0f, -40.0f, 0.01f);
	glVertex3f(  0.0f,  40.0f, 0.01f);
	glVertex3f(  -750.0f, 40.0f, 0.01f);
	glVertex3f( -750, -40.0f, 0.01f);
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
	snprintf(points_txt, 255, "Level: %d\t\tPoints: %d ", max_flights, points);

	textDisplay->displayText(points_txt, GUI::win_width-300, 25, GUI::win_width, GUI::win_height, WHITE, GLUT_BITMAP_TIMES_ROMAN_24);

	snprintf(points_txt, 255, "Time speed: x%3.1f", SimTimeMod);
	textDisplay->displayText(points_txt, 10, GUI::win_height-5, GUI::win_width, GUI::win_height, WHITE, GLUT_BITMAP_HELVETICA_12);

	char help_txt[255];
	strcpy(help_txt, "Press Mouse3 and move mouse to change orientation");
	textDisplay->displayText(help_txt, GUI::win_width-310, GUI::win_height-5, GUI::win_width, GUI::win_height, WHITE, GLUT_BITMAP_HELVETICA_12);
	strcpy(help_txt, "<Tab> Change flight info");
	textDisplay->displayText(help_txt, GUI::win_width-160, GUI::win_height-160, GUI::win_width, GUI::win_height, WHITE, GLUT_BITMAP_HELVETICA_12);
	strcpy(help_txt, "<w>Move camera forward");
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
