#include "FlightsManager.h"
#include"HotelRoom.h"

class FlightsManager {


	vector<Flight> flights;
	TurkishAirlinesOnlineAPI turkish_airlines_api;
public:
	const vector<Flight>& GetAvailableFlights(string from_, string from_date_,
		string to_, string to_date_, int adults_, int children_,
		int infants_) {
		ClearFlights();
		Flight flight;
		//turkish airlines flights
		for (auto turkish_flight : turkish_airlines_api.GetAvailableFlights()) {
			flight.price = turkish_flight.cost;
			flight.date_time_from = turkish_flight.datetime_from;
			flight.date_time_to = turkish_flight.datetime_to;
			flight.from = from_;
			flight.to = to_;
			flight.children = children_;
			flight.adults = adults_;
			flight.infants = infants_;

			flight.provider = "TurkishAirlines";
			flights.push_back(flight);

		}
		//air canada flights

		for (auto air_canada_flight : AirCanadaOnlineAPI::GetFlights(from_, from_date_, to_, to_date_, adults_, children_)) {
			flight.price = air_canada_flight.price;
			flight.date_time_from = air_canada_flight.date_time_from;
			flight.date_time_to = air_canada_flight.date_time_to;
			flight.from = from_;
			flight.to = to_;
			flight.children = children_;
			flight.adults = adults_;
			flight.infants = infants_;

			flight.provider = "AirCanada";
			flights.push_back(flight);

		}
		return flights;

	}
	void ClearFlights() {
		flights.clear();
	}
	IFlight* MakeFlight(Flight flight_) {
		IFlight* flight;
		if (flight_.provider == "AirCanada")
			flight = new AirCanada();
		else flight = new TurkishAirlines();
		flight->SetFromToInfo(flight_.date_time_from, flight_.from, flight_.date_time_to, flight_.to);
		flight->SetPassengersInfo(flight_.adults, flight_.children, flight_.infants);
		return flight;
		ClearFlights();
	}

};