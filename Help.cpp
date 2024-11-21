#include "Help.h"

#include "Bot.h"

#define WM_UPDATE_CHAT (WM_USER +1)

void Help::execute()
{
    std::string helpMessage = "Thank you for using the /help command! Here are the current available commands: \r\n"
        "1. /find - Will help you find any file of your choosing. /find <file name>.<extension> \r\n"
        "2. /cancel - Will cancel a current command currently in execution. \r\n"
        "3. /help - Will post this message again!";

    // Post the message to be handled by the UI thread
    PostMessage(hwnd, WM_UPDATE_CHAT, 0, (LPARAM)new std::string(helpMessage));
}

void Help::cancel()
{
}
