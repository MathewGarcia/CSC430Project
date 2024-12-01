#pragma once
#include "USER.h"
#include "DatabaseManager.h"

using namespace std;

class UserManager
{
public:
    void signUp();
    void signIn();
    bool checkUserExists(const string& username, const string& email); // Moved to public section

private:
    DatabaseManager newDBmanager;
};