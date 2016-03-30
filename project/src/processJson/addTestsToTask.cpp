
#include "../inc/main.h"

bool addTestsToTask( FCGI_Stream &stream, jsonParser &jSON, int thread_id, string &error, bool &need_stream)
{



	//string lang = jSON.getAsStringS("lang");
	string table;
	table = ConnectorSQL::getAssignmentTable(" hahaha dont need");

	vector<string> labl = ConnectorSQL::getAssignmentTableLabels();
	/*labl.push_back("ID");
		labl.push_back("header");
		labl.push_back("etalon");
		labl.push_back("footer");
		labl.push_back("json");*/
	SqlConnectionPool sql;

	stream << "Status: 200\r\n Content-type: text/html\r\n" << "\r\n";
	JsonValue res;

	if (sql.connectToTable(table, labl))
	{

		if (!jSON.mustExistBeInt(jSON.getParsedFromString()[FIELD_TASK_ID], "task"))
		{
			res["status"] = "failed";
			res["error"] = jSON.getLastError();
			stream << res.toStyledString();
			stream.close();
			return false;
		}

		int task = jSON.getAsIntS("task");

		string jsona = sql.getJsonFromTable(task);
		//jsona = removeDoubleBrackets(jsona);



		//cout << jsona;
		Value json_db(jsona);



		jsonParser parse(jsona);
		if (!(parse.isValidFields() && parse.isJson() ))
		{
			res["status"] = "failed";
			res["error"] = "Task jsonf from DB invalid";
			stream << res.toStyledString();
			stream.close();
			return false;
		}
		json_db = parse.getParsedFromString();
		//string ss = json_db[FUNCTION].asString();

		if ( !jSON.parseAddUtest(json_db))
		{
			string last_err = jSON.getLastError();
			last_err = last_err.erase(0, last_err.find("correct") + 8);
			res["json"] = "";
			res["status"] = "failed";
			res["error"] = "Unit tests don`t match structure of task: " + last_err;

			stream << res.toStyledString();
			stream.close();
			return false;
		}

	}
	else
	{
		res["json"] = "";
		res["status"] = "failed";
		res["error"] = "Connection to assignment table failed";
		stream << res.toStyledString();
		stream.close();
		return false;
	}
}
