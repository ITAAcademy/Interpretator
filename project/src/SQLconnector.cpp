/*
 * SQLconnector.cpp
 *
 *  Created on: Jun 10, 2015
 *      Author: root
 */

#include "inc/SQLconnector.h"
#include "inc/logfile.h"
#include <boost/foreach.hpp>

string str_with_spec_character(string s) {

	int size = s.size();
	string rezult;
	for (int i=0;i <size; i++) {
		if (s[i] ==  '\"' || s[i] ==  '\'' ) {
			rezult+= "\\";
			rezult+= s[i];
		}
		else
			rezult+= s[i];
	}
	return rezult;
}

ConnectorSQL::ConnectorSQL(){

}
ConnectorSQL::~ConnectorSQL(){
		delete res;
		delete stmt;
		delete con;
}
ConnectorSQL& ConnectorSQL::getInstance(){
	static ConnectorSQL conn;
		conn.connect_table = false;
		if(conn.driver == NULL){
		try
			{
				conn.driver = get_driver_instance();
			}
			catch (sql::SQLException *e)
			{
				string ss = "Could not get a database driver. Error message: ";
				ss+=+ e->what() ;

				logfile::addLog(ss);
			}
		}
	return conn;
}



bool ConnectorSQL::connectToDataBase(string database) {
	std::lock_guard<std::recursive_mutex> locker(_lock);
	 connect_table = false;
	 stmt = NULL;
	 logfile::addLog("1");
	 try {
	 con->setSchema(database);
}
			catch (sql::SQLException *e)
			{
				string ss = "Connection to database " + database + " failed. Error message: ";
				ss+=+ e->what() ;
				logfile::addLog(ss);
				return false;
			}
			  stmt = con->createStatement();
			  return true;
}


void ConnectorSQL::resetConection() {
	delete res;
		delete stmt;
		delete con;
}

bool ConnectorSQL::connectToHost(string host,string user, string password) {
	std::lock_guard<std::recursive_mutex> locker(_lock);
	connect_table = false;
	//if(con == NULL){
if (driver == NULL)
		return false;
	//cout << driver->getName();
con = NULL;
	//if (con == NULL)
try {
		con = driver->connect(host, user, password);
}
			catch (sql::SQLException e)
			{
				string ss = "Connection  to host failed. Error message: ";
				ss+=+ e.what() ;
				logfile::addLog(ss);
			}
	if (con == NULL) {
		//printf("Connection  to host segwereswr\n");
		return false;
	}
	logfile::addLog("Connection to host successful");
		  return true;
//}	return true;
}
bool ConnectorSQL::connectToTable(string table, vector<string> labels) {
	std::lock_guard<std::recursive_mutex> locker(_lock);
	connect_table = false;
		//if (this->table.empty()) {
	this->tableName=table;
	this->labels_vec = labels;
	this->labels="`" + labels[0] +"`" ;
	labels_num=1;
	for (int i=1; i<labels.size(); i++) {
		this->labels+=",`" + labels[i] +"`" ;
		labels_num++;
	}


		try {
			res = stmt->executeQuery("SELECT * FROM  `" + table + "` LIMIT 1");
			//res->next();
}
			catch (sql::SQLException *e)
			{
				string ss = "Connection  to table " + table + " failed. Error message: ";
				ss+=+ e->what() ;
				logfile::addLog(ss);
				connect_table = false;
						 return false;
			}
			logfile::addLog("Connection  to table " + table + " successful");
		 connect_table = true;
		 return true;

}

bool ConnectorSQL::isConnectedToTable() {
	std::lock_guard<std::recursive_mutex> locker(_lock);
return connect_table;
}

bool ConnectorSQL::addRecordsInToTable(vector<map<int,string> > records) {
	std::lock_guard<std::recursive_mutex> locker(_lock);
	string query= "INSERT INTO `" + tableName + "` ("+ this->labels +") Values (";// + this->records +");"
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
					query += " \"" + records[i].find(keys[r])->second + "\" " ;
						r++;
					}
					else query += "DEFAULT";
					if (y<num_of_labels - 1)  query += ",";
				}
				if (i<num_of_querys - 1)  query += "),(";
				else  query += ");";

			}
			//cout<< query << "\n";
			logfile::addLog(query);
			try		{
				stmt->execute(query) ;
					}
					catch (sql::SQLException e)
					{
						string ss = "Could not add records in to table:  ";
						ss+=+ e.what() ;
						logfile::addLog(ss);
						return false;
					}
					return true;

}

