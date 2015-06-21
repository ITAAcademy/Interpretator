#include "inc/config.h"
#include <iostream>
#include <string>
using namespace std;
Config::Config()
{

}

const int commandsCount = 8;

void Config::runCommandLine()
{
    string input;
    bool running = true;
    long long hashInput;
    makeValueStructure();
    scanConfigFile();

    while(running)
    {
        makeConfigFile();

        cout << '>';
        getline(cin, input);
        hashInput = getHash(input);

        switch (hashInput) {
        case COMMAND_EXIT:
            running = false;
            break;
        case COMMAND_HELP:
            help();
            break;
        case COMMAND_SHOW_CONFIG_FILE:
            showConfigFile();
            break;
        case COMMAND_SET_DEFAULT_CONFIG:
            setDefaultConfig();
            break;
        case COMMAND_GET_PORT:
            cout << "port: " << getPort() << "\n";
            break;
        case COMMAND_GET_USERNAME:
            cout << "userName: " << getUserName() << "\n";
            break;
        case COMMAND_GET_USERPASWORD:
            cout << "password: " << getPassword() << "\n";
            break;
        case COMMAND_GET_DATABASE_NAME:
            cout << "dataBaseName: " << getDataBaseName() << "\n";
            break;
        case COMMAND_GET_DATABASE_HOST:
            cout << "dataBaseHost: " << getDataBaseHost() << "\n";
            break;
        case COMMAND_GET_TABLE_NAME:
            cout << "tableName: " << getTableName() << "\n";
            break;
        case COMMAND_GET_LOG_LOCATION:
            cout << "logLocation: " << getLogLocation() << "\n";
            break;
        case COMMAND_GET_THREAD_COUNT:
            cout << "threadCount: " << getThreadCount() << "\n";
            break;
        case COMMAND_SET_PORT:
            cout << "port: ";
            getline(cin, input);
            setPort(input);
            break;
        case COMMAND_SET_USERNAME:
            cout << "userName: ";
            getline(cin, input);
            setUserName(input);
            break;
        case COMMAND_SET_PASSWORD:
            cout << "password: ";
            getline(cin, input);
            setPassword(input);
            break;
        case COMMAND_SET_DATABASE_NAME:
            cout << "dataBaseName: ";
            getline(cin, input);
            setDataBaseName(input);
            break;
        case COMMAND_SET_DATABASE_HOST:
            cout << "dataBaseHost: ";
            getline(cin, input);
            setDataBaseHost(input);
            break;
        case COMMAND_SET_TABLE_NAME:
            cout << "tableName: ";
            getline(cin, input);
            setTableName(input);
            break;
        case COMMAND_SET_LOG_LOCATION:
            cout << "logLocation: ";
            getline(cin, input);
            setLogLocation(input);
            break;
        case COMMAND_SET_THREAD_COUNT:
            cout << "threadCount: ";
            getline(cin, input);
            if(isnumber(input))
                setThreadCount(stoi(input));
            else
                cout << "need integer\n";
            break;
        default:
            cout << "error \n";
        }
    }
}

struct fields
{
    string name;
    string value;
} values[commandsCount];

void Config::makeValueStructure()
{
    values[0].name = "port";
    values[0].value = port;
    values[1].name = "userName";
    values[1].value = userName;
    values[2].name = "password";
    values[2].value = password;
    values[3].name = "dataBaseName";
    values[3].value = dataBaseName;
    values[4].name = "dataBaseHost";
    values[4].value = dataBaseHost;
    values[5].name = "tableName";
    values[5].value = tableName;
    values[6].name = "logLocation";
    values[6].value = logLocation;
    values[7].name = "threadCount";
    values[7].value = to_string(threadCount);
}

void Config::makeConfigFile()
{
    makeValueStructure();
    ofstream config("settings.conf");
    config << "Settings: \n";
    for (int i = 0; i < commandsCount; i++)
    {
       config << values[i].name << ": " << values[i].value << "\n";
    }
    config.close();
}

