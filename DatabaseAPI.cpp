#include <iostream>
#include <curl/curl.h>
#include "DatabaseAPI.h"

size_t DatabaseAPI::WriteCallback(void* contents, size_t size, size_t nmemb, std::string* response) {
    size_t totalSize = size * nmemb;
    response->append((char*)contents, totalSize);
    return totalSize;
}

bool DatabaseAPI::UserLoginAuthentication(const std::string& username, const std::string& password) {
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
        } else {
            /*std::cout << "Response from Supabase (Login): " << responseString << std::endl;*/

            curl_slist_free_all(headers);
            curl_easy_cleanup(curl);

            if (responseString == "true")
                return true;
            else
                return false;
        }
    } else {
        std::cerr << "Failed to initialize CURL." << std::endl;
        return false;
    }
}

bool DatabaseAPI::UserSignUp(const std::string& username, const std::string& password, const std::string& email) {
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

    // Debug: Log the JSON payload(used to identify the insert user bug)
    // std::wstring debugPayload = L"Constructed JSON Payload: " + std::wstring(jsonData.begin(), jsonData.end());
    // MessageBoxW(NULL, debugPayload.c_str(), L"Debug - JSON Payload", MB_OK);

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

        // Enable verbose output for debugging(used to identify the insert user bug)
        // curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);

        // Perform the request
        res = curl_easy_perform(curl);
        if (res != CURLE_OK) {
            // Debug: Log CURL errors(used to identify the insert user bug)
            // std::wstring curlError = L"CURL Error: " + std::wstring(curl_easy_strerror(res), curl_easy_strerror(res) + strlen(curl_easy_strerror(res)));
            // MessageBoxW(NULL, curlError.c_str(), L"Debug - CURL Error", MB_OK);

            curl_slist_free_all(headers);
            curl_easy_cleanup(curl);
            return false;
        }
        else {
            // Debug: Log the API response(used to identify the insert user bug)
            // std::wstring debugResponse = L"API Response: " + std::wstring(responseString.begin(), responseString.end());
            // MessageBoxW(NULL, debugResponse.c_str(), L"Debug - API Response", MB_OK);

            curl_slist_free_all(headers);
            curl_easy_cleanup(curl);

            // Analyze the response
            long http_code = 0;
            curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &http_code);
            return (http_code == 200);
        }
    }
    else {
        // MessageBoxW(NULL, L"Failed to initialize CURL.", L"Error - CURL Init", MB_OK | MB_ICONERROR);(used to identify the insert user bug)
        std::cerr << "Failed to initialize CURL." << std::endl;
    }
    return false;  // Fallback if curl initialization fails
}
