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
#include <boost/algorithm/string.hpp>
#include <boost/foreach.hpp>

using namespace std;



class SqlConnectionPool : public mysqlpp::ConnectionPool
{
public:

  SqlConnectionPool(const char *db_name,const char * host,const char *user,const char *pass);
  ~SqlConnectionPool();
  static SqlConnectionPool&  getInstance( );
  vector<map<int,string> >   getAllRecordsFromTable( string where ="1") ;
  bool addRecordsInToTable(vector<map<int,string> > records);
  bool addRecordsInToTable(map<int,string>  records);
  bool updateRecordsInToTable(map<int,string> records,map<int,string>  where) ;
  bool connectToTable(string table, vector<string> labels);
  string getCustomCodeOfProgram(string ID, string text_of_program,int thrdId) ;
protected:
  unsigned int max_idle_time();
   mysqlpp::Connection* create() ;
   void destroy(mysqlpp::Connection*) ;

private:
   bool connected_db;
  mysqlpp::Connection* conn;
  vector<string> labels_vec;
  string labels;
  string tableName;
  const char *db_name,* host,*user,*pass;
};

#endif /* SQLCONNECTIONPOOL_H_ */
