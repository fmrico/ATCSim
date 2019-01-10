/*
 * GUI.h
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
 */

#ifndef SRC_CPPGUI_GUI_H_
#define SRC_CPPGUI_GUI_H_

#define KEY_ESCAPE 27

#include "TextDisplay.h"
#include "colours.h"
#include "ATCDisplay.h"

#include <vector>

class GUI {
 public:
    GUI(int argc, char *argv[]);
    virtual ~GUI();

    void init(ATCDisplay::AirportInterfacePrx as);
    void run();

    static void DrawFlight(ATCDisplay::ATCDFlight flight);
    static void DrawStorm(ATCDisplay::ATCDStorm storm);
    static void DrawAirport();

    static ATCDisplay::ATCDFlight getFlightFocused();
    static const int win_width;
    static const int win_height;
    static const int wpt_size;

 private:
    static const float field_of_view_angle;
    static const float x_near;
    static const float x_far;

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

    static ATCDisplay::AirportInterfacePrx airportsim;
    static ATCDisplay::ATCDAirport airportinfo;
};
#endif  // SRC_CPPGUI_GUI_H_
