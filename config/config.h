#ifndef CONFIG_H
#define CONFIG_H
#pragma once
#include <string>
#include <iostream>
#include <fstream>

using namespace std;

class Config
{
public:
	Config();


    //static Config *sConfig;

    string port;
    string userName;
    string password;
    string dataBaseName;
    string dataBaseHost;
    string tableName;
    string logLocation;
    int threadCount;

    void runCommandLine();
    void makeValueStructure();
    void makeConfigFile();
    void scanConfigFile();
    void showConfigFile();
    void setDefaultConfig();
    void help();

    bool isnumber(string value);
    long long getHash(string value);

    void setPort(string value);
    void setUserName(string value);
    void setPassword(string value);
    void setDataBaseName(string value);
    void setDataBaseHost(string value);
    void setTableName(string value);
    void setLogLocation(string value);
    void setThreadCount(int value);

    string getPort();
    string getUserName();
    string getPassword();
    string getDataBaseName();
    string getDataBaseHost();
    string getTableName();
    string getLogLocation();
    int getThreadCount();
};

#endif // CONFIG_H
