#pragma once
#include "IPayment.h"
#include"expedia_payments_api.h"
class PayPalPayment :
    public IPayment
{
		PayPalCreditCard card;
		PayPalOnlinePaymentAPI paypal;
	public:
		void SetCardInfo(std::string id, std::string expiry_date, int ccv = 0) override ;
		void SetUserInfo(std::string name, std::string address = "") override;
		bool WithDrawMoney(double amount) override;
		~PayPalPayment();
};

