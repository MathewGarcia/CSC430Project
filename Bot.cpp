#include "Bot.h"

#include <iostream>
#include "MessageHolder.h"
#include <regex>
#include "FindFile.h"


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
				return message.empty() ? "" : "succeeded";
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
	case findfile:

		if (input.empty()) {  //checks if the filename is empty
			cout << "Please provide a filename and its extension to search for.(eg. /find filename.txt)" << endl;
			break;  // Exit the case without executing the search
		}


		cout << "running find command" << endl;

		vector<string> foundfiles;

		string directory = "C:";


		//smart pointer so that if lets say it is accidentally skipped, the memory will still be freed.
		std::unique_ptr<FindFile> fileSearch = std::make_unique<FindFile>(directory, input, foundfiles);

		fileSearch->execute();

		if(foundfiles.size() == 0)
		{
			cout << "No files found: " << endl;
		}
		else
		{
			cout << "files found" << endl;
			for (const auto& foundfile : foundfiles)
			{
				cout << foundfile << endl;
			}
		}

		break;
	}
}