//============================================================================
// Name        : SQLconector.cpp
// Author      :
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include "includes.h"
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
	ConnectorSQL();
	bool connectToHost(string domen, string port, string user, string password);
	~ConnectorSQL();
	bool connectToDataBase(string database);
	bool connectToTable(string table, vector<string> labels);
	void addRecordsInToTable(vector<map<int,string> > records) ;
	void addRecordsInToTable(map<int,string>  records) ;
	vector<map<int,string> >   getAllRecordsFromTable() ;
	//id-label is first label which you set!!!
	bool isConnectedToTable();
	string getCustomCodeOfProgram(string ID, string text_of_program);
	string getFullCodeOfProgram(string ID);
void resetConection();
private:
	 sql::Driver *driver;
		  sql::Connection *con;
bool connect_table;
	 string table;
	 string labels;
	//string records;
	 vector<string> labels_vec;
	 int labels_num;

	 sql::Statement *stmt;
	sql::ResultSet *res;
};
