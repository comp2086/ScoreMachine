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
	void editProfile(User &, bool del);
	bool userNameAvailable(const std::string&);
	void printTopTen();
	//std::multiset<User> records;
	//std::multiset<User>::iterator it;

	const std::string users = "Users.dat";
	const std::string records = "Records.dat";
};

