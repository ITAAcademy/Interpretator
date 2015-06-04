#ifndef LOGFILE_H
#define LOGFILE_H
#define normLog 0
#define errLog 1

#include <fstream>
#include "includes.h"

/*
 * non staic not haven't realization
 */
class logfile
{
public:
    logfile(FCGX_Request *request);
    ~logfile();
    void addLog();
    /*
     *  add some info from request + str
     */
    static void addLog(FCGX_Request *request, string addStr = " ");
    /*
     *  add str to log.txt (also date stamp)
     */
    static void addLog(string str);
    static void addLog(int threadID, string str);
private:
    FCGX_Request *Request;
    char *returnIP();
    char *returnPOST();
    char *returnBrowserVersion();
    char *returnOS();
    char *returnData();
    static char * getDateStamp();
    /*
     * no control symbol
     */
    static int legthClearnStr(string str);
};

#endif // LOGFILE_H
