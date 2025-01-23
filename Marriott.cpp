#include "Marriott.h"

class Marriott : public IHotel {
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
