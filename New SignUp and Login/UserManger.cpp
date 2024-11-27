#define CURL_STATICLIB

#include "UserManager.h"
#include <iostream>
#include <string>
#include "DatabaseAPI.h"



using namespace std;

void UserManager::signIn()
{
	string username, password;

	while (1)
	{
		cout << "Enter username: ";
		getline(cin, username);
		cout << "Enter password: ";
		getline(cin, password);

		DatabaseAPI NewAPI;
		if (NewAPI.UserLoginAuthentication(username, password) == true)
		{
			cout << "Login Success!" << endl;
			break;
		}
		else
		{
			cout << "Login Fail!" << endl;
			continue;
		}
			
		

	}
}


void UserManager::signUp()
{
	string username, password, email;

	while (1)
	{
		cout << "Enter new username: ";
		getline(cin, username);
		cout << "Enter new password: ";
		getline(cin, password);
		cout << "Enter new email: ";
		getline(cin, email);

		DatabaseAPI NewAPI;
		if (NewAPI.UserSignUp(username, password, email) == true)
		{
			cout << "SignUp Success!" << endl;
			break;
		}
		else
		{
			cout << "SignUp Fail!" << endl;
			continue;
		}



	}
}
