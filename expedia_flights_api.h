#pragma once
/*
 * expedia_flights_api.h
 *
 *  Created on: Sep 18, 2020
 *      Author: moustafa
 */

#ifndef EXPEDIA_FLIGHTS_API_H_
#define EXPEDIA_FLIGHTS_API_H_
#include<iostream>
#include<vector>
using namespace std;


class AirCanadaCustomerInfo {

};

class AirCanadaFlight {
public:
	/*added by me*/
	string from;
	string to;
	int adults;
	int children;
	int infants;
	/*added by me*/
	double price;
	string date_time_from;
	string date_time_to;
	//added by my
	AirCanadaFlight() {}
	AirCanadaFlight(double price, string date_time_from, string date_time_to) : price(price), date_time_from(date_time_from), date_time_to(date_time_to) {

	}
	//added by me
};



class AirCanadaOnlineAPI {
public:
	static vector<AirCanadaFlight> GetFlights(string from, string from_date, string to, string to_date, int adults, int childern) {
		vector<AirCanadaFlight> flights;

		flights.push_back({ 200, "25-01-2022", "10-02-2022" });
		flights.push_back({ 250, "29-01-2022", "10-02-2022" });
		return flights;
	}
	static bool ReserveFlight(const AirCanadaFlight& flight, const AirCanadaCustomerInfo& info) {
		return true;
	}
	static bool CancelReserveFlight(const AirCanadaFlight& flight, const AirCanadaCustomerInfo& info) {
		return true;
	}
};

class TurkishFlight {
public:
	double cost;
	string datetime_from;
	string datetime_to;
	/*added by me*/
	string from;
	string to;
	int adults;
	int children;
	int infants;
	/*added by me*/
	TurkishFlight() {}
	TurkishFlight(double price, string date_time_from, string date_time_to) : cost(price), datetime_from(date_time_from), datetime_to(date_time_to) {

	}
};

class TurkishCustomerInfo {

};

class TurkishAirlinesOnlineAPI {
public:
	void SetFromToInfo(string datetime_from, string from, string datetime_to, string to) {
	}
	void SetPassengersInfo(int infants, int childern, int adults) {
	}
	vector<TurkishFlight> GetAvailableFlights(/*string from, string from_date,
		string to, string to_date, int adults, int children*/) const {
		vector<TurkishFlight> flights;

		flights.push_back({ 300, "10-01-2022", "10-02-2022" });
		flights.push_back({ 320, "12-01-2022", "10-02-2022" });
		return flights;
	}

	static bool ReserveFlight(const TurkishCustomerInfo& info, const TurkishFlight& flight) {
		return false;
	}
	static bool CancelReserveFlight(const TurkishCustomerInfo& info, const TurkishFlight& flight) {
		return false;
	}
};

#endif /* EXPEDIA_FLIGHTS_API_H_ */
