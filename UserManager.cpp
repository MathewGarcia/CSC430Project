#include "UserManager.h"

void UserManager::signUp() 
{
	string username, email, password, repeatedPW;

	while (1)
	{
		cout << "Enter username: ";
		getline(cin, username);
		cout << "Enter email: ";
		getline(cin, email);

		if (checkUserExists(username, email))
		{
			cout << "Username or email exists already! Try different one." << endl;
			continue;
		}
		break;
	}

	while (1)
	{
		cout << "Enter password: ";
		getline(cin, password);
		cout << "Repeat password: ";
		getline(cin, repeatedPW);

		if (password == repeatedPW)
			break;
		else
			cout << "Passwords do not match. Please try again." << endl;
	}

	USER newUser(username, password, email);

	
	if (!newDBmanager.insert_user(newUser))
		cout << "Problem occured when insert a new user" << endl;
	else
		cout << "Sign up successfully." << endl;

}

bool UserManager::checkUserExists(const string& username, const string& email)
{
	string query = "SELECT * FROM Users WHERE username = ? OR email = ?";

	newDBmanager.pstmt = newDBmanager.con->prepareStatement(query);
	newDBmanager.pstmt->setString(1, username);
	newDBmanager.pstmt->setString(2, email);

	newDBmanager.res = newDBmanager.pstmt->executeQuery();
	if (newDBmanager.res->next())
		return true;

	return false;
}

void UserManager::signIn()
{
	string username, password;

	while (1)
	{
		cout << "Enter username: ";
		getline(cin, username);
		cout << "Enter password: ";
		getline(cin, password);

		string query = "SELECT * FROM Users WHERE username = ? AND password_hash = ?";

		newDBmanager.pstmt = newDBmanager.con->prepareStatement(query);
		newDBmanager.pstmt->setString(1, username);
		newDBmanager.pstmt->setString(2, password);

		newDBmanager.res = newDBmanager.pstmt->executeQuery();

		if (newDBmanager.res->next())
		{
			cout << "Sign-in succeeded" << endl;
			break;
		}
		else
		{
			cout << "Incorrect username or password" << endl;
			continue;
		}

	}
}

