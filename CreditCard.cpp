#include "CreditCard.h"
#include<sstream>
class CreditCard : public Card {
public:
	CreditCard() : Card() {
	}
	CreditCard(string name_, int card_number_) : Card(name_, card_number_) {

	}
	void PrintCardInfo() const override {
		cout << "[Credit Card]: Owner: " << name << " Card number: " << card_number << "\n";
	}
	string ToString() const override {
		ostringstream oss;
		oss << "[Credit Card]: Owner: " << name << " Card number: " << card_number << "\n";
		return oss.str();
	}
	CreditCard* Clone() const override {
		return new CreditCard(*this);
	}
	~CreditCard() override {}
};
