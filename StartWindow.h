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

	//void OpenSignUp(HWND parentHwnd);
	void OpenSignIn(HWND parentHwnd);
};
