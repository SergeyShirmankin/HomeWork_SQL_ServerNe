#pragma once
#include <iostream>
#include <string>
class Log_pass
{
public:
	Log_pass();//Конструктор по умолчанию
	//void set_PasswUser(const std::string& newName);
	void set_PasswUser(const std::string&);
	void set_NameUserSend(const std::string&);
	void set_NameUserRecive(const std::string&);
	void set_Request(const std::string&);
	void set_CurrentState(const std::string&);
	void set_NumMess(const std::string&);  //количество сообщени
	void set_NumCurrMess(const std::string&); //номер сообщения
	void set_Messaqge(const std::string&);
	//std::string Messaqge;
	void set_StateProgram(int);

	std::string& get_PasswordUser();
	std::string& get_NameUserSend();
	std::string& get_NameUserRecive();
	std::string& get_Request();
	std::string& get_CurrentState();
	std::string& get_Messaqge();
	std::string& get_NumMess();  //количество сообщени
	std::string& get_NumCurrMess(); //номер сообщения
	std::string& get_currUser();
	int get_StateProgram();
	//----------------------------------------------------------------------
	void parser(char str[]);
	void addLogPass();
	std::string createMessLogToClient();
	//----------------------------------------------------------------------
private:
	int countObjectLogPass;//счетчик обьектов логов и паролей
	int StateProgram;
	int curSession;
	std::string currUser;//под этим погином заходят в систему

	Log_pass* ptrObject;// Указатель на обьект
	std::string login;//поле логина в обьекте
	std::string password;// поле пароля в обьектн

	std::string PasswordUser;//Пароль пользователя  отправителя сообщения
	std::string NameUserSend;// Имя пользователя  отправителя сообщения
	std::string NameUserRecive;//  Имя пользователя принимающего сообщения
	std::string Request;// Запрос на измененимя состояния (команда)
	std::string CurrentState;//Текущее состояние программы
	std::string NumCurrMess; //номер сообщения
	std::string NumMess;  //количество сообщени
	std::string Messaqge;//само сообщение
};
