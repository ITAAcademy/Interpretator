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
#include "config.h"
#include <mutex>
extern Config* config;
using namespace std;

string getDateTime();
std::recursive_mutex _lock;
class ConnectorSQL
{

	  ConnectorSQL(ConnectorSQL const&);
		  ConnectorSQL& operator= (ConnectorSQL const&);
		  ConnectorSQL();
		  ~ConnectorSQL();
public:
	 static ConnectorSQL& getInstance();
	bool connectToHost(string host, string user, string password);
	bool connectToDataBase(string database);
	bool connectToTable(string table, vector<string> labels);
	bool addRecordsInToTable(vector<map<int,string> > records) ;
	bool addRecordsInToTable(map<int,string>  records) ;
	vector<map<int,string> >   getAllRecordsFromTable() ;
	//id-label is first label which you set!!!
	bool isConnectedToTable();
	string getCustomCodeOfProgram(string ID, string text_of_program,int thrdId);
	string getFullCodeOfProgram(string ID);
void resetConection();
private:
	 sql::Driver *driver;
		  sql::Connection *con;


bool connect_table;
	 string tableName;
	 string labels;
	//string records;
	 vector<string> labels_vec;
	 int labels_num;

	 sql::Statement *stmt;
	sql::ResultSet *res;
};
