#pragma once
#include<map>
#include<iostream>
#include"Customer.h"

using namespace std;

class CustomersManager {
	map<string, Customer*> username_userobject_map;
	Customer* current_user{ nullptr };
public:
	void LoadDatabase();
	void SignUp();
	void LogIn();
	void LogOut();

	void AcessSystem();

	Customer* GetCurrentUser();

	void FreeLoadedData();

	~CustomersManager();

};

