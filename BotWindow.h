#pragma once
#include <string>
#include <windows.h>
#include "UserStates.h"
enum UserStates : uint8_t;

class BotWindow
{
public:

	static LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
	void startBotWindow(HINSTANCE hInstance, int nCmdShow);
	static void updateChat(std::string newText);
private:
	
	UserStates currentState = UserStates::none;

};

