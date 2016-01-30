/*
 * SqlConnectionPool.cpp
 *
 *  Created on: Jul 1, 2015
 *      Author: yurock
 */

#include "inc/SQLConnectionPool.h"
#include "mysql.h"

SqlConnectionPool&  SqlConnectionPool::getInstance()
{
	static SqlConnectionPool connection (
			Config::getInstance().dataBaseName.c_str(),
			Config::getInstance().dataBaseHost.c_str() ,
			Config::getInstance().userName.c_str() ,
			Config::getInstance().password.c_str());
	INFO("SQLConnectionPool created");
	return connection;
}

SqlConnectionPool::SqlConnectionPool()
{
	reconect();
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
		ERROR("SqlConnectionPool(constructor) INCORRECT " + string(ex.what()));
	}
	if (conn)
	{
		DEBUG("Connection to host and database successful");
	}
	else
	{
		ERROR("Connection to host and database failed");
	}
	pthread_mutex_unlock(&accept_mutex);
}




SqlConnectionPool::~SqlConnectionPool()
{
	pthread_mutex_lock(&accept_mutex);
	this->release( conn );
	//delay 1-4 sec before it will be able to using
	//srand( time(0) );
	//sleep( rand()%4 + 1 );

	delete conn;
	clear();
	mysqlpp::Connection::thread_end();
	INFO("Pool connection deleted.");
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
			ERROR("connectToTable INCORRECT " + string(ex.what()));
		}
		mysqlpp::Connection::thread_end();
		if (res.capacity()) {
			this->labels="`" + labels_vec[0] +"`" ;
			for (int i=1; i<labels_vec.size(); i++)
				this->labels+=",`" + labels_vec[i] +"`" ;

			INFO("Connection  to table " + table + " successfull");
			pthread_mutex_unlock(&accept_mutex);
			return true;
		}

		ERROR ("Connection  to table " + table + " failed");
	}
	else
	{
		ERROR("Connection  to table " + table + " failed, because no connection to database");
	}
	pthread_mutex_unlock(&accept_mutex);
	return false;
}

string SqlConnectionPool::getLabelVecByInd(int ind)
{
	if (ind >= 0 && ind < labels_vec.size())
		return labels_vec[ind];
	else
		return string("");
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
			ERROR("getAllRecordsFromTable INCORRECT " + string(ex.what()));
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
			INFO("Getting all records from table " + tableName + " successfull");
		}
		else
		{
			ERROR("Getting all records from table " + tableName + " failed or table is empty");
		}
	}
	pthread_mutex_unlock(&accept_mutex);
	return records;
}

////////////////////

string  SqlConnectionPool::getJsonFromTable( int task )  {
	pthread_mutex_lock(&accept_mutex);
	string json="";
	vector<map<int,string> >  records;
	string quer = "SELECT `json` FROM `" + tableName + "` WHERE `id` = " + to_string(task);

	if (conn->connected())
	{
		mysqlpp::Connection::thread_start();
		mysqlpp::StoreQueryResult res;
		try{
			mysqlpp::Query query( conn->query( quer) );
			res = query.store();
		}
		catch(mysqlpp::Exception &ex){
			ERROR("getJsonFromTable INCORRECT " + string(ex.what()));
		}
		mysqlpp::Connection::thread_end();

		if (res.capacity())
		{
			mysqlpp::StoreQueryResult::const_iterator it;
			for (it = res.begin(); it != res.end(); ++it)
			{
				map<int,string> temp;
				mysqlpp::Row row = *it;
				json = string(row[0]);
			}
			INFO("getJsonFromTable " + tableName + " successfull");
		}
		else
		{
			ERROR("Getting json from table " + tableName + " failed or table is empty");
		}
	}
	pthread_mutex_unlock(&accept_mutex);

	return json;
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
		catch(mysqlpp::Exception &ex)
		{
			ERROR("get lastInsertId INCORRECT " + string(ex.what()));
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
		catch(mysqlpp::Exception &ex)
		{
			ERROR("getCustomCodeOfProgram INCORRECT " + string(ex.what()));
		}
		mysqlpp::Connection::thread_end();
		INFO(quer);

		if (res.capacity())
		{
			mysqlpp::Row row = *res.begin();
			string header = string(row[1]);
			string footer = string(row[3]);
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
			int secondBracketFromEndPosition = 0;
			if (lang == "java")
				secondBracketFromEndPosition = footer.length() - 3;//footer.substr(0,footer.find_last_of('{')-1).find_last_of('{');//second from end
			else
				if (lang == "c++")
					secondBracketFromEndPosition=footer.length()-2;
			//secondBracketFromEndPosition--;
			//if (secondBracketFromEndPosition<0)secondBracketFromEndPosition=0;


			if (beforeFooter.size() > 0)
				//footer.append(beforeFooter);
				footer.insert(secondBracketFromEndPosition, beforeFooter);// new 11.2015 for end main!!!
			//ReplaceAll(header,"#NUM#",std::to_string(thrdId));
			rezult = beforeHeader + header + "\n " +
					text_of_program + " \n " +
					/*beforeFooter+*/ footer;
			logfile::addLog(rezult);
		}
		else
		{
			ERROR("getCustomCodeOfProgram: empty result ");
			rezult = text_of_program;
		}
		//mysql_free_result(resptr);
	}
	else
	{
		ERROR("getCustomCodeOfProgram failed, not connected to database");
	}
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
			ERROR("addRecordsInToTable INCORRECT " + string(ex.what()));
		}
		mysqlpp::Connection::thread_end();
		if (result.rows()) {
			INFO ("Adding records in to table " + tableName + " successfull");
			delete query;
			pthread_mutex_unlock(&accept_mutex);
			return true;
		}
		ERROR ("Adding records in to table " + tableName + " failed");
	}
	else
	{
		ERROR("addRecordsInToTable failed, not connected to database");
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
					quer += " '" + str_with_spec_character(records.find(keys[r])->second) + "' " ;
					r++;
				}
				else quer += "DEFAULT";
				if (y<num_of_labels - 1)  quer += ",";
			}
			quer += ");";
		}
		INFO ("addRecordsInToTable: " + quer);
		mysqlpp::Connection::thread_start();
		mysqlpp::Query *query;
		mysqlpp::SimpleResult result;

		try{
			query = new mysqlpp::Query( conn->query( quer) );
			result=query->execute();
		}
		catch(mysqlpp::Exception &ex){
			ERROR("addRecordsInToTable INCORRECT " + string(ex.what()));
		}
		mysqlpp::Connection::thread_end();
		if (result.rows()) {
			INFO ("Adding records in to table " + tableName + " successfull");
			delete query;
			pthread_mutex_unlock(&accept_mutex);
			return true;
		}
		ERROR ("Adding records in to table " + tableName + " failed");
	}
	else
	{
		ERROR("addRecordsInToTable failed, not connected to database");
	}
	pthread_mutex_unlock(&accept_mutex);
	return false;
}


