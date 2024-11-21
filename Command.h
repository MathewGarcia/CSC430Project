#pragma once
#include <string>

class Command
{
public:
	virtual ~Command() = default;
	virtual void execute() = 0;

private:

	std::string commandName;

};

