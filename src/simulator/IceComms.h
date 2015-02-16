/**
 *
 * Created: Francisco Martín (fmrico@gmail.com) 26/12/2013
 *
**/


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
