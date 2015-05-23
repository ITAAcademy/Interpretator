//============================================================================
// Name        : SQLconector.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================
#include "inc/SQLconnector.h"

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
	this->labels="`" + labels[0] +"`" ;
	labels_num=1;
	for (int i=1; i<labels.size(); i++) {
		this->labels+=",`" + labels[i] +"`" ;
		labels_num++;
	}
}

void conectorSQL::addRecordInToTable(vector<string> records) {
	this->records="\"" + records[0] +"\"" ;

		for (int i=1; i<records.size(); i++) {
			this->records+=",\"" + records[i] +"\"" ;
		}
		stmt->execute("INSERT INTO `" + table + "` ("+ this->labels +") Values (" + this->records +");") ;
}


vector<vector< string> >  conectorSQL::getAllRecordsFromTable() {
	vector<vector< string> >  records;
	res = stmt->executeQuery("SELECT * FROM  `" + table + "`");
	 while (res->next()) {
		 vector< string> temp;
		 for (int i=1; i<=labels_num; i++)
			 temp.push_back( res->getString(i) );
		 records.push_back(temp);
	 }
	 return records;
}

/*

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


	//write record into table
	vector <string> rec;
	rec.push_back("NULL");
	rec.push_back("Last44444444Name");
	rec.push_back("Firs444444tName");
	rec.push_back("Addr4444444ess");
		ff.addRecordInToTable(rec);






//get all records,  example for cout them
vector<vector< string> > rr = ff.getAllRecordsFromTable();
for (int i=0; i<rr.size(); i++)
	for (int u=0; u<rr[i].size(); u++)
		cout << rr[i][u] <<"\n";

	return 0;
}


*/
