#pragma once
#include <functional>
#include <map>
#include <memory>
#include <string>
#include <vector>

#include "FindFile.h"
#include "UserStates.h"


enum UserStates : uint8_t;
class MessageHolder;
using namespace std;
class Bot
{
public:
	Bot(const UserStates& state, function<void(const string&)> updateChatCallBack) : currentState(state), updateChat(updateChatCallBack), hwnd(nullptr)
	{
		Commands.insert({ "find",findfile });
		Commands.insert({ "help",help });
		Commands.insert({ "cancel",cancel });


	}

	function<void(const string&)> updateChat;
	string Listen(string& text);
	void SetState(UserStates newState);
	unique_ptr<MessageHolder> ParseString(string& text);
	bool isCommand(const string& currentCommand);

	void executeCommand(const string& input);

	void setHwnd(HWND Hwnd);

	unique_ptr<Command> ActiveCommand = nullptr;

	map<string, UserStates>Commands;
private:
	UserStates currentState;
	HWND hwnd;
};

