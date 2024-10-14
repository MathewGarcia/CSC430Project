// CSC430Project.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

#include "Bot.h"

using namespace std;

int main()
{

	UserStates currentState = none;

	Bot* bot = new Bot(currentState);
	
	string input;
	cout << "Welcome to File Bot! Please enter a command to get started." << endl;
	while(getline(cin,input))
	{
		string result = bot->Listen(input);
		cout << result << endl;
	}

	delete bot;
	return 0;
}

