
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

	//stream << "Status: 200\r\n Content-type: text/html\r\n" << "\r\n";
	JsonValue res;

	if (sql.connectToTable(table, labl))
	{

		if (!jSON.mustExistBeInt(jSON.getParsedFromString()[FIELD_TASK_ID], "task"))
		{
			stream << "Status: 200\r\n Content-type: text/html\r\n" << "\r\n";
			res["status"] = "failed";
			res["error"] = jSON.getLastError();
			stream << res.toStyledString();
			stream.close();
			return false;
		}

		int task = jSON.getAsIntS("task");

		string json_prev_task = sql.getJsonFromTable(task);

		jsonParser parse(json_prev_task);

		if (!(parse.isValidFields() && parse.isJson() ))
		{
			stream << "Status: 200\r\n Content-type: text/html\r\n" << "\r\n";
			res["status"] = "failed";
			res["error"] = "Task jsonf from DB invalid";
			stream << res.toStyledString();
			stream.close();
			return false;
		}

		Value json_db(parse.getParsedFromString());


		if ( !jSON.parseAddUtest(json_db))
		{
			stream << "Status: 200\r\n Content-type: text/html\r\n" << "\r\n";
			string last_err = jSON.getLastError();
			last_err = last_err.erase(0, last_err.find("correct") + 8);
			res["json"] = "";
			res["status"] = "failed";
			res["error"] = "Unit tests don`t match structure of task: " + last_err;

			stream << res.toStyledString();
			stream.close();
			return false;
		}

		Value json_tests = jSON.getJsonValue();

		Value res_value = mergeUtestsAndTask(json_tests, json_db);

string res_value_str = res_value.toStyledString();
res_value_str = replaceSlashTabsParagBreakets( res_value_str );


Value val; //(res_value_str);
Json::Reader reader;
  reader.parse( res_value_str.c_str(), val );

		jsonParser merged_json;
		//merged_json.setParsedFromString(val);
		merged_json.setJson(res_value_str);
		//setJson(res_value_str);



		cout.flush();
		//cout << val.toStyledString();
		//cout << res_value_str;

	//	cout << merged_json.getParsedFromString().toStyledString();
		//merged_json.setParsedFromString(Json(res_value.toStyledString());



		//cout << merged_json.getParsedFromString();

	/*
		map<int, string> temp;

		int valuesCount = 0;
			temp.insert( { valuesCount++, std::to_string(task) });
			temp.insert( { valuesCount++, (generator.getHeader())});
			temp.insert( { valuesCount++, (generator.getEtalon())});
			DEBUG("qwe33");
			temp.insert( { valuesCount++, (footer)});
			temp.insert({valuesCount++, (jSON.getJson())});
*/

		//return false;
		return addNewtask(stream, merged_json, thread_id, error, need_stream);
		//string json_utest = jSON.getJson();
		//json_db[FUNCTION]{FIELD_UNIT_TESTS_NUM] = "5";

		//	json_db.append(jSON.getJsonValue());
		//cout << json_tests.toStyledString();

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
