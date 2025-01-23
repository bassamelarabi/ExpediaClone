#include "PayPalPayment.h"

class PayPalPayment : public IPayment {
	PayPalCreditCard card;
	PayPalOnlinePaymentAPI paypal;
public:
	void SetCardInfo(string id, string expiry_date, int ccv = 0) override {
		card.id = id;
		card.ccv = ccv;
		card.expiry_date = expiry_date;
	}
	void SetUserInfo(string name, string address = "") override {
		card.name = name;
		card.address = address;
	}
	bool WithDrawMoney(double amount) override {
		paypal.SetCardInfo(&card);
		return paypal.MakePayment(amount);
	}
	~PayPalPayment() {}
};
