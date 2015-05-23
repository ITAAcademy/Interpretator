#ifndef LOGFILE_H
#define LOGFILE_H
#define normLog 0
#define errLog 1

#include <fstream>

class logfile
{
public:
    logfile(FCGX_Request request);
    ~logfile();
    void AddLog();
private:
    FCGX_Request Request;
    char *returnIP();
    char *returnPOST();
    char *returnBrowserVersion();
    char *returnOS();
    char *returnData();
};

#endif // LOGFILE_H
