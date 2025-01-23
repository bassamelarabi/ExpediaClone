#include"expedia_hotels_api.h"
#include"expedia_flights_api.h"
#include"expedia_payments_api.h"

#include <iostream>
#include<vector>
#include<ctime>
#include<sstream>

using namespace std;
///a strucutre to represent the time/////
tm make_tm(int year, int month, int day) {
	tm tm{ 0 };
	tm.tm_year = year;
	tm.tm_mon = month - 1; // months count from January =0
	tm.tm_mday = day;
	return tm;
}


///utilities//////
int ReadInt(int low, int high) {
	cout << "\nEnter number in range " << low << " - " << high << ": ";
	int value;

	cin >> value;

	if (low <= value && value <= high)
		return value;

	cout << "ERROR: invalid number...Try again\n";
	return ReadInt(low, high);
}

int ShowReadMenu(const vector<string>& choices) {
	cout << "\nMenu:\n";
	for (int ch = 0; ch < (int)choices.size(); ++ch) {
		cout << "\t" << ch + 1 << ": " << choices[ch] << "\n";
	}
	return ReadInt(1, (int)choices.size());
}


/// Payments handling////////////

class IPayment {
public:
	virtual bool WithDrawMoney(double amount) = 0;
	virtual void SetUserInfo(string name, string address="") = 0;
	virtual void SetCardInfo(string id, string expiry_date, int ccv = 0 ) = 0;
	virtual ~IPayment() = 0;
};


class PayPalPayment : public IPayment {
	PayPalCreditCard card;
	PayPalOnlinePaymentAPI paypal;
public:
	void SetCardInfo(string id, string expiry_date, int ccv = 0) override {
		card.id = id;
		card.ccv = ccv;
		card.expiry_date = expiry_date;
	}
	void SetUserInfo(string name, string address = "") override {
		card.name = name;
		card.address = address;
	}
	bool WithDrawMoney(double amount) override {
		paypal.SetCardInfo( &card);
		return paypal.MakePayment(amount);
	}
	~PayPalPayment(){}
};

class StripePayment : public IPayment {
	StripeUserInfo user_info;
	StripeCardInfo card_info;
public:
	void SetCardInfo(string id, string expiry_date, int ccv ) override {
		card_info.id = id;
		card_info.expiry_date = expiry_date;
	}
	void SetUserInfo(string name, string address) override{
		user_info.name = name;
		user_info.address = address;
	}
	bool WithDrawMoney(double amount) override {
		return StripePaymentAPI::WithDrawMoney(user_info, card_info, amount);
	}
	~StripePayment() {}
};


class PaymentFactory {
public:
	static IPayment* GetHelperPayment() {
		if (true)
			return new StripePayment();
		else 
			return new PayPalPayment();
	}
};

class Card {
protected:
	string name;
	string address;
	double credit;
	int ccv;
	string id;
	int card_number;
	string expiry_date;
public:
	Card(){
	}
	Card(string name_, int card_number_) : name(name_), card_number(card_number_) {

	}
	void SetCardInfo(string name_, string address_, string id_, int ccv_, int card_number_, int expiry_date_, double credit_) {
		name = name_;
		address = address_;
		id = id_;
		ccv = ccv_;
		card_number = card_number_;
		expiry_date = expiry_date_;
		credit = credit_;
	}
	const string GetName  () const {
		return name;
	}
	const string GetAddress() const {
		return address;
	}
	const string GetId() const {
		return id;
	}
	const string GetExpiryDate() const {
		return expiry_date;
	}
	const int GetCCV() const {
		return ccv;
	}
	virtual void PrintCardInfo() const = 0;
	virtual string ToString() const = 0;
	virtual Card* Clone() const = 0;
	virtual ~Card() = 0;
};

