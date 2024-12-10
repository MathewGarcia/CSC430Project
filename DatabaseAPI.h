#pragma once
#include <string>
#include <cstdint> // Include this for std::uint8_t
#include <curl/curl.h>
using namespace std;

class DatabaseAPI
{
public:
	string UserLoginAuthentication(const string& username, const string& password);
	string UserSignUp(const string& username, const string& password, const string& email);

	// Callback function to capture the response
	static size_t WriteCallback(void* contents, size_t size, size_t nmemb, std::string* response);

private:
	const string apiKey = "eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9.eyJpc3MiOiJzdXBhYmFzZSIsInJlZiI6InJwZGx1d2hmeGZtbHNxZnBib3VrIiwicm9sZSI6ImFub24iLCJpYXQiOjE3MzE5OTAwMDksImV4cCI6MjA0NzU2NjAwOX0.AbjEaGCgHtLReH_rO_XTerk-EgwrDcBZpisov061Sfs";
};
