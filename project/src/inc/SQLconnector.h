/*
 * SQLconnector.h
 *
 *  Created on: May 20, 2015
 *      Author: root
 */
#include <iostream>
#include <string.h>
#include "mysql_connection.h"
#include <cstring>
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>
#include <vector>
#include <cstdlib>
#include <boost/algorithm/string.hpp>

using namespace std;

#ifndef SQLCONNECTOR_H_
#define SQLCONNECTOR_H_

class conectorSQL
{
public:
	conectorSQL(string domen, string port, string user, string password);
	~conectorSQL();
	void setDataBase(string database);
	void setTableAndLabels(string table, vector<string> labels);
	void addRecordInToTable(vector<string> records);
	vector<vector< string> >    getAllRecordsFromTable() ;
private:
	string table;
	string labels;
	string records;
	int labels_num;
	sql::Driver *driver;
	sql::Connection *con;
	sql::Statement *stmt;
	sql::ResultSet *res;
};




#endif /* SQLCONNECTOR_H_ */
