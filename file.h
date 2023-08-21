#pragma once
bool FileIsExistToServer();
bool deleteFileToServer();
bool createFileToServer(std::string msg);
bool readFileToServer(std::string& Mess);
bool FileIsExistFromServer();
bool deleteFileFromServer();
bool createFileFromServer(std::string msg);
bool readFileFromServer(std::string& Mess);
