#include "PaymentFactory.h"
#include"PayPalPayment.h"
#include"StripePayment.h"


class PaymentFactory {
public:
	static IPayment* GetHelperPayment() {
		if (true)
			return new StripePayment();
		else
			return new PayPalPayment();
	}
};
