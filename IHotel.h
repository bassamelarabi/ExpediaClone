#pragma once
#include "IReservation.h"
tm make_tm(int year, int month, int day);
class IHotel : public IReservation {
protected:
	virtual int CalculateTotalNights() const ;
public:
	virtual bool Reserve();
	virtual bool Cancel() ;
	virtual double CalculateCost() const ;
	virtual IHotel* Clone() const ;
	virtual bool ReserveRoom() const ;
	virtual bool CancelReserveRoom() const ;
	virtual string ToString() const ;
	virtual void SetRoomInfo(string room_type, int available, double price_per_night, string date_from, string date_to) ;
	virtual void SetCountryCityInfo(string country, string city) ;
	virtual void PrintAPIInfo() const ;
	virtual ~IHotel() {}
};

