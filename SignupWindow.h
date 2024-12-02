#pragma once
#include <windows.h>
#include "DatabaseManager.h"

class SignupWindow {
public:
    SignupWindow() : hUsername(nullptr), hEmail(nullptr), hPassword(nullptr), hRepeatPassword(nullptr), hSubmitButton(nullptr), hBackButton(nullptr) {} // Constructor

    static LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam); // Processes messages sent to the window
    void signWin(HINSTANCE hInstance, int nCmdShow); // Display window

private:
    HWND hUsername = nullptr, hEmail = nullptr, hPassword = nullptr, hRepeatPassword = nullptr, hSubmitButton = nullptr, hBackButton = nullptr; // Handles for controls
    DatabaseManager dbManager; // To check for duplicate usernames or emails and insert new users

    void handleSignup(HWND hwnd);  // Function to handle signup logic
    void navigateBack(HWND hwnd);  // Function to handle back navigation
};