module ATCDisplay {

	struct ATCDPosition{
		float x;
		float y;
		float z;
	};

	struct ATCDWaypoint{
		string name;
		float lat;
		float lon;
	};

	["java:type:java.util.LinkedList<ATCDWaypoint>"]
	sequence<ATCDWaypoint> ATCDWaypoints;

	struct ATCDRoute{
		ATCDPosition pos;
		ATCDWaypoint wpt;
		float speed;
		float alt;
	};

	["java:type:java.util.LinkedList<ATCDRoute>"]
	sequence<ATCDRoute> ATCDLegs;

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
		ATCDLegs flightRoute;
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
		idempotent ATCDWaypoints getWaypoints();
		idempotent ATCDStorm getStorm();
		idempotent ATCDAirport getAirportInfo();
		void UpdateSimT(float inc);
		void NextFocus();
		idempotent float getSimT();
		idempotent int getMaxFlights();
		idempotent int getPoints();
	};

};