void Config::scanConfigFile()
{
	ifstream inputStream("settings.conf");
    if(!inputStream.is_open())
    {
        setDefaultConfig();
    }

    string settings;
    ifstream config;
    config.open("settings.conf");

    getline(config,settings);

    getline(config,settings);
    port = settings.substr(values[0].name.size()+2);

    getline(config,settings);
    userName = settings.substr(values[1].name.size()+2);

    getline(config,settings);
    password = settings.substr(values[2].name.size()+2);

    getline(config,settings);
    dataBaseName = settings.substr(values[3].name.size()+2);

    getline(config,settings);
    dataBaseHost = settings.substr(values[4].name.size()+2);

    getline(config,settings);
    tableName = settings.substr(values[5].name.size()+2);

    getline(config,settings);
    logLocation = settings.substr(values[6].name.size()+2);

    getline(config,settings);
    threadCount = stoi(settings.substr(values[7].name.size()+2));

    config.close();
}

void Config::showConfigFile()
{
    ifstream config;
    string buf;
    config.open("settings.conf");
    getline(config,buf);
    cout << buf;
    while(!config.eof())
    {
        cout << '\n';
        getline(config,buf);
        cout << buf;
    }
}

void Config::setDefaultConfig()
{
    port = "8000";
    userName = "-----";
    password = "-----";
    dataBaseName = "-----";
    dataBaseHost = "-----";
    tableName = "-----";
    logLocation = ".";
    threadCount = 8;
    makeConfigFile();
}

void Config::help()
{
    cout << "commands:\n\t"
            "exit\n\t"
            "showconfig\n\t"
            "setdefault";
    for(int i=0; i < commandsCount; i++)
    {
        cout << "\n\t" << "get";
        for(int j=0; j < values[i].name.size(); j++)
        {
            cout << (char)tolower(values[i].name[j]);
        }
    }
    for(int i=0; i < commandsCount; i++)
    {
        cout << "\n\t" << "set";
        for(int j=0; j < values[i].name.size(); j++)
        {
            cout << (char)tolower(values[i].name[j]);
        }
    }
    cout << '\n';
}

bool Config::isnumber(string value)
{
    bool num = true;
    for(int i=0; i < value.size(); i++)
    {
        if(!isdigit(value[i]))
        {
            num = false;
        }
    }
    return num;
}

long long Config::getHash(string value)
{
    long long hash = 0;
    for(int i = 0; i < value.size(); i++)
    {
       hash *= 2;
       hash += (value[i] - 'A' + 1);
    }
    return hash;
}



void Config::setPort(string value)
{
    port = value;
    makeConfigFile();
}

void Config::setUserName(string value)
{
    userName = value;
    makeConfigFile();
}

void Config::setPassword(string value)
{
    password = value;
    makeConfigFile();
}

void Config::setDataBaseName(string value)
{
    dataBaseName = value;
    makeConfigFile();
}

void Config::setDataBaseHost(string value)
{
    dataBaseHost = value;
    makeConfigFile();
}

void Config::setTableName(string value)
{
    tableName = value;
    makeConfigFile();
}

void Config::setLogLocation(string value)
{
    logLocation = value;
    makeConfigFile();
}

void Config::setThreadCount(int value)
{
    threadCount = value;
    makeConfigFile();
}

string Config::getPort()
{
    scanConfigFile();
    return port;
}

string Config::getUserName()
{
    scanConfigFile();
    return userName;
}

string Config::getPassword()
{
    scanConfigFile();
    return password;
}

string Config::getDataBaseName()
{
    scanConfigFile();
    return dataBaseName;
}

string Config::getDataBaseHost()
{
    scanConfigFile();
    return dataBaseHost;
}

string Config::getTableName()
{
    scanConfigFile();
    return tableName;
}

string Config::getLogLocation()
{
    scanConfigFile();
    return logLocation;
}

int Config::getThreadCount()
{
    scanConfigFile();
    return threadCount;
}

