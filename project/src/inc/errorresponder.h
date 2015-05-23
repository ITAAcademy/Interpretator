#ifndef ERRORRESPONDER_H
#define ERRORRESPONDER_H

#include <string>
#include <iostream>

using namespace std;

typedef std::string str;

class ErrorResponder
{
public:
    ErrorResponder();
    ~ErrorResponder();
    void showError(int nErrorCode, str sMoreText);
    void showClientError(str sHeader, str sErrorText, str sMoreText);
    str sDefaultText = "Just Error!";
};

#endif // ERRORRESPONDER_H
