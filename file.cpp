#include <iostream>
#include <fstream>
#include "file.h"
#include <string>
std::string nameFileToServer = "bufferToServer.txt";
char fileNameToServer[] = "bufferToServer.txt";
std::string nameFileFromServer = "bufferToServer.txt";
char fileNameFromServer[] = "bufferToServer.txt";

//-------------------------------------
bool FileIsExistToServer()
{
	bool isExist = false;
	std::ifstream fin(nameFileToServer.c_str());

	if (fin.is_open())
		isExist = true;

	fin.close();
	return isExist;
}
//------------------------------------
bool deleteFileToServer()
{
	if (FileIsExistToServer())
	{

		if (remove(fileNameToServer) == 0)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	return false;
}
//--------------------------------------
bool createFileToServer(std::string msg)
{
	if (!FileIsExistToServer())
	{
		std::ofstream MyFile(nameFileToServer);
		MyFile << msg;
		MyFile.close();
		return true;
	}
	else
		return false;
}
//------------------------------------
bool readFileToServer(std::string & Mess)
{
	std::string line;
	if (FileIsExistToServer())
	{
		std::ifstream in(nameFileToServer); // окрываем файл для чтения
		if (in.is_open())
		{
			while (std::getline(in, line))
			{
				Mess = Mess + line;
				//'std::cout << line << std::endl;
			}
			in.close();     // закрываем файл
			if (deleteFileToServer())
				return true;
			else
				return false;
		}
		else
			return false;
	}
	else
		return false;
}
// ------------------------------------ -
bool FileIsExistFromServer()
{
	bool isExist = false;
	std::ifstream fin(nameFileFromServer.c_str());

	if (fin.is_open())
		isExist = true;

	fin.close();
	return isExist;
}
//------------------------------------
bool deleteFileFromServer()
{
	if (FileIsExistFromServer())
	{

		if (remove(fileNameFromServer) == 0)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	return false;
}
//--------------------------------------
bool createFileFromServer(std::string msg)
{
	if (!FileIsExistFromServer())
	{
		std::ofstream MyFile(nameFileFromServer);
		MyFile << msg;
		MyFile.close();
		return true;
	}
	else
		return false;
}
//------------------------------------
bool readFileFromServer(std::string& Mess)
{
	std::string line;
	if (FileIsExistFromServer())
	{
		std::ifstream in(nameFileFromServer); // окрываем файл для чтения
		if (in.is_open())
		{
			while (std::getline(in, line))
			{
				Mess = Mess + line;
				//'std::cout << line << std::endl;
			}
			in.close();     // закрываем файл
			if (deleteFileFromServer())
				return true;
			else
				return false;
		}
		else
			return false;
	}
	else
		return false;
}