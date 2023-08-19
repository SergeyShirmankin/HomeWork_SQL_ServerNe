#include <iostream>
#include <mysql.h>
#include "SQL.h"
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

	mysql_query(&mysql, "CREATE TABLE table_fromCplusplus(id INT AUTO_INCREMENT PRIMARY KEY, name VARCHAR(255))");
	mysql_query(&mysql, "INSERT INTO table_fromCplusplus(id, name) values(default, 'Daria')");
	mysql_query(&mysql, "INSERT INTO table_fromCplusplus(id, name) values(default, 'Lida')");
	mysql_query(&mysql, "INSERT INTO table_fromCplusplus(id, name) values(default, 'Nastya')");


	mysql_query(&mysql, "SELECT * FROM table_fromCplusplus"); //Делаем запрос к таблице

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

	system("Pause");
}