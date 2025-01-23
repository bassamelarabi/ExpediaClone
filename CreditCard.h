#pragma once
#include"Card.h"
class CreditCard : public Card {
public:
	CreditCard();
	CreditCard(string name_, int card_number_);
	void PrintCardInfo() const override;
	string ToString() const override;
	CreditCard* Clone() const override;
	~CreditCard() override;
};

