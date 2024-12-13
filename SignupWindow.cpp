#include "SignupWindow.h"
#include <string>
#include "USER.h"
#include "UserManager.h"

using namespace std;

// Function to create and display the signup window
void SignupWindow::signWin(HINSTANCE hInstance, int nCmdShow) {
    const wchar_t CLASS_NAME[] = L"SignupWindow";

    WNDCLASS wc = { 0 };
    wc.lpfnWndProc = SignupWindow::WndProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = CLASS_NAME;
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1); // Sets the background to the default window color
    RegisterClassW(&wc);
    //added new styles to fix resizing issues
    HWND hwnd = CreateWindowExW(
     0, CLASS_NAME,
     L"Sign Up",
     WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX,  // Disable resizing and maximizing
     CW_USEDEFAULT, CW_USEDEFAULT, 600, 400,
     NULL, NULL, hInstance, this);
    if (hwnd == NULL) return;

    ShowWindow(hwnd, nCmdShow);

    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
}


// Window procedure for handling messages sent to the signup window
LRESULT CALLBACK SignupWindow::WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    SignupWindow* pThis = nullptr; // Pointer to the current instance of SignupWindow

    if (msg == WM_CREATE) { // If the window is being created   
        pThis = (SignupWindow*)((LPCREATESTRUCT)lParam)->lpCreateParams; // Retrieve the pointer to the SignupWindow instance from the window creation parameters
        SetWindowLongPtr(hwnd, GWLP_USERDATA, (LONG_PTR)pThis); // Store the pointer in the window's user data

        // Helper lambda to set up label and textbox pairs to reduce boilerplate code
        auto createControl = [&](LPCWSTR label, int y, HWND& editHandle) {
            CreateWindowW(L"STATIC", label, WS_VISIBLE | WS_CHILD, 50, y, 120, 20, hwnd, NULL, NULL, NULL);
            editHandle = CreateWindowW(L"EDIT", L"", WS_VISIBLE | WS_CHILD | WS_BORDER, 180, y, 200, 20, hwnd, NULL, NULL, NULL);
            };

        // Creating controls using the helper lambda
        createControl(L"Username:", 50, pThis->hUsername);
        createControl(L"Email:", 90, pThis->hEmail);
        createControl(L"Password:", 130, pThis->hPassword);
        SendMessage(pThis->hPassword, EM_SETPASSWORDCHAR, (WPARAM)L'*', 0);  // Hide password characters
        createControl(L"Repeat Password:", 170, pThis->hRepeatPassword);
        SendMessage(pThis->hRepeatPassword, EM_SETPASSWORDCHAR, (WPARAM)L'*', 0);  // Hide password characters

        // Create Submit and Back Buttons
        pThis->hSubmitButton = CreateWindowW(L"BUTTON", L"Submit", WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON, 50, 220, 100, 30, hwnd, (HMENU)1, NULL, NULL);
        pThis->hBackButton = CreateWindowW(L"BUTTON", L"Back", WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON, 200, 220, 100, 30, hwnd, (HMENU)2, NULL, NULL);
    }
    else {
        pThis = (SignupWindow*)GetWindowLongPtr(hwnd, GWLP_USERDATA);
    }

    switch (msg) {
    case WM_CTLCOLORSTATIC: { // Set text color and background for static controls(eg. username, email, password, repeat password)
        HDC hdcStatic = (HDC)wParam;
        SetBkMode(hdcStatic, TRANSPARENT);  // Make label background transparent
        SetTextColor(hdcStatic, RGB(0, 0, 0));  // Set text color to black for readability
        return (INT_PTR)GetStockObject(NULL_BRUSH);
    }
    case WM_COMMAND:
        if (LOWORD(wParam) == 1) pThis->handleSignup(hwnd); // Submit button clicked then handle signup
        else if (LOWORD(wParam) == 2) pThis->navigateBack(hwnd); // Back button clicked then navigate back
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hwnd, msg, wParam, lParam);
    }
    return 0;
}


// Function to handle the signup process when the submit button is clicked
void SignupWindow::handleSignup(HWND hwnd) {
    // Retrieve text from input fields
    wchar_t username[100], email[100], password[100], repeatPassword[100];
    GetWindowTextW(hUsername, username, 100);
    GetWindowTextW(hEmail, email, 100);
    GetWindowTextW(hPassword, password, 100);
    GetWindowTextW(hRepeatPassword, repeatPassword, 100);

    // Convert wchar_t to string
    std::string sUsername(username, username + wcslen(username));
    std::string sEmail(email, email + wcslen(email));
    std::string sPassword(password, password + wcslen(password));
    std::string sRepeatPassword(repeatPassword, repeatPassword + wcslen(repeatPassword));

    // Check for empty fields
    if (sUsername.empty() || sEmail.empty() || sPassword.empty() || sRepeatPassword.empty()) {
        MessageBoxW(hwnd, L"All fields are required!", L"Error", MB_OK | MB_ICONERROR);
        return;
    }

    // Check if passwords match
    if (sPassword != sRepeatPassword) {
        MessageBoxW(hwnd, L"Passwords do not match. Please re-enter!", L"Error", MB_OK | MB_ICONERROR);
        return;
    }

    // Check if the password meets minimum requirements
    if (sPassword.length() < 6) {
        MessageBoxW(hwnd, L"Password must be at least 6 characters long.", L"Error", MB_OK | MB_ICONERROR);
        return;
    }

    // Delegate the sign-up process to UserManager
    //UserManager userManager;

    DatabaseAPI dbAPI;
    try {
        // Call UserSignUp once and store the result
        std::string rawResult = dbAPI.UserSignUp(sUsername, sPassword, sEmail);

        // Strip quotes from the response
        std::string result = rawResult;
        if (!rawResult.empty() && rawResult.front() == '"' && rawResult.back() == '"') {
            result = rawResult.substr(1, rawResult.size() - 2);
        }

        if (result == "success") {
            MessageBoxW(hwnd, L"Sign-up successful!", L"Success", MB_OK | MB_ICONINFORMATION);
            navigateBack(hwnd); // Navigate back to startup page
        }
        else if (result == "exist") {
            MessageBoxW(hwnd, L"Username or email already exists. Please try a different one.", L"Error", MB_OK | MB_ICONERROR);
        }
        else if (result == "error") {
            MessageBoxW(hwnd, L"An unexpected error occurred. Please try again later.", L"Error", MB_OK | MB_ICONERROR);
        }
        else {
            MessageBoxW(hwnd, L"Unknown response from server.", L"Error", MB_OK | MB_ICONERROR);
        }
    }
    catch (std::exception& e) {
        // Handle generic exceptions from the sign-up process
        std::wstring errorMsg = L"An error occurred during sign-up: ";
        errorMsg += std::wstring(e.what(), e.what() + strlen(e.what()));
        MessageBoxW(hwnd, errorMsg.c_str(), L"Error", MB_OK | MB_ICONERROR);
    }
}


// Function to navigate back to the startup window
void SignupWindow::navigateBack(HWND hwnd) {
    DestroyWindow(hwnd);  // Close the signup window and return to the startup window
}
