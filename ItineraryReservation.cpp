#include "ItineraryReservation.h"

class ItineraryReservation : public IReservation {
	vector<IReservation*> reservations;
public:
	ItineraryReservation() {

	}
	ItineraryReservation(const ItineraryReservation& another) {
		for (const IReservation* reservation : another.GetReservations())
			reservations.push_back(reservation->Clone());
		///////RETHINK///////////////////
	}
	const int GetSize() const {
		return (int)reservations.size();
	}


	virtual bool Reserve() {
		bool success_flag = true;
		for (int i = 0; i < (int)reservations.size(); i++) {
			success_flag = AddReservation(*reservations[i]);
		}
		if (!success_flag)
			CancelItinerary();
		return success_flag;
	}
	virtual bool Cancel() {
		return CancelItinerary();
	}
	virtual bool AddReservation(IReservation& reservation) {
		try {
			if (reservation.Reserve()) {
				reservations.push_back(reservation.Clone());
				return true;
			}
			else {
				throw std::runtime_error("Reservation failed.");
			}
		}
		catch (const std::exception& e) {
			std::cerr << e.what() << "\nCancelling all reservations in the itinerary...\n";
			CancelItinerary();
			return false;
		}
	}
	virtual bool CancelItinerary() {
		bool sucess_flag = true;
		for (int i = 0; i < (int)reservations.size(); i++)
			sucess_flag = reservations[i]->Cancel();
		if (!sucess_flag)
			cout << "\tfailed to cancel itinerary \n";
		else {
			for (const IReservation* reservation : reservations)
				delete reservation;
			reservations.clear();
		}
		return sucess_flag;
	}
	virtual double CalculateCost() const override {
		double total = 0;
		for (auto reservation : reservations)
			total += reservation->CalculateCost();
		return total;
	}
	const vector<IReservation*>& GetReservations() const {
		return reservations;
	}
	void Clear() {
		for (const IReservation* reservation : reservations)
			delete reservation;
		reservations.clear();
	}

	virtual string ToString() const override {
		string str;
		for (int i = 0; i < (int)reservations.size(); i++)
			str.append(reservations[i]->ToString());
		return str;

	}

	virtual ItineraryReservation* Clone() const override {
		return new ItineraryReservation(*this);
	}

	~ItineraryReservation() {
		Clear();
	}
	void PrintItinerary() const {
		///to be editted
		cout << "Itinerary of " << reservations.size() << " sub-reservations\n";
		for (int i = 0; i < (int)reservations.size(); i++)
			;
	}
};