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

void User::setId(int newId)
{
	id = newId;
}

void User::setUserName(const string& newUserName)
{
	int N = newUserName.size();
	N = N < 15 ? N : 14;
	newUserName.copy(userName, N);
	userName[N] = '\0';
}

void User::setPassword(const string& newPassword)
{
	int N = newPassword.size();
	N = N < 15 ? N : 14;
	newPassword.copy(password, N);
	password[N] = '\0';
}

void User::setScore(double newScore)
{
	if (!(score > 100) && !(score < 0)) score = newScore;
}

void User::setScore(const string& newScoreStr)
{
	double newScore = strtod(newScoreStr.c_str(), NULL);
	setScore(newScore);
}

void User::setDate(const string& score)
{
	int N = score.length();
	N = N < 11 ? N : 10;
	score.copy(this->date, N);
	date[N] = '\0';
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

string User::getDate() const
{
	return date;
}

bool User::isAuthenticated() const
{
	return authenticated;
}