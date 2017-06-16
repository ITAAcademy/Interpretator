/*#include "fcgi_stdio.h"

#include <stdlib.h>

int count;

void initialize(void)
{
  count=0;
}

int main(void)
{

  initialize();


  while (FCGI_Accept() >= 0)   {
    printf("Content-type: text/html\r\n"
           "\r\n"
           "<title>FastCGI Hello! (C, fcgi_stdio library)</title>"
           "<h1>FastCGI Hello! (C, fcgi_stdio library)</h1>"
           "Request number %d running on host <i>%s</i>\n",
            ++count, getenv("SERVER_HOSTNAME"));
  }
}*/
#ifndef MAIN_H_
#define MAIN_H_

#define ETALON_ENDING "_etalon"
#define ETALON_FOR_FUNCTION_ENDING "_for_etalon"

#include "includes.h"
#include "fcgio.h"
#include <sstream>
#include "cLang.h"
#include "codeclear.h"
#include "errorresponder.h"
#include "logfile.h"
#include "jsonParser.h"
#include "SQLconnector.h"
#include "config.h"
#include "ctpl_stl.h"
#include <iostream>
#include <string>
#include <regex>
#include <algorithm>

#include <ctime>
//#include <pstream.h>

#include <cassert>
#include <exception>
#include "FCGI_Stream.h"

//TIMER
#include <functional>
#include <chrono>
#include <future>
#include <cstdio>
#include <ctime>
#include "ctpl_stl.h"
#include "SQLConnectionPool.h"
#include "TaskCodeGenerator.h"
#include "TokenSystem.h"
#include "SQLconnector.h"

using namespace std;
using namespace code;



struct ThreadArguments {
	int id;
};


#ifndef VERSION_INTERPRETATOR
#define VERSION_INTERPRETATOR "1.106"
#endif


//static void *doit(void *a);
int Apache(void);


void processTask(int id,Job job);
void *receiveTask(void *a);

void changeIdInJsonFromOldToNew(string&json, int newId);

void show404();
string removeDoubleBrackets(string value);
void replaceAll( string &s, const string &search, const string &replace );
bool result_status(FCGI_Stream &stream, jsonParser &jSON, string operation);
bool start(FCGI_Stream &stream, jsonParser &jSON, string ip_user, string &error, bool &need_stream);
bool addTestValues(FCGI_Stream &stream, jsonParser &jSON);
bool addTests(FCGI_Stream &stream, jsonParser &jSON);
bool retreiveTests(FCGI_Stream &stream, jsonParser &jSON);
bool addTestSignature(FCGI_Stream &stream, jsonParser &jSON);
bool addNewtask( FCGI_Stream &stream, jsonParser &jSON, int thread_id, string &error, bool &need_stream);
bool addTestsToTask( FCGI_Stream &stream, jsonParser &jSON, int thread_id, string &error, bool &need_stream);
string mergeUtestsAndTask(Json::Value& tests, Json::Value& task);
string replaceSlashTabsParagBreakets (string input);

bool copyTask( FCGI_Stream &stream, jsonParser &jSON, int thread_id, string &error, bool &need_stream);
bool getJson( FCGI_Stream &stream, jsonParser &jSON, int thread_id);
bool editTask( FCGI_Stream &stream, jsonParser &jSON);
#endif
