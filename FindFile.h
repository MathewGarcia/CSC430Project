#pragma once
#include <vector>

#include "Command.h"
class FindFile : public Command
{
public:
    FindFile(const std::string& directory, const std::string& fileName,std::vector<std::string>&foundFiles) : p_directory(directory), p_fileName(fileName),p_foundFiles(foundFiles){};

    virtual void execute() override;

private:
    std::string p_directory;

    std::string p_fileName;

    std::vector<std::string>& p_foundFiles;

    std::string commandName = "find";

};

