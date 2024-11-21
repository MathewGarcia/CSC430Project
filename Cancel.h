#pragma once
#include "Bot.h"
#include "Command.h"
class Cancel :
    public Command
{
public:
    Cancel(HWND hw,Bot*bot) :hwnd(hw), currentBot(bot){};

    void execute() override;
    void cancel() override;

private:
    HWND hwnd;
    Bot* currentBot;
};

