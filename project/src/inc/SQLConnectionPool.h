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
#include <iostream>
#include "includes.h"

using namespace std;

/*
class MyConnectionPool : public mysqlpp::ConnectionPool
{
public:
  MyConnectionPool( const char *db, const char *server,
                    const char *user, const char *password );

  ~MyConnectionPool();
protected:
  //superclass method
  mysqlpp::Connection* create();
  void destroy( mysqlpp::Connection *con );
  unsigned int max_idle_time();
private:
  std::string p_db, p_server, p_user, p_password;   // параметры соединения
};

MyConnectionPool *pool = 0;

static void* work_thread( void *running_flag );
//static int create_thread( (void *)(*worker)(void *), (void *)arg );
*/
#endif /* SQLCONNECTIONPOOL_H_ */
