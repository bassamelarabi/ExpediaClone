#include "IReservation.h"
class IReservation {
public:
	virtual double CalculateCost() const = 0;
	virtual IReservation* Clone() const = 0;
	virtual bool Reserve() = 0;
	virtual bool Cancel() = 0;
	virtual std::string ToString() const = 0;
	virtual ~IReservation() {}
};