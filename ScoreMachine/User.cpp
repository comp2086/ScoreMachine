#include "User.h"
#include <fstream>

using namespace std;

User::User(int userId, double newScore)
	: id(userId), score(newScore)
{
	authenticated = false;

	// Set default date
	setDate(2016, 1, 1);
}

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

// Overloaded setter with a string parameter
void User::setScore(const string& newScoreStr)
{
	double newScore = strtod(newScoreStr.c_str(), NULL);
	setScore(newScore);
}

void User::setDate(int year, int month, int day)
{
	time_t rawtime;
	struct tm* temp = new tm();
	
	temp->tm_year = year - 1900;
	temp->tm_mon = month - 1;
	temp->tm_mday = day;
	// Set daylight savings to 0 for a generic 00:00:00 time
	temp->tm_isdst = 0;

	rawtime = mktime(temp);
	char* dt = ctime(&rawtime);
	string newDate = dt;
	int N = newDate.length();

	newDate.copy(date, N);
	// ctime returns newline as the last character, replace it
	date[N - 1] = '\0';
}

// Overloaded setDate to assign date read from the file
void User::setDate(const string& newDate)
{
	newDate.copy(date, newDate.length());
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

bool User::operator >(const User& u) const
{
	return getScore() > u.getScore();
}