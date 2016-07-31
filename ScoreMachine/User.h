#pragma once
#include <string>

class User
{
public:
	User();
	User(std::string);
	User(std::string, double);
	void setUserName(std::string);
	void setScore(double);
	std::string getUserName() const;
	double getScore() const;
private:
	std::string userName;
	double score;
};

