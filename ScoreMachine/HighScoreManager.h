#pragma once
#include <string>
#include <set>
#include "User.h"

namespace HighScoreManager
{
	void setUserId(User&);
	void saveUser(User&, bool = false);
	void login(User&);
	void logout(User&);
	void deleteProfile(User &);
	//std::multiset<User> records;
	//std::multiset<User>::iterator it;

	const std::string users = "Users.dat";
	const std::string records = "Records.dat";
};

