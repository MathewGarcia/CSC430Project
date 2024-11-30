#include "SignupWindow.h"

void SignupWindow::signWin(HINSTANCE hInstance, int nCmdShow) {
	const wchar_t CLASS_NAME[] = L"SignupWindow";

	WNDCLASS wc = {};

	wc.lpfnWndProc = SignupWindow::WndProc;
	wc.hInstance = hInstance;
	wc.lpszClassName = CLASS_NAME;

	RegisterClassW(&wc);

	HWND hwnd = CreateWindowExW(
		0, CLASS_NAME,
		L"SignUp/SignIn",
		WS_OVERLAPPEDWINDOW, 
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

LRESULT CALLBACK SignupWindow::WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
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
			hwnd, (HMENU)1, NULL, NULL);

		break;
	}
	case WM_COMMAND:
		if (LOWORD(wParam) == 1) {
			SignupWindow().OpenSignUp(hwnd);
		}
		else if (LOWORD(wParam) == 2) {
			SignupWindow().OpenSignIn(hwnd);
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

void SignupWindow::OpenSignUp(HWND parentHwnd) {
	MessageBoxW(parentHwnd, L"Sign Up Window Functionality Coming Soon", L"Sign Up", MB_OK);
}

void SignupWindow::OpenSignIn(HWND parentHwnd) {
	MessageBoxW(parentHwnd, L"Sign In Window Functionality Coming Soon", L"Sign In", MB_OK);
}