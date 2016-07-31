#include "User.h"

using namespace std;

// Default no arguments constructor
User::User()
{
}

// Constructor without highest score
User::User(string userName)
{
	this->userName = userName;
	this->score = -1;
}

// Constructor with highest score
User::User(string userName, double score)
{
	this->userName = userName;
	this->score = score;
}

void User::setUserName(string userName)
{
	this->userName = userName;
}

void User::setScore(double score)
{
	this->score = score;
}

string User::getUserName() const
{
	return this->userName;
}

double User::getScore() const
{
	return this->score;
}
