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
	l12("getInstance");
	return connection;
}


mysqlpp::Connection*  SqlConnectionPool::create() {};
void  SqlConnectionPool::destroy(mysqlpp::Connection*) {};


SqlConnectionPool::SqlConnectionPool(const char *db_name,const char * host,const char *user,const char *pass)
{

	pthread_mutex_lock(&accept_mutex);
	// start_time = clock();
	try{
		conn = new mysqlpp::Connection(db_name,host,user,pass);
		iscon = true;
	}
	catch(mysqlpp::Exception &ex){
		iscon = false;
		logfile::addLog("SqlConnectionPool(constructor) INCORRECT " + string(ex.what()));
	}
	if (conn)
	{
		logfile::addLog ("Connection to host and database successful");
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
	if (conn->connected())
	{
		mysqlpp::Connection::thread_start();
		mysqlpp::StoreQueryResult res;
		try{
			mysqlpp::Query query( conn->query( quer) );
			res = query.store();
		}
		catch(mysqlpp::Exception &ex){
			logfile::addLog("connectToTable INCORRECT " + string(ex.what()));
		}
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
	if (conn->connected())
	{
		mysqlpp::Connection::thread_start();
		mysqlpp::StoreQueryResult res;
		try{
			mysqlpp::Query query( conn->query( quer) );
			res = query.store();
		}
		catch(mysqlpp::Exception &ex){
			logfile::addLog("getAllRecordsFromTable INCORRECT " + string(ex.what()));
		}
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



int SqlConnectionPool::lastInsertId()
{
	string quer = " SELECT LAST_INSERT_ID();" ;
	pthread_mutex_lock(&accept_mutex);
	int rezult =-1;
	if (conn->connected())
	{
		mysqlpp::Connection::thread_start();
		mysqlpp::StoreQueryResult res;
		try{
			mysqlpp::Query query( conn->query( quer) );
			res = query.store();
		}
		catch(mysqlpp::Exception &ex){
			logfile::addLog("getCustomCodeOfProgram INCORRECT " + string(ex.what()));
		}
		mysqlpp::Connection::thread_end();
		logfile::addLog (quer);


		if (res.capacity())
		{
			mysqlpp::Row row = *res.begin();
			rezult = int(row[0]);
		}
	}
	pthread_mutex_unlock(&accept_mutex);
	return rezult;
}


string SqlConnectionPool::getCustomCodeOfProgram(string ID, string text_of_program,int thrdId, string lang) {
	pthread_mutex_lock(&accept_mutex);
	string rezult ="";
	string quer = "SELECT * FROM  `" + tableName + "` where `" + labels_vec[0] +"` = "+ ID +";";
	if (conn->connected())
	{
		mysqlpp::Connection::thread_start();
		mysqlpp::StoreQueryResult res;
		try{
			mysqlpp::Query query( conn->query( quer) );
			res = query.store();
		}
		catch(mysqlpp::Exception &ex){
			logfile::addLog("getCustomCodeOfProgram INCORRECT " + string(ex.what()));
		}
		mysqlpp::Connection::thread_end();
		logfile::addLog (quer);


		if (res.capacity())
		{
			mysqlpp::Row row = *res.begin();
			string header = string(row[2]);
			string footer = string(row[4]);
			string beforeHeader = "";
			string beforeFooter = "";
			if (lang=="c++"){
				beforeHeader=
						//"#pragma once\n"
						"#include <unistd.h>\n"
						"#include <ios>\n"
						"#include <iostream>\n"
						"#include <fstream>\n"
						"#include <string>\n"
						"void process_mem_usage(double& vm_usage, double& resident_set)\n"
						"{"
						"using std::ios_base;\n"
						"using std::ifstream;\n"
						"using std::string;\n"
						"vm_usage     = 0.0;\n"
						"resident_set = 0.0;\n"
						"ifstream stat_stream(\"/proc/self/stat\",ios_base::in);\n"
						"string pid, comm, state, ppid, pgrp, session, tty_nr;\n"
						"string tpgid, flags, minflt, cminflt, majflt, cmajflt;\n"
						"string utime, stime, cutime, cstime, priority, nice;\n"
						"string O, itrealvalue, starttime;\n"
						"unsigned long vsize;\n"
						"long rss;\n"
						"stat_stream >> pid >> comm >> state >> ppid >> pgrp >> session >> tty_nr\n"
						">> tpgid >> flags >> minflt >> cminflt >> majflt >> cmajflt\n"
						">> utime >> stime >> cutime >> cstime >> priority >> nice\n"
						">> O >> itrealvalue >> starttime >> vsize >> rss;\n" // don't care about the rest

						"stat_stream.close();\n"
						"long page_size_kb = sysconf(_SC_PAGE_SIZE) / 1024;\n" // in case x86-64 is configured to use 2MB pages
						"vm_usage     = vsize / 1024.0;\n"
						"resident_set = rss * page_size_kb;\n"
						"}\n";



				beforeFooter="using std::cout;"
						"using std::endl;"
						"double vm, rss;"
						"process_mem_usage(vm, rss);"
						"cout << \"VM: \" << vm << \"; RSS: \" << rss << endl;";
			}
			else if(lang=="java")
				beforeFooter =
						"System.gc();"
						"Runtime rt = Runtime.getRuntime();"
						"long usedMB = (rt.totalMemory() - rt.freeMemory()) / 1024 / 1024;"
						"System.out.println(\"memory usage\" + usedMB);";

			//string memoryUsageC++ =
			if (beforeFooter.size() > 0)
				footer.insert(footer.size() - 2, beforeFooter);// new 11.2015 for end main!!!
			ReplaceAll(header,"#NUM#",std::to_string(thrdId));
			rezult = beforeHeader + header + "\n " +
					text_of_program + " \n" +
					/*beforeFooter+*/ footer;
			logfile::addLog(rezult);
		}
		else
		{
			logfile::addLog("empty result ");
			rezult = text_of_program;
		}
		//mysql_free_result(resptr);
	}
	l12("failed, not connected to database");
	pthread_mutex_unlock(&accept_mutex);
	return rezult;
}

//work12
bool SqlConnectionPool::addRecordsInToTable(vector<map<int,string> > records) {
	pthread_mutex_lock(&accept_mutex);
	if (conn->connected())
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
		mysqlpp::Query *query;
		logfile::addLog (quer);
		mysqlpp::SimpleResult result;
		try{
			query = new mysqlpp::Query( conn->query( quer) );
			result=query->execute();
		}
		catch(mysqlpp::Exception &ex){
			logfile::addLog("getCustomCodeOfProgram INCORRECT " + string(ex.what()));
		}
		mysqlpp::Connection::thread_end();
		if (result.rows()) {
			logfile::addLog ("Adding records in to table " + tableName + " successfull");
			delete query;
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
	if (conn->connected())
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
		mysqlpp::Query *query;
		mysqlpp::SimpleResult result;

		try{
			query = new mysqlpp::Query( conn->query( quer) );
			result=query->execute();
		}
		catch(mysqlpp::Exception &ex){
			logfile::addLog("getCustomCodeOfProgram INCORRECT " + string(ex.what()));
		}
		mysqlpp::Connection::thread_end();
		if (result.rows()) {
			logfile::addLog ("Adding records in to table " + tableName + " successfull");
			delete query;
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
	if (conn->connected())
	{
		string quer= "UPDATE `"+ tableName+ "` SET ";
		vector<int> keys;
		for (	pair<int,string> me  : records)
			keys.push_back(me.first);
		for(int a : keys){
			quer += "`"+ labels_vec[a] + "`='" + str_with_spec_character(records.find(a)->second) + "'" ;
			quer += ", ";
		}
		quer.erase(quer.size()-2);
		quer += " WHERE " ;

		//for(int a : keys)
		//quer += "`"+ labels_vec[a] + "`='" + records.find(a)->second + "'" ;




		vector<int> keys2;
		for (	pair<int,string> mal  : where)
			keys2.push_back(mal.first);
		for(int a : keys2){
			quer += "`"+tableName+"`.`"+ labels_vec[a] + "`='" + where.find(a)->second + "'" ;
			quer += " AND ";
		}
		quer.erase(quer.size()-4);
		logfile::addLog(quer);
		mysqlpp::Connection::thread_start();
		mysqlpp::Query *query;
		mysqlpp::SimpleResult result;
		try{
			query = new mysqlpp::Query( conn->query( quer) );
			result=query->execute();
		}
		catch(mysqlpp::Exception &ex){
			logfile::addLog("getCustomCodeOfProgram INCORRECT " + string(ex.what()));
		}
		mysqlpp::Connection::thread_end();
		if (result.rows()) {
			logfile::addLog ("Updating records in table " + tableName +" successfull");
			delete query;
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

bool SqlConnectionPool::isConnected()
{
	// end_time = clock();
	//
	pthread_mutex_lock(&accept_mutex);
	l12("isConnected( )");
	if (conn)
	{
		string quer = "show databases;";
		mysqlpp::Connection::thread_start();
		mysqlpp::StoreQueryResult res;
		try{
			mysqlpp::Query query( conn->query( quer) );
			res = query.store();
			iscon = true;
		}
		catch(mysqlpp::Exception &ex){
			iscon = false;
			logfile::addLog("Server not connected to DB" + string(ex.what()));
		}
		mysqlpp::Connection::thread_end();
		l12("Server connected to DB");
	}
	else logfile::addLog("Server not connected to DB");
	pthread_mutex_unlock(&accept_mutex);
	return iscon ;//&& (((end_time-start_time)/CLOCKS_PER_SEC*1000- max_idle_time())>0);
}

void SqlConnectionPool::reconect()
{l12("recoon0");

pthread_mutex_lock(&accept_mutex);
l12("recoon1");

try{
	l12("recoon3");
	conn = new mysqlpp::Connection(	Config::getInstance().dataBaseName.c_str(),
			Config::getInstance().dataBaseHost.c_str() ,
			Config::getInstance().userName.c_str() ,
			Config::getInstance().password.c_str());
	l12("recoon5");
}
catch(mysqlpp::Exception &ex){
	logfile::addLog("reconect INCORRECT " + string(ex.what()));
}
if (conn)
{
	logfile::addLog ("Connection to host and database successful");
}
else
	logfile::addLog ("Connection to host and database failed");
pthread_mutex_unlock(&accept_mutex);

}



