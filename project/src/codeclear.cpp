#include "inc/codeclear.h"

CodeClear::CodeClear()
{
    sumbol.push_back('\a');
    sumbol.push_back('\b');
    sumbol.push_back('\t');
    sumbol.push_back('\n');
    sumbol.push_back('\v');
    sumbol.push_back('\r');
    sumbol.push_back('\f');
}

CodeClear::~CodeClear()
{
    sumbol.clear();
}

void CodeClear::SomeExtraSpace(string &str)
{
    string right_str = "";

    for(int i = 0; i < (int)str.size(); i++)
    {
        if(str[i] == str[i+1] && str[i] == ' ');
        else
            right_str += str[i];
    }

    str = right_str;
}

void CodeClear::Trim(string &str)
{
	str.erase(str.find_last_not_of(" \n\r\t")+1);
}

void CodeClear::ClearText(string &str)
{
    for(int i = 0; i < (int)sumbol.size(); i++)
    {
        replace(str.begin(), str.end(), sumbol[i], ' ');
    }

    SomeExtraSpace(str);
    Trim(str);
}
