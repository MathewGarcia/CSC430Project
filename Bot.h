#pragma once
#include <map>
#include <memory>
#include <string>
#include <vector>

#include "UserStates.h"


enum UserStates : uint8_t;
class MessageHolder;
using namespace std;
class Bot
{
public:
	Bot(const UserStates& state) : currentState(state)
	{
		Commands.insert({ "find",findfile });
	}
	string Listen(string& text);
	void SetState(UserStates newState);
	unique_ptr<MessageHolder> ParseString(string& text);
	bool isCommand(const string& currentCommand);

	void executeCommand(const string& input);

	map<string, UserStates>Commands;
private:
	UserStates currentState;
};

