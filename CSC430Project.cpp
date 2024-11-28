
// CSC430Project.cpp : This file contains the 'main' function. Program execution begins and ends there.
//SV-GUI 

#include <iostream>
#include "StartWindow.h"
#include "Bot.h"
#include "UserManager.h"
#include <windows.h>
#include <string>
#include <sstream>
#define WM_UPDATE_CHAT (WM_USER +1)


using namespace std;
LRESULT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
HWND hChatLog, hInputBox, hSendButton;
UserStates currentState = none;
void updateChat(string newText);
Bot bot(currentState, updateChat);

/*
Original File Bot code in a seperate txt
*/

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	StartWindow sw;
	sw.startWin(hInstance,nCmdShow);


	
	
	const wchar_t CLASS_NAME[] = L"File Search Window Class";

	WNDCLASSW wc = {};
	wc.lpfnWndProc = WndProc;
	wc.hInstance = hInstance;
	wc.lpszClassName = CLASS_NAME;

	RegisterClassW(&wc);

	HWND hwnd = CreateWindowExW(
		0,
		CLASS_NAME,
		L"File Bot",
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT, 600, 400,
		NULL, NULL, hInstance, NULL
	);


	if (hwnd == NULL) return 0;

	ShowWindow(hwnd, nCmdShow);
	


	// Main message loop
	MSG msg = {};
	while (GetMessage(&msg, NULL, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return 0;
}


LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
	switch (msg) {
	case WM_CREATE: {
		// Create the chat log (multi-line edit box)
		hChatLog = CreateWindowExW(
			0, L"EDIT", NULL,
			WS_CHILD | WS_VISIBLE | WS_BORDER | ES_MULTILINE | ES_READONLY | WS_VSCROLL,
			10, 10, 560, 300,
			hwnd, NULL, NULL, NULL
		);

		// Create the input box (single-line edit box)
		hInputBox = CreateWindowExW(
			0, L"EDIT", NULL,
			WS_CHILD | WS_VISIBLE | WS_BORDER,
			10, 320, 400, 20,
			hwnd, (HMENU)2, NULL, NULL
		);

		// Create the send button
		hSendButton = CreateWindow(
			L"BUTTON", L"Send",
			WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
			420, 320, 150, 20,
			hwnd, (HMENU)1, NULL, NULL
		);

		bot.setHwnd(hwnd);

		//first time opening application.
		updateChat("Welcome to File Bot! Please use \"/help\" to get started! \r\n");

		break;
	}

	case WM_COMMAND:
		if (LOWORD(wParam) == 1) { // If "Send" button is clicked
			char buffer[256];
			GetWindowTextA(hInputBox, buffer, 256); // Get text from input box
			string botresult = "";

			string input(buffer);
			botresult = bot.Listen(input);

			// Append text to the chat log
			std::string chatLog = "You: ";
			chatLog += buffer;
			chatLog += "\r\n";
			chatLog += "Bot: ";
			chatLog += botresult;
			chatLog += "\r\n";


			updateChat(chatLog);

			// Clear the input box
			SetWindowTextA(hInputBox, "");

		}
		break;

	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	case WM_UPDATE_CHAT: {
		string* msg = (string*)lParam;
		updateChat(*msg + "\r\n");
		delete msg;
	}
	default:
		return DefWindowProc(hwnd, msg, wParam, lParam);
	}
	return 0;
}

void updateChat(string newText)
{
	int chatLength = GetWindowTextLengthA(hChatLog);
	char* currentText = new char[chatLength + 1];
	GetWindowTextA(hChatLog, currentText, chatLength + 1);

	stringstream updatedText;

	updatedText << currentText << newText;

	SetWindowTextA(hChatLog, updatedText.str().c_str());

	delete[] currentText;

}