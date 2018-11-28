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
#include <pthread.h>
//
//#ifdef __APPLE__
//#include <OpenGL/gl.h>
//#include <OpenGL/glu.h>
//#else
//#include <GL/glu.h>
//#include <GL/gl.h>
//#endif

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
	storm = NULL;

	pthread_mutex_init(&mutex, NULL);

	acum_ =  0;

  any_landing_ = false;
}

Airport::~Airport() {
	std::list<Flight*>::iterator it;
	for(it = flights.begin(); it!=flights.end(); ++it)
		delete(*it);
	flights.clear();
}


void
Airport::checkFinishStorm()
{
	float x, y, z, dist;

	x = storm->getPosition().get_x();
	y = storm->getPosition().get_y();

	dist = sqrt(x*x+y*y);

	if(sqrt(x*x+y*y)>(AIRPORT_DISTANCE_MAX*1.5))
	{
		delete storm;
		storm=NULL;
		std::cerr<<"Storm gone"<<std::endl;
	}

}

void
Airport::generate_storm()
{

	float angle, x, y, z, rad, height, bearing, speed;

	//Storm Pos
	angle = toRadians((float)(rand() % 360 - 180));
	x = fabs(AIRPORT_DISTANCE_MAX*1.5 * cos(angle)); //Only positive, for GyV3D!!!!!!!!!!!
	y = AIRPORT_DISTANCE_MAX*1.5 * sin(angle);
	z = ((float)rand() / RAND_MAX)*(STORM_MIN_ELEVATION-STORM_MIN_ELEVATION)+STORM_MIN_ELEVATION;

	//Storm height
	height = ((float)rand() / RAND_MAX)*(STORM_MAX_HEIGHT-STORM_MIN_HEIGHT)+STORM_MIN_HEIGHT;

	//Radius
	rad =  ((float)rand() / RAND_MAX)*(STORM_MAX_RAD-STORM_MIN_RAD)+STORM_MIN_RAD;

	//Bearing
	bearing = toRadians((float)(rand() % 360 - 180));

	//Speed
	speed = ((float)rand() / RAND_MAX)*(STORM_MAX_SPEED-STORM_MIN_SPEED)+STORM_MIN_SPEED;
	Position ipos(x, y, z);
	storm = new Storm(ipos, bearing, speed, rad, height);

}

void
Airport::generate_flight()
{


	std::cerr<<"Generate new flight";
	float angle, x, y, z;
	float bear, inc;
	char id[6];

	angle = toRadians((float)(rand() % 360 - 180));

	x = fabs(AIRPORT_DISTANCE_MAX * cos(angle)); //Only positive, for GyV3D!!!!!!!!!!!
	y = AIRPORT_DISTANCE_MAX * sin(angle);
	z = FLIGHT_HEIGHT + (float)(rand() % 2000);

	Position ipos(x, y, z);
	Position pos0(0.0, 0.0, 0.0);

	pos0.angles(ipos, bear, inc);

	sprintf(id, "IB%4.4d", sec++);
	std::cerr<<": ["<<id;
	Flight *aux;
	aux = new Flight(id, ipos, bear, 0.0, 200.0);
	flights.push_back(aux);

	if(flights.size() == 1)
		NextFocus();
	std::cerr<<"]"<<std::endl;
}

