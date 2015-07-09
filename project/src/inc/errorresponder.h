#ifndef ERRORRESPONDER_H
#define ERRORRESPONDER_H

#include <iostream>
#include "FCGI_Stream.h"

using namespace std;

typedef std::string str;

class ErrorResponder
{
	FCGI_Stream *stream;
public:
    ErrorResponder(FCGI_Stream *stream);
    ~ErrorResponder();
    void selectStream(FCGI_Stream *stream);
    void showError(int nErrorCode, str sMoreText = " ");
    void showClientError(str sHeader, str sErrorText, str sMoreText = " ");
};


#endif // ERRORRESPONDER_H
