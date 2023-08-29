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
		std::cout << " Создал таблицу для Логина и пароля\n";
	else
		std::cout << "Не смог создать таблицу  для Логина и пароля, возможно она уже создана\n";	

//-----------------------------------------------------------------------------------------------------------------------------
//----------------------------- создаем таблицу для сообщений------------------------------------------------------------------

	if (mysql_query(&mysql, "CREATE TABLE Messages(id INT AUTO_INCREMENT PRIMARY KEY,own VARCHAR(10),receiver VARCHAR(10),message VARCHAR(200))") == 0)
		std::cout << " Создал таблицу для Логина и пароля\n";
	else
		std::cout << "Не смог создать таблицу для сообщений, возможно она уже создана\n";
//-----------------------------------------------------------------------------------------------------------------------------
//----------------------------- создаем таблицу текущих пользователей------------------------------------------------------------------

	if (mysql_query(&mysql, "CREATE TABLE onlineUsers(user VARCHAR(10),stateUser VARCHAR(10))") == 0)
		std::cout << " Создал таблицу для активных пользователей\n";
	else
		std::cout << "Не смог создать таблицу для активных пользователей, возможно она уже создана\n";
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
	char cLgn [10];
	char cPswrd[10];
	// Получаем дескриптор соединения
	mysql_init(&mysql);
	int errInsert = 1;
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
			sLgn=objLogPass.get_NameUserSend();
			sPswrd = objLogPass.get_PasswordUser();
			std::string isLogPass = "SELECT * FROM _log_pass WHERE login = '" + sLgn + "'";
			int errIsLogPass = mysql_query(&mysql, isLogPass.c_str());	
			if ((res = mysql_store_result(&mysql)) && ( row = mysql_fetch_row(res)))
			{
				std::cout << " Такой логин  уже есть  \n";
				objLogPass.set_CurrentState("5");//Такой логин  уже есть 
				objLogPass.set_Messaqge("--");//--Создаем пустое сообение 
				objLogPass.set_NumCurrMess("1");//--номер текущего сообщения
				objLogPass.set_NumMess("1");//--количество сообщений
				result = msgForClient();//Сформировать сообщение
				mysql_close(&mysql);
				return true;
			}	
			else
			{
				std::string insertLogPass = "INSERT INTO _log_pass(login, password) values('" + sLgn + "','" + sPswrd + "' )";
				errInsert = mysql_query(&mysql, insertLogPass.c_str()); //------Проверка на наличие логина и пароля Создать решение
			}
			if (errInsert ==0)
			{
				std::cout << " Запись Log Pass  создана \n";
				objLogPass.set_CurrentState("3");//Успешное создание логина и пароля
				objLogPass.set_Messaqge("--");//--Создаем пустое сообение 
				objLogPass.set_NumCurrMess("1");//--номер текущего сообщения
				objLogPass.set_NumMess("1");//--количество сообщений
				result = msgForClient();//Сформировать сообщение
				mysql_close(&mysql);
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
				mysql_close(&mysql);
				return true;
			}
		}

		else if (tempRequestProgram.compare("6") == 0) //Авторизация  на лог и пароль
		{
			sLgn = objLogPass.get_NameUserSend();
			sPswrd = objLogPass.get_PasswordUser();
			std::string isLogPass = "SELECT * FROM _log_pass WHERE login = '" + sLgn + "' AND password  = '" + sPswrd + "'";
			//std::string isLogPass = "SELECT * FROM _log_pass WHERE login = 'sega' AND password  = '123123'";
			int errIsLogPass = mysql_query(&mysql, isLogPass.c_str());
			if ((res = mysql_store_result(&mysql)) && (row = mysql_fetch_row(res)))
			{
				std::cout << " Успешное автоизация  \n";
				
				std::string insertUsers = "INSERT INTO onlineUsers(user, stateUser) values('" + sLgn + "','1' )";// 1 user на линиии
				errInsert = mysql_query(&mysql, insertUsers.c_str()); //------Проверка на наличие логина и пароля Создать решение
				if (errInsert == 0)
					std::cout << " Запись в таблицу onlineUsers  создана \n";
				else 
					std::cout << "Не смог создать запись в таблицу onlineUsers \n";

				objLogPass.set_CurrentState("7");//Успешная активация 
				objLogPass.set_Messaqge("--");//--Создаем пустое сообение 
				objLogPass.set_NumCurrMess("1");//--номер текущего сообщения
				objLogPass.set_NumMess("1");//--количество сообщений
				result = msgForClient();//Сформировать сообщение
				mysql_close(&mysql);
				return true;
			}
			else
			{
				std::cout << "не успешная автоизация  \n";
				objLogPass.set_CurrentState("8");//Такой логин  уже есть 
				objLogPass.set_Messaqge("--");//--Создаем пустое сообение 
				objLogPass.set_NumCurrMess("1");//--номер текущего сообщения
				objLogPass.set_NumMess("1");//--количество сообщений
				result = msgForClient();//Сформировать сообщение
				mysql_close(&mysql);
				return true;
			}
		}

		else if (tempRequestProgram.compare("9") == 0) //Запрос о количестве пользователей на линии
		{
			std::string msgClient="";
			MYSQL_ROW tempRow;
			MYSQL_FIELD* field;
			std::string tmpStrForClient;
			std::string isUser = "SELECT * FROM onlineUsers";
			int errIsUsers = mysql_query(&mysql, isUser.c_str());
			if (errIsUsers == 0)
			{
		        if (res = mysql_store_result(&mysql))
				{
                    int num_fields = mysql_num_fields(res); // количество полей
                    int num_rows = mysql_num_rows(res); // и количество строк.
					while(tempRow = mysql_fetch_row(res))
				   {
				   	std::cout<< "row[0] = "<< tempRow[0]<<std::endl; // Выводим поля				
					msgClient = msgClient + "  "+ tempRow[0];

				   }
					objLogPass.set_CurrentState("10");//Такой логин  уже есть 
					objLogPass.set_Messaqge(msgClient);//--Создаем  сообение 
					objLogPass.set_NumCurrMess("1");//--номер текущего сообщения
					objLogPass.set_NumMess("1");//--количество сообщений
					result = msgForClient();//Сформировать сообщение
					mysql_close(&mysql);
					return true;
				}
			}
			mysql_close(&mysql);
			return true;
			//----------------------------------------------------------------------------

		}
		else if (tempRequestProgram.compare("14") == 0) //Запрос об удаление ползоваетелей
		{
		sLgn = objLogPass.get_NameUserSend();
		std::string isUser = "SELECT * FROM onlineUsers WHERE user = '" + sLgn + "'";
		int errIsUser = mysql_query(&mysql, isUser.c_str());
	
			if (errIsUser == 0)
			{
				if ((res = mysql_store_result(&mysql)) && (row = mysql_fetch_row(res)))
				{
					isUser = "DELETE  FROM onlineUsers WHERE user = '" + sLgn + "'";
					int errIsUser = mysql_query(&mysql, isUser.c_str());
					if (errIsUser == 0)
					{
						std::cout << "Удалось удалить записи онлайн пользователей\n";
						mysql_close(&mysql);
						return true;
					}
					else
					{
						std::cout << "Ошибка удаления  записи онлайн пользователей\n";
						mysql_close(&mysql);
						return true;
					}
				}
			}
			mysql_close(&mysql);
			return true;
		}
	}
	mysql_close(&mysql);
	system("Pause");
}
