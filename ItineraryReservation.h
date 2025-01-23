#pragma once
#include"IReservation.h"
#include<vector>
#include<iostream>
using namespace std;

class ItineraryReservation : public IReservation {
	vector<IReservation*> reservations;
public:
	ItineraryReservation() {

	}
	ItineraryReservation(const ItineraryReservation& another);
	const int GetSize() const;


	virtual bool Reserve();
	virtual bool Cancel();
	virtual bool AddReservation(IReservation& reservation);
	virtual bool CancelItinerary();
	virtual double CalculateCost() const override;
	const vector<IReservation*>& GetReservations() const;
	void Clear();

	virtual string ToString() const override;

	virtual ItineraryReservation* Clone() const override;
	~ItineraryReservation();
	void PrintItinerary() const;
};

