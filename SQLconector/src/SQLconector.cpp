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

ConnectorSQL::ConnectorSQL(string domen, string port, string user, string password) {
		  driver = get_driver_instance();
		  con = driver->connect(domen + ":" + port, user, password);
}

void ConnectorSQL::setDataBase(string database) {
			  con->setSchema(database);
			  stmt = con->createStatement();
}

ConnectorSQL::~ConnectorSQL() {
	delete res;
	delete stmt;
	delete con;
}

void ConnectorSQL::setTableAndLabels(string table, vector<string> labels) {
	this->table=table;
	this->labels_vec = labels;
	this->labels="`" + labels[0] +"`" ;
	labels_num=1;
	for (int i=1; i<labels.size(); i++) {
		this->labels+=",`" + labels[i] +"`" ;
		labels_num++;
	}
}


void ConnectorSQL::addRecordsInToTable(vector<map<int,string> > records) {

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

//if return -1, then ID isn`t valid
string ConnectorSQL::getFullCodeOfProgram(uint ID, string text_of_program) {

	char id[12];
	sprintf(id,"%d",ID);

	string quer = "SELECT * FROM  `" + table + "` where `" + labels_vec[0] +"` = "+ id +";";
		res = stmt->executeQuery(quer);
		string rezult;
		if (res->next())
		{
		 rezult = res->getString(2) + "\n" + text_of_program ;

			 for (int i=3; i<=labels_num; i++)
				 rezult += "\n" +  res->getString(i);
		}
		else rezult = "-1";
	return rezult;

}

vector<map<int,string> >  ConnectorSQL::getAllRecordsFromTable() {
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
	ConnectorSQL ff("localhost", "3306", "root", "testsql");
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
		temp.insert({1,"22arrrrrrrrrr2222"});
		temp.insert({2,"rrrrrrrrrrrrrrfg"});
		temp.insert({3,"444rrrrrrrrrrrfgsf4444444"});
			records.push_back(temp);

		ff.addRecordsInToTable(records);



//get all records, example for cout them
		vector<map<int,string> > all_records = ff.getAllRecordsFromTable();
for (int i=0; i<all_records.size(); i++)
	for (int u=0; u<all_records[i].size(); u++)
		cout << all_records[i][u] <<"\n";


labl.clear();
labl.push_back("ID");
labl.push_back("header");
labl.push_back("etalon");
labl.push_back("footer");
	ff.setTableAndLabels("Tasks",labl);
cout << ff.getFullCodeOfProgram(235,"code of program");

	return 0;
}


