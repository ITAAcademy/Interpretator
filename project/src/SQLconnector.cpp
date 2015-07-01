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

ConnectorSQL::ConnectorSQL() {
	mysql_init(&mysql);
}
ConnectorSQL::~ConnectorSQL(){
	mysql_close (connection);
}
ConnectorSQL& ConnectorSQL::getInstance(){
	static ConnectorSQL conn;
		conn.connect_table = false;
	return conn;
}


//work12
bool ConnectorSQL::connectToHostDB(const char * host,const char *port, const char *user,
		const char *password, const char *database) {
	std::lock_guard<std::recursive_mutex> locker(_lock);
	 connect_table = false;

		 connection = mysql_real_connect(&mysql,host,user,password,database,atoi(port),0,0);
		 if (connection==NULL)
		 {
			 logfile::addLog ("Connection to host and database failed");
			 			  return false;
		 }

			logfile::addLog ("Connection to host and database successful");
			  return true;
}


void ConnectorSQL::resetConection() {
	mysql_close (connection);
}


//work12
bool ConnectorSQL::connectToTable(string table, vector<string> labels) {
	//std::lock_guard<std::recursive_mutex> locker(_lock);
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
	string quer = "SELECT * FROM  `" + table + "` ;";
	int query_state = 	mysql_query(connection, quer.c_str());
		resptr = mysql_store_result(connection);
	if  (query_state)
	{
		logfile::addLog ("Connection  to table " + table + " failed");
		return false;
	}
	else {
if ((row = mysql_fetch_row(resptr)) == NULL) {
logfile::addLog ("Table " + table + " is empty");
return false;
 }
}
			logfile::addLog ("Connection  to table " + table + " successful");
		 connect_table = true;
		 return true;

}

bool ConnectorSQL::isConnectedToTable() {
	//std::lock_guard<std::recursive_mutex> locker(_lock);
return connect_table;
}

//work12
bool ConnectorSQL::addRecordsInToTable(vector<map<int,string> > records) {
	std::lock_guard<std::recursive_mutex> locker(_lock);
	string quer= "INSERT INTO `" + tableName + "` ("+ this->labels +") Values (";// + this->records +");"
	//string quer = "SELECT * FROM  `" + tableName + "` where `" + labels_vec[0] +"` = "+ ID +";";
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
		//Zero for success. Nonzero if an error occurred.
		int query_state = 	mysql_query(connection, quer.c_str());
			logfile::addLog (quer);
			if (query_state==0) {
				logfile::addLog ("Adding records in to table successfull");
				return true;
			}
				logfile::addLog ("Adding records in to table failed");
					return false;

}

//work12
bool ConnectorSQL::addRecordsInToTable(map<int,string> records) {
	std::lock_guard<std::recursive_mutex> locker(_lock);
		string quer= "INSERT INTO `" + tableName + "` ("+ this->labels +") Values (";// + this->records +");"
		//string quer = "SELECT * FROM  `" + tableName + "` where `" + labels_vec[0] +"` = "+ ID +";";


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

			//Zero for success. Nonzero if an error occurred.
			int query_state = 	mysql_query(connection, quer.c_str());
				logfile::addLog (quer);
				if (query_state==0) {
					logfile::addLog ("Adding records in to table successfull");
					return true;
				}
					logfile::addLog ("Adding records in to table failed");
						return false;
}

//work12
string ConnectorSQL::getFullCodeOfProgram(string ID,int thrdId)  {
	std::lock_guard<std::recursive_mutex> locker(_lock);
	string quer = "SELECT * FROM  `" + tableName + "` where `" + labels_vec[0] +"` = "+ ID +";";
	//Zero for success. Nonzero if an error occurred.
	int query_state = 	mysql_query(connection, quer.c_str());

		string rezult ;
		logfile::addLog (quer);
		if (query_state==0) {
			resptr = mysql_store_result(connection);

			 if ((row = mysql_fetch_row(resptr)) != NULL) {
				 string header = string(row[2]);
				 boost::replace_all(header,"#NUM#",std::to_string(thrdId));
				 string code = string(row[3]);
				 string footer = string(row[4]);
						 rezult = str_with_spec_character(header) + "\n" +
						 			str_with_spec_character(code) + "\n" +
						 			str_with_spec_character(footer);
					 }
			 else rezult = "empty";
			 mysql_free_result(resptr);
		}
		else if (query_state == CR_SOCKET_CREATE_ERROR)rezult = "CR_SOCKET_CREATE_ERROR";
		else
			rezult = "failed";
		//logfile::addLog (std::to_string(query_state));

					 return rezult;
}

