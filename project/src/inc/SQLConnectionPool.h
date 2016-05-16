/*
 * SqlConnectionPool.h
 *
 *  Created on: Jul 1, 2015
 *      Author: yurock
 */

#ifndef SQLCONNECTIONPOOL_H_
#define SQLCONNECTIONPOOL_H_

#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <mysql++/mysql++.h>
#include <mysql++/scopedconnection.h>
#include <mysql++/cpool.h>
#include <iostream>
#include "includes.h"
#include "config.h"
#include <algorithm>
using namespace std;


class SqlConnectionPool : public mysqlpp::ConnectionPool
{

public:
	static string generateProgramCode(string header,string text_of_program, string footer, string lang  );
  static SqlConnectionPool&  getInstance( );
  SqlConnectionPool();
  ~SqlConnectionPool();
  string  getJsonFromTable( int task );
  vector<map<int,string> >   getAllRecordsFromTable( string where ="1", bool use_mutex = true) ;
  bool addRecordsInToTable(vector<map<int,string> > records);
  bool addRecordsInToTable(map<int,string>  records);
  bool copyRecordFromIdToNewId(int id, int new_id);
  bool updateRecordFromIdToNewId(int id, int new_id);
  bool updateRecordsInToTable(map<int,string> records,map<int,string>  where, bool use_mutex = true) ;
  bool connectToTable(string table, vector<string> labels);
  string getCustomCodeOfProgram(string ID, string text_of_program,int thrdId, string lang) ;
  bool isConnected();
  void reconect();
int lastInsertId();
protected:
  unsigned int max_idle_time();
   mysqlpp::Connection* create() ;
   void destroy(mysqlpp::Connection*) ;

   string getLabelVecByInd(int ind);

private:
   bool iscon ;
   int max_time;
   int timer;
   int start_time,end_time;
   SqlConnectionPool(const char *db_name,const char * host,const char *user,const char *pass);
   bool connected_db;
   pthread_mutex_t accept_mutex = PTHREAD_MUTEX_INITIALIZER;
  mysqlpp::Connection* conn;
   vector<string> labels_vec;
  string labels;
  string tableName;
  const char *db_name,* host,*user,*pass;
};

#endif /* SQLCONNECTIONPOOL_H_ */
