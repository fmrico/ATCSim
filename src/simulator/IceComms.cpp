/*
 * IceComms.h
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


#include "IceComms.h"

#define ICE_PORT 10000

Ice::CommunicatorPtr IceComms::ic;
Ice::ObjectAdapterPtr IceComms::adapter;

void* IceComms::iceServerThread(void *obj)
{
	std::stringstream endpoint;
	int icePort = ICE_PORT;

	std::string str = "atcsim";
	char* argv[2];
	argv[0] = new char[str.size() + 1];
	std::copy(str.begin(), str.end(), argv[0]);
	argv[0][str.size()] = '\0'; // don't forget the terminating 0

	str = "0";
	argv[1] = new char[str.size() + 1];
	std::copy(str.begin(), str.end(), argv[1]);
	argv[1][str.size()] = '\0'; // don't forget the terminating 0

	//char* argv[] = {name.c_str(), 0};
	int argc = 1;
	int *status = new int(0);

	try {

		endpoint << "default -p " << icePort;
		std::cout<<"Starting ICE ["<<endpoint.str()<<"]..."<<std::endl;

		Ice::InitializationData initData;
		initData.properties = Ice::createProperties(argc, argv);
		ic = Ice::initialize(argc, argv, initData);

		adapter = ic->createObjectAdapterWithEndpoints("ATCSimAdapter", endpoint.str());


		adapter->add(Airport::getInstance(), ic->stringToIdentity("AirportInterface"));

		adapter->activate();

		std::cout<<"Starting ICE ["<<adapter->getName()<<"]..."<<std::endl;
		ic->waitForShutdown();
		std::cout<<"ICE stopped"<<std::endl;

	} catch (const Ice::Exception& e) {
		std::cerr << e << std::endl;
		*status = 1;
	} catch (const char* msg) {
		std::cerr << msg << std::endl;
		*status = 1;
	}
	if (ic) {
		try {
			ic->destroy();
		} catch (const Ice::Exception& e) {
			std::cerr << e << std::endl;
			*status = 1;
		}
	}
	return status;
}

IceComms::IceComms()
{
	tIceServer = 0;
}

void
IceComms::startServer()
{
	pthread_create(&tIceServer, NULL, iceServerThread, NULL);
}
