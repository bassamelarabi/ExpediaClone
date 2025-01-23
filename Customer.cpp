#include"Customer.h"


using namespace std;
class Customer : public User {
	vector<ItineraryReservation*> itineraries;
	vector<Card*> cards;
	Card* current_card{ nullptr };
	void LoadDatabase() {
		Card* debit_card = new DebitCard(name, 11);
		Card* credit_card = new CreditCard(name, 33);
		cards.push_back(debit_card);
		cards.push_back(credit_card);
	}
public:
	Customer() : User() {
		LoadDatabase();
	}
	Customer(string username_, string password_) : User(username_, password_) {
		LoadDatabase();
	}
	Customer(string username_, string name_, string password_, string email_, string country_)
		: User(username_, name_, password_, email_, country_) {
		LoadDatabase();
	}
	bool IsAdmin() {
		return false;
	}
	bool AddItinerary(ItineraryReservation& itinerary) {
		itineraries.push_back(itinerary.Clone());

	}
	void Clear() {
		for (auto itinerary : itineraries)
			delete itinerary;
		itineraries.clear();
		for (auto card : cards)
			delete card;
		cards.clear();
	}
	void AddCard(const Card& card) {
		cards.push_back(card.Clone());
	}
	vector<ItineraryReservation*>& GetItineraries() {
		return itineraries;
	}
	bool ChooseCard() {
		vector<string> strs;
		for (int i = 0; i < (int)cards.size(); i++)
			strs.push_back(cards[i]->ToString());
		int index = ShowReadMenu(strs);
		current_card = cards[index];
		return true;

	}
	vector<Card*>& GetCards() {
		return cards;
	}
	Card* GetCurrent_Card() const {
		return current_card;
	}
	void ListItineraries() const {
		for (int i = 0; i < (int)itineraries.size(); i++) {
			cout << "****************************************";
			cout << "Itinerary of " << itineraries[i]->GetSize() << " sub reservations";
			cout << itineraries[i]->ToString();
			cout << "Total Itinerary cost: " << itineraries[i]->CalculateCost();
			cout << "****************************************";
		}
	}
	string GetProfile() {
		ostringstream oss;
		oss << "\nHello " << name << " | Admin View";
		return oss.str();
	}

	~Customer() {
		Clear();
	}

};

