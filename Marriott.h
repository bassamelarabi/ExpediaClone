#pragma once
#include<sstream>

#include"expedia_hotels_api.h"

#include "IHotel.h"
class Marriott : public IHotel {
	MarriottCustomerInfo customer;
	MarriottFoundRoom room;
	int CalculateTotalNights() const override;
public:
	Marriott();
	Marriott(string room_type, int available, double price, string date_from, string date_to);
	virtual bool Reserve() override;
	virtual bool Cancel() override;
	virtual bool ReserveRoom() const override;
	virtual bool CancelReserveRoom() const override;
	virtual void SetRoomInfo(string room_type, int available, double price_per_night, string date_from, string date_to)override;
	virtual void SetCountryCityInfo(string country, string city);
	virtual string ToString() const override;
	virtual void PrintAPIInfo() const override;
	virtual IHotel* Clone() const;

};
