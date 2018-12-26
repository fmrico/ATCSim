/*
 * cppgui.cpp
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

#include "GUI.h"

/**
 *
 * Created: Francisco Martín (fmrico@gmail.com) 26/12/2013
 *
**/


#include <Ice/Ice.h>
#include "ATCDisplay.h"
#include <time.h>
#include <string>

int main(int argc, char* argv[]) {
    int status = 0;
    int count = 0;
    Ice::CommunicatorPtr ic;
    GUI gui(argc, argv);

    try {
        ic = Ice::initialize(argc, argv);
        Ice::ObjectPrx base = ic->stringToProxy("AirportInterface:default -p 10000");

        if (!base)
                  throw "Invalid base";

        ATCDisplay::AirportInterfacePrx airportsim = ATCDisplay::AirportInterfacePrx::checkedCast(base);

        if (!airportsim)
            throw "Invalid proxy";

        int milisec = 100;  // length of time to sleep, in miliseconds
        struct timespec req;
        req.tv_sec = 0;
        req.tv_nsec = milisec * 1000000L;

        // while(1)
        // std::cout<<airportsim->getPoints()<<std::endl;

        gui.init(airportsim);
        gui.run();
    } catch (const Ice::Exception& ex) {
        std::cerr << ex << std::endl;
        status = 1;
    } catch (const char* msg) {
        std::cerr << msg << std::endl;
        status = 1;
    }
    if (ic)
        ic->destroy();
    return status;
}
