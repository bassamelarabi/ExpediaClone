#pragma once
#include "User.h"
#include<iostream>
#include<vector>
#include"ItineraryReservation.h"
#include"Card.h"
#include"CreditCard.h"
#include"DebitCard.h"
#include<sstream>

class Customer : public User {
	vector<ItineraryReservation*> itineraries;
	vector<Card*> cards;
	Card* current_card{ nullptr };
	void LoadDatabase();
public:
	Customer();
	Customer(string username_, string password_) ;
	Customer(string username_, string name_, string password_, string email_, string country_);
	bool IsAdmin();
	bool AddItinerary(ItineraryReservation& itinerary);
	void Clear();
	void AddCard(const Card& card);
	vector<ItineraryReservation*>& GetItineraries();
	bool ChooseCard();
	vector<Card*>& GetCards();
	Card* GetCurrent_Card() const;
	void ListItineraries() const;
	string GetProfile();

	~Customer();

};


