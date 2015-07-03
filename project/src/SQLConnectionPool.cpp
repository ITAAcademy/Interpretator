/*
 * SqlConnectionPool.cpp
 *
 *  Created on: Jul 1, 2015
 *      Author: yurock
 */

#include "inc/SQLConnectionPool.h"

 SqlConnectionPool&  SqlConnectionPool::getInstance()
 {

	static SqlConnectionPool connection (
			Config::getInstance().dataBaseName.c_str(),
			Config::getInstance().dataBaseHost.c_str() ,
			Config::getInstance().userName.c_str() ,
			Config::getInstance().password.c_str());

	return connection;
}


 mysqlpp::Connection*  SqlConnectionPool::create() {};
  void  SqlConnectionPool::destroy(mysqlpp::Connection*) {};


  SqlConnectionPool::SqlConnectionPool(const char *db_name,const char * host,const char *user,const char *pass)
  {
		pthread_mutex_lock(&accept_mutex);
	  connected_db = false;
	  conn = new mysqlpp::Connection(db_name,host,user,pass);
	  if (conn)
	  {
		  logfile::addLog ("Connection to host and database successful");
		  connected_db = true;
	  }
	  else
		  logfile::addLog ("Connection to host and database failed");
		pthread_mutex_unlock(&accept_mutex);
  }




 SqlConnectionPool::~SqlConnectionPool()
  {
		pthread_mutex_lock(&accept_mutex);
	 this->release( conn );
	    //delay 1-4 sec before it will be able to using
	 srand( time(0) );
	     sleep( rand()%4 + 1 );

	delete conn;
    clear();
    mysqlpp::Connection::thread_end();
    logfile::addLog("Pool connection deleted.");
    pthread_mutex_unlock(&accept_mutex);
  }

 //work12
 bool SqlConnectionPool::connectToTable(string table, vector<string> labels) {
		pthread_mutex_lock(&accept_mutex);
		tableName=table;
		this->labels_vec = labels;
		string quer = "SHOW TABLES FROM  `" +
		Config::getInstance().dataBaseName +"` LIKE  '" + table +"'";
if (connected_db)
{
	mysqlpp::Connection::thread_start();
		mysqlpp::Query query( conn->query( quer) );
		mysqlpp::StoreQueryResult res = query.store();
		mysqlpp::Connection::thread_end();
		if (res.capacity()) {
			 this->labels="`" + labels_vec[0] +"`" ;
			 	for (int i=1; i<labels_vec.size(); i++)
			 		this->labels+=",`" + labels_vec[i] +"`" ;

		logfile::addLog ("Connection  to table " + table + " successfull");
		pthread_mutex_unlock(&accept_mutex);
		return true;
		}

		logfile::addLog ("Connection  to table " + table + " failed");
}
pthread_mutex_unlock(&accept_mutex);
return false;
 }

//work11
 vector<map<int,string> >  SqlConnectionPool::getAllRecordsFromTable( string where )  {
		pthread_mutex_lock(&accept_mutex);

 	 vector<map<int,string> >  records;
 	 	string quer = "SELECT * FROM `" + tableName + "` WHERE "+where;
 	 	l12 (quer);
 	 	if (connected_db)
 	 	{
 	 		mysqlpp::Connection::thread_start();
 	 				mysqlpp::Query query( conn->query( quer) );
 	 				mysqlpp::StoreQueryResult res = query.store();
 	 				mysqlpp::Connection::thread_end();
 	 	  if (res.capacity())
 	 	  {

 	 		mysqlpp::StoreQueryResult::const_iterator it;
 	 		            for (it = res.begin(); it != res.end(); ++it)
 	 		            {
 	 		            	map<int,string> temp;
 	 		                mysqlpp::Row row = *it;
 	 		              for( int i=0; i < res.num_fields(); i++)
 	 		              {
 	 		                string ss = string(row[i]);
 	 		              temp.insert( {i, ss } );
 	 		            //l12(ss);
 	 		              }
 	 		            records.push_back(temp);
 	 		             }
 	 	logfile::addLog ("Getting all records from table " + tableName + " successfull");
 	 	}
 	 	  else logfile::addLog ("Getting all records from table " + tableName + " failed or table is empty");
 	 	}
 	 	pthread_mutex_unlock(&accept_mutex);
 	 return records;
 }


 string SqlConnectionPool::getCustomCodeOfProgram(string ID, string text_of_program,int thrdId) {
		pthread_mutex_lock(&accept_mutex);
	 string rezult ;
 string quer = "SELECT * FROM  `" + tableName + "` where `" + labels_vec[0] +"` = "+ ID +";";
 if (connected_db)
  	 	{
  	 		mysqlpp::Connection::thread_start();
  	 				mysqlpp::Query query( conn->query( quer) );
  	 				mysqlpp::StoreQueryResult res = query.store();

  	 				mysqlpp::Connection::thread_end();
  	 				logfile::addLog (quer);


 if (res.capacity())
	 	  {
	 mysqlpp::Row row = *res.begin();
 string header = string(row[2]);
 string footer = string(row[4]);
 boost::replace_all(header,"#NUM#",std::to_string(thrdId));
 rezult = str_with_spec_character(header) + "\n" +
 text_of_program + "\n" +
 str_with_spec_character(footer);
 }
 else rezult = "empty";
 //mysql_free_result(resptr);
 }
 rezult = "failed, not connected to database";
 pthread_mutex_unlock(&accept_mutex);
 return rezult;
 }

