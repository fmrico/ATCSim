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

#ifndef ICECOMMS_H
#define ICECOMMS_H

#include <Ice/Ice.h>
#include "Singleton.h"
#include "Airport.h"

class IceComms: public Singleton<IceComms>
{
public:

	IceComms();

	void startServer();

	static const Ice::CommunicatorPtr& getIC() {return ic;};
	static const Ice::ObjectAdapterPtr& getAdapter() {return adapter;};

private:
	pthread_t tIceServer;
	static void* iceServerThread(void *obj);
	static Ice::CommunicatorPtr ic;
	static Ice::ObjectAdapterPtr adapter;
};

#endif
