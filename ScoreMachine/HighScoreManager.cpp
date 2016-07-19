#include "HighScoreManager.h"
#include <iostream>

using namespace std;

HighScoreManager::HighScoreManager() {}
HighScoreManager::HighScoreManager(string userName, float score, string date)
{
	createRecord(userName, score, date);
}

bool HighScoreManager::Record::operator<(const Record& r) const
{
	return score > r.score;
}

void HighScoreManager::createRecord(string userName, float score, string date)
{
	// Create a new record
	Record r;
	r.userName = userName;
	r.score = score;
	r.date = date;

	// Add a record to sorted collection
	records.insert(r);
}

void HighScoreManager::updateRecord(string userName)
{
	// Create an iterator
	// Find a record by the userName
	// Update the record
}

void HighScoreManager::printTopTen()
{
	// Counter
	int counter = 1;

	// Iterator for the records collection
	it = records.begin();

	// Iterate through the records starting at the beginning 
	// until top 10 records were printed out
	while (counter <= 10 && it != records.end())
	{
		cout << counter << ". " << (*it).userName << " "
			<< (*it).date << " " 
			<< (*it).score << endl;
		it++;
		counter++;
	}
}
