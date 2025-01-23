#include "User.h"

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
	User(string username_, string name_, string password_, string email_, string country_) : user_name(username_), password(password_)
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
