#pragma once
#include"expedia_flights_api.h"
#include"IFlight.h"
#include<vector>
#include"Flight.h"
#include"AirCanada.h"
#include"TurkishAirlines.h"

class FlightsManager {


	vector<Flight> flights;
	TurkishAirlinesOnlineAPI turkish_airlines_api;
public:
	const vector<Flight>& GetAvailableFlights(string from_, string from_date_,
		string to_, string to_date_, int adults_, int children_,
		int infants_);
	void ClearFlights();
	IFlight* MakeFlight(Flight flight_);

};
