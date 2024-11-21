#pragma once
#include <atomic>
#include <string>

class Command
{
public:
	virtual ~Command() = default;
	virtual void execute() = 0;
	virtual void cancel() = 0;
	std::atomic<bool> cancelCommand = false;

private:

	std::string commandName;


};

