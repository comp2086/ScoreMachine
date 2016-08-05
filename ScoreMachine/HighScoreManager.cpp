#include "HighScoreManager.h"
#include <fstream>
#include <iostream>
#include <iomanip>

using namespace std;

// Gets the next available id from Users.dat file
void HighScoreManager::setUserId(User& u)
{
	User temp;
	bool exists = false;
	ifstream inFileStream("Users.dat", ios::in | ios::binary);

	/*
	For some reason, it doesn't recognize a user object
	if i start from the end - offset of User size
	*/
	//inFileStream.seekg(sizeof(User), ios::end);

	// Locate the last record in the file
	inFileStream.read(reinterpret_cast<char*>(&temp), sizeof(User));

	while (inFileStream && !inFileStream.eof() && !exists)
	{
		// If a username exists, do not assign id
		if (temp.getUserName() == u.getUserName()) exists = true;
		inFileStream.read(reinterpret_cast<char*>(&temp), sizeof(User));
	}

	// Assign the next available id to the new User record 
	// Id is equal to 0 (empty User object if there are no records in the file)
	if (!exists) u.setId(temp.getId() + 1);

	inFileStream.close();
}

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
		
		// If a username available, create a new user
		if (u.getId() != 0)
		{
			// Starting to write from 0th position
			outFileStream.seekp((u.getId() - 1) * sizeof(User));
			outFileStream.write(reinterpret_cast<const char*>(&u), sizeof(User));
		}
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
			u.setScore(temp.getScore());
			u.setDate(temp.getDate());
			u.toggleAuth();
			break;
		}

		inFileStream.read(reinterpret_cast<char *> (&temp), sizeof(User));
	}

	inFileStream.close();
}

void HighScoreManager::logout(User& u)
{
	// Clear all fields
	u.setId(-1);
	u.setUserName("");
	u.setPassword("");
	u.setScore(0);
	u.setDate("");
	u.toggleAuth();
}

// This method handles edit/delete profile functionality
void HighScoreManager::editProfile(User& u, bool del)
{
	User tempUser;
	ifstream inFileStream;
	ofstream outFileStream;

	inFileStream.open(users, ios::in | ios::binary);
	outFileStream.open("temp.dat", ios::out | ios::binary);

	if (!inFileStream || !outFileStream)
	{
		cerr << "Users file couldn't be open";
		exit(EXIT_FAILURE);
	}

	// Copy everything but the record we want to delete into a temporary file
	inFileStream.read(reinterpret_cast<char *> (&tempUser), sizeof(User));
	while (inFileStream && !inFileStream.eof())
	{
		if (!(tempUser.getId() == u.getId()))
		{
			outFileStream.write(reinterpret_cast<const char *> (&tempUser), sizeof(User));
		}
		else if (!del)
		{
			outFileStream.write(reinterpret_cast<const char *> (&u), sizeof(User));
		}

		inFileStream.read(reinterpret_cast<char *> (&tempUser), sizeof(User));
	}

	// Write back to the original file
	inFileStream.close();
	outFileStream.close();
	inFileStream.open("temp.dat", ios::in | ios::binary);
	outFileStream.open(users, ios::out | ios::binary);

	inFileStream.read(reinterpret_cast<char *> (&tempUser), sizeof(User));
	while (inFileStream && !inFileStream.eof())
	{
		outFileStream.write(reinterpret_cast<const char *> (&tempUser), sizeof(User));
		inFileStream.read(reinterpret_cast<char *> (&tempUser), sizeof(User));
	}

	outFileStream.close();
	inFileStream.close();

	// Delete temporary file
	remove("temp.dat");
}

bool HighScoreManager::userNameAvailable(const string& userName)
{
	User temp;
	ifstream inFileStream("Users.dat", ios::in | ios::binary);

	inFileStream.read(reinterpret_cast<char*>(&temp), sizeof(User));

	while (inFileStream && !inFileStream.eof())
	{
		// If a username exists, do not assign id
		if (temp.getUserName() == userName)
		{
			inFileStream.close();
			return false;
		}
		inFileStream.read(reinterpret_cast<char*>(&temp), sizeof(User));
	}

	inFileStream.close();
	return true;
}

void HighScoreManager::printTopTen()
{
	// Counter
	int counter = 0;
	User tempUser;
	ifstream inFileStream("Users.dat", ios::in | ios::binary);

	// Array to hold top 10
	User topTen[10];
	
	inFileStream.read(reinterpret_cast<char *> (&tempUser), sizeof(User));
	
	while (inFileStream && inFileStream.good())
	{
		// Just add a User record if it's empty
		if (counter < 10)
		{
			topTen[counter] = tempUser;
			counter++;
		}
		else
		{
			// Store a record only if it's larger 
			// than the last(and the smallest) element
			if (tempUser > topTen[counter - 1]) topTen[counter - 1] = tempUser;
		}

		// Sort
		for (int i = counter - 1; i > 0; i--)
		{
			if (topTen[i] > topTen[i - 1])
			{
				topTen[i] = topTen[i - 1];
				topTen[i - 1] = tempUser;
			}
			else break;
		}

		inFileStream.read(reinterpret_cast<char *> (&tempUser), sizeof(User));
	}

	// Print it all out
	cout << endl
		<< left
		<< setw(9) << "Ranking"
		<< setw(15) << "User Name"
		<< setw(30) << "Date" 
		<< right << setw(7) << "Score" << endl;

	for (int i = 0; i < counter; i++)
	{
		// Dont print out empty User objects
		// that get created when declaring an array
		if (topTen[i].getId() != 0)
			cout << left << setw(9) << to_string(i + 1) + "."
			<< setw(15) << topTen[i].getUserName()
			<< setw(30) << topTen[i].getDate()
			<< right << setw(7) << setprecision(4) << topTen[i].getScore()
			<< endl;
	}
}
