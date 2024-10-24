#pragma once
#include "USER.h"
#include "DatabaseManager.h"

using namespace std;

class UserManager
{
public:
	void signUp();
	void signIn();

private:
	DatabaseManager newDBmanager;
	bool checkUserExists(const string& username, const string& email);
};