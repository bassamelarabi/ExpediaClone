#include "IFlight.h"
class IFlight : public IReservation {
public:
	virtual bool Reserve() = 0;
	virtual bool Cancel() = 0;
	virtual bool ReserveFlight() const = 0;
	virtual bool CancelReserveFlight() const = 0;
	virtual double CalculateCost() const = 0;
	virtual IReservation* Clone() const = 0;
	virtual void SetFromToInfo(string datetime_from, string from, string datetime_to, string to) = 0;
	virtual void SetPassengersInfo(int adults, int children, int infants) = 0;
	virtual void PrintAPIInfo() const = 0;
	virtual string ToString() const = 0;
	virtual ~IFlight() {}
};