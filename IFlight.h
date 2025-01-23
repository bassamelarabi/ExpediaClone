#pragma once
#include "IReservation.h"
using namespace std;
class IFlight : public IReservation {
public:
	virtual bool Reserve() ;
	virtual bool Cancel() ;
	virtual bool ReserveFlight() const ;
	virtual bool CancelReserveFlight() const ;
	virtual double CalculateCost() const ;
	virtual IReservation* Clone() const ;
	virtual void SetFromToInfo(string datetime_from, string from, string datetime_to, string to) ;
	virtual void SetPassengersInfo(int adults, int children, int infants) ;
	virtual void PrintAPIInfo() const ;
	virtual string ToString() const ;
	virtual ~IFlight();
};

