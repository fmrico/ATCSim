/*
 * ATCSim.cpp
 *
 *  Created on: 16/07/2014
 *      Author: paco
 */

#include <stdio.h>
#include "GUI.h"

int main(int argc, char **argv)
{
	GUI gui(argc, argv);

	gui.init();
	gui.run();

	return 0;

}

