#pragma once
#include <string>

class User
{
public:
	User(int = 0, double = 0.0);
	User(const std::string&, const std::string&, 
		int = 0, double = 0.0);
	void setId(int);
	void setUserName(const std::string&);
	void setPassword(const std::string&);
	void setScore(double);
	void authenticate();
	int getId() const;
	std::string getUserName() const;
	std::string getPassword() const;
	double getScore() const;
	bool isAuthenticated() const;
private:
	unsigned int id;
	char userName[ 15 ];
	char password[ 15 ];
	double score;
	bool authenticated;
};

