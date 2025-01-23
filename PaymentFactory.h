#pragma once
#include"IPayment.h"
class PaymentFactory
{
	public:
		static IPayment* GetHelperPayment() {
			if (true)
				return new StripePayment();
			else
				return new PayPalPayment();
		}
	
};

