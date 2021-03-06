#include "HighScoreManager.h"
#include <iostream>
#include <iomanip>
#include <sstream>

using namespace std;
using namespace HighScoreManager;

void printMenu();
void printOptions();
void printEditOptions();
void getCredentials(User&);
int validateAnswer(int);
void validateScore(string&);
void validateDateFields(string&, int, int);

int main()
{
	int menuChoice = -1;
	string userName, password;
	bool exitMenu1 = false, exitMenu2 = false, exitMenu3 = false;
	User currentUser;

	// 1st level menu
	while (!exitMenu1)
	{
		exitMenu2 = false;
		printMenu();
		menuChoice = validateAnswer(2);

		switch (menuChoice)
		{
			// Login
			case 1:
				getCredentials(currentUser);
				login(currentUser);

				if (currentUser.isAuthenticated())
				{
					cout << "You are now logged in" << endl;

					// 2nd level menu
					while (!exitMenu2)
					{
						exitMenu3 = false;
						printOptions();
						menuChoice = validateAnswer(4);
						string newProfileFields[6];

						switch (menuChoice)
						{
							// Top 10 scores
							case 1:
								printTopTen();
								break;
							// Display profile info
							case 2:
								cout << endl;
								cout << "   Your current profile" << endl;
								cout << "   User Name: " << currentUser.getUserName() << " | ";
								cout << "Password: " << currentUser.getPassword() << " | ";
								cout << "Score: " << currentUser.getScore() << " | ";
								cout << "Date: " << currentUser.getDate() << endl;
								break;
							// Edit user profile
							case 3:
								while (!exitMenu3)
								{
									printEditOptions();
									menuChoice = validateAnswer(5);

									switch (menuChoice)
									{
									case 1:
										cout << "New User Name (max 15 chars): ";
										getline(cin, newProfileFields[0]);
										while (!userNameAvailable(newProfileFields[0]))
										{
											cout << "This User Name has already been taken, enter a new one: ";
											getline(cin, newProfileFields[0]);
										}
										break;
									case 2:
										cout << "New Password (max 15 chars): ";
										getline(cin, newProfileFields[1]);
										break;
									case 3:
										cout << "New Score [1 - 100]: ";
										validateScore(newProfileFields[2]);
										break;
									case 4:
										cout << "New Year [2010 - 2050]: ";
										validateDateFields(newProfileFields[3], 2010, 2050);
										cout << "New Month [1 - 12]: " ;
										validateDateFields(newProfileFields[4], 1, 12);
										cout << "New Day [1 - 31]: ";
										validateDateFields(newProfileFields[5], 1, 31);
										break;
									case 5:
										cout << "Your changes have been saved" 
											<< endl;
										if (newProfileFields[0].length() > 0)
											currentUser.setUserName(newProfileFields[0]);
										if (newProfileFields[1].length() > 0)
											currentUser.setPassword(newProfileFields[1]);
										if (newProfileFields[2].length() > 0)
											currentUser.setScore(newProfileFields[2]);
										if (newProfileFields[3].length() > 0)
											currentUser.setDate(stoi(newProfileFields[3]),
												stoi(newProfileFields[4]),
												stoi(newProfileFields[5]));
										editProfile(currentUser, false);
										exitMenu3 = true;
										break;
									case 0:
										exitMenu3 = true;
										break;
									}
								}
								break;
							case 4:
								cout << "Are you sure? 1 - yes, 0 - exit" 
									<< endl;
								menuChoice = validateAnswer(1);
								if (menuChoice == 1)
								{
									editProfile(currentUser, true);
									logout(currentUser);
									exitMenu2 = true;
								}
								break;
							case 0:
								logout(currentUser);
								exitMenu2 = true;
								break;
						}
					}
				}
				else
				{
					cout << "Incorrect User Name and/or Password" 
						<< endl;
				}
				break;
			// Register
			case 2:
				getCredentials(currentUser);
				saveUser(currentUser, true);
				if (currentUser.getId() == 0)
					cout << "This User Name has already been taken, try a different one" << endl;
				else
					cout << "You can now login using your User Name and Password" << endl;
				break;
			case 0:
				exitMenu1 = true;
				break;
		}
	}
	
	return 0;
}

void printMenu()
{
	cout << endl 
		<< "   1 - Login | 2 - Register | 0 - Exit" 
		<< endl 
		<< endl;
}

void printOptions()
{
	cout << endl
		<< "   1 - Display TOP 10 scores | " 
		<< "2 - View Profile | "
		<< "3 - Edit Profile | "
		<< "4 - Delete Profile | "
		<< "0 - Logout" 
		<< endl
		<< endl;
}

void printEditOptions()
{
	cout << endl
		<< "   Choose what to edit"
		<< endl
		<< "   1 - User Name | "
		<< "2 - Password | "
		<< "3 - Score | "
		<< "4 - Date"
		<< endl
		<< "   5 - Save Changes | "
		<< "0 - Discard Changes"
		<< endl
		<< endl;
}

// Prompts to enter username/password
void getCredentials(User& u)
{
	string userName, password;

	cout << "User Name: ";
	getline(cin, userName);
	cout << "Password: ";
	getline(cin, password);
	u.setUserName(userName);
	u.setPassword(password);
}

int validateAnswer(int range)
{
	int answer = -1;
	string userInput = "";
	string errMsg = "Invalid input, please enter ";

		errMsg += "1 - " + to_string(range) + " or 0 to Exit: ";

	cout << "Your choice: ";
	while (getline(cin, userInput))
	{
		stringstream strStream(userInput);
		if (!(strStream >> answer))
		{
			// Parse error
			cout << errMsg;
			continue;
		}

		if ((answer > range) || (answer < 0))
		{
			cout << errMsg;
			continue;
		}
		char badChar;
		if (strStream >> badChar)
		{
			// If there was something after the number, e.g 2a
			cout << errMsg;
			continue;
		}

		// Input validated, quit the loop
		break;
	}

	return answer;
}

void validateScore(string& newDateField)
{
	double answer;
	string userInput;
	string errMsg = "Please enter a value in range [0 - 100]: ";

	while (getline(cin, userInput))
	{
		stringstream strStream(userInput);
		if (!(strStream >> answer))
		{
			cout << errMsg;
			continue;
		}

		if ((answer > 100) || (answer < 0))
		{
			cout << errMsg;
			continue;
		}
		char badChar;
		if (strStream >> badChar)
		{
			// If there was something after the number, e.g 2a
			cout << errMsg;
			continue;
		}

		// Input validated, quit the loop
		break;
	}

	newDateField = to_string(answer) ;
}

void validateDateFields(string& newDateField, int low, int high)
{
	int answer;
	string userInput;
	string errMsg = "Please enter a value in range [" 
		+ to_string(low) + " - " + to_string(high) + "]: ";

	while (getline(cin, userInput))
	{
		stringstream strStream(userInput);
		if (!(strStream >> answer))
		{
			cout << errMsg;
			continue;
		}

		if ((answer > high) || (answer < low))
		{
			cout << errMsg;
			continue;
		}
		char badChar;
		if (strStream >> badChar)
		{
			// If there was something after the number, e.g 2a
			cout << errMsg;
			continue;
		}

		// Input validated, quit the loop
		break;
	}

	newDateField = userInput;
}