#include "StartWindow.h"
#include "SignupWindow.h"

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
		CW_USEDEFAULT,CW_USEDEFAULT,600,400,
		NULL,NULL,hInstance,this);

	if (hwnd == NULL) return;

	ShowWindow(hwnd, nCmdShow);

	MSG msg = {};
	while (GetMessage(&msg, NULL, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

}

LRESULT CALLBACK StartWindow::WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    switch (msg) {
    case WM_CREATE: {
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

        break;
    }
    case WM_COMMAND:
        if (LOWORD(wParam) == 1) { // Sign Up Button Clicked
            SignupWindow signupWindow; // Create an instance of SignupWindow
            signupWindow.signWin(GetModuleHandle(NULL), SW_SHOW); // Call the function to open the signup window
        }
        else if (LOWORD(wParam) == 2) { // Sign In Button Clicked
            StartWindow().OpenSignIn(hwnd); // Placeholder for Sign In
        }
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hwnd, msg, wParam, lParam);
    }

    return 0;

}

/* Commenting out OpenSignUp because it is no longer needed
void StartWindow::OpenSignUp(HWND parentHwnd) {
	MessageBoxW(parentHwnd, L"Sign Up Window Functionality Coming Soon", L"Sign Up", MB_OK);
}
*/

void StartWindow::OpenSignIn(HWND parentHwnd) {
	MessageBoxW(parentHwnd, L"Sign In Window Functionality Coming Soon", L"Sign In", MB_OK);
}