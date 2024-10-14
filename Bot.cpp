#include "Bot.h"

#include <iostream>

#include "MessageHolder.h"
#include <regex>

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
				//run the command
				executeCommand();
				return "succeeded";
			}
		}
		else
		{
			return "That command doesn't exist.";
		}
	}
	return "There was a problem with the current message sent";
	
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

bool Bot::isCommand(string currentCommand)
{
	//check if it is a command
	return Commands.find(currentCommand) != Commands.end();
}

void Bot::executeCommand()
{
	switch(currentState)
	{
	case findfile:
		cout << "running find command" << endl;
		break;
	default: cout << "default command" << endl;
	}
}

