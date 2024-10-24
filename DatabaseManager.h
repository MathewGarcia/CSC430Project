#pragma once
#include <mysql_driver.h>
#include <mysql_connection.h>
#include <cppconn/prepared_statement.h>
#include <cppconn/resultset.h>
#include <iostream>
#include <string>
#include "USER.h"

using namespace std;



class DatabaseManager 
{
public:
	DatabaseManager();
	~DatabaseManager();

	bool insert_user(USER& u);

	sql::mysql::MySQL_Driver* driver;
	sql::Connection* con;
	sql::PreparedStatement* pstmt;
	sql::ResultSet* res;

private:
	const string Server = "sql5.freesqldatabase.com";
	const string User = "sql5739134";
	const string PW = "pgltBbITZn";
	const string Database_Name = "sql5739134";

};