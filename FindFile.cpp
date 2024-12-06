#include "FindFile.h"
#include <string>
#include <windows.h>
#define WM_UPDATE_CHAT (WM_USER +1)

using namespace std;
void FindFile::execute()
{
	//win 32 find data holds the file data such as file name.
	WIN32_FIND_DATAA FindFileData;
	

	//hfind is a reference to the file search which is returned by find file.
	HANDLE hFind;

	//search path to look for.
	string searchPath = p_directory + "\\" + p_fileName;


	hFind = FindFirstFileA(searchPath.c_str(), &FindFileData);

	//if the return isn't empty continue the search.
	if (hFind != INVALID_HANDLE_VALUE)
	{
		//do while to & bitwise the file attribute  if the file attributes is not 0. then it is a directory. ie. 1&1.
		do
		{
			if (cancelCommand)
			{
				break;
			}
			//so if it is NOT 1 then it is a file. (i.e, 0.)
			if (!(FindFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY))
			{
				//lock to safely update thread.
				lock_guard<mutex> lock(fileMutex);
				//add the file to the vector.
				p_foundFiles.push_back(p_directory + "\\" + FindFileData.cFileName);
				//Post the message, use WM_UPDATE_CHAT case.
				PostMessage(hWnd, WM_UPDATE_CHAT, 0, (LPARAM)new std::string(p_directory + "\\" + FindFileData.cFileName));
			}
		

		} while (FindNextFileA(hFind, &FindFileData) != 0);

		FindClose(hFind);
	}


	//repeat the process but look for sub directories recursively.
	std::string subDirectories = p_directory + "\\*";

	hFind = FindFirstFileA(subDirectories.c_str(), &FindFileData);

	if (hFind != INVALID_HANDLE_VALUE)
	{
		do {
			if(cancelCommand)
			{
				break;
			}
			//if the attributes is 1, then it is a directory
			if (FindFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
			{
				//search the directory
				std::string subDirName = FindFileData.cFileName;
				if (subDirName != "." && subDirName != "..")
				{
					//recursivley pass it into runfind function and search that path for files.
					std::string subDirPath = p_directory + "\\" + subDirName;
					FindFile subDirCommand(subDirPath, p_fileName, p_foundFiles,hWnd,fileMutex);
					subDirCommand.execute();

				}
			}
		} while (FindNextFileA(hFind, &FindFileData) != 0);

		FindClose(hFind);
	}
}

void FindFile::cancel()
{
	cancelCommand = true;
}
