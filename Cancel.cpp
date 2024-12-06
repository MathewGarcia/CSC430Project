#include "Cancel.h"
#define WM_UPDATE_CHAT (WM_USER +1)

void Cancel::execute()
{
	if(currentBot && currentBot->ActiveCommand != nullptr)
	{
		currentBot->ActiveCommand->cancel();
		PostMessage(hwnd, WM_UPDATE_CHAT, 0, (LPARAM)new std::string("Canceling command..."));
	}
	else
	{
		PostMessage(hwnd, WM_UPDATE_CHAT, 0, (LPARAM)new std::string("There is no command to cancel."));
	}
}

void Cancel::cancel()
{
}
