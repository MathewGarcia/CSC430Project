
// CSC430Project.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

#include "Bot.h"
#include "UserManager.h"

using namespace std;

int main()
{
	while (1)
	{

		cout << "Welcome to File Bot! Please register or log in with an existing account." << endl;
		cout << "1.Sign Up" << endl;
		cout << "2.Sign In" << endl;

		int userChoice;
		cin >> userChoice;
		cin.ignore();

		UserManager newUserManager;
		switch (userChoice)
		{
		case 1:
			newUserManager.signUp();
			continue;
		case 2:
			newUserManager.signIn();

			UserStates currentState = none;

			Bot* bot = new Bot(currentState);

			string input;
			cout << "Please enter a command to get started." << endl;
			while (getline(cin, input))
			{
				string result = bot->Listen(input);
				cout << result << endl;
			}

			delete bot;
			break;
		}
	}
	
	return 0;

}
