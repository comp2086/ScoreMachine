#pragma once
#include <string>
#include <set>

class HighScoreManager
{
public:
	HighScoreManager();
	HighScoreManager(std::string, float, int, int, int);
	void createRecord(std::string, float, int, int, int);
	void updateRecord(std::string);
	void printTopTen();
private:
	struct Date
	{
		int year;
		int month;
		int day;
	};
	struct Record 
	{
		std::string userName;
		float score;
		Date date;
		bool operator<(const Record& r) const;
		std::string getDate() const;
	};
	std::multiset<Record> records;
	std::multiset<Record>::iterator it;
};

