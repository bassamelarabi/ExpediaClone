#pragma once
#include<iostream>
using namespace std;
class Card {
protected:
	string name;
	string address;
	double credit;
	int ccv;
	string id;
	int card_number;
	string expiry_date;
public:
	Card();
	Card(string name_, int card_number_) ;
	void SetCardInfo(string name_, string address_, string id_, int ccv_, int card_number_, int expiry_date_, double credit_);
	const string GetName() const;
		
	const string GetAddress() const;
	const string GetId() const;
	const string GetExpiryDate() const;
	const int GetCCV() const;
	virtual void PrintCardInfo() const = 0;
	virtual string ToString() const = 0;
	virtual Card* Clone() const = 0;
	virtual ~Card() = 0;
};

