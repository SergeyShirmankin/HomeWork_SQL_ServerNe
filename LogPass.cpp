#include <iostream>
#include "LogPass.h"
#include "ServerNet.h"
#include <winsock2.h>
#include "SQL.h"
#pragma warning (disable:4996)

#define DEBUG
Log_pass::Log_pass()//конструктор по умолчанию
{
	StateProgram = 1;
	countObjectLogPass = 0;
	CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)createSQL, NULL, NULL, NULL);
}

void Log_pass::set_StateProgram(int newStateProgram)
{
	StateProgram = newStateProgram;
}
void Log_pass::set_NameUserSend(const std::string& newNameUserSend)
{
	NameUserSend = newNameUserSend;
}
void Log_pass::set_PasswUser(const std::string& newPasswUser)
{
	PasswordUser = newPasswUser;
}
void Log_pass::set_NameUserRecive(const std::string& newNameUserRecive)
{
	NameUserRecive = newNameUserRecive;
}
void Log_pass::set_Request(const std::string& newRequest)
{
	Request = newRequest;
}
void Log_pass::set_CurrentState(const std::string& newCurrentStat)
{
	CurrentState = newCurrentStat;
}
void Log_pass::set_Messaqge(const std::string& newMessaqge)
{
	Messaqge = newMessaqge;
}
void Log_pass::set_NumMess(const std::string& newNumMess)
{
	NumMess = newNumMess;
}
void Log_pass::set_NumCurrMess(const std::string& newNumCurrMess)
{
	NumCurrMess = newNumCurrMess;
}


std::string& Log_pass::get_NameUserSend()
{
	return NameUserSend;
}
std::string& Log_pass::get_PasswordUser()
{
	return PasswordUser;
}
std::string& Log_pass::get_NameUserRecive()
{
	return NameUserRecive;
}
std::string& Log_pass::get_Request()
{
	return Request;
}
std::string& Log_pass::get_CurrentState()
{
	return CurrentState;
}
std::string& Log_pass::get_Messaqge()
{
	return Messaqge;
}
int Log_pass::get_StateProgram()
{
	return StateProgram;
}
std::string& Log_pass::get_NumMess()  //количество сообщени
{
	return NumMess;
}
std::string& Log_pass::get_NumCurrMess() //номер сообщени€
{
	return NumCurrMess;
}

void Log_pass::parser(char arrChar[])
{
	std::string delimiter = ":";
	std::string line;
	std::string markerBegin = "*";
	std::string markerEnd = "&";
	size_t posBegin;
	size_t posEnd;
	size_t pos;
	size_t oldPos;
	std::string tempPassword;
	std::string tempLogin;

	line = recivMess(arrChar);
	posBegin = line.find(markerBegin);
	//posBegin = 0;
	posEnd = line.find(markerEnd);
	if (posEnd != std::string::npos || posBegin != std::string::npos)
	{
		pos = line.find(delimiter, posBegin);
		set_PasswUser(line.substr(posBegin + 1, pos - 1));//”станавливаем в приватном поле пароль

#ifdef DEBUG
		tempPassword = get_PasswordUser();
		std::cout << "Password = " << tempPassword << std::endl;
#endif

		oldPos = pos;

		pos = line.find(delimiter, oldPos + 1);
		set_NameUserSend(line.substr(oldPos + 1, pos - oldPos - 1));//”станавливаем в приватном поле им€


#ifdef DEBUG
		tempLogin = get_NameUserSend();
		std::cout << "NameUserSen = " << tempLogin << std::endl;
#endif
		oldPos = pos;

		pos = line.find(delimiter, oldPos + 1);
		set_NameUserRecive(line.substr(oldPos + 1, pos - oldPos - 1));//”станавливаем в приватном поле им€

#ifdef DEBUG
		tempLogin = get_NameUserRecive();
		std::cout << "NameUserReciv = " << tempLogin << std::endl;
#endif
		oldPos = pos;

		pos = line.find(delimiter, oldPos + 1);
		set_Request(line.substr(oldPos + 1, pos - oldPos - 1));//”станавливаем в приватном поле им€

#ifdef DEBUG
		tempLogin = get_Request();
		std::cout << "Request = " << tempLogin << std::endl;
#endif

		oldPos = pos;

		pos = line.find(delimiter, oldPos + 1);
		set_CurrentState(line.substr(oldPos + 1, pos - oldPos - 1));//”станавливаем в приватном поле им€

#ifdef DEBUG
		tempLogin = get_CurrentState();
		std::cout << "CurrentState = " << tempLogin << std::endl;
#endif
		//-------------------¬ставка новых полей---------------------------------------------------
		oldPos = pos;

		pos = line.find(delimiter, oldPos + 1);
		set_NumCurrMess(line.substr(oldPos + 1, pos - oldPos - 1));//”станавливаем в приватном поле им€

#ifdef DEBUG
		tempLogin = get_NumCurrMess();
		std::cout << "NumCurrMess = " << tempLogin << std::endl;
#endif

		oldPos = pos;

		pos = line.find(delimiter, oldPos + 1);
		set_NumMess(line.substr(oldPos + 1, pos - oldPos - 1));//”станавливаем в приватном поле им€

#ifdef DEBUG
		tempLogin = get_NumMess();
		std::cout << "NumMess = " << tempLogin << std::endl;
#endif
		//----------------------------------------------------------------------------------------

		oldPos = pos;

		pos = line.find(delimiter, oldPos + 1);
		set_Messaqge(line.substr(oldPos + 1, posEnd - oldPos - 1));//”станавливаем в приватном поле им€

#ifdef DEBUG
		tempLogin = get_Messaqge();
		std::cout << tempLogin << "Messaqge = " << tempLogin << std::endl;
#endif

	}
}