#pragma once
#include "IPayment.h"
#include "expedia_payments_api.h"

class StripePayment :
    public IPayment
{

		StripeUserInfo user_info;
		StripeCardInfo card_info;

	public:
		void SetCardInfo(std::string id, std::string expiry_date, int ccv) override;
		void SetUserInfo(std::string name, std::string address) override;
		bool WithDrawMoney(double amount) override;

		~StripePayment() {}
};

