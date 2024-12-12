#pragma once
#include <windows.h>
#include <string>
#include "DatabaseAPI.h"


class StartWindow {
public:

	static LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);//processes messages sent to the window
	void startWin(HINSTANCE hInstance,int nCmdShow);//Display window

private:
	HWND hSignUp;
	HWND hSignIn;
	bool LoggedIn;

	static void ClearChildren(HWND hwnd);
	//void OpenSignUp(HWND parentHwnd);
	static void OpenSignIn(HWND parentHwnd, HWND& hUsernameEditText, HWND& hPasswordEditText);

	static void BeginningButtons(HWND hwnd);

	static string wcharToString(const wchar_t* wstr);
	static void updateLoggedIn(bool& loggedin,bool newState);
};
