#pragma once
#include <mutex>
#include <vector>
#include <windows.h>

#include "Command.h"
class FindFile : public Command
{
public:
    FindFile(const std::string& directory, const std::string& fileName,std::vector<std::string>&foundFiles,HWND Wnd, std::mutex& fm) : p_directory(directory), p_fileName(fileName),p_foundFiles(foundFiles), hWnd(Wnd),fileMutex(fm){};

	 void execute() override;

    void cancel() override;

private:
    std::string p_directory;

    std::string p_fileName;

    std::vector<std::string>& p_foundFiles;

    std::string commandName = "find";

    HWND hWnd;

    std::mutex& fileMutex;
};

