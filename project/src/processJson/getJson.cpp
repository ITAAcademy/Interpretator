/*
 * getJson.cpp
 *
 *  Created on: Mar 30, 2016
 *      Author: name
 */


#include "../inc/main.h"



bool getJson( FCGI_Stream &stream, jsonParser &jSON, int thread_id)
{
	if ( !jSON.isValidFields() )
		return false;
	int task = jSON.getAsIntS("task");

	//string lang = jSON.getAsStringS("lang");
	string table;
	table = ConnectorSQL::getAssignmentTable(" hahaha dont need");

	vector<string> labl;
	labl.push_back("ID");
	labl.push_back("header");
	labl.push_back("etalon");
	labl.push_back("footer");
	labl.push_back("json");
	SqlConnectionPool sql;

	stream << "Status: 200\r\n Content-type: text/html\r\n" << "\r\n";
	JsonValue res;

	if (sql.connectToTable(table, labl))
	{

		string jsona = sql.getJsonFromTable(task);
		int size = jsona.size();
		if (size > 0)
		{
			res["status"] = "success";
			res["json"] = jsona;
		}
		else
		{
			res["json"] = "";
			res["status"] = "failed";
		}
		stream << res.toStyledString();
		stream.close();
		return true;
	}
	else
		return false;
}