bool SqlConnectionPool::updateRecordsInToTable(map<int,string> records,map<int,string>  where) {
	pthread_mutex_lock(&accept_mutex);
	if (conn->connected())
	{

		string quer= "UPDATE `"+ tableName+ "` SET ";

		for (	pair<int,string> me  : records)
		{
			int key = me.first;
			quer += "`"+ getLabelVecByInd(key) + "`='" + str_with_spec_character(me.second) + "', " ;//SpecSymbol
			//quer += "`1`='" + str_with_spec_character(me.second) + "', " ;//SpecSymbol
		}

		quer.erase(quer.size()-2);
		quer += " WHERE " ;

		for (	pair<int,string> mal  : where)
		{
			int key = mal.first;
			quer += "`"+tableName+"`.`"+ getLabelVecByInd(key) + "`='" + mal.second + "' AND " ;
		}

		quer.erase(quer.size()-4);
		INFO("updateRecordsInToTable: " + quer);

		mysqlpp::Query *query;
		mysqlpp::SimpleResult result;

		mysqlpp::Connection::thread_start();
		try{
			query = new mysqlpp::Query( conn->query( quer) );
			result=query->execute();
		}
		catch(mysqlpp::Exception &ex){
			ERROR("updateRecordsInToTable INCORRECT " + string(ex.what()));
		}
		mysqlpp::Connection::thread_end();
		if (result.rows()) {
			INFO ("Updating records in table " + tableName +" successfull");
			delete query;
			pthread_mutex_unlock(&accept_mutex);
			return true;
		}
		ERROR ("Updating records in table " + tableName +" failed");
	}
	else
	{
		ERROR("updateRecordsInToTable failed, not connected to database");
	}
	pthread_mutex_unlock(&accept_mutex);
	return false;

}


unsigned int SqlConnectionPool::max_idle_time()
{
	//3 seconds
	return 3;

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
			INFO("Server connected to DB");
		}
		catch(mysqlpp::Exception &ex){
			iscon = false;
			ERROR("Server not connected to DB" + string(ex.what()));
		}
		mysqlpp::Connection::thread_end();
	}
	else ERROR("Server not connected to DB");
	pthread_mutex_unlock(&accept_mutex);
	return iscon ;//&& (((end_time-start_time)/CLOCKS_PER_SEC*1000- max_idle_time())>0);
}

void SqlConnectionPool::reconect()
{
	pthread_mutex_lock(&accept_mutex);
	try{
		conn = new mysqlpp::Connection(	Config::getInstance().dataBaseName.c_str(),
				Config::getInstance().dataBaseHost.c_str() ,
				Config::getInstance().userName.c_str() ,
				Config::getInstance().password.c_str());
	}
	catch(mysqlpp::Exception &ex){
		ERROR("reconect INCORRECT " + string(ex.what()));
	}
	if (conn)
	{
		INFO ("Connection to host and database successful");
	}
	else
		ERROR ("Connection to host and database failed");
	pthread_mutex_unlock(&accept_mutex);

}



