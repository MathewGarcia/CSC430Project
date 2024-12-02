#include <iostream>
#include "DatabaseAPI.h"
#include "curl/curl.h"


size_t DatabaseAPI::WriteCallback(void* contents, size_t size, size_t nmemb, std::string* response) {
    size_t totalSize = size * nmemb;
    response->append((char*)contents, totalSize);
    return totalSize;
}

bool DatabaseAPI::UserLoginAuthentication(const string& username, const string& password)
{

    CURL* curl;
    CURLcode res;

    // Supabase API URL for user login
    std::string apiUrl = "https://rpdluwhfxfmlsqfpbouk.supabase.co/rest/v1/rpc/authenticate_user_login";

    // JSON payload for user login
    std::string jsonData = R"({
        "username": ")" + username + R"(",
        "password": ")" + password + R"("
    })";

    // Initialize curl
    curl = curl_easy_init();
    if (curl) {
        std::string responseString;
        struct curl_slist* headers = nullptr;

        // Set HTTP headers
        headers = curl_slist_append(headers, ("apikey: " + apiKey).c_str());
        headers = curl_slist_append(headers, ("Authorization: Bearer " + apiKey).c_str());
        headers = curl_slist_append(headers, "Content-Type: application/json");

        // Set curl options
        curl_easy_setopt(curl, CURLOPT_URL, apiUrl.c_str());
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
        curl_easy_setopt(curl, CURLOPT_POST, 1L);
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, jsonData.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &responseString);

        // Perform the request
        res = curl_easy_perform(curl);
        if (res != CURLE_OK) {
            std::cerr << "curl_easy_perform() failed: " << curl_easy_strerror(res) << std::endl;

            curl_slist_free_all(headers);
            curl_easy_cleanup(curl);
            return false;
        }
        else {
            /*std::cout << "Response from Supabase (Login): " << responseString << std::endl;*/

            curl_slist_free_all(headers);
            curl_easy_cleanup(curl);

            if (responseString == "true")
                return true;
            else
                return false;

        }

    }

}

bool DatabaseAPI::UserSignUp(const string& username, const string& password, const string& email)
{
    CURL* curl;
    CURLcode res;

    // Supabase API URL for inserting new users
    std::string apiUrl = "https://rpdluwhfxfmlsqfpbouk.supabase.co/rest/v1/rpc/user_signup";

    // JSON payload for user sign-up
    std::string jsonData = R"({
        "username": ")" + username + R"(",
        "password": ")" + password + R"(",
		"email": ")" + email + R"("
    })";

    // Initialize curl
    curl = curl_easy_init();
    if (curl) {
        std::string responseString;
        struct curl_slist* headers = nullptr;

        // Set HTTP headers
        headers = curl_slist_append(headers, ("apikey: " + apiKey).c_str());
        headers = curl_slist_append(headers, ("Authorization: Bearer " + apiKey).c_str());
        headers = curl_slist_append(headers, "Content-Type: application/json");

        // Set curl options
        curl_easy_setopt(curl, CURLOPT_URL, apiUrl.c_str());
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
        curl_easy_setopt(curl, CURLOPT_POST, 1L);
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, jsonData.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &responseString);

        // Perform the request
        res = curl_easy_perform(curl);
        if (res != CURLE_OK) {
            std::cerr << "curl_easy_perform() failed: " << curl_easy_strerror(res) << std::endl;

            curl_slist_free_all(headers);
            curl_easy_cleanup(curl);
            return false;
        }
        else {
            /*std::cout << "Response from Supabase (Sign-Up): " << responseString << std::endl;*/

            curl_slist_free_all(headers);
            curl_easy_cleanup(curl);

            if (responseString == "true")
                return true;
            else
                return false;
        }
    }
}
