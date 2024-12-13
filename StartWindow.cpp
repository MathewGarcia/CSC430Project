#include "StartWindow.h"

#include <codecvt>
#include <locale>
#include <memory>

#include "SignupWindow.h"
#include "BotWindow.h"

void StartWindow::startWin(HINSTANCE hInstance, int nCmdShow) {
    const wchar_t CLASS_NAME[] = L"StartWindow";

    WNDCLASS wc = {};

    wc.lpfnWndProc = StartWindow::WndProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = CLASS_NAME;
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1); // Sets the background to the default window color
    RegisterClassW(&wc);

    HWND hwnd = CreateWindowExW(
        0, CLASS_NAME,
        L"SignUp/SignIn",
        WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN | WS_CLIPSIBLINGS | WS_THICKFRAME,
        CW_USEDEFAULT, CW_USEDEFAULT, 600, 400,
        NULL, NULL, hInstance, this);

    if (hwnd == NULL) return;

    ShowWindow(hwnd, nCmdShow);

    MSG msg = {};
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

}

LRESULT CALLBACK StartWindow::WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {

    static int currentScreen = 0;
    static HWND hUsernameEditText = nullptr;
    static HWND hPasswordEditText = nullptr;
    StartWindow* pThis = nullptr;
    if (msg == WM_NCCREATE) {
        CREATESTRUCT* pCreate = reinterpret_cast<CREATESTRUCT*>(lParam);
        pThis = reinterpret_cast<StartWindow*>(pCreate->lpCreateParams);
        SetWindowLongPtr(hwnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(pThis));
    }
    else {
        pThis = reinterpret_cast<StartWindow*>(GetWindowLongPtr(hwnd, GWLP_USERDATA));
    }
    if (pThis) {
        switch (msg) {
        case WM_CREATE: {

            BeginningButtons(hwnd);

            break;
        }
        case WM_COMMAND:

            switch (LOWORD(wParam))
            {
            case 1:
            {
                SignupWindow signupWindow; // Create an instance of SignupWindow
                signupWindow.signWin(GetModuleHandle(NULL), SW_SHOW); // Call the function to open the signup window
                currentScreen = 1;
                break;
            }
            case 2:
            {
                currentScreen = 2;
                InvalidateRect(hwnd, NULL, TRUE);
                OpenSignIn(hwnd, hUsernameEditText, hPasswordEditText);
                break;
            }
            case 4:
            {
                wchar_t username[256];
                wchar_t password[256];
                if (hUsernameEditText && hPasswordEditText)
                {


                    GetWindowTextW(hUsernameEditText, username, 256);
                    GetWindowTextW(hPasswordEditText, password, 256);

                }

                string SUsername = wcharToString(username);
                string SPassword = wcharToString(password);
                std::unique_ptr<DatabaseAPI> dbapi = make_unique<DatabaseAPI>();

                OutputDebugStringA(SUsername.c_str());

                OutputDebugStringA(SPassword.c_str());

                string response = dbapi->UserLoginAuthentication(SUsername, SPassword);


                if (response == "\"success\"")
                {


                    pThis->LoggedIn = true;
                    DestroyWindow(hwnd);

                    BotWindow botWindow;
                    botWindow.startBotWindow(GetModuleHandle(NULL), SW_SHOW);

                }
                else if (response == "\"incorrect\"")
                {
                    MessageBoxW(NULL, L"Username or Password incorrect!", L"Error", MB_OK);

                }
                else
                {
                    MessageBoxW(NULL, L"Unexpected Error! Please try again later.", L"Error", MB_OK);
                }

                OutputDebugStringA(response.c_str());

                break;
            }
            case 5:
            {

                currentScreen = 0;
                InvalidateRect(hwnd, NULL, TRUE);
                ClearChildren(hwnd);

                BeginningButtons(hwnd);
                break;
            }
            }
            break;
        case WM_DESTROY:
            PostQuitMessage(0);
            break;
        case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hwnd, &ps);

            if (currentScreen == 2)
            {
                TextOutW(hdc, 50, 10, L"Sign In Screen", 20);
            }
            EndPaint(hwnd, &ps);
            break;
        }
        default:
            return DefWindowProc(hwnd, msg, wParam, lParam);
        }
    }
    return 0;

}

/* Commenting out OpenSignUp because it is no longer needed
void StartWindow::OpenSignUp(HWND parentHwnd) {
    MessageBoxW(parentHwnd, L"Sign Up Window Functionality Coming Soon", L"Sign Up", MB_OK);
}
*/

void StartWindow::ClearChildren(HWND hwnd)
{
    HWND child = GetWindow(hwnd, GW_CHILD);
    while (child)
    {
        DestroyWindow(child);
        child = GetWindow(hwnd, GW_CHILD);
    }
}

void StartWindow::OpenSignIn(HWND parentHwnd, HWND& hUsernameEditText, HWND& hPasswordEditText) {
    ClearChildren(parentHwnd);
    hUsernameEditText = CreateWindowW(L"EDIT", L"Username",
        WS_TABSTOP | WS_VISIBLE | WS_CHILD | WS_BORDER,
        50, 50, 200, 25,
        parentHwnd, NULL, NULL, NULL);
    hPasswordEditText = CreateWindowW(L"EDIT", L"Password",
        WS_TABSTOP | WS_VISIBLE | WS_CHILD | WS_BORDER,
        50, 90, 200, 25,
        parentHwnd, NULL, NULL, NULL);
    CreateWindowW(L"BUTTON", L"Submit",
        WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
        50, 130, 100, 30,
        parentHwnd, (HMENU)4, NULL, NULL);
    CreateWindowW(L"BUTTON", L"Back",
        WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
        200, 130, 100, 30,
        parentHwnd, (HMENU)5, NULL, NULL);
}

void StartWindow::BeginningButtons(HWND hwnd)
{
    //SignUp Button
    CreateWindowW(L"BUTTON", L"Sign Up",
        WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
        50, 50, 100, 30,
        hwnd, (HMENU)1, NULL, NULL);
    //SignIn Button
    CreateWindowW(L"BUTTON", L"Sign In",
        WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
        200, 50, 100, 30,
        hwnd, (HMENU)2, NULL, NULL); // Changed identifier to 2 for Sign In button
}

string StartWindow::wcharToString(const wchar_t* wstr)
{
    if (!wstr) return "";

    std::wstring_convert<codecvt_utf8<wchar_t>> converter;
    return converter.to_bytes(wstr);
}

void StartWindow::updateLoggedIn(bool& loggedin, bool newState)
{
    loggedin = newState;
}
