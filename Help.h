#pragma once
#include <functional>

#include "Bot.h"
#include "Command.h"
class Help :
    public Command
{
public:
    Help(HWND hw) : hwnd(hw)
    {

    };

    void execute() override;
    void cancel() override;
private:
    HWND hwnd;
};

