#include "config.h"

Config::Config()
{

}

void Config::runCommandLine()
{
    string input;

    scanConfigFile();

    while(1)
    {
        makeConfigFile();

        cout << '>';
        getline(cin, input);

        if(input == "exit")
        {
            break;
        }
        else
        if(input == "help")
        {
            help();
        }
        else
        if(input == "showconfig")
        {
            showConfigFile();
        }
        else
        if(input == "setdefault")
        {
            setDefaultConfig();
        }
        else
        if(input == "getlogin")
        {
            cout << "Login: " << getLogin() << "\n";
        }
        else
        if(input == "getpassword")
        {
            cout << "Password: " << getPassword() << "\n";
        }
        else
        if(input == "getnumber")
        {
            cout << "Number: " << getNumber() << "\n";
        }
            else
        if(input == "setlogin")
        {
            cout << "Login: ";
            getline(cin, input);
            setLogin(input);
        }
        else
        if(input == "setpassword")
        {
            cout << "Password: ";
            getline(cin, input);
            setPassword(input);
        }
        else
        if(input == "setnumber")
        {
            cout << "Number: ";
            getline(cin, input);
            if(isnumber(input))
                setNumber(stoi(input));
            else
                cout << "need integer\n";
        }
        else
            cout << "error \n";
    }
}

void Config::makeConfigFile()
{
    ofstream config("settings.conf");
    config << "Settings: \n";
    config << "login: " + login + "\n";
    config << "password: " + password + "\n";
    config << "number: " << number << "\n";
    config.close();
}

void Config::scanConfigFile()
{
    if(_access("settings.conf", 0))
    {
        makeConfigFile();
    }
    string settings;
    ifstream config;
    config.open("settings.conf");

    getline(config,settings);

    getline(config,settings);
    login = settings.substr(7);

    getline(config,settings);
    password = settings.substr(10);

    getline(config,settings);
    temp = settings.substr(8);
    number = stoi(temp);

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
    login = "defaultLogin";
    password = "defaultPassword";
    number = 1;
    makeConfigFile();
}

void Config::help()
{
    cout << "commands:\n\texit\n\tshowconfig\n\tsetdefault\n\tsetlogin\n\tsetpassword\n\tsetnumber\n\tgetlogin\n\tgetpassword\n\tgetnumber\n";
}

bool Config::isnumber(string value)
{
    //int numinput = 0;
    bool num = true;
    for(int i=0; i < value.size(); i++)
    {
        if(isdigit(value[i]))
        {
            //numinput*=10;
            //numinput+=value[i]-48;
        }
        else
        {
            num = false;
        }
    }
    return num;
}

void Config::setLogin(string value)
{
    login = value;
    makeConfigFile();
}

void Config::setPassword(string value)
{
    password = value;
    makeConfigFile();
}

void Config::setNumber(int value)
{
    number = value;
    makeConfigFile();
}

string Config::getLogin()
{
    return login;
}

string Config::getPassword()
{
    return password;
}

int Config::getNumber()
{
    return number;
}

