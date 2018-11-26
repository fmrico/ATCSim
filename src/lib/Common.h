/*
 * Common.h
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



#ifndef __Math_Common_h__
#define __Math_Common_h__

#include <cmath>
#include <cstdlib>
#include <string>
#include <stdlib.h>

#define COLLISION_DISTANCE 1000.0f
#define CRASH_Z 20.0f
#define CRASH_INC 25.0f
#define CRASH_SPEED_MAX 265.0f   // Approx. 950 km/h
#define CRASH_SPEED 10.0f
#define INIT_MAX_FLIGHTS 1

#define MAX_FLIFGT_W	0.2f //12 grados/sec
#define DIST_POINT 	200.0 //15 grados/sec
#define MAX_ACELERATION 	50.0 //50 m/sec2


#define AIRPORT_DISTANCE_MAX 	20000.0f
#define FLIGHT_HEIGHT	 		2000.0f
#define LANDING_STRIP_L	 		750.0f
#define LANDING_STRIP_W	 		80.0f

#define STORM_MAX_RAD				5000.0f
#define STORM_MIN_RAD				2000.0f
#define STORM_MAX_HEIGHT				2000.0f
#define STORM_MIN_HEIGHT				500.0f
#define STORM_MAX_ELEVATION				2000.0f
#define STORM_MIN_ELEVATION				500.0f
#define STORM_MAX_SPEED				500.0f
#define STORM_MIN_SPEED				30.0f


//Conditions for landing

#define LANDING_POS_X		0.0f
#define LANDING_POS_Y		0.0f
#define LANDING_POS_Z		25.0f


#define LANDING_SPEED 			20.0f
#define LANDING_BEAR  			-180.0f
#define LANDING_BEAR_MAX_ERROR	20.0f
#define LANDING_DIST  			50.0f

#define INIT_FLIGHT_POINTS  200
#define INIT_POINTS 0
#define LANDING_POINTS 	 	(10)
#define COLLISION_POINTS 	(-50)
#define CRASH_HEIGHT_POINTS	(-25)
#define CRASH_INC_POINTS	(-25)
#define CRASH_SPEED_POINTS 	(-25)

#define INC_DIFF		30000000//30 sec
#define INC_PEN			1 	 	//fligts/inc

#define INC_SIMTIME			0.1

/**
* defines the sign of a (-1, 0 or 1)
*/
#ifndef sgn
#define sgn(a)   ( (a) < 0 ? -1 : ((a)==0) ? 0 : 1 )
#endif

/**
* defines the sign of a (-1 or 1)
*/
#ifndef sign
#define sign(a)   ( (a) < 0 ? -1 : 1 )
#endif

/**
* defines the square of a value
*/
#ifndef sqr
#define sqr(a) ( (a) * (a) )
#endif

inline double sec(const double a){return 1/cos(a);}

inline double cosec(const double a){return 1/sin(a);}

/** @name constants for some often used angles */
///@{
/** constant for a half circle*/
const double pi = 3.1415926535897932384626433832795;
/** constant for a full circle*/
const double pi2 = 2.0*3.1415926535897932384626433832795;
/** constant for three quater circle*/
const double pi3_2 = 1.5*3.1415926535897932384626433832795;
/** constant for a quarter circle*/
const double pi_2 = 0.5*3.1415926535897932384626433832795;
/** constant for a 1 degree*/
const double pi_180 = 3.1415926535897932384626433832795/180;
/** constant for a 1/8 circle*/
const double pi_4 = 3.1415926535897932384626433832795*0.25;
/** constant for a 3/8 circle*/
const double pi3_4 = 3.1415926535897932384626433832795*0.75;
/** constant for an expression used by the gaussian function*/
const double sqrt2pi = sqrt(2.0*pi);
///@}


/**
 * Converts angle from rad to degrees.
 * \param angle code in rad
 * \return angle coded in degrees
 */
inline double toDegrees(double angle){return angle * 180.0 / pi;}

/** Converts angle from degrees to rad.
 * \param degrees angle coded in degrees
 * \return angle coded in rad
 */
inline double fromDegrees(double degrees){return degrees * pi_180;}

/** Converts angle from degrees to rad.
 * \param degrees angle coded in degrees
 * \return angle coded in rad
 */
inline double toRadians(double degrees){return degrees * pi_180;}

/**
* reduce angle to [-pi..+pi[
* \param data angle coded in rad
* \return normalized angle coded in rad
*/
inline double normalizePi(double data)
{
  if (data < pi && data >= -pi) return data;
  double ndata = data - ((int )(data / pi2))*pi2;
  while (ndata >= pi)
  {
    ndata -= pi2;
  }
  while (ndata < -pi)
  {
    ndata += pi2;
  }
  return ndata;
}

/**
* The function returns a random number in the range of [0..1].
* @return The random number.
*/
inline double randomDouble() {return double(rand()) / RAND_MAX;}

/**
* The function returns a random integer number in the range of [0..n-1].
* @param n the number of possible return values (0 ... n-1)
* @return The random number.
*/
inline int random(int n) {return (int)(randomDouble()*n*0.999999);}

/** constant, cast before execution*/
const double RAND_MAX_DOUBLE = static_cast<double>(RAND_MAX);

/**
* The function returns a random integer number in the range of [0..n].
* @param n the number of possible return values (0 ... n)
* @return The random number.
*/
inline int randomFast(int n)
{
  return static_cast<int>((rand()*n) / RAND_MAX_DOUBLE);
}

/**
* Round to the next integer
* @param d A number
* @return The number as integer
*/
inline int roundNumberToInt(double d)
{
  return static_cast<int>(floor(d+0.5));
}

/**
* Round to the next integer but keep type
* @param d A number
* @return The number
*/
inline double roundNumber(double d)
{
  return floor(d+0.5);
}

inline float normalAng(float x, float mu, float st)
{
	float diff = normalizePi(x-mu);
	float d1 = st*sqrt(2.0*M_PI);
	float d2 = 2*st*st;

	if(d1==0.0) d1 = 0.00001;
	if(d2==0.0) d2 = 0.00001;

	return (1.0/d1)*exp(-(diff*diff)/d2);
}
inline float normalDist(float x, float mu, float st)
{
	float diff = x-mu;
	float d1 = st*sqrt(2.0*M_PI);
	float d2 = 2*st*st;

	if(d1==0.0) d1 = 0.00001;
	if(d2==0.0) d2 = 0.00001;

	return (1.0/d1)*exp(-(diff*diff)/d2);
}

#endif // __Math_Common_h__
