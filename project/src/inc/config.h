#ifndef CONFIG_H
#define CONFIG_H
#pragma once
#include <string>
#include <iostream>
#include <fstream>
using namespace std;

class Config
{
private:
	Config(Config const&);
	Config& operator= (Config const&);
	Config();
	~Config();
public:
	  static Config& getInstance();
	enum COMMAND_TYPE {
						COMMAND_EXIT=654,
						COMMAND_HELP=604,
						COMMAND_SHOW_CONFIG_FILE=48401,
						COMMAND_SET_DEFAULT_CONFIG=46952,
						COMMAND_GET_PORT=5236,
						COMMAND_GET_USERNAME=84851,
						COMMAND_GET_USERPASWORD=83660,
						COMMAND_GET_DATABASE_NAME=1306979,
						COMMAND_GET_DATABASE_HOST=1307014,
						COMMAND_GET_TABLE_NAME=166723,
						COMMAND_GET_LOG_LOCATION=667648,
						COMMAND_GET_THREAD_COUNT=673356,
					//	COMMAND_GET_TASK_CPP_TABLE_NAME=765955,
				//		COMMAND_GET_TASK_JAVA_TABLE_NAME=765956,
						COMMAND_SET_PORT=6004,
						COMMAND_SET_USERNAME=97139,
						COMMAND_SET_PASSWORD=95948,
						COMMAND_SET_DATABASE_NAME=1503587,
						COMMAND_SET_DATABASE_HOST=1503622,
						COMMAND_SET_TABLE_NAME=191299,
						COMMAND_SET_LOG_LOCATION=765952,
						COMMAND_SET_TASK_CPP_TABLE_NAME=765953,
						COMMAND_SET_TASK_JAVA_TABLE_NAME=765954,
						COMMAND_SET_THREAD_COUNT=771660};

    //static Config *sConfig;
	string  dataBasePort;
    string port;
    string userName;
    string password;
    string dataBaseName;
    string dataBaseHost;
    string tableName;
   // string taskCppTableName;
   // string taskJavaTableName;
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
    void setLogLocation(string value);
    void setThreadCount(int value);
    void setDataBasePort(int value);


  /*  void setTaskCppTableName(string value);
    void setTaskJavaTableName(string value);

    string getTaskCppTableName();
	string getTaskJavaTableName();*/
    string getPort();
    string getUserName();
    string getPassword();
    string getDataBaseName();
    string getDataBaseHost();
    string getLogLocation();
    string getDataBasePort();
    int getThreadCount();

};

#endif // CONFIG_H
