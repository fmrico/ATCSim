/*
 * TextDisplay.h
 *
 *  Created on: 29/07/2014
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

#include <stdio.h>
#include <string.h>

#ifdef __APPLE__
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <glut.h>
#else
#include <GL/glu.h>
#include <GL/gl.h>
#include <GL/glut.h>
#endif

#include "Singleton.h"

#ifndef TEXTDISPLAY_H_
#define TEXTDISPLAY_H_

class TextDisplay: public Singleton<TextDisplay> {
public:
private:
	int frame;
	int time;
	int timebase;
	char msj[255];
	char msj1[255];
	std::string projectName;
	float fps;

public:
	TextDisplay();
	~TextDisplay(void);

	void calculateFramesPerSecond(void);
	void displayText(char *text, float x, float y, int width, int height, float R = 1.0f, float G = 1.0f, float B = 0.0f, void* font = GLUT_BITMAP_HELVETICA_18);
	void displayFPS(float x, float y, int width, int height, float R = 1.0f, float G = 1.0f, float B = 0.0f);

};

#endif /* TEXTDISPLAY_H_ */
