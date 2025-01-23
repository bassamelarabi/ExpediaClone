#pragma once
#include "IFlight.h"
#include"expedia_flights_api.h"

class AirCanada : public IFlight {
	AirCanadaCustomerInfo customer;
	AirCanadaFlight flight;
public:
	AirCanada() {

	}
	AirCanada(string date_time_from, string date_time_to, double price);
	virtual bool Reserve() override;
	virtual bool Cancel() override;
	virtual bool ReserveFlight() const override;
	virtual bool CancelReserveFlight() const override;
	virtual double CalculateCost() const override;
	virtual void SetFromToInfo(string datetime_from, string from, string datetime_to, string to) override;
	virtual void SetPassengersInfo(int adults, int children, int infants);
	virtual string ToString() const override;
	virtual void PrintAPIInfo() const;
	virtual IFlight* Clone() const override;
	~AirCanada();
};

