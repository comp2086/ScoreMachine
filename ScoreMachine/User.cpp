#include "User.h"
#include <fstream>

using namespace std;

// Default no arguments constructor
User::User(int userId, double newScore)
	: id(userId), score(newScore)
{
	authenticated = false;
}

// Constructor without highest score
User::User(const string& userName, const string& password, int userId, double newScore)
	: id(userId), score(newScore)
{
	authenticated = false;
	setUserName(userName);
	setPassword(password);
}

void User::setId(int userId)
{
	id = userId;
}

void User::setUserName(const string& userName)
{
	int N = userName.size();
	N = N < 15 ? N : 14;
	userName.copy(this->userName, N);
	//this->userName[N] = '\0';
}

void User::setPassword(const string& password)
{
	int N = password.size();
	N = N < 15 ? N : 14;
	password.copy(this->password, N);
	//this->password[N] = '\0';
}

void User::setScore(double newScore)
{
	score = newScore;
}

void User::toggleAuth()
{
	authenticated = !authenticated;
}

int User::getId() const
{
	return id;
}

string User::getUserName() const
{
	return userName;
}

string User::getPassword() const
{
	return password;
}

double User::getScore() const
{
	return score;
}

bool User::isAuthenticated() const
{
	return authenticated;
}