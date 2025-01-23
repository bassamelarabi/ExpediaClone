#include "Expedia.h"

class Expedia {
	CustomersManager* customers_manager;
	IPayment* payment;
	FlightsManager* flights_manager;
	HotelsManager* hotels_manager;
	void ViewProfile() {
		cout << customers_manager->GetCurrentUser()->GetProfile() << "\n";
	}
	void MakeItinerary() {
		while (true) {
			ItineraryReservation* itinerary = new ItineraryReservation();
			vector<string> mn;
			mn.push_back("Add Flight");
			mn.push_back("Add Hotel");
			mn.push_back("Done");
			mn.push_back("Cancel");
			int choice = ShowReadMenu(mn);
			if (choice == 1) {
				IReservation* reservation = AddFilght();
				if (reservation != nullptr)
					itinerary->AddReservation(*reservation);
			}
			else if (choice == 2)
				AddHotel();
			else if (choice == 3) {
				bool flag = itinerary->Reserve();
				if (!flag) {
					cout << "Failed to reserve itinerary \n";
					cout << "canceling all reservations in this itinerary\n";
					break;
				}
				flag = PayItinieraries(itinerary);
				if (!flag)
					cout << "Failed to pay for itinerary\n";
				else {
					cout << "Money withdraw successfully \n";
					cout << "Reservation confirmed\n";
					cout << "Itinerary reserved\n";
				}
				break;
			}
			else break;
		}

	}
	IReservation* AddHotel() {
		return new Hilton();
	}
	IReservation* AddFilght() {
		string from_date, to_date, from, to;
		int adults, children, infants;

		cout << "\nEnter from: "; cin >> from;
		cout << "\nEnter from date: "; cin >> from_date;
		cout << "\nEnter to: "; cin >> to;
		cout << "\nEnter to date: "; cin >> to_date;
		cout << "\n Enter # of adults children and infants: "; cin >> adults >> children >> infants;
		vector<Flight> flights = GetAvailableFlights(from, from_date, to, to_date, adults, children, infants);
		if ((int)flights.size() == 0) {
			cout << "\nNo available flights";
			return nullptr;
		}
		for (int i = 0; i < (int)flights.size(); i++) {
			cout << "\nAirline: " << flights[i].provider << " Cost: " << flights[i].price;
			cout << " Departure date " << flights[i].date_time_from << " Arrival date " << flights[i].date_time_to;
		}
		int num;
		cout << "Enter -1 to cancel or number in range 1 - " << flights.size();
		cin >> num;
		if (num == -1)
			return nullptr;;
		return flights_manager->MakeFlight(flights[num - 1]);

	}
	bool PayItinieraries(IReservation* reservation) {
		Customer* customer = customers_manager->GetCurrentUser();
		customer->ChooseCard();
		Card* card = customer->GetCurrent_Card();

		payment->SetCardInfo(card->GetId(), card->GetExpiryDate(), card->GetCCV());
		payment->SetUserInfo(customer->GetName());
		return payment->WithDrawMoney(reservation->CalculateCost());

	}
	void LoadDatabase() {
		//Payments/////////
		payment = PaymentFactory::GetHelperPayment();

		///Load customers data
		customers_manager->LoadDatabase();


	}

	const vector<Flight>& GetAvailableFlights(string from_, string from_date_,
		string to_, string to_date_, int adults_, int children_, int infants_) {
		return flights_manager->GetAvailableFlights(from_, from_date_, to_, to_date_, adults_, children_, infants_);

	}
	bool PayReservation(const IReservation& reservation_) {
		return payment->WithDrawMoney(reservation_.CalculateCost());
	}

	void AccessSystem() {
		customers_manager->AcessSystem();
	}

	string GetProfile() {
		return customers_manager->GetCurrentUser()->GetProfile();

	}

	void ListItineraries() {
		customers_manager->GetCurrentUser()->ListItineraries();
	}

	void FreeLoadedData() {
		delete customers_manager;
		customers_manager = nullptr;
		delete flights_manager;
		flights_manager = nullptr;
		delete hotels_manager;
		hotels_manager = nullptr;
		delete payment;
		payment = nullptr;
	}

public:
	Expedia() : customers_manager(new CustomersManager), flights_manager(new FlightsManager),
		hotels_manager(new HotelsManager) {

	}


	void Run() {
		LoadDatabase();
		AccessSystem();
		ViewProfile();
		while (true) {

			int choice = ShowReadMenu({ "Add Flight", "Add Hotel", "Done", "Cancel" });
			if (choice == 1)
				ViewProfile();
			else if (choice == 2)
				MakeItinerary();
			else if (choice == 3)
				ListItineraries();
			else break;

		}
	}

	~Expedia() {
		FreeLoadedData();
	}
};
