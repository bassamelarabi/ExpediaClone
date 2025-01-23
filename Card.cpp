#include "Card.h"
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
	Card() {
	}
	Card(string name_, int card_number_) : name(name_), card_number(card_number_) {

	}
	void SetCardInfo(string name_, string address_, string id_, int ccv_, int card_number_, int expiry_date_, double credit_) {
		name = name_;
		address = address_;
		id = id_;
		ccv = ccv_;
		card_number = card_number_;
		expiry_date = expiry_date_;
		credit = credit_;
	}
	const string GetName() const {
		return name;
	}
	const string GetAddress() const {
		return address;
	}
	const string GetId() const {
		return id;
	}
	const string GetExpiryDate() const {
		return expiry_date;
	}
	const int GetCCV() const {
		return ccv;
	}
	virtual void PrintCardInfo() const = 0;
	virtual string ToString() const = 0;
	virtual Card* Clone() const = 0;
	virtual ~Card() = 0;
};
