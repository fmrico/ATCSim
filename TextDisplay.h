/*
 * TextDisplay.h
 *
 *  Created on: 29/07/2014
 *      Author: paco
 */

#include <stdio.h>
#include <string.h>
#include <GL/glut.h>

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
