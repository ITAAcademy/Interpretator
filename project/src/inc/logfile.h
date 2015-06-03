#ifndef LOGFILE_H
#define LOGFILE_H
#define normLog 0
#define errLog 1

#include <fstream>
#include "includes.h"

class logfile
{
public:
    logfile(FCGX_Request *request);
    ~logfile();
    void AddLog();
    static void AddLog(FCGX_Request *request, string addStr = " ");
    static void AddLog(string str);
private:
    FCGX_Request *Request;
    char *returnIP();
    char *returnPOST();
    char *returnBrowserVersion();
    char *returnOS();
    char *returnData();
    static char *getDateStamp();
};

#endif // LOGFILE_H
