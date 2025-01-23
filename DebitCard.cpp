#include "DebitCard.h"
#include"Card.h"
#include<sstream>


class DebitCard : public Card {
public:
	DebitCard() : Card() {
	}
	DebitCard(string name_, int card_number_) : Card(name_, card_number_) {

	}
	string ToString() const override {
		ostringstream oss;
		oss << "[Debit Card]: Owner: " << name << " Card number: " << card_number;
		return oss.str();
	}
	void PrintCardInfo() const override {
		cout << "[Debit Card]: Owner: " << name << " Card number: " << card_number;
	}
	DebitCard* Clone()const override {
		return new DebitCard(*this);
	}
	~DebitCard() {}
};