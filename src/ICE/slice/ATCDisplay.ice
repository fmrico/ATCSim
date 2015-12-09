module ATCDisplay {

	struct ATCDPosition{
		float x;
		float y;
		float z;
	};

	["java:type:java.util.LinkedList<ATCDPosition>"]
	sequence<ATCDPosition> ATCDRoute;

	struct ATCDStorm{
		bool valid;
		float speed;
		ATCDPosition pos;
		float bearing;
		float radious;
		float height; 
	};
	
	struct ATCDFlight{
		float points;
		float speed;
		bool focused;	
		string id;
		ATCDPosition pos;
		float inclination;
		float bearing;
		float collisionRadious; 
		ATCDRoute flightRoute;
	};
	
	["java:type:java.util.LinkedList<ATCDFlight>"]
	sequence<ATCDFlight> ATCDFlights;

	struct ATCDLandStrip{
		ATCDPosition pos;
		float width;
		float length;
		float orientation;
	};
	
	["java:type:java.util.LinkedList<ATCDLandStrip>"]
	sequence<ATCDLandStrip> ATCDLandStrips;
	
	struct ATCDAirport
	{
		ATCDLandStrips airportLandstrips;
		float radious;
	};
		
	interface AirportInterface {
		idempotent ATCDFlights getFlights();
		idempotent ATCDStorm getStorm();
		idempotent ATCDAirport getAirportInfo();
		void UpdateSimT(float inc);
		void NextFocus();
		idempotent float getSimT();
		idempotent int getMaxFlights();
		idempotent int getPoints();
	};
		
};