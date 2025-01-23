#pragma once
#include<sstream>
#include "User.h"
class Admin : public User {
public:
	bool IsAdmin();
	string GetProfile();
};