//work12
 bool SqlConnectionPool::addRecordsInToTable(vector<map<int,string> > records) {
		pthread_mutex_lock(&accept_mutex);
	 if (connected_db)
	 {
 	string quer= "INSERT INTO `" + tableName + "` ("+ this->labels +") Values (";
 	int num_of_querys = records.size();
 				//num of querys
 				for (int i=0; i<num_of_querys; i++) {
 					//get keys
 					// what a map<int, int> is made of
 						vector<int> keys;
 							for (	pair<int,string> me  : records[i])
 								keys.push_back(me.first);
 							std::sort(keys.begin(),keys.end());
 				int num_of_labels = labels_vec.size();
 				int r=0;
 					for (int y=0; y< num_of_labels; y++) {
 						if (keys[r] == y) {
 							quer += " \"" + records[i].find(keys[r])->second + "\" " ;
 							r++;
 						}
 						else quer += "DEFAULT";
 						if (y<num_of_labels - 1)  quer += ",";
 					}
 					if (i<num_of_querys - 1)  quer += "),(";
 					else  quer += ");";
 				}

			mysqlpp::Connection::thread_start();
			logfile::addLog (quer);
					mysqlpp::Query query( conn->query( quer) );
					query.exec();
					mysqlpp::Connection::thread_end();
			if (query.result_empty()) {
 				logfile::addLog ("Adding records in to table " + tableName + " successfull");
 				pthread_mutex_unlock(&accept_mutex);
 				return true;
 			}
 				logfile::addLog ("Adding records in to table " + tableName + " failed");
	 }
	 pthread_mutex_unlock(&accept_mutex);
 					return false;

 }

//work12
 bool SqlConnectionPool::addRecordsInToTable(map<int,string> records) {
		pthread_mutex_lock(&accept_mutex);
	 if (connected_db)
	 {
 	string quer= "INSERT INTO `" + tableName + "` ("+ this->labels +") Values (";
 				{
 					//get keys
 					// what a map<int, int> is made of
 						vector<int> keys;
 							for (	pair<int,string> me  : records)
 								keys.push_back(me.first);
 							std::sort(keys.begin(),keys.end());
 				int num_of_labels = labels_vec.size();
 				int r=0;
 					for (int y=0; y< num_of_labels; y++) {
 						if (keys[r] == y) {
 							quer += " \"" + records.find(keys[r])->second + "\" " ;
 							r++;
 						}
 						else quer += "DEFAULT";
 						if (y<num_of_labels - 1)  quer += ",";
 					}
 					 quer += ");";
 				}
			logfile::addLog (quer);
			mysqlpp::Connection::thread_start();
					mysqlpp::Query query( conn->query( quer) );
					query.exec();
					mysqlpp::Connection::thread_end();
			if (query.result_empty()) {
 				logfile::addLog ("Adding records in to table " + tableName + " successfull");
 				pthread_mutex_unlock(&accept_mutex);
 				return true;
 			}
 				logfile::addLog ("Adding records in to table " + tableName + " failed");
	 }
	 pthread_mutex_unlock(&accept_mutex);
 					return false;
 }


 bool SqlConnectionPool::updateRecordsInToTable(map<int,string> records,map<int,string>  where) {
		pthread_mutex_lock(&accept_mutex);
	 if (connected_db)
	 {
 	string quer= "UPDATE `"+ tableName+ "` SET ";
 	vector<int> keys;
 	for (	pair<int,string> me  : records)
 		keys.push_back(me.first);
 	std::sort(keys.begin(),keys.end());
 	int r=0;
 	for (int y=0; y< records.size(); y++) {
 	if (keys[r] == y) {
 		quer += "`"+ labels_vec[r] + "`=`" + records.find(keys[r])->second + "` " ;
 	r++;
 	quer += ",";
 	}
 	}
 	quer += " WHERE " ;

 	vector<int> keys2;
 for (	pair<int,string> mal  : where)
 	keys2.push_back(mal.first);
 std::sort(keys.begin(),keys.end());
 r=0;
 for (int y=0; y< labels_vec.size(); y++) {
 if (keys2[r] == y) {
	 quer += "`"+ labels_vec[r] + "`=`" + where.find(keys2[r])->second + "` " ;
 r++;
 quer += ",";
 }
 }
 				logfile::addLog(quer);
 				mysqlpp::Connection::thread_start();
 						mysqlpp::Query query( conn->query( quer) );
 						mysqlpp::Connection::thread_end();
 				if (query.result_empty()) {
 				logfile::addLog ("Updating records in table " + tableName +" successfull");
 				pthread_mutex_unlock(&accept_mutex);
 				return true;
 				}
 				logfile::addLog ("Updating records in table " + tableName +" failed");
	 }
 					return false;
 					pthread_mutex_unlock(&accept_mutex);
 }


 unsigned int SqlConnectionPool::max_idle_time()
   {
		pthread_mutex_lock(&accept_mutex);
     //3 seconds
     return 3;
 	pthread_mutex_unlock(&accept_mutex);
   }



