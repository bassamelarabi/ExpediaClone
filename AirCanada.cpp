#include<sstream>
#include"AirCanada.h"


class AirCanada : public IFlight {
	AirCanadaCustomerInfo customer;
	AirCanadaFlight flight;
public:
	AirCanada() {

	}
	AirCanada(string date_time_from, string date_time_to, double price) {
		flight.date_time_from = date_time_from;
		flight.date_time_to = date_time_to;
		flight.price = price;
	}
	virtual bool Reserve() override {
		return ReserveFlight();
	}
	virtual bool Cancel() override {
		return CancelReserveFlight();
	}
	virtual bool ReserveFlight() const override {
		return AirCanadaOnlineAPI::ReserveFlight(flight, customer);
	}
	virtual bool CancelReserveFlight() const override {
		return AirCanadaOnlineAPI::CancelReserveFlight(flight, customer);
	}
	virtual double CalculateCost() const override {
		return flight.price;
	}
	virtual void SetFromToInfo(string datetime_from, string from, string datetime_to, string to) override {
		flight.date_time_from = datetime_from;
		flight.date_time_to = datetime_to;
	}
	virtual void SetPassengersInfo(int adults, int children, int infants) {
		flight.adults = adults;
		flight.children = children;
		flight.infants = infants;
	}
	virtual string ToString() const override {
		ostringstream oss;
		oss << "Airline reservation with reservation: AirCanada Airlines From: " << flight.from;
		oss << " on " << flight.date_time_from << "\t to " << flight.to;
		oss << " on " << flight.date_time_to << "\n";
		oss << "\tAdults: " << flight.adults << " children:" << flight.children;
		oss << " infants: " << flight.infants << " \n \t Total Cost: " << flight.price;
		return oss.str();
	}
	virtual void PrintAPIInfo() const {
		cout << "Airline: AirCanada Airlines Cost: " << CalculateCost();
		cout << " Departure Date " << flight.date_time_from;
		cout << " Arrival date " << flight.date_time_to;
	}
	virtual IFlight* Clone() const override {
		return new AirCanada(*this);
	}
	~AirCanada() {}
};