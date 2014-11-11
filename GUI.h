/*
 * GUI.h
 *
 *  Created on: 16/07/2014
 *      Author: paco
 */

#ifndef GUI_H_
#define GUI_H_

#define KEY_ESCAPE 27

#include "TextDisplay.h"
#include "colours.h"

class GUI {
public:
	GUI(int argc, char *argv[]);
	virtual ~GUI();


	void init();
	void run();

	static const int win_width  = 1024;
	static const int win_height = 768;

private:

	static const float field_of_view_angle = 60;
	static const float x_near = 1.0f;
	static const float x_far = 40000.0f;

	static void render();
	static void step();

	static void keyboard(unsigned char key, int mousePositionX, int mousePositionY);
	static void processMouseFunc(int button, int state, int x, int y);
	static void processMouseMotion(int x, int y);
	static int mousebutton;
	static int mousestate;
	static int mousex, mousey;
	static float cam_alpha, cam_beta;
	static float cam_x, cam_y, cam_z;



};

#endif /* GUI_H_ */
