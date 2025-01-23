#include "HotelsManager.h"

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
		for (auto hilton_room : HiltonHotelAPI::SearchRooms(country_, city_, from_date_, to_date_, adults_, children_, needed_rooms_)) {
			room.price_per_night = hilton_room.price_per_night;
			room.date_time_from = hilton_room.date_from;
			room.date_time_to = hilton_room.date_to;
			room.room_type = hilton_room.room_type;
			room.country = country_;
			room.city = city_;
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
