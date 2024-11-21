#include "Cancel.h"
#define WM_UPDATE_CHAT (WM_USER +1)

void Cancel::execute()
{
	if(currentBot && currentBot->ActiveCommand)
	{
		currentBot->ActiveCommand->cancel();
		PostMessage(hwnd, WM_UPDATE_CHAT, 0, (LPARAM)new std::string("Canceling command..."));


	}
}

void Cancel::cancel()
{
}
