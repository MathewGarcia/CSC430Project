#pragma once
#include <string>

using namespace std;

struct USER
{
	string username;
	string password;
	string email;

	USER(const string& uname, const string& pwd, const string& mail)
		: username(uname), password(pwd), email(mail) {}
};