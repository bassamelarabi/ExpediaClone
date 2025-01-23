#include "IPayment.h"
#include"expedia_payments_api.h"
class IPayment
{
public:
	virtual bool WithDrawMoney(double amount) = 0;
	virtual void SetUserInfo(std::string name, std::string address = "") = 0;
	virtual void SetCardInfo(std::string id, std::string expiry_date, int ccv = 0) = 0;
	virtual ~IPayment() = 0;
};