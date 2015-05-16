#include <QCoreApplication>
#include "codeclear.h"
#include <iostream>
#include <fstream>
#include <conio.h>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    std::ifstream ifs("D:/Work/Interpretator/Code_Clearing/test.cpp");

    string str = "";
//    string test = "    for(int \t i = 0; \a \b \v \f  i < (int)str.size();   i++) { \n    str[i] = str[i+1];  \r   }";

    std::getline(ifs,str,'\0');

//    std::cout << test << endl << endl;
    std::cout << str << endl << endl;

    _getch();

    CodeClear code;

//    code.ClearText(test);
    code.ClearText(str);

//    std::cout << test << endl << endl;
    std::cout << str << endl << endl;

    return a.exec();
}
