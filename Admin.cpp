#include "Admin.h"

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
