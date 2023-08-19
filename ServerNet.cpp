#pragma comment(lib,"ws2_32.lib")
#include <winsock2.h>
#include <iostream>
#include "SQL.h"
#pragma warning (disable:4996)

SOCKET Connection[100];
int Counter = 0;
//-------------------------------------------------------------------------------
void ClientHandler(int index)
{
	char msg[256];
	while (true)
	{
		recv(Connection[index], msg, sizeof(msg), NULL);
		for (int i = 0; i < Counter; i++)
		{
			if (i == index)
			{
				continue;
			}
			send(Connection[i], msg, sizeof(msg), NULL);
		}

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
			CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)mainSQL, NULL, NULL, NULL);
		}
	}

	system("pause");
}