// CSC430Project.cpp : This file contains the 'main' function. Program execution begins and ends there.
//SV-GUI 

#include <iostream>
#include "StartWindow.h"
#include "Bot.h"
#include "UserManager.h"
#include <windows.h>
#include <string>
#include <sstream>



using namespace std;

/*
Original File Bot code in a seperate txt
*/

int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow) {

		
			StartWindow sw;
			sw.startWin(hInstance, nCmdShow);
		


	return 0;
}

