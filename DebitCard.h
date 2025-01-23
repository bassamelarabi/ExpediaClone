#pragma once
#include "Card.h"
class DebitCard : public Card {
public:
	DebitCard() ;
	DebitCard(string name_, int card_number_) ;
	string ToString() const override;
	void PrintCardInfo() const override;
	DebitCard* Clone()const override;
	~DebitCard();
};