//work12
string ConnectorSQL::getCustomCodeOfProgram(string ID, string text_of_program,int thrdId) {
//std::lock_guard<std::recursive_mutex> locker(_lock);
string quer = "SELECT * FROM  `" + tableName + "` where `" + labels_vec[0] +"` = "+ ID +";";
//Zero for success. Nonzero if an error occurred.
int query_state = 	mysql_query(connection, quer.c_str());

string rezult ;
logfile::addLog (quer);
if (query_state==0) {
resptr = mysql_store_result(connection);
if ((row = mysql_fetch_row(resptr)) != NULL) {
string header = string(row[2]);
string footer = string(row[4]);
boost::replace_all(header,"#NUM#",std::to_string(thrdId));
rezult = str_with_spec_character(header) + "\n" +
text_of_program + "\n" +
str_with_spec_character(footer);
}
else rezult = "empty";
mysql_free_result(resptr);
}
else
rezult = "failed";
return rezult;
}

//work12
vector<map<int,string> >  ConnectorSQL::getAllRecordsFromTable() {
	//std::lock_guard<std::recursive_mutex> locker(_lock);
	vector<map<int,string> >  records;


	 string quer = "SELECT * FROM  `" + tableName + "`";
	 	//Zero for success. Nonzero if an error occurred.
	 	int query_state = 	mysql_query(connection, quer.c_str());

	 		string rezult = "failed";


	 		if  (query_state)
	 			logfile::addLog ("Getting all records from table " + tableName + " failed.");
	 		else {
	 			logfile::addLog (quer);
	 			resptr = mysql_store_result(connection);
	 				while ( ( row = mysql_fetch_row(resptr)) != NULL ) {
	 				 map<int,string> temp;
	 						 for (int i=0; i<labels_num; i++)
	 							 temp.insert( {i, string(row[i]) });
	 						 records.push_back(temp);
	 					 }
	 				 mysql_free_result(resptr);
	 		}
	 return records;
}

//work12
bool ConnectorSQL::updateRecordsInToTable(map<int,string> records,map<int,string>  where) {
//string where ="`" + tabl + "`.`ID`='"+id + "' AND `" + tabl +"`.`name`='"+"21"+"'";
	string query= "UPDATE `"+ tableName+ "` SET ";
	vector<int> keys;
	for (	pair<int,string> me  : records)
		keys.push_back(me.first);
	std::sort(keys.begin(),keys.end());
	int r=0;
	for (int y=0; y< records.size(); y++) {
	if (keys[r] == y) {
		query += "`"+ labels_vec[r] + "`=`" + records.find(keys[r])->second + "` " ;
	r++;
	query += ",";
	}
	}
	query += " WHERE " ;

	vector<int> keys2;
for (	pair<int,string> mal  : where)
	keys2.push_back(mal.first);
std::sort(keys.begin(),keys.end());
r=0;
for (int y=0; y< labels_vec.size(); y++) {
if (keys2[r] == y) {
	query += "`"+ labels_vec[r] + "`=`" + where.find(keys2[r])->second + "` " ;
r++;
query += ",";
}
}
		std::lock_guard<std::recursive_mutex> locker(_lock);
				logfile::addLog(query);
				int query_state = 0;//	mysql_query(connection, query.c_str());
				if (query_state==0) {
				logfile::addLog ("Updating records in table " + tableName +" successfull");
				return true;
				}
				logfile::addLog ("Updating records in table " + tableName +" failed");
					return false;
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




