#include "TurkishAirlines.h"

class TurkishAirlines : public IFlight {
	TurkishCustomerInfo customer;
	TurkishFlight flight;
public:
	TurkishAirlines() {

	}
	TurkishAirlines(string date_time_from, string date_time_to, double price) {
		flight.datetime_from = date_time_from;
		flight.datetime_to = date_time_to;
		flight.cost = price;
	}
	virtual bool Reserve()  override {
		return ReserveFlight();
	}
	virtual bool Cancel() override {
		return CancelReserveFlight();
	}
	virtual bool ReserveFlight() const override {
		return TurkishAirlinesOnlineAPI::ReserveFlight(customer, flight);
	}
	virtual bool CancelReserveFlight() const override {
		return TurkishAirlinesOnlineAPI::CancelReserveFlight(customer, flight);
	}
	virtual double CalculateCost() const override {
		return flight.cost;
	}
	virtual void SetFromToInfo(string datetime_from, string from, string datetime_to, string to) override {
		flight.datetime_from = datetime_from;
		flight.datetime_to = datetime_to;
	}
	virtual void SetPassengersInfo(int adults, int children, int infants) {
		flight.adults = adults;
		flight.children = children;
		flight.infants = infants;
	}
	virtual string ToString() const override {
		ostringstream oss;
		oss << "Airline reservation with reservation: Turkish Flight Airlines From: " << flight.from;
		oss << " on " << flight.datetime_from << "\t to " << flight.to;
		oss << " on " << flight.datetime_to << "\n";
		oss << "\tAdults: " << flight.adults << " children:" << flight.children;
		oss << " infants: " << flight.infants << " \n \t Total Cost: " << flight.cost;
		return oss.str();
	}
	virtual void PrintAPIInfo() const {
		cout << "Airline: Turkish Airlines Cost: " << CalculateCost();
		cout << " Departure Date " << flight.datetime_from;
		cout << " Arrival date " << flight.datetime_to;
	}
	virtual IFlight* Clone() const override {
		return new TurkishAirlines(*this);
	}
	~TurkishAirlines() {}
};

