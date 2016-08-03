#include "HighScoreManager.h"
#include <iostream>
#include <iomanip>
#include <sstream>

using namespace std;
using namespace HighScoreManager;

void printMenu();
void printOptions();
void getCredentials(User&);
int validateAnswer(int);

int main()
{
	int menuChoice;
	string userName, password;
	bool exitMenu = false;
	User u;

	// 1st level menu
	while (!exitMenu)
	{
		// The program starts and User sees the main menu with 3 options
		// 1 - login, 2 - register and 0 - exit
		printMenu();
		menuChoice = validateAnswer(2);

		switch (menuChoice)
		{
			// User selects the 1st option and is logged into the system
			case 1:
				getCredentials(u);
				login(u);

				if (u.isAuthenticated())
				{
					cout << "You are now logged in" << endl;
					bool exitOptions = false;

					// 2nd level menu
					while (!exitOptions && u.isAuthenticated())
					{
						printOptions();
						menuChoice = validateAnswer(3);

						switch (menuChoice)
						{
							case 1:
								break;
							case 2:
								break;
							case 3:
								deleteProfile(u);
								exitOptions = true;
								break;
							case 0:
								logout(u);
								exitOptions = true;
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
			// User selects the 2nd option and is registered in the system
			case 2:
				getCredentials(u);
				saveUser(u, true);
				cout << "You can now login using your User Name and Password" 
					<< endl;
				break;
			case 0:
				exitMenu = true;
				break;
		}
	}
	
	return 0;
}

void printMenu()
{
	cout << endl 
		<< "   "
		<< "1 - Login | 2 - Register | 0 - Exit" 
		<< endl 
		<< endl;
}

void printOptions()
{
	cout << endl
		<< "   "
		<< "1 - Display TOP 10 scores | " 
		<< "2 - Edit Profile | "
		<< "3 - Delete Profile | "
		<< "0 - Exit" 
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
	for (int i = 1; i <= range; i++)
	{
		errMsg += to_string(i);
		errMsg += i < range ? ", " : " or 0 to exit: ";
	}

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