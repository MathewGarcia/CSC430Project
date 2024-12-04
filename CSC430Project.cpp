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
HWND hChatLog = nullptr, hInputBox = nullptr, hSendButton = nullptr;
UserStates currentState = none;
void updateChat(string newText);
Bot bot(currentState, updateChat);

/*
Original File Bot code in a seperate txt
*/

int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow) {
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

		// Create and set font for input box in one line
		SendMessage(hInputBox, WM_SETFONT, (WPARAM)CreateFont(24, 0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, L"Arial"), TRUE);

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

			// Append user message to the chat log
			std::string chatLog = "You: ";
			chatLog += buffer;
			chatLog += "\r\n";
			updateChat(chatLog);

			// Append bot label to the chat log
			updateChat("Bot: ");

			// Get the response from the bot
			botresult = bot.Listen(input);

			// Append bot response to the chat log
			if (!botresult.empty()) {
				updateChat(botresult + "\r\n");
			}

			// Clear the input box
			SetWindowTextA(hInputBox, "");
		}

		break;

	case WM_PAINT: {
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hwnd, &ps);
		// Fill the window with a white background
		FillRect(hdc, &ps.rcPaint, (HBRUSH)(COLOR_WINDOW + 1));
		EndPaint(hwnd, &ps);
		break;
	}

    case WM_SIZE: {
        // Get the new dimensions of the window
        int width = LOWORD(lParam);
        int height = HIWORD(lParam);

        // Resize the chat log
        SetWindowPos(hChatLog, NULL, 10, 10, width - 20, height - 80, SWP_NOZORDER);

        // Resize the input box (increased height)
        SetWindowPos(hInputBox, NULL, 10, height - 60, width - 180, 30, SWP_NOZORDER);

        // Resize the send button (adjusted position)
        SetWindowPos(hSendButton, NULL, width - 160, height - 60, 150, 30, SWP_NOZORDER);

        break;
    }

	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	case WM_UPDATE_CHAT: {
		string* msg = (string*)lParam;
		updateChat(*msg + "\r\n");
		delete msg;
		break; // Added break to prevent fallthrough
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