class CreditCard : public Card {
public:
	CreditCard(): Card() {
	}
	CreditCard(string name_, int card_number_) : Card(name_, card_number_) {

	}
	void PrintCardInfo() const override {
		cout << "[Credit Card]: Owner: " << name << " Card number: " << card_number << "\n";
	}
	string ToString () const override {
		ostringstream oss;
		oss<< "[Credit Card]: Owner: " << name << " Card number: " << card_number << "\n";
		return oss.str();
	}
	CreditCard* Clone() const override {
		return new CreditCard(*this);
	}
	~CreditCard() override{}
};

class DebitCard : public Card {
public:
	DebitCard() : Card() {
	}
	DebitCard(string name_, int card_number_) : Card(name_, card_number_) {

	}
	string ToString() const override{
		ostringstream oss;
		oss<< "[Debit Card]: Owner: " << name << " Card number: " << card_number ;
		return oss.str();
	}
	void PrintCardInfo() const override {
		cout << "[Debit Card]: Owner: " << name << " Card number: " << card_number ;
	}
	DebitCard* Clone()const override {
		return new DebitCard(*this);
	}
	~DebitCard() {}
};


///Itineraries ///////////////////
class IReservation {
public:
	virtual double CalculateCost() const = 0;
	virtual IReservation* Clone() const = 0;
	virtual bool Reserve() = 0;
	virtual bool Cancel() = 0;
	virtual string ToString() const = 0;
	virtual ~IReservation() {}
};

class IFlight : public IReservation {
public:
	virtual bool Reserve()   = 0;
	virtual bool Cancel() = 0;
	virtual bool ReserveFlight() const = 0;
	virtual bool CancelReserveFlight() const= 0;
	virtual double CalculateCost() const = 0;
	virtual IReservation* Clone() const = 0;
	virtual void SetFromToInfo(string datetime_from, string from, string datetime_to, string to) = 0;
	virtual void SetPassengersInfo(int adults, int children, int infants) = 0;
	virtual void PrintAPIInfo() const = 0;
	virtual string ToString() const = 0;
	virtual ~IFlight() {}
};

class IHotel : public IReservation {
protected:
	virtual int CalculateTotalNights() const = 0;
public:
	virtual bool Reserve()  = 0;
	virtual bool Cancel() = 0;
	virtual double CalculateCost() const = 0;
	virtual IHotel* Clone() const = 0;
	virtual bool ReserveRoom() const  = 0;
	virtual bool CancelReserveRoom() const = 0;
	virtual string ToString() const = 0;
	virtual void SetRoomInfo(string room_type, int available, double price_per_night, string date_from, string date_to)  = 0;
	virtual void SetCountryCityInfo(string country, string city) = 0;
	virtual void PrintAPIInfo() const = 0;
	virtual ~IHotel(){}
};

class ItineraryReservation : public IReservation {
	vector<IReservation*> reservations;
public:
	ItineraryReservation() {

	}
	ItineraryReservation(const ItineraryReservation& another) {
		for ( const IReservation* reservation : another.GetReservations())
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
	virtual bool Cancel()  {
		return CancelItinerary();
	}
	virtual bool AddReservation( IReservation& reservation) {
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
	
	virtual string ToString() const override{
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

class AirCanada : public IFlight{
	AirCanadaCustomerInfo customer;
	AirCanadaFlight flight;
public:
	AirCanada() {

	}
	AirCanada(string date_time_from, string date_time_to, double price) {
		flight.date_time_from = date_time_from;
		flight.date_time_to = date_time_to;
		flight.price = price;
	}
	virtual bool Reserve() override{
		return ReserveFlight();
	}
	virtual bool Cancel() override{
		return CancelReserveFlight();
	}
	virtual bool ReserveFlight() const override {
		return AirCanadaOnlineAPI::ReserveFlight(flight, customer);
	}
	virtual bool CancelReserveFlight() const override{
		return AirCanadaOnlineAPI::CancelReserveFlight(flight, customer);
	}
	virtual double CalculateCost() const override {
		return flight.price;
	}
	virtual void SetFromToInfo(string datetime_from, string from, string datetime_to, string to) override{
		flight.date_time_from = datetime_from;
		flight.date_time_to = datetime_to;
	}
	virtual void SetPassengersInfo(int adults, int children, int infants) {
		flight.adults = adults;
		flight.children = children;
		flight.infants = infants;
	}
	virtual string ToString() const override {
		ostringstream oss;
		oss << "Airline reservation with reservation: AirCanada Airlines From: " << flight.from;
		oss<<" on " << flight.date_time_from<< "\t to "<<flight.to;
		oss << " on " << flight.date_time_to<<"\n";
		oss << "\tAdults: " << flight.adults << " children:" << flight.children ;
		oss << " infants: " << flight.infants << " \n \t Total Cost: " << flight.price;
		return oss.str();
	}
	virtual void PrintAPIInfo() const {
		cout << "Airline: AirCanada Airlines Cost: " << CalculateCost();
		cout << " Departure Date " << flight.date_time_from;
		cout << " Arrival date " << flight.date_time_to;
	}
	virtual IFlight* Clone() const override {
		return new AirCanada(*this);
	}
	~AirCanada() {}
};

class TurkishAirlines : public IFlight{
	TurkishCustomerInfo customer;
	TurkishFlight flight;
public:
	TurkishAirlines() {

	}
	TurkishAirlines(string date_time_from, string date_time_to, double price) {
		flight.datetime_from = date_time_from;
		flight.datetime_to = date_time_to;
		flight.cost = price;
	}
	virtual bool Reserve()  override{
		return ReserveFlight();
	}
	virtual bool Cancel() override{
		return CancelReserveFlight();
	}
	virtual bool ReserveFlight() const override {
		return TurkishAirlinesOnlineAPI::ReserveFlight(customer, flight);
	}
	virtual bool CancelReserveFlight() const override {
		return TurkishAirlinesOnlineAPI::CancelReserveFlight(customer, flight);
	}
	virtual double CalculateCost() const override {
		return flight.cost;
	}
	virtual void SetFromToInfo(string datetime_from, string from, string datetime_to, string to) override {
		flight.datetime_from= datetime_from;
		flight.datetime_to = datetime_to;
	}
	virtual void SetPassengersInfo(int adults, int children, int infants) {
		flight.adults = adults;
		flight.children = children;
		flight.infants = infants;
	}
	virtual string ToString() const override {
		ostringstream oss;
		oss << "Airline reservation with reservation: Turkish Flight Airlines From: " << flight.from;
		oss << " on " << flight.datetime_from << "\t to " << flight.to;
		oss << " on " << flight.datetime_to << "\n";
		oss << "\tAdults: " << flight.adults << " children:" << flight.children;
		oss << " infants: " << flight.infants << " \n \t Total Cost: " << flight.cost;
		return oss.str();
	}
	virtual void PrintAPIInfo() const {
		cout << "Airline: Turkish Airlines Cost: " << CalculateCost();
		cout << " Departure Date " << flight.datetime_from;
		cout << " Arrival date " << flight.datetime_to;
	}
	virtual IFlight* Clone() const override {
		return new TurkishAirlines(*this);
	}
	~TurkishAirlines() {}
};


class Hilton : public IHotel{
	HiltonCustomerInfo customer;
	HiltonRoom room;
	int CalculateTotalNights() const override {
		string s1 = room.date_from;
		string s2 = room.date_to;
		///date_from//////
		int day11 = (int(s1[0]) - 48) * 10;
		int day12 = int(s1[1]) - 48;
		int day1 = day11 + day12;

		int month11 = (int(s1[3]) - 48) * 10;
		int month12 = int(s1[4]) - 48;
		int month1 = month11 + month12;

		int year11 = (int(s1[6]) - 48) * 1000;
		int year12 = (int(s1[7]) - 48) * 100;
		int year13 = (int(s1[8]) - 48) * 10;
		int year14 = (int(s1[9]) - 48);
		int year1 = year11 + year12 + year13 + year14;

		tm tm1 = make_tm(year1, month1, day1);

		///date_to//////
		int day21 = (int(s2[0]) - 48) * 10;
		int day22 = int(s2[1]) - 48;
		int day2 = day21 + day22;

		int month21 = (int(s2[3]) - 48) * 10;
		int month22 = int(s2[4]) - 48;
		int month2 = month21 + month22;

		int year21 = (int(s2[6]) - 48) * 1000;
		int year22 = (int(s2[7]) - 48) * 100;
		int year23 = (int(s2[8]) - 48) * 10;
		int year24 = (int(s2[9]) - 48);
		int year2 = year21 + year22 + year23 + year24;

		tm tm2 = make_tm(year2, month2, day2);

		/// caluculating difference in days////
		const int seconds_per_day = 60 * 60 * 24;
		time_t time1 = mktime(&tm1);
		time_t time2 = mktime(&tm2);
		time_t difference = (time2 - time1) / seconds_per_day;
		int days = int(difference);
		return days;
	}
public:
	Hilton() {

	}
	Hilton(string room_type, int available, double price, string date_from, string date_to) {
		room.room_type = room_type;
		room.available = available;
		room.price_per_night = price;
		room.date_from = date_from;
		room.date_to = date_to;
	}
	virtual bool Reserve() override {
		return ReserveRoom();
	}
	virtual bool Cancel() override {
		return CancelReserveRoom();
	}
	virtual bool ReserveRoom() const override {
		return HiltonHotelAPI::ReserveRoom(room, customer);
	}
	virtual bool CancelReserveRoom() const override {
		return HiltonHotelAPI::CancelReserveRoom(room, customer);
	}
	virtual void SetRoomInfo(string room_type, int available, double price_per_night, string date_from, string date_to)override {
		room.available = available;
		room.date_from = date_from;
		room.date_to = date_to;
		room.price_per_night = price_per_night;
		room.room_type = room_type;

	}
	virtual void SetCountryCityInfo(string country, string city) {
		room.country = country;
		room.city = city;
	}
	virtual double CalculateCost() const override{
		return CalculateTotalNights() * room.price_per_night;
	}
	virtual string ToString() const override {
		ostringstream oss;
		oss << "Hotel reservation with reservation: Hilton Hotel: " << room.country<<" @ "<<room.city<<"\n";
		oss << "\t"<<room.date_from << " to " << room.date_to <<" : "<<CalculateTotalNights() << "\n";
		oss << "\tAdults: " << room.adults << " children:" << room.children;
		oss <<" \n \t Total Cost: " << CalculateCost();
		return oss.str();
	}
	virtual void PrintAPIInfo() const override {
		cout << "Hilton Hotel Room Type: " << room.room_type;
		cout << " Price per night: " << room.price_per_night;
		cout << " From Date " << room.date_from;
		cout << " to " << room.date_to;
	}
	virtual IHotel* Clone() const override {
		return new Hilton(*this);
	}
	~Hilton() {

	}
	/*
	*
	*/
};


class Marriott : public IHotel{
	MarriottCustomerInfo customer;
	MarriottFoundRoom room;
	int CalculateTotalNights() const override {
		string s1 = room.date_from;
		string s2 = room.date_to;
		///date_from//////
		int day11 = (int(s1[0]) - 48) * 10;
		int day12 = int(s1[1]) - 48;
		int day1 = day11 + day12;

		int month11 = (int(s1[3]) - 48) * 10;
		int month12 = int(s1[4]) - 48;
		int month1 = month11 + month12;

		int year11 = (int(s1[6]) - 48) * 1000;
		int year12 = (int(s1[7]) - 48) * 100;
		int year13 = (int(s1[8]) - 48) * 10;
		int year14 = (int(s1[9]) - 48);
		int year1 = year11 + year12 + year13 + year14;

		tm tm1 = make_tm(year1, month1, day1);

		///date_to//////
		int day21 = (int(s2[0]) - 48) * 10;
		int day22 = int(s2[1]) - 48;
		int day2 = day21 + day22;

		int month21 = (int(s2[3]) - 48) * 10;
		int month22 = int(s2[4]) - 48;
		int month2 = month21 + month22;

		int year21 = (int(s2[6]) - 48) * 1000;
		int year22 = (int(s2[7]) - 48) * 100;
		int year23 = (int(s2[8]) - 48) * 10;
		int year24 = (int(s2[9]) - 48);
		int year2 = year21 + year22 + year23 + year24;

		tm tm2 = make_tm(year2, month2, day2);

		/// caluculating difference in days////
		const int seconds_per_day = 60 * 60 * 24;
		time_t time1 = mktime(&tm1);
		time_t time2 = mktime(&tm2);
		time_t difference = (time2 - time1) / seconds_per_day;
		int days = int(difference);
		return days;
	}
public:
	Marriott() {

	}
	Marriott(string room_type, int available, double price, string date_from, string date_to) {
		room.room_type = room_type;
		room.available = available;
		room.price_per_night = price;
		room.date_from = date_from;
		room.date_to = date_to;
	}
	virtual bool Reserve() override {
		return ReserveRoom();
	}
	virtual bool Cancel() override {
		return CancelReserveRoom();
	}
	virtual bool ReserveRoom() const override {
		return MarriottHotelAPI::ReserveRoom(room, customer);
	}
	virtual bool CancelReserveRoom() const override {
		return MarriottHotelAPI::CancelReserveRoom(room, customer);
	}
	virtual void SetRoomInfo(string room_type, int available, double price_per_night, string date_from, string date_to)override {
		room.available = available;
		room.date_from = date_from;
		room.date_to = date_to;
		room.price_per_night = price_per_night;
		room.room_type = room_type;

	}
	virtual void SetCountryCityInfo(string country, string city) {
		room.country = country;
		room.city = city;
	}
	virtual double CalculateCost() const {
		return CalculateTotalNights() * room.price_per_night;
	}
	virtual string ToString() const override {
		ostringstream oss;
		oss << "Hotel reservation with reservation: Marriott Hotel: " << room.country << " @ " << room.city << "\n";
		oss << "\t" << room.date_from << " to " << room.date_to << " : " << CalculateTotalNights() << "\n";
		oss << "\tAdults: " << room.adults << " children:" << room.children;
		oss << " \n \t Total Cost: " << CalculateCost();
		return oss.str();
	}
	virtual void PrintAPIInfo() const override {
		cout << "Marriott Hotel Room Type: " << room.room_type;
		cout << " Price per night: " << room.price_per_night;
		cout << " From Date " << room.date_from;
		cout << " to " << room.date_to;
	}
	virtual IHotel* Clone() const {
		return new Marriott(*this);

	}

};


struct HotelRoom {
	string provider;
	string country;
	string city;
	string date_time_from;
	string date_time_to;
	string room_type;
	double price_per_night;
	int adults;
	int children;
	int available;

};
struct Flight {
	string provider;
	string from;
	string to;
	string date_time_from;
	string date_time_to;
	double price;
	int adults;
	int children;
	int infants;

};

//Managers

class FlightsManager {
	

	vector<Flight> flights;
	TurkishAirlinesOnlineAPI turkish_airlines_api;
public:
	const vector<Flight>& GetAvailableFlights(string from_, string from_date_,
		string to_, string to_date_, int adults_, int children_, 
		int infants_) {
		ClearFlights();
		Flight flight;
		//turkish airlines flights
		for (auto turkish_flight : turkish_airlines_api.GetAvailableFlights()) {
			flight.price = turkish_flight.cost;
			flight.date_time_from = turkish_flight.datetime_from;
			flight.date_time_to = turkish_flight.datetime_to;
			flight.from = from_;
			flight.to = to_;
			flight.children = children_;
			flight.adults = adults_;
			flight.infants = infants_;

			flight.provider = "TurkishAirlines";
			flights.push_back(flight);

		}
		//air canada flights

		for (auto air_canada_flight : AirCanadaOnlineAPI::GetFlights(from_, from_date_, to_, to_date_, adults_, children_ )) {
			flight.price = air_canada_flight.price;
			flight.date_time_from = air_canada_flight.date_time_from;
			flight.date_time_to = air_canada_flight.date_time_to;
			flight.from = from_;
			flight.to = to_;
			flight.children = children_;
			flight.adults = adults_;
			flight.infants = infants_;

			flight.provider = "AirCanada";
			flights.push_back(flight);

		}
		return flights;

	}
	void ClearFlights() {
		flights.clear();
	}
	IFlight* MakeFlight(Flight flight_) {
		IFlight* flight;
		if (flight_.provider == "AirCanada")
			flight = new AirCanada();
		else flight = new TurkishAirlines();
		flight->SetFromToInfo(flight_.date_time_from, flight_.from, flight_.date_time_to, flight_.to);
		flight->SetPassengersInfo(flight_.adults, flight_.children, flight_.infants);
		return flight;
		ClearFlights();
	}

};



class HotelsManager {
	

	vector<HotelRoom> rooms;
	TurkishAirlinesOnlineAPI turkish_airlines_api;
public:
	const vector<HotelRoom>& GetAvailableRooms(string country_, string from_date_,
		string city_, string to_date_, int adults_, int children_,
		int needed_rooms_) {
		ClearRooms();
		HotelRoom room;
		//turkish airlines flights
		for (auto hilton_room: HiltonHotelAPI::SearchRooms(country_, city_,from_date_, to_date_,adults_, children_, needed_rooms_)) {
			room.price_per_night = hilton_room.price_per_night;
			room.date_time_from = hilton_room.date_from;
			room.date_time_to = hilton_room.date_to;
			room.room_type = hilton_room.room_type;
			room.country = country_;
			room.city= city_;
			room.children = children_;
			room.adults = adults_;

			room.provider = "Hilton";
			rooms.push_back(room);

		}
		//air canada flights

		for (auto marriott_room : MarriottHotelAPI::FindRooms(from_date_, to_date_, country_, city_, needed_rooms_, adults_, children_)) {
			room.price_per_night = marriott_room.price_per_night;
			room.date_time_from = marriott_room.date_from;
			room.date_time_to = marriott_room.date_to;
			room.room_type = marriott_room.room_type;
			room.country = country_;
			room.city = city_;
			room.children = children_;
			room.adults = adults_;

			room.provider = "Marriott";
			rooms.push_back(room);

		}
		return rooms;

	}
	void ClearRooms() {
		rooms.clear();
	}
	IHotel* MakeFlight(HotelRoom room_) {
		IHotel* room;
		if (room_.provider == "Hitlon")
			room = new Hilton();
		else room = new Marriott();
		room->SetRoomInfo(room_.room_type, room_.available, room_.price_per_night, room_.date_time_from, room_.date_time_to);
		room->SetCountryCityInfo(room_.country, room_.city);
		return room;
		ClearRooms();
	}

};



class User {
protected:
	string name;
	string user_name;
	string email;
	string password;
	string country;
public:
	User() {}
	User(string username_, string password_) : user_name(username_), password(password_) {

	}
	User(string username_, string name_, string password_, string email_,string country_) : user_name(username_), password(password_)
	, name(name_), email(email_), country(country_) {

	}
	void SetUsername(string& name) {
		user_name = name;
	}
	const string GetUsername() const {
		return user_name;
	}
	void Setname(string& name_) {
		name = name_;
	}
	const string GetName() const {
		return name;
	}
	void SetPassword(string& password_) {
		password = password_;
	}
	bool CheckPassword(string passcode) const {
		if (passcode == password)
			return true;
		else return false;
	}
	void SetEmail(string& email_) {
		email = email_;
	}
	const string GetEmail() const {
		return email;
	}

	virtual bool IsAdmin() = 0;
	virtual string GetProfile() = 0;
	virtual ~User() {

	}
};

class Admin : public User {
public:
	bool IsAdmin() {
		return true;
	}
	string GetProfile() {
		ostringstream oss;
		oss << "\nHello " << name << " | Admin View";
		return oss.str();
	}
};

class Customer : public User {
	vector<ItineraryReservation*> itineraries;
	vector<Card*> cards;
	Card* current_card{ nullptr };
	void LoadDatabase() {
		Card* debit_card = new DebitCard(name, 11 );
		Card* credit_card = new CreditCard(name, 33 );
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
	vector<Card*>& GetCards  () {
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



class CustomersManager {
	map<string, Customer*> username_userobject_map;
	Customer* current_user{ nullptr };
public:
	void LoadDatabase() {
		if (username_userobject_map.size() > 0)
			return;
		Customer* user1 = new Customer("Mostafa_Saad", "Mostafa Saad", "123", "mostafa@mail.com", "Canada");
		username_userobject_map.insert({ user1->GetUsername(), user1 });

		Customer* user2 = new Customer("Bassam", "Bassam", "122", "basssam@mail.com", "Egypt");
		username_userobject_map.insert({ user1->GetUsername(), user1 });


	}
	void SignUp() {
		string username, password;
		cout << "\nenter username and password: ";
		cin >> username >> password;
		if (username_userobject_map.count(username)) {
			cout << "\nalready existing username ";
			SignUp();
		}
		else {
			Customer* new_user = new Customer(username, password);
			username_userobject_map.insert({ username, new_user });
			cout << "\nSigned in successfully !!";
		}
	}
	void LogIn() {
		string name, password;
		cout << "\nenter username and password: ";
		cin >> name >> password;
		if (username_userobject_map.count(name) == 0) {
			cout << "\nwrong username or password";
			LogIn();
		}
		else {
			if (!username_userobject_map[name]->CheckPassword(password)) {
				cout << "\nwrong username or password";
				LogIn();
			}
			else {
				current_user = username_userobject_map[name];
				cout << "\nLogged in successfully";
			}


		}
	}
	void LogOut() {
		current_user = NULL;
	}

	void AcessSystem() {
		int choice = ShowReadMenu({ "Log In", "Sign Up" });
		if (choice == 1)
			LogIn();
		else SignUp();
	}

	Customer* GetCurrentUser() {
		return current_user;
	}

	void FreeLoadedData() {
		for (auto user : username_userobject_map) {
			delete user.second;
		}
		username_userobject_map.clear();
		current_user = nullptr;
		delete current_user;
	}
	
	~CustomersManager() {
		FreeLoadedData();
	}

};


class CustomerView {
	User* current_user { nullptr };
public:
	CustomerView(User& user) {

	}

};

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





int main()
{
	
	Expedia expedia;
	expedia.Run();

}



///////////////APIs///////////
//class ItineraryAPI {
//public:
//	virtual const vector<Reservation*> GetAvailable() const = 0;
//};
//
//class FlightsAPI : public ItineraryAPI {
//public:
//	const vector<Reservation*> GetAvailable() const {
//		string from, from_date, to, to_date;
//		int adults, children;
//		cout << "Enter From: "; cin >> from;
//		cout << "\nEnter From Date (dd-mm-yy): "; cin >> from_date;
//		cout << "\nEnter To: "; cin >> to;
//		cout << "\nEnter To Date: "; cin >> to_date;
//		cout << "\nEnter # of adults children (5-16) and infants: "; cin >> adults >> children;
//		cout << "\n";
//		//inversion of control ////
//		return GetAvailableFlights(from, from_date, to, to_date, adults, children);
//	}
//	virtual const vector<Reservation*> GetAvailableFlights(string from, string from_date,
//		string to, string to_date, int adults, int children) const = 0;
//
//
//	/////////////////
//
//
//};
//
//class HotelsAPI : public ItineraryAPI {
//public:
//	const vector<Reservation*> GetAvailable() const {
//		string country, city, from_date, to_date;
//		int needed_rooms, adults, children;
//		cout << "\nEnter From Date (dd-mm-yy): "; cin >> from_date;
//		cout << "\nEnter To Date: "; cin >> to_date;
//		cout << "Enter Country: "; cin >> country;
//		cout << "Enter City: "; cin >> city;
//		cout << "\nEnter # of adults and children: "; cin >> adults >> children;
//		cout << "\n";
//		//inversion of control///
//		return GetAvailableHotels(country, city, from_date, to_date, adults, children, needed_rooms);
//	}
//	virtual const vector<Reservation*> GetAvailableHotels(string country, string city, string from_date,
//		string to_date, int adults, int children, int needed_rooms) const = 0;
//
//
//};
//
//class AirCanadaAPI : public FlightsAPI {
//public:
//	virtual const vector<Reservation*> GetAvailableFlights(string from, string from_date,
//		string to, string to_date, int adults, int children) const {
//		vector<AirCanadaFlight> flights = AirCanadaOnlineAPI::GetFlights(from, from_date, to, to_date,
//			adults, children);
//		vector<Reservation*> reservations;
//		for (auto flight : flights) {
//			Reservation* reservation = new AirCanada(flight.date_time_from, flight.date_time_to, flight.price);
//			reservations.push_back(reservation->Clone());
//		}
//		return reservations;
//	}
//
//	//////////////
//};
//
//class TurkishAirlinesAPI : public FlightsAPI {
//	TurkishAirlinesOnlineAPI api;
//public:
//	virtual const vector<Reservation*> GetAvailableFlights(string from, string from_date,
//		string to, string to_date, int adults, int children) const {
//		vector<TurkishFlight> flights = api.GetAvailableFlights(from, from_date, to, to_date,
//			adults, children);
//		vector<Reservation*> reservations;
//		for (auto flight : flights) {
//			Reservation* reservation = new TurkishAirlines(flight.datetime_from, flight.datetime_to, flight.cost);
//			reservations.push_back(reservation->Clone());
//		}
//		return reservations;
//
//	}
//};
//
//
//class HiltonAPI : public HotelsAPI {
//public:
//	virtual const vector<Reservation*> GetAvailableHotels(string country, string city,
//		string from_date, string to_date, int adults, int children, int needed_rooms) const {
//		vector<HiltonRoom> rooms = HiltonHotelAPI::SearchRooms(country, city, from_date, to_date, adults, children, needed_rooms);
//		vector<Reservation*> reservations;
//		for (auto room : rooms) {
//			Reservation* reservation = new Hilton(room.room_type, room.available, room.price_per_night, room.date_from, room.date_to);
//			reservations.push_back(reservation->Clone());
//		}
//		return reservations;
//
//	}
//};
//
//class MarriottAPI : public HotelsAPI {
//public:
//	virtual const vector<Reservation*> GetAvailableHotels(string country, string city,
//		string from_date, string to_date, int adults, int children, int needed_rooms) const {
//		vector<MarriottFoundRoom> rooms = MarriottHotelAPI::FindRooms(from_date, to_date, country, city, needed_rooms, adults, children);
//		vector<Reservation*> reservations;
//		for (auto room : rooms) {
//			Reservation* reservation = new Marriott(room.room_type, room.available, room.price_per_night, room.date_from, room.date_to);
//			reservations.push_back(reservation->Clone());
//		}
//		return reservations;
//
//	}
//};