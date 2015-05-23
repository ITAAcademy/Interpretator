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
#include <cstring>
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>
#include <vector>
#include <cstdlib>
#include <boost/algorithm/string.hpp>
#include <boost/foreach.hpp>
#include <set>


using namespace std;

class conectorSQL
{
public:
	conectorSQL(string domen, string port, string user, string password);
	~conectorSQL();
	void setDataBase(string database);
	void setTableAndLabels(string table, vector<string> labels);
	void addRecordsInToTable(vector<map<int,string> > records) ;
	vector<map<int,string> >   getAllRecordsFromTable() ;
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

conectorSQL::conectorSQL(string domen, string port, string user, string password) {
		  driver = get_driver_instance();
		  con = driver->connect(domen + ":" + port, user, password);
}

void conectorSQL::setDataBase(string database) {
			  con->setSchema(database);
			  stmt = con->createStatement();
}

conectorSQL::~conectorSQL() {
	delete res;
	delete stmt;
	delete con;
}

void conectorSQL::setTableAndLabels(string table, vector<string> labels) {
	this->table=table;
	this->labels_vec = labels;
	this->labels="`" + labels[0] +"`" ;
	labels_num=1;
	for (int i=1; i<labels.size(); i++) {
		this->labels+=",`" + labels[i] +"`" ;
		labels_num++;
	}
}


void conectorSQL::addRecordsInToTable(vector<map<int,string> > records) {

	string query= "INSERT INTO `" + table + "` ("+ labels +") Values (";// + this->records +");"
			int num_of_querys = records.size();
			//num of querys
			for (int i=0; i<num_of_querys; i++) {
				//get keys
					pair<int,string> me; // what a map<int, int> is made of
					vector<int> keys;
						BOOST_FOREACH(me, records[i])
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
		stmt->execute(query) ;
}


vector<map<int,string> >  conectorSQL::getAllRecordsFromTable() {
	vector<map<int,string> >  records;
	res = stmt->executeQuery("SELECT * FROM  `" + table + "`");
	 while (res->next()) {
		 map<int,string> temp;
		 for (int i=1; i<=labels_num; i++)
			 temp.insert( {i-1, res->getString(i) });
		 records.push_back(temp);
	 }
	 return records;
}



int main() {



//you must do next for normal access
	conectorSQL ff("localhost", "3306", "root", "testsql");
	ff.setDataBase("muglo");
	vector <string> labl;
//write labels of table
	labl.push_back("ID");
	labl.push_back("LastName");
	labl.push_back("FirstName");
	labl.push_back("Address");
		ff.setTableAndLabels("Persons",labl);


	//write records into table

			vector<map<int,string> > records ;
			map<int,string> temp;
		//temp.insert({0,"11111111"});
		temp.insert({1,"2222222222"});
		temp.insert({2,"333333333333"});
		temp.insert({3,"44444444444"});
			records.push_back(temp);

		ff.addRecordsInToTable(records);



//get all records, example for cout them
		vector<map<int,string> > all_records = ff.getAllRecordsFromTable();
for (int i=0; i<all_records.size(); i++)
	for (int u=0; u<all_records[i].size(); u++)
		cout << all_records[i][u] <<"\n";

	return 0;
}


