#ifndef LOGFILE_H
#define LOGFILE_H
#define normLog 0
#define errLog 1

#include "includes.h"
#include <fstream>
#include <iostream>
#include <stdio.h>      /* printf */
#include <stdlib.h>     /* strtol */
#include <string.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <pthread.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <iomanip>
#include <list>

#include "fcgi_config.h"
#include "fcgiapp.h"

using namespace std;

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
    static void clear();
    static string getDateStamp();
    static bool isFileExist(const char *fileName);
    static void putLogInArchiveTar();
private:
    FCGX_Request *Request;
    char *returnIP();
    char *returnPOST();
    char *returnBrowserVersion();
    char *returnOS();
    char *returnData();

    /*
     * no control symbol
     */
    static int legthClearnStr(string str);
};

#endif // LOGFILE_H
