#pragma once
bool createFile(std::string msg);//создани файла для обмнена мкежду потоками
bool deleteFile();//удаление файла для обмнена мкежду потоками
bool FileIsExist();//проверка существования файла 
bool readFile(std::string& Mess);// чтение файла
