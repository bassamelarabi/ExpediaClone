#pragma once
#include"HotelRoom.h"
#include"expedia_hotels_api.h"
#include"IHotel.h"

class HotelsManager {


	vector<HotelRoom> rooms;
	TurkishAirlinesOnlineAPI turkish_airlines_api;
public:
	const vector<HotelRoom>& GetAvailableRooms(string country_, string from_date_,
		string city_, string to_date_, int adults_, int children_,
		int needed_rooms_);
	void ClearRooms();
	IHotel* MakeFlight(HotelRoom room_);

};

