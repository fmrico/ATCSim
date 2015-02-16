/*
 * ATCSim.cpp
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

#include <stdio.h>
#include "Airport.h"
#include "AirController.h"
#include "IceComms.h"

int main(int argc, char **argv)
{
	IceComms::getInstance()->startServer();

	while(true)
	{
		Airport::getInstance()->step();
		AirController::getInstance()->doWork();
	}
	return 0;

}

