#pragma once
#include "LogPass.h"
const int maxPerson = 3;//максимальное количество людей которое можно работать в чате
static int countObject;
static int curSesion;//активная сессия
const int maxMess = 100;//максимальное количество сообщений в чате
int createNullMap()// создание пустых сообщений
{
	int size;
	Log_pass* pSt = new Log_pass;
	Log_pass& st = *pSt;
	for (int i = 0; i < maxMess; ++i) {
		Messages* pMess = new Messages;
		Messages& mess = *pMess; //преобразование указателя в ссылку
		size = st.AddScore(i, mess);
	}
	return size;
}
