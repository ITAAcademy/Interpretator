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
	//driver = get_driver_instance();
	//cout << driver->getName();
	connect_table = false;
	if(driver == NULL){
	try
		{
			driver = get_driver_instance();
		}
		catch (sql::SQLException e)
		{
			string ss = "Could not get a database driver. Error message: ";
			ss+=+ e.what() ;

			logfile::addLog(ss);
		}
	}
}


bool ConnectorSQL::connectToDataBase(string database) {
	 stmt = NULL;
	 con->setSchema(database);
	 connect_table = false;
			  stmt = con->createStatement();

			  if (stmt == NULL) return false;
			  		  else return true;
}

ConnectorSQL::~ConnectorSQL() {
	delete res;
	delete stmt;
	delete con;
}

void ConnectorSQL::resetConection() {
	delete res;
		delete stmt;
		delete con;
}

bool ConnectorSQL::connectToHost(string domen, string port, string user, string password) {
	connect_table = false;
	//if(con == NULL){
if (driver == NULL)
		return false;
	//cout << driver->getName();
con = NULL;
	//if (con == NULL)
		con = driver->connect(domen + ":" + port, user, password);
	if (con == NULL) {
		//printf("Connection  to host segwereswr\n");
		return false;
	}
		  return true;
//}	return true;
}
bool ConnectorSQL::connectToTable(string table, vector<string> labels) {
	connect_table = false;
		//if (this->table.empty()) {
	this->table=table;
	this->labels_vec = labels;
	this->labels="`" + labels[0] +"`" ;
	labels_num=1;
	for (int i=1; i<labels.size(); i++) {
		this->labels+=",`" + labels[i] +"`" ;
		labels_num++;
	}

		res = stmt->executeQuery("SELECT * FROM  `" + table + "` LIMIT 1");
		 if (res->next()) 
		 {
		 connect_table = true;
		 return true;
		 }
		 else 
		 {
		 connect_table = false;
		 return false;
		 }
}

bool ConnectorSQL::isConnectedToTable() {
return connect_table;
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
			logfile::addLog(query);
			try		{
				stmt->execute(query) ;
					}
					catch (sql::SQLException e)
					{
						string ss = "Could not run sql-reques:  ";
						ss+=+ e.what() ;

						logfile::addLog(ss);
					}

}

void ConnectorSQL::addRecordsInToTable(map<int,string> records) {

	string query= "INSERT INTO `" + table + "` ("+ labels +") Values (";// + this->records +");"
	//int num_of_labels = labels_vec.size();
				//get keys
					pair<int,string> me; // what a map<int, int> is made of
					vector<int> keys;
						BOOST_FOREACH(me, records)
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
									catch (sql::SQLException e)
									{
										string ss = "Could not run sql-reques:  ";
										ss+=+ e.what() ;

										logfile::addLog(ss);
									}
}

//if return -1, then ID isn`t valid
string ConnectorSQL::getFullCodeOfProgram(string ID) {

	string quer = "SELECT * FROM  `" + table + "` where `" + labels_vec[0] +"` = "+ ID +";";
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

string ConnectorSQL::getCustomCodeOfProgram(string ID, string text_of_program) {
	string rezult;
	if (ID.size()>0)
	{
	string quer = "SELECT * FROM  `" + table + "` where `" + labels_vec[0] +"` = "+ ID +";";

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
	return rezult;
}

vector<map<int,string> >  ConnectorSQL::getAllRecordsFromTable() {
	vector<map<int,string> >  records;
	string query = "SELECT * FROM  `" + table + "`";
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



int testSQL() {



//you must do next for normal access
	ConnectorSQL con;
	con.connectToHost("localhost", "3306", "root", "testsql");



	con.connectToDataBase("Databass");

	vector <string> labl;
	labl.push_back("ID");
	labl.push_back("header");
	labl.push_back("etalon");
	labl.push_back("footer");
	con.connectToTable("Tasks",labl);







	//cout << con.getFullCodeOfProgram((char *)"1");//,"code of program");

	/*
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
*/



	return 0;
}
