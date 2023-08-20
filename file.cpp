#include <iostream>
#include <fstream>
#include "file.h"
#include <string>
std::string nameFile = "buffer.txt";
char fileName[] = "buffer.txt";

//-------------------------------------
bool FileIsExist()
{
	bool isExist = false;
	std::ifstream fin(nameFile.c_str());

	if (fin.is_open())
		isExist = true;

	fin.close();
	return isExist;
}
//------------------------------------
bool deleteFile()
{
	if (FileIsExist())
	{

		if (remove(fileName) == 0)
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
bool createFile(std::string msg)
{
	if (!FileIsExist())
	{
		std::ofstream MyFile(nameFile);
		MyFile << msg;
		MyFile.close();
		return true;
	}
	else
		return false;
}
//------------------------------------
bool readFile(std::string & Mess)
{
	std::string line;
	if (FileIsExist())
	{
		std::ifstream in(nameFile); // окрываем файл для чтения
		if (in.is_open())
		{
			while (std::getline(in, line))
			{
				Mess = Mess + line;
				//'std::cout << line << std::endl;
			}
			in.close();     // закрываем файл
			if (deleteFile())
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