#include"expedia_hotels_api.h"
#include"expedia_flights_api.h"
#include"expedia_payments_api.h"

#include <iostream>
#include<vector>
#include<ctime>
#include<sstream>
#include"Expedia.h"
using namespace std;
int main() {
	Expedia ex;
	ex.Run();
}


/// Payments handling////////////


















///Itineraries ///////////////////


















//Managers




























///////////////APIs///////////
//class ItineraryAPI {
//public:
//	virtual const vector<Reservation*> GetAvailable() const = 0;
//};
//
//class FlightsAPI : public ItineraryAPI {
//public:
//	const vector<Reservation*> GetAvailable() const {
//		string from, from_date, to, to_date;
//		int adults, children;
//		cout << "Enter From: "; cin >> from;
//		cout << "\nEnter From Date (dd-mm-yy): "; cin >> from_date;
//		cout << "\nEnter To: "; cin >> to;
//		cout << "\nEnter To Date: "; cin >> to_date;
//		cout << "\nEnter # of adults children (5-16) and infants: "; cin >> adults >> children;
//		cout << "\n";
//		//inversion of control ////
//		return GetAvailableFlights(from, from_date, to, to_date, adults, children);
//	}
//	virtual const vector<Reservation*> GetAvailableFlights(string from, string from_date,
//		string to, string to_date, int adults, int children) const = 0;
//
//
//	/////////////////
//
//
//};
//
//class HotelsAPI : public ItineraryAPI {
//public:
//	const vector<Reservation*> GetAvailable() const {
//		string country, city, from_date, to_date;
//		int needed_rooms, adults, children;
//		cout << "\nEnter From Date (dd-mm-yy): "; cin >> from_date;
//		cout << "\nEnter To Date: "; cin >> to_date;
//		cout << "Enter Country: "; cin >> country;
//		cout << "Enter City: "; cin >> city;
//		cout << "\nEnter # of adults and children: "; cin >> adults >> children;
//		cout << "\n";
//		//inversion of control///
//		return GetAvailableHotels(country, city, from_date, to_date, adults, children, needed_rooms);
//	}
//	virtual const vector<Reservation*> GetAvailableHotels(string country, string city, string from_date,
//		string to_date, int adults, int children, int needed_rooms) const = 0;
//
//
//};
//
//class AirCanadaAPI : public FlightsAPI {
//public:
//	virtual const vector<Reservation*> GetAvailableFlights(string from, string from_date,
//		string to, string to_date, int adults, int children) const {
//		vector<AirCanadaFlight> flights = AirCanadaOnlineAPI::GetFlights(from, from_date, to, to_date,
//			adults, children);
//		vector<Reservation*> reservations;
//		for (auto flight : flights) {
//			Reservation* reservation = new AirCanada(flight.date_time_from, flight.date_time_to, flight.price);
//			reservations.push_back(reservation->Clone());
//		}
//		return reservations;
//	}
//
//	//////////////
//};
//
//class TurkishAirlinesAPI : public FlightsAPI {
//	TurkishAirlinesOnlineAPI api;
//public:
//	virtual const vector<Reservation*> GetAvailableFlights(string from, string from_date,
//		string to, string to_date, int adults, int children) const {
//		vector<TurkishFlight> flights = api.GetAvailableFlights(from, from_date, to, to_date,
//			adults, children);
//		vector<Reservation*> reservations;
//		for (auto flight : flights) {
//			Reservation* reservation = new TurkishAirlines(flight.datetime_from, flight.datetime_to, flight.cost);
//			reservations.push_back(reservation->Clone());
//		}
//		return reservations;
//
//	}
//};
//
//
//class HiltonAPI : public HotelsAPI {
//public:
//	virtual const vector<Reservation*> GetAvailableHotels(string country, string city,
//		string from_date, string to_date, int adults, int children, int needed_rooms) const {
//		vector<HiltonRoom> rooms = HiltonHotelAPI::SearchRooms(country, city, from_date, to_date, adults, children, needed_rooms);
//		vector<Reservation*> reservations;
//		for (auto room : rooms) {
//			Reservation* reservation = new Hilton(room.room_type, room.available, room.price_per_night, room.date_from, room.date_to);
//			reservations.push_back(reservation->Clone());
//		}
//		return reservations;
//
//	}
//};
//
//class MarriottAPI : public HotelsAPI {
//public:
//	virtual const vector<Reservation*> GetAvailableHotels(string country, string city,
//		string from_date, string to_date, int adults, int children, int needed_rooms) const {
//		vector<MarriottFoundRoom> rooms = MarriottHotelAPI::FindRooms(from_date, to_date, country, city, needed_rooms, adults, children);
//		vector<Reservation*> reservations;
//		for (auto room : rooms) {
//			Reservation* reservation = new Marriott(room.room_type, room.available, room.price_per_night, room.date_from, room.date_to);
//			reservations.push_back(reservation->Clone());
//		}
//		return reservations;
//
//	}
//};