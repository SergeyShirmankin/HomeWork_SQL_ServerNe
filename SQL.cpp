#include <iostream>
#include <mysql.h>
#include "SQL.h"
#include "LogPass.h"
#pragma warning (disable:4996)
Log_pass  objLogPass;
#define DEBUG_STEP_1
using namespace std;

//----------------------------------Формироавание сообщения для клиента--------------------------------------------------
//-----------------------------------------------------------------------------------------------------------------------
std::string msgForClient()
{
	std::string tempStr ="*";//---знак начала сообщения
	tempStr = tempStr + ":";// ---разделитель сообщения
	tempStr =tempStr + objLogPass.get_PasswordUser();//--пароль 
	tempStr = tempStr + ":";
	tempStr = tempStr + objLogPass.get_NameUserSend();//--логин отправителя  сообщения
	tempStr = tempStr + ":";
	tempStr = tempStr + objLogPass.get_NameUserRecive();//--логин получателя сообщения
	tempStr = tempStr + ":";
	tempStr = tempStr + objLogPass.get_Request();//--запрос на действия сервера
	tempStr = tempStr + ":";
	tempStr = tempStr + objLogPass.get_CurrentState();//--- состояние сервера
	tempStr = tempStr + ":";
	tempStr = tempStr + objLogPass.get_NumCurrMess();//--номер сообщения 
	tempStr = tempStr + ":";
	tempStr = tempStr + objLogPass.get_NumMess();//--количество сообщений
	tempStr = tempStr + ":";
	tempStr = tempStr + objLogPass.get_Messaqge();//--само сообщение
	tempStr = tempStr + "&";
	return tempStr;
}


//-----------------------------------------------------------------------------------------------------------------------
//--------------------------------------Создание таблиц------------------------------------------------------------------
void  createSQL() {
	MYSQL mysql;
	MYSQL_RES* res;
	MYSQL_ROW row;

	int i = 0;

	// Получаем дескриптор соединения
	mysql_init(&mysql);
	if (&mysql == nullptr) {
		// Если дескриптор не получен — выводим сообщение об ошибке
		cout << "Error: can't create MySQL-descriptor" << endl;
	}

	// Подключаемся к серверу
	if (!mysql_real_connect(&mysql, "localhost", "root", "sega261970", "testdb", NULL, NULL, 0)) {
		// Если нет возможности установить соединение с БД выводим сообщение об ошибке
		cout << "Error: can't connect to database " << mysql_error(&mysql) << endl;
	}
//---------------------------------------------------------------------------------------------------------------------------
//------------------------ Создаем таблицу для логинов и паролей-------------------------------------------------------------
	
	if (mysql_query(&mysql, "CREATE TABLE _log_pass(id INT AUTO_INCREMENT PRIMARY KEY, login VARCHAR(10),password VARCHAR(10))") == 0)
		std::cout << " Создал базу данных для Логина и пароля\n";
	else
		std::cout << "Не смог создать базу данных для Логина и пароля, возможно она уже создана\n";	

//-----------------------------------------------------------------------------------------------------------------------------
//----------------------------- создаем таблицу для сообщений------------------------------------------------------------------

	if (mysql_query(&mysql, "CREATE TABLE Messages(id INT AUTO_INCREMENT PRIMARY KEY,own VARCHAR(10),receiver VARCHAR(10),message VARCHAR(200))") == 0)
		std::cout << " Создал базу данных для Логина и пароля\n";
	else
		std::cout << "Не смог создать базу для сообщений, возможно она уже создана\n";
}

//-------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------Основная программа SQL-------------------------------------------------------------------

bool  insert_Log_Pass_SQL(char buffer[256],std::string & result) 
{
	MYSQL mysql;
	MYSQL_RES* res;
	MYSQL_ROW row;
	//char buffer[256];
	int i = 0;
	std::string sLgn;
	std::string sPswrd;
	char cLgn [9];
	char cPswrd[9];
	// Получаем дескриптор соединения
	mysql_init(&mysql);
	if (&mysql == nullptr) {
		// Если дескриптор не получен — выводим сообщение об ошибке
		cout << "Error: can't create MySQL-descriptor" << endl;
	}

	// Подключаемся к серверу
	if (!mysql_real_connect(&mysql, "localhost", "root", "sega261970", "testdb", NULL, NULL, 0)) {
		// Если нет возможности установить соединение с БД выводим сообщение об ошибке
		cout << "Error: can't connect to database " << mysql_error(&mysql) << endl;
	}
	   
	//Конвертировать string char
	if (buffer != nullptr)
	{
		objLogPass.parser(buffer);
		std::string  tempRequestProgram = objLogPass.get_Request();
		if (tempRequestProgram.compare("2") == 0)// хапрос на создание лога и пароля
		{
			//sLgn = "sega";
			sLgn=objLogPass.get_NameUserRecive();
			strcpy(cLgn, sLgn.c_str());//преооразуем строку в массив char
			//sPswrd = "123";
			sPswrd = objLogPass.get_PasswordUser();
			strcpy(cPswrd, sPswrd.c_str());//преооразуем строку в массив char
			//------Проверка на наличие логина и пароля Создать решение
			//...................................
			//...................................
			if (mysql_query(&mysql, "INSERT INTO _log_pass(id, login, password) values(default,cLgn,cPswrd)") == 0)
			{
				std::cout << " Запись Log Pass  создана \n";
				objLogPass.set_CurrentState("3");//Успешное создание логина и пароля
				objLogPass.set_Messaqge("--");//--Создаем пустое сообение 
				objLogPass.set_NumCurrMess("1");//--номер текущего сообщения
				objLogPass.set_NumMess("1");//--количество сообщений
				result = msgForClient();//Сформировать сообщение
				return true;
			}
			else
			{
				std::cout << " Запись Logpass не может быть создана \n";
				std::cout << " Запись Log Pass  создана \n";
				objLogPass.set_CurrentState("4");//Не удалось создать логин и пароль
				objLogPass.set_Messaqge("--");//--Создаем пустое сообение 
				objLogPass.set_NumCurrMess("1");//--номер текущего сообщения
				objLogPass.set_NumMess("1");//--количество сообщений
				result = msgForClient();//Сформировать сообщение
				return false;
			}
		}
	}
#ifdef  DEBUG_STEP_1
	mysql_query(&mysql, "SELECT * FROM _log_pass"); //Делаем запрос к таблице

	//Выводим все что есть в таблице через цикл
	if (res = mysql_store_result(&mysql)) {
		while (row = mysql_fetch_row(res)) {
			for (i = 0; i < mysql_num_fields(res); i++) {
				cout << row[i] << "  ";
			}
			cout << endl;
		}
	}
	else
		cout << "Ошибка MySql номер " << mysql_error(&mysql);
	// Закрываем соединение с базой данных
	mysql_close(&mysql);
#endif
	system("Pause");
}

//---------------------------------------------------------------------------------------------------------------------------
	//------------------------ Создаем таблицу для логинов и паролей-------------------------------------------------------------

	//if (mysql_query(&mysql, "CREATE TABLE _log_pass(id INT AUTO_INCREMENT PRIMARY KEY, login VARCHAR(10),password VARCHAR(10))") == 0)
	//	std::cout << " Создал базу данных для Логина и пароля\n";
	//else
	//	std::cout << "Не смог создать базу данных для Логина и пароля\n";

	//for (int i = 0; i < 3; i++)
	//{
	//	if (mysql_query(&mysql, "INSERT INTO _log_pass(id, login, password) values(default,'******','******')") == 0)
	//		std::cout << " Запись Log Pass  создана \n";
	//	else
	//		std::cout << " Запись Logpass не может быть создана \n";
	//}
	////-----------------------------------------------------------------------------------------------------------------------------
	////----------------------------- создаем таблицу для сообщений------------------------------------------------------------------

	//if (mysql_query(&mysql, "CREATE TABLE Messages(id INT AUTO_INCREMENT PRIMARY KEY,own VARCHAR(10),receiver VARCHAR(10),message VARCHAR(200))") == 0)
	//	std::cout << " Создал базу данных для Логина и пароля\n";
	//else
	//	std::cout << "Не смог создать базу для сообщений\n";

	//for (int i = 0; i < 100; i++)
	//{
	//	if (mysql_query(&mysql, "INSERT INTO Messages(id, own,receiver,message) values(default,'*******','******','**********')") == 0)
	//		std::cout << " Запись Message создана \n";
	//	else
	//		std::cout << " Запись Message не может быть создана \n";
	//}
	//----------------------------------------------------------------------------------------------------------------------------
		//mysql_query(&mysql, "CREATE TABLE table_fromCplusplus(id INT AUTO_INCREMENT PRIMARY KEY, name VARCHAR(10))");
		//mysql_query(&mysql, "INSERT INTO table_fromCplusplus(id, name) values(default, 'Daria')");
		//mysql_query(&mysql, "INSERT INTO table_fromCplusplus(id, name) values(default, 'Lida')");
		//mysql_query(&mysql, "INSERT INTO table_fromCplusplus(id, name) values(default, 'Nastya')");
