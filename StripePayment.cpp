#include "StripePayment.h"

class StripePayment : public IPayment {
	StripeUserInfo user_info;
	StripeCardInfo card_info;
public:
	void SetCardInfo(string id, string expiry_date, int ccv) override {
		card_info.id = id;
		card_info.expiry_date = expiry_date;
	}
	void SetUserInfo(string name, string address) override {
		user_info.name = name;
		user_info.address = address;
	}
	bool WithDrawMoney(double amount) override {
		return StripePaymentAPI::WithDrawMoney(user_info, card_info, amount);
	}
	~StripePayment() {}
};