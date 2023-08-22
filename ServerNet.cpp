#pragma comment(lib,"ws2_32.lib")
#include <winsock2.h>
#include <iostream>
#include "SQL.h"
#include "LogPass.h"
#pragma warning (disable:4996)
#define RUN



SOCKET Connection[100];
int Counter = 0;
int message_size;
const char* end_string = "end";
//Log_pass  objLogPass;

std::string  recivMess(char arryChar[]) //формирование сообщения для полученная с сервера
{
	char tempChar = 't';//инициализация пустой ячейки  значением "temp"
	int i = 0;
	std::string tempStr = "";
	while (tempChar != '\0')
	{
		tempChar = arryChar[i];
		tempStr = tempStr + tempChar;
		i++;
	}
	
	return  tempStr;
}
//-------------------------------------------------------------------------------
void ClientHandler(int index)
{
	char msg[256];
	char buffer[256];
	std::string sMsg ;
	while (true)
	{
#ifdef RUN
		int i = 0;
		message_size=recv(Connection[index], buffer, sizeof(buffer), NULL);
		for (; i < Counter; i++)
		{
			if (i == index)
			{
				continue;
			}		
		}
		if (insert_Log_Pass_SQL(buffer, sMsg))//обмен сообщениями при успешной операции
		{
			strcpy(msg, sMsg.c_str());//преооразуем строку в массив char
			send(Connection[index], msg, sizeof(msg), NULL);
		}
#else
		std::cout << "Hello" << std::endl;
#endif
	}
}
//-------------------------------------------------------------------------------
   void mainNet()
{
	//WSAStartup
	WSAData wsaData;
	WORD DLLVersion = MAKEWORD(2, 1);
	if (WSAStartup(DLLVersion, &wsaData) != 0)
	{
		std::cout << "Error" << std::endl;
		exit(1);
	}
	SOCKADDR_IN addr;
	int sizeofaddr = sizeof(addr);
	addr.sin_addr.s_addr = inet_addr("127.0.0.1");
	addr.sin_port = htons(7777);
	addr.sin_family = AF_INET;

	SOCKET sListen = socket(AF_INET, SOCK_STREAM, NULL);
	bind(sListen, (SOCKADDR*)& addr, sizeof(addr));
	listen(sListen, SOMAXCONN);

	SOCKET newConnection;
	for (int i = 0; i < 100; i++)
	{
		newConnection = accept(sListen, (SOCKADDR*)& addr, &sizeofaddr);

		if (newConnection == 0)
		{
			std::cout << "Error #2\n";
		}
		else
		{
			std::cout << "Client Connected\n";
			char msg[256] = "Hello. It's my first network program!";
			send(newConnection, msg, sizeof(msg), NULL);
			Connection[i] = newConnection;
			Counter++;
			CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)ClientHandler, (LPVOID)(i), NULL, NULL);
			
		}
	}

	system("pause");
}

   //CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)insert_Log_Pass_SQL, (LPVOID)(buffer), NULL, NULL);
	   //std::cout << "message_size ="<< message_size << std::endl;
	   //objLogPass.parser(buffer);