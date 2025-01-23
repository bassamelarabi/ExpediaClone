#pragma once
#include<iostream>
using namespace std;

class User {
protected:
	string name;
	string user_name;
	string email;
	string password;
	string country;
public:
	User() {}
	User(string username_, string password_) ;
	User(string username_, string name_, string password_, string email_, string country_);
	void SetUsername(string& name);
	const string GetUsername() const;
	void Setname(string& name_);
	const string GetName() const;
	void SetPassword(string& password_);
	bool CheckPassword(string passcode) const;
	void SetEmail(string& email_);
	const string GetEmail() const;

	virtual bool IsAdmin() = 0;
	virtual string GetProfile() = 0;
	virtual ~User();
};
