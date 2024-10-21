#pragma once
#include <string>

using namespace std;

class MessageHolder
{
public:
	MessageHolder(const string& command, const string& message) : Command(command), Message(message)
	{
		
	}

	string GetCommand()
	{
		return Command;
	}

	string GetActualMessage()
	{
		return Message;
	}
private:

	string Command;
	string Message;

};

