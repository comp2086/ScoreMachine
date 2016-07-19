#pragma once
#include <string>
#include <set>

class HighScoreManager
{
public:
	HighScoreManager();
	HighScoreManager(std::string, float, std::string);
	void createRecord(std::string, float, std::string);
	void updateRecord(std::string);
	void printTopTen();
private:
	struct Record {
		std::string userName;
		float score;
		std::string date;
		bool operator<(const Record& r) const;
	};
	std::multiset<Record> records;
	std::multiset<Record>::iterator it;
};

