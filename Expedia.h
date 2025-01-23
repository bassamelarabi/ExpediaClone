#pragma once

#include"CustomersManager.h"
#include"IPayment.h"
#include"CustomersManager.h"
#include"FlightsManager.h"
#include"HotelsManager.h"
#include"PaymentFactory.h"
#include"Hilton.h";

#include"Utilities.h"


class Expedia {
	CustomersManager* customers_manager;
	IPayment* payment;
	FlightsManager* flights_manager;
	HotelsManager* hotels_manager;
	void ViewProfile();
	void MakeItinerary();
	IReservation* AddHotel();
	IReservation* AddFilght();
	void LoadDatabase();

	const vector<Flight>& GetAvailableFlights(string from_, string from_date_,
		string to_, string to_date_, int adults_, int children_, int infants_);
	bool PayReservation(const IReservation& reservation_);

	void AccessSystem();

	string GetProfile();

	void ListItineraries();

	void FreeLoadedData();

public:
	Expedia();


	void Run();

	~Expedia();
};