void
Airport::NextFocus(const Ice::Current&)
{
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

	//pthread_mutex_lock (&mutex);
	float delta_t;
	struct timeval tv;
	std::list<Flight*>::iterator it;
	long ta, tb;

	gettimeofday(&tv, NULL);

	ta = tv.tv_sec*1000000 + tv.tv_usec;
	tb = last_ts.tv_sec*1000000 + last_ts.tv_usec;

	delta_t =((float)(ta-tb)) /1000000.0;
	last_ts = tv;
	acum_ = acum_ + (delta_t * SimTimeMod)*1000000.0;
//En la siguiente funcion realizar un acumulador que se inicialice a 0 en cada cambio
//de nivel el cual es tal que acum =0, y va cambiando segun acum = acum +(differencial del tiempo * factor de aceleracion)
	if(acum_>INC_DIFF)
	{
		max_flights += INC_PEN;
		//std::cerr<<"Increase flights in "<<INC_PEN<<" to "<<max_flights<<std::endl;

	 	acum_ = 0;
	}

	if(!flights.empty())
	{
		for(it = flights.begin(); it!=flights.end(); ++it)
		{
			(*it)->update(SimTimeMod*delta_t);
			//std::cerr<<"["<<(*it)->getId()<<"] on the way"<<std::endl;
			//(*it)->draw();
		}

		pthread_mutex_lock (&mutex);
		checkLandings();
		checkCollisions();
		checkCrashes();
		pthread_mutex_unlock (&mutex);
	}

	pthread_mutex_lock (&mutex);

	if(storm==NULL)
	{
		generate_storm();
	}
	else
	{
		storm->update(SimTimeMod * delta_t);
		checkFlightsInStorm();
		checkFinishStorm();
	}
	pthread_mutex_unlock (&mutex);

	if(flights.size()<max_flights)
	{
		pthread_mutex_lock (&mutex);
		generate_flight();
		pthread_mutex_unlock (&mutex);
	}




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
	if(flights.empty()) return;

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
Airport::checkFlightsInStorm()
{
	if(flights.empty() || storm==NULL ) return;

	std::list<Flight*>::iterator it;

	for(it = flights.begin(); it != flights.end(); ++it)
	{
		bool in=false;
		float xf,yf, zf, xs, ys, zs;
		float dist;

		xf = (*it)->getPosition().get_x();
		yf = (*it)->getPosition().get_y();
		zf = (*it)->getPosition().get_z();
		xs = storm->getPosition().get_x();
		ys = storm->getPosition().get_y();
		zs = storm->getPosition().get_z();

		dist = sqrt((xf-xs)*(xf-xs)+(yf-ys)*(yf-ys));


		in = dist < storm->getRadious() && fabs(zs-zf)<storm->getHeight();
		(*it)->setInStorm(in);


		//std::cerr<<"["<<(*it)->getId()<<" = "<<dist<<" < "<<storm->getRadious()<<std::endl;


	}
}

void
Airport::checkCrashes()
{
	if(flights.empty()) return;

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
	if(flights.empty()) return;

	//pthread_mutex_lock (&mutex);
	std::list<Flight*>::iterator it;

	it = flights.begin();

	while(it != flights.end())
	{

		if((final_pos.distance((*it)->getPosition()) < LANDING_DIST) &&
				(toDegrees(normalizePi(fabs((*it)->getBearing() - toRadians(LANDING_BEAR))))<LANDING_BEAR_MAX_ERROR) &&
				((*it)->getSpeed()<LANDING_SPEED))
		{

			std::cerr<<"Flight "<<(*it)->getId()<<" landed"<<std::endl;
			points += (int)(*it)->getPoints();

			it = removeFlight((*it)->getId());

			std::cerr<<"*";

      any_landing_ = false;


			return;
		}else
			it++;
	}
	//pthread_mutex_unlock (&mutex);
}

void
Airport::UpdateSimTime(float inc)
{
	SimTimeMod = SimTimeMod + inc;

	if(SimTimeMod < 0) SimTimeMod = 0;
}

ATCDisplay::ATCDStorm
Airport::getStorm(const Ice::Current&)
{
	pthread_mutex_lock (&mutex);
	ATCDisplay::ATCDStorm ret;

	if(storm==NULL)
	{
		ret.valid =false;
		return ret;
	}else
		ret.valid =true;

	ATCDisplay::ATCDPosition p;
	p.x = storm->getPosition().get_x();
	p.y = storm->getPosition().get_y();
	p.z = storm->getPosition().get_z();

	ret.pos = p;
	ret.bearing = storm->getBearing();
	ret.height = storm->getHeight();
	ret.radious = storm->getRadious();
	ret.speed = storm->getSpeed();

	pthread_mutex_unlock (&mutex);
	return ret;
}

ATCDisplay::ATCDFlights
Airport::getFlights(const Ice::Current&)
{

	pthread_mutex_lock (&mutex);

	//std::cerr<<"["<<flights.size()<<": ";
	ATCDisplay::ATCDFlights ret;

	ret.clear();

	std::list<Flight*>::iterator it;

	for(it= flights.begin(); it!=flights.end(); ++it)
	{
		//std::cerr<<"A";

		std::list<Route>::iterator itr;
		ATCDisplay::ATCDRoute atcdr;
		atcdr.clear();

		for(itr= (*it)->getRoute()->begin(); itr!=(*it)->getRoute()->end(); ++itr)
		{
			//std::cerr<<"B";
			Route r= (*itr);

			ATCDisplay::ATCDPosition p;
			p.x = r.pos.get_x();
			p.y = r.pos.get_y();
			p.z = r.pos.get_z();

			atcdr.push_back(p);
		}

		//std::cerr<<"C";
		ATCDisplay::ATCDPosition fp;
		fp.x = (*it)->getPosition().get_x();
		fp.y = (*it)->getPosition().get_y();
		fp.z = (*it)->getPosition().get_z();

		//std::cerr<<"D";
		ATCDisplay::ATCDFlight f;
		f.speed = (*it)->getSpeed();
		f.focused = (*it)->getFocused();
		f.points = (*it)->getPoints();
		f.id =  (*it)->getId();
		f.bearing = (*it)->getBearing();
		f.collisionRadious = COLLISION_DISTANCE;
		f.flightRoute = atcdr;
		f.inclination = (*it)->getInclination();
		f.pos = fp;
		//std::cerr<<"E";
		ret.push_back(f);
	}

	//std::cerr<<"]"<<std::endl;
	pthread_mutex_unlock (&mutex);
	return ret;
}

ATCDisplay::ATCDAirport
Airport::getAirportInfo(const Ice::Current&)
{
	ATCDisplay::ATCDAirport ret;

	ATCDisplay::ATCDLandStrip lstrip0;

	ATCDisplay::ATCDPosition lsp;
	lsp.x = LANDING_POS_X;
	lsp.y = LANDING_POS_Y;
	lsp.z = LANDING_POS_Z;

	lstrip0.length = LANDING_STRIP_L;
	lstrip0.width = LANDING_STRIP_W;
	lstrip0.pos = lsp;
	lstrip0.orientation = 0.0;

	ret.airportLandstrips.push_back(lstrip0);
	ret.radious = AIRPORT_DISTANCE_MAX;

	return ret;
}

void
Airport::UpdateSimT(float inc, const Ice::Current&)
{
	UpdateSimTime(inc);
}

float
Airport::getSimT(const Ice::Current&)
{
	return SimTimeMod;
}

int
Airport::getMaxFlights(const Ice::Current&)
{
	return max_flights;
}

int
Airport::getPoints(const Ice::Current&)
{
	return points;
}


//void
//Airport::draw()
//{
//	glBegin(GL_QUADS);
//	glColor3f(0.2f,0.2f,0.2f);
//	glVertex3f( -AIRPORT_DISTANCE_MAX, AIRPORT_DISTANCE_MAX, 0.0f);
//	glVertex3f(  AIRPORT_DISTANCE_MAX, AIRPORT_DISTANCE_MAX, 0.0f);
//	glVertex3f(  AIRPORT_DISTANCE_MAX,-AIRPORT_DISTANCE_MAX, 0.0f);
//	glVertex3f( -AIRPORT_DISTANCE_MAX,-AIRPORT_DISTANCE_MAX, 0.0f);
//	glEnd();
//
//	glBegin(GL_QUADS);
//	glColor3f(1.0f,1.0f,0.0f);
//	glVertex3f(  0.0f, -(LANDING_STRIP_W/2.0), 0.01f);
//	glVertex3f(  0.0f,  LANDING_STRIP_W, 0.01f);
//	glVertex3f( -LANDING_STRIP_L, LANDING_STRIP_W, 0.01f);
//	glVertex3f( -LANDING_STRIP_L, -LANDING_STRIP_W, 0.01f);
//	glEnd();
//
//	glPushMatrix();
//	glTranslatef(1.0f, 0.0f, 25.0f);
//	GLUquadric *quadratic = gluNewQuadric();
//	gluQuadricNormals(quadratic, GLU_SMOOTH);
//	gluQuadricTexture(quadratic, GL_TRUE);
//	gluSphere( quadratic, 25.0f, 32, 32);
//	glPopMatrix();
//
//	TextDisplay *textDisplay = TextDisplay::getInstance();
//	char points_txt[255];
//	snprintf(points_txt, 255, "Level: %d\t\tPoints: %d ", max_flights, points);
//
//	textDisplay->displayText(points_txt, GUI::win_width-300, 25, GUI::win_width, GUI::win_height, WHITE, GLUT_BITMAP_TIMES_ROMAN_24);
//
//	snprintf(points_txt, 255, "Time speed: x%3.1f", SimTimeMod);
//	textDisplay->displayText(points_txt, 10, GUI::win_height-5, GUI::win_width, GUI::win_height, WHITE, GLUT_BITMAP_HELVETICA_12);
//	char help_txt[255];
//	strcpy(help_txt, "Press Mouse3 and move mouse to change orientation");
//	textDisplay->displayText(help_txt, GUI::win_width-310, GUI::win_height-5, GUI::win_width, GUI::win_height, WHITE, GLUT_BITMAP_HELVETICA_12);
//	strcpy(help_txt, "<Tab> Change flight info");
//	textDisplay->displayText(help_txt, GUI::win_width-160, GUI::win_height-200, GUI::win_width, GUI::win_height, WHITE, GLUT_BITMAP_HELVETICA_12);
//	strcpy(help_txt, "<w>Move camera forward");
//	textDisplay->displayText(help_txt, GUI::win_width-160, GUI::win_height-180, GUI::win_width,
//GUI::win_height, WHITE, GLUT_BITMAP_HELVETICA_12);
//	strcpy(help_txt, "<+>Speed up time");
//	textDisplay->displayText(help_txt, GUI::win_width-160, GUI::win_height-160, GUI::win_width,
//GUI::win_height, WHITE, GLUT_BITMAP_HELVETICA_12);
//	strcpy(help_txt, "<->Slow down time");
//	textDisplay->displayText(help_txt, GUI::win_width-160, GUI::win_height-140, GUI::win_width, GUI::win_height, WHITE, GLUT_BITMAP_HELVETICA_12);
//	strcpy(help_txt, "<s>Move camera backward");
//	textDisplay->displayText(help_txt, GUI::win_width-160, GUI::win_height-120, GUI::win_width, GUI::win_height, WHITE, GLUT_BITMAP_HELVETICA_12);
//	strcpy(help_txt, "<a>Move camera side left");
//	textDisplay->displayText(help_txt, GUI::win_width-160, GUI::win_height-100, GUI::win_width, GUI::win_height, WHITE, GLUT_BITMAP_HELVETICA_12);
//	strcpy(help_txt, "<d>Move camera side right");
//	textDisplay->displayText(help_txt, GUI::win_width-160, GUI::win_height-80, GUI::win_width, GUI::win_height, WHITE, GLUT_BITMAP_HELVETICA_12);
//	strcpy(help_txt, "<c>Reset camera position");
//	textDisplay->displayText(help_txt, GUI::win_width-160, GUI::win_height-60, GUI::win_width, GUI::win_height, WHITE, GLUT_BITMAP_HELVETICA_12);
//	strcpy(help_txt, "<f>Center camera in flight");
//	textDisplay->displayText(help_txt, GUI::win_width-160, GUI::win_height-40, GUI::win_width, GUI::win_height, WHITE, GLUT_BITMAP_HELVETICA_12);
//	strcpy(help_txt, "<esc>Finish");
//	textDisplay->displayText(help_txt, GUI::win_width-160, GUI::win_height-20, GUI::win_width, GUI::win_height, WHITE, GLUT_BITMAP_HELVETICA_12);
//
//}
