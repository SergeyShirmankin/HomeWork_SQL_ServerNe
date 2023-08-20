#include <iostream>
#include <mysql.h>
#include "SQL.h"
#define DEBUG_STEP_1
using namespace std;

void  mainSQL() {
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
		std::cout << "Не смог создать базу данных для Логина и пароля\n";	
	
	for (int i = 0; i < 3; i++)
	{
		if (mysql_query(&mysql, "INSERT INTO _log_pass(id, login, password) values(default,'******','******')") == 0)
			std::cout << " Запись Log Pass  создана \n";
		else
			std::cout << " Запись Logpass не может быть создана \n";
	}
//-----------------------------------------------------------------------------------------------------------------------------
//----------------------------- создаем таблицу для сообщений------------------------------------------------------------------

	if (mysql_query(&mysql, "CREATE TABLE Messages(id INT AUTO_INCREMENT PRIMARY KEY,own VARCHAR(10),receiver VARCHAR(10),message VARCHAR(200))") == 0)
		std::cout << " Создал базу данных для Логина и пароля\n";
	else
		std::cout << "Не смог создать базу для сообщений\n";
		
	for (int i = 0; i < 100; i++)
	{
		if (mysql_query(&mysql, "INSERT INTO Messages(id, own,receiver,message) values(default,'*******','******','**********')") == 0)
			std::cout << " Запись Message создана \n";
		else
			std::cout << " Запись Message не может быть создана \n";
	}
//----------------------------------------------------------------------------------------------------------------------------
	//mysql_query(&mysql, "CREATE TABLE table_fromCplusplus(id INT AUTO_INCREMENT PRIMARY KEY, name VARCHAR(10))");
	//mysql_query(&mysql, "INSERT INTO table_fromCplusplus(id, name) values(default, 'Daria')");
	//mysql_query(&mysql, "INSERT INTO table_fromCplusplus(id, name) values(default, 'Lida')");
	//mysql_query(&mysql, "INSERT INTO table_fromCplusplus(id, name) values(default, 'Nastya')");

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