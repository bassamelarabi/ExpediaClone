#include "IHotel.h"
using namespace std;

class IHotel : public IReservation {
protected:
	virtual int CalculateTotalNights() const = 0;
public:
	virtual bool Reserve() = 0;
	virtual bool Cancel() = 0;
	virtual double CalculateCost() const = 0;
	virtual IHotel* Clone() const = 0;
	virtual bool ReserveRoom() const = 0;
	virtual bool CancelReserveRoom() const = 0;
	virtual string ToString() const = 0;
	virtual void SetRoomInfo(string room_type, int available, double price_per_night, string date_from, string date_to) = 0;
	virtual void SetCountryCityInfo(string country, string city) = 0;
	virtual void PrintAPIInfo() const = 0;
	virtual ~IHotel() {}
};
