#pragma once
#include<iostream>
class IReservation {
public:
	virtual double CalculateCost() const ;
	virtual IReservation* Clone() const ;
	virtual bool Reserve();
	virtual bool Cancel() ;
	virtual std::string ToString() const ;
	virtual ~IReservation();
};