bool ConnectorSQL::addRecordsInToTable(map<int,string> records) {
	std::lock_guard<std::recursive_mutex> locker(_lock);
	string query= "INSERT INTO `" + tableName + "` ("+ labels +") Values (";// + this->records +");"
	//int num_of_labels = labels_vec.size();
				//get keys
					pair<int,string> me; // what a map<int, int> is made of
					vector<int> keys;
						for(pair<int,string> me  : records)
							keys.push_back(me.first);
						std::sort(keys.begin(),keys.end());
			int num_of_labels = labels_vec.size();
			int r=0;
				for (int y=0; y< num_of_labels; y++) {
					if (keys[r] == y) {
					query += " \"" + records.find(keys[r])->second + "\" " ;
						r++;
					}
					else query += "DEFAULT";
					if (y<num_of_labels - 1)  query += ",";
				}
				query += ");";
				logfile::addLog(query);
				try		{
				stmt->execute(query) ;
					}
					catch (sql::SQLException *e)
					{
						string ss = "Could not add records in to table:  ";
						ss+=+ e->what() ;
						logfile::addLog(ss);
						return false;
					}
					return true;
}

//if return -1, then ID isn`t valid
string ConnectorSQL::getFullCodeOfProgram(string ID) {
	std::lock_guard<std::recursive_mutex> locker(_lock);
	string quer = "SELECT * FROM  `" + tableName + "` where `" + labels_vec[0] +"` = "+ ID +";";
		res = stmt->executeQuery(quer);
		string rezult;
		if (res->next())
		{
		 rezult = str_with_spec_character(res->getString(3)) + "\n" +
	str_with_spec_character(res->getString(4)) + "\n" +
	str_with_spec_character(res->getString(5));
		}
		else rezult = "ID does not exist";
		logfile::addLog(quer);
	return rezult;
}

string ConnectorSQL::getCustomCodeOfProgram(string ID, string text_of_program,int thrdId) {
	std::lock_guard<std::recursive_mutex> locker(_lock);
	string rezult;
	if (ID.size()>0)
	{
	string quer = "SELECT * FROM  `" + tableName + "` where `" + labels_vec[0] +"` = "+ ID +";";

		try		{
			logfile::addLog(quer);
			res = stmt->executeQuery(quer);
			}
			catch (sql::SQLException e)
			{
				string ss = "Could not run sql-reques:  ";
				ss+=+ e.what() ;

				logfile::addLog(ss);
			}

		if (res->next())
		{
		/* rezult = str_with_spec_character(res->getString(3)) + "\n" +
				 str_with_spec_character(text_of_program) + "\n" +  res->getString(5);*/
		 rezult = (res->getString(3)) + "\n" +
		 				 (text_of_program) + "\n" +  res->getString(5);
		}
		else rezult = "ID does not exist";
	}
	else rezult = "ID invalid";
	//TEST

	boost::replace_all(rezult,"#NUM#",std::to_string(thrdId));
	//TEST
	return rezult;
}

vector<map<int,string> >  ConnectorSQL::getAllRecordsFromTable() {
	std::lock_guard<std::recursive_mutex> locker(_lock);
	vector<map<int,string> >  records;
	string query = "SELECT * FROM  `" + tableName + "`";
	res = stmt->executeQuery(query);
	//res = stmt->executeQuery(query);
	 while (res->next()) {

		 map<int,string> temp;
		 for (int i=1; i<=labels_num; i++)
			 temp.insert( {i-1, res->getString(i) });
		 records.push_back(temp);
	 }
	 logfile::addLog(query);
	 return records;
}


string getDateTime()
{
	 time_t t = time(0);   // get time now
												struct tm * now = localtime( & t );
					string s_datime; //'YYYY-MM-DD HH:MM:SS'
					s_datime += std::to_string(now->tm_year + 1900)+ "-" +
					 std::to_string(now->tm_mon + 1) + "-" + std::to_string(now->tm_mday)+ " "+
					 std::to_string(now->tm_hour) + ":" +  std::to_string(now->tm_min) + ":" +
					 std::to_string(now->tm_sec) ;
					return s_datime;
}




