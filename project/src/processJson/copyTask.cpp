/*
 * copyTask.cpp
 *
 *  Created on: May 14, 2016
 *      Author: name
 */




#include "../inc/main.h"



bool copyTask( FCGI_Stream &stream, jsonParser &jSON, int thread_id, string &error, bool &need_stream)
{
	cout.flush();
	JsonValue res;
	stream << "Status: 200\r\n Content-type: text/html\r\n" << "\r\n";
	if ( !jSON.isJson() )
	{
		string error = "ERROR: json format is not correct. it isn`t json";
		res["status"] = error;
		stream << res.toStyledString();
		stream.close();
		return false;
	}

	if ( !jSON.isValidFields() )
	{
		string error = jSON.getLastError();
		res["status"] = error;
		stream << res.toStyledString();
		stream.close();
		return false;
	}

	string table;
	table=ConnectorSQL::getAssignmentTable("");

	vector<string> labl;
	labl.push_back("ID");
	labl.push_back("header");
	labl.push_back("etalon");
	labl.push_back("footer");
	labl.push_back("json");
	SqlConnectionPool sql;

	if (sql.connectToTable(table, labl))
	{
		int id = jSON.getAsIntS("task");
		int new_id = jSON.getAsIntS("new_task");

		if ( sql.copyRecordFromIdToNewId(id, new_id))
		{
			res["status"] = "success";
			res["table"] = table;
			res["id"] = to_string(id);
		}
		else
		{
			if ( sql.updateRecordFromIdToNewId(id, new_id))
			{
				res["status"] = "updated";
				res["table"] = table;
				res["id"] = to_string(id);
			}
			else
				res["status"] = "failed";


		}
		stream << res.toStyledString();
					stream.close();

					need_stream = false;
					return true;
	}
	else
	{
		res["status"] = "failed";

		stream << res.toStyledString();
		stream.close();

		need_stream = false;
		return false;
	}
}


