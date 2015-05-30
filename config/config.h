#ifndef CONFIG_H
#define CONFIG_H

#include <string>
#include <iostream>
#include <fstream>
#include <io.h>

using namespace std;

class Config
{
public:
    Config();

    string login = "defaultLogin";
    string password = "defaultPassword";
    string temp = "bla";
    int number = 1;

    void runCommandLine();
    void makeConfigFile();
    void scanConfigFile();
    void showConfigFile();
    void setDefaultConfig();
    void help();
    bool isnumber(string value);

    void setLogin(string value);
    void setPassword(string value);
    void setNumber(int value);

    string getLogin();
    string getPassword();
    int getNumber();
};

#endif // CONFIG_H
