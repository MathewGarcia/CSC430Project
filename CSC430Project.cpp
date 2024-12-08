
// CSC430Project.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
 //Hello S.V
#include <iostream>

#include "Bot.h"
#include "UserManager.h"


using namespace std;

int main()
{
	while (1)
	{

		cout << "Welcome to File Bot! Please choose an option to get started." << endl;
		cout << "Press 1 to Sign Up (Create a new account)" << endl;
		cout << "Press 2 to Sign In (Log in with an existing account)" << endl;

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
			cout << "Please enter a command to get started.(Available Commands: /find)" << endl;
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
