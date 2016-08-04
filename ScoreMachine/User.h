#pragma once
#include <string>
#include <ctime>

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
	void setScore(const std::string&);
	void setDate(int, int, int);
	void setDate(const std::string&);
	void toggleAuth();
	int getId() const;
	std::string getUserName() const;
	std::string getPassword() const;
	double getScore() const;
	std::string getDate() const;
	bool isAuthenticated() const;
private:
	unsigned int id;
	char userName[ 16 ];
	char password[ 16 ];
	double score;
	char date[ 30 ];
	bool authenticated;
};

