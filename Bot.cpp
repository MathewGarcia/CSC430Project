#include "Bot.h"

#include <iostream>
#include <windows.h>
#include "MessageHolder.h"
#include <regex>

#include "Cancel.h"
#include "FindFile.h"
#include "Help.h"
#define WM_UPDATE_CHAT (WM_USER +1)

using namespace std;

string Bot::Listen(string& text)
{
	//here we create an auto pointer because parse string is returning a safe pointer. to MessageHolder
	auto currentMessage = ParseString(text);
	//check if current message exists, if not we don't want an nullptr exception
	if (currentMessage) {
		//check if we have a valid command
		if (isCommand(currentMessage->GetCommand()))
		{
			//check the map again to find the exact command we should run
			auto it = Commands.find(currentMessage->GetCommand());

			if (it != Commands.end())
			{
				//set the state to the value of the map key.
				SetState(it->second);
				string message = currentMessage->GetActualMessage();
				//run the command
				executeCommand(message);

				// Return "succeeded" only if the message is not empty
				return message.empty() ? "" : "Running " + currentMessage->GetCommand() + " command";

			}
		}
		else
		{
			return "That command doesn't exist. Available commands: /find";
		}
	}
	return "There was a problem with the current message sent.  Please ensure the command is entered in lowercase. Available commands: /find";

}

void Bot::SetState(UserStates newState)
{
	currentState = newState;
}

unique_ptr<MessageHolder> Bot::ParseString(string& text)
{
	//regex for the command + message
	regex reg(R"(/([a-z]+)\s*(.*))");
	smatch matches;
	//search the string for the match. if it succeeds then we have a /command message 
	if(regex_search(text,matches,reg))
	{
		string command = matches[1];
		string message = matches[2];
		//create smart pointer to MessageHolder
		return make_unique<MessageHolder>(command, message);
	}
	return nullptr;
}

bool Bot::isCommand(const string& currentCommand)
{
	//check if it is a command
	return Commands.find(currentCommand) != Commands.end();
}

void Bot::executeCommand(const string& input)
{
	switch(currentState)
	{
	case findfile: {

		if (input.empty()) {  //checks if the filename is empty
			updateChat("Please provide a filename and its extension to search for.(eg. / find filename.txt) \r\n");
			break;  // Exit the case without executing the search
		}
			//thread safe int
		atomic<int> numOfActiveThreads = -1;
		//create new thread to search. DETATCH it so that it is asyc.
		thread([this, input, &numOfActiveThreads]()
			{
				//count the number of threads
				++numOfActiveThreads;

				vector<string> foundfiles;

				string directory = "C:";

				mutex fileMutex;

				//smart pointer so that if lets say it is accidentally skipped, the memory will still be freed.
				std::unique_ptr<FindFile> fileSearch = std::make_unique<FindFile>(directory, input, foundfiles, hwnd, fileMutex);

				ActiveCommand = move(fileSearch);

				ActiveCommand->execute();

			if (foundfiles.empty() && !ActiveCommand->cancelCommand)
				{
					
					PostMessage(hwnd, WM_UPDATE_CHAT, 0, (LPARAM)new std::string("No files found \r\n"));

				}
				//decrement the number of active threads when we are done.
				--numOfActiveThreads;

				//if we have no more active threads, post command has finished.
				if (numOfActiveThreads < 0)
				{
					if(ActiveCommand->cancelCommand)
					{
						PostMessage(hwnd, WM_UPDATE_CHAT, 0, (LPARAM)new std::string("Command Canceled \r\n"));
						return;
					}
					PostMessage(hwnd, WM_UPDATE_CHAT, 0, (LPARAM)new std::string("Command finished."));

				}
			}).detach();






		break;
	}

	case help:
	{
		unique_ptr<Help> help = make_unique<Help>(hwnd);
		help->execute();

		break;
	}
	case cancel:
	{
		unique_ptr<Cancel> cancel = make_unique<Cancel>(hwnd, this);
		cancel->execute();
	}
	}
}


void Bot::setHwnd(HWND Hwnd)
{
	hwnd = Hwnd;
}
