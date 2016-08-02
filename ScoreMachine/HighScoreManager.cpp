#include "HighScoreManager.h"
#include <fstream>
#include <iostream>

using namespace std;

void HighScoreManager::saveUser(User& u, bool newUser)
{
	ofstream outFileStream(users, ios::in | ios::out | ios::binary);

	// Terminate if Users.dat couldn't be open
	if (!outFileStream)
	{
		cerr << "Users file couldn't be open";
		exit(EXIT_FAILURE);
	}

	// This is a new user
	if (newUser)
	{		
		// Set the next available id for a new user
		setUserId(u);
		outFileStream.seekp((u.getId() - 1) * sizeof(User));
		outFileStream.write(reinterpret_cast<const char*>(&u), sizeof(User));
	}
	// We're updating an existing user
	else
	{
		// Find the first byte of the user record by id
		int location = (u.getId() - 1) * sizeof(u);

		// Update the record
		outFileStream.seekp(location);
		outFileStream.write(reinterpret_cast<const char*>(&u), sizeof(User));
	}

	outFileStream.close();
}

void HighScoreManager::login(User& u)
{
	User temp;
	ifstream inFileStream(users, ios::in | ios::binary);

	if (!inFileStream)
	{
		cerr << "Users file couldn't be open";
		exit(EXIT_FAILURE);
	}

	inFileStream.read(reinterpret_cast<char *> (&temp), sizeof(User));

	while (inFileStream && !inFileStream.eof())
	{
		// Login OK
		if (temp.getUserName() == u.getUserName() &&
			temp.getPassword() == u.getPassword())
		{
			u.setId(temp.getId());
			u.authenticate();
			break;
		}

		inFileStream.read(reinterpret_cast<char *> (&temp), sizeof(User));
	}

	inFileStream.close();
}

// Gets the next available id from Users.dat file
void HighScoreManager::setUserId(User& u)
{
	User temp;
	ifstream inFileStream("Users.dat", ios::in | ios::binary);

	// Locate the last record in the file
	//inFileStream.seekg(sizeof(User), ios::end);
	inFileStream.read(reinterpret_cast<char*>(&temp), sizeof(User));

	while (inFileStream && !inFileStream.eof())
	{
		inFileStream.read(reinterpret_cast<char*>(&temp), sizeof(User));
	}

	// Assign the next available id to the new User record 
	// Id is equal to 0 if there are no records in the file
	u.setId(temp.getId() + 1);

	inFileStream.close();
}

//bool HighScoreManager::Record::operator<(const Record& r) const
//{
//	return score > r.score;
//}

//void HighScoreManager::printTopTen()
//{
//	// Counter
//	int counter = 1;
//
//	// Iterator for the records collection
//	it = records.begin();
//
//	// Iterate through the records starting at the beginning 
//	// until top 10 records were printed out
//	while (counter <= 10 && it != records.end())
//	{
//		cout << counter << ". " << (*it).userName << " "
//			<< (*it).getDate() << " " 
//			<< (*it).score << endl;
//		it++;
//		counter++;
//	}
//}
