//============================================================================
// Name        : SQLconector.cpp
// Author      :
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <string.h>
#include "mysql_connection.h"
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>
#include <vector>
#include <cstdlib>
#include <boost/algorithm/string.hpp>
#include <boost/foreach.hpp>
#include <map>
#include <set>
#include <boost/lexical_cast.hpp>


using namespace std;

class ConnectorSQL
{
public:
	ConnectorSQL(string domen, string port, string user, string password);
	~ConnectorSQL();
	void setDataBase(string database);
	void setTableAndLabels(string table, vector<string> labels);
	void addRecordsInToTable(vector<map<int,string> > records) ;
	vector<map<int,string> >   getAllRecordsFromTable() ;
	//id-label is first label which you set!!!
	string getFullCodeOfProgram(uint ID, string text_of_program);
private:
	string table;
	string labels;
	string records;
	vector<string> labels_vec;
	int labels_num;
	sql::Driver *driver;
	sql::Connection *con;
	sql::Statement *stmt;
	sql::ResultSet *res;
};
