#include "DatabaseManager.h"

DatabaseManager::DatabaseManager() : pstmt(nullptr), res(nullptr) // Initialize pstmt and res to nullptr
{
	//Initialize MySQL Driver
	driver = sql::mysql::get_mysql_driver_instance();

	//Connect to the database
	try {
		con = driver->connect(Server, User, PW);
	}
	catch (sql::SQLException& e) {
		std::cerr << "SQLException: " << e.what() << std::endl;
		std::cerr << "MySQL error code: " << e.getErrorCode() << std::endl;
		std::cerr << "SQLState: " << e.getSQLState() << std::endl;
	}

	//Choose the database we will use
	con->setSchema(Database_Name);

}


DatabaseManager::~DatabaseManager()
{
	if (con != nullptr)
	{
		delete con;
		con = nullptr;
	}
}


bool DatabaseManager::insert_user(USER& u)
{
	string SqlQuery = "INSERT INTO Users (username, password_hash, email) VALUES (?, ?, ?)";

	pstmt = con->prepareStatement(SqlQuery);

	pstmt->setString(1, u.username);
	pstmt->setString(2, u.password);
	pstmt->setString(3, u.email);

	//pstmt->executeUpdate() returns an int representing the number of affected rows
	if (pstmt->executeUpdate() == 1)
	{
		delete pstmt;
		return true;
	}
		
	else
		return false;
}