#include "CustomersManager.h"
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

