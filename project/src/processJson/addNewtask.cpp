/*
 * addNewtask.cpp
 *
 *  Created on: Mar 26, 2016
 *      Author: name
 */


#include "../inc/main.h"


bool addNewtask( FCGI_Stream &stream, jsonParser &jSON, int thread_id, string &error, bool &need_stream)//***
{
	JsonValue res;
	stream << "Status: 200\r\n Content-type: text/html\r\n" << "\r\n";
	if ( !jSON.isValidFields() )
	{
		string error = jSON.getLastError();
		res["status"] = error;
		stream << res.toStyledString();
		stream.close();
		return false;
	}
	string lang = jSON.getAsStringS("lang");
	string table;
	table=ConnectorSQL::getAssignmentTable(lang);

	vector<string> labl;
	labl.push_back("ID");
	labl.push_back("header");
	labl.push_back("etalon");
	labl.push_back("footer");
	labl.push_back("json");
	SqlConnectionPool sql;


	DEBUG("before connectToTable");
	if (sql.connectToTable(table, labl))
	{
		DEBUG("connectedToTable");
		map<int, string> temp;

		//new code for testcases part
		int id = jSON.getAsIntS("task");//t("task",false));
		DEBUG("task");
		DEBUG(std::to_string(id));




		TaskCodeGenerator generator(jSON, thread_id);

		/*{
			string etalona = generator.getEtalon();
			int pre_last_return_pos = 0;
			int last_return_pos = 0;
			while(true)
			{
				int pos = etalona.find("return", last_return_pos + 2);
				if (pos == -1)
					break;
				pre_last_return_pos = last_return_pos;
				last_return_pos = pos;
			}
			etalona.erase(pre_last_return_pos, last_return_pos );

		}*/

		LangCompiler compiler(thread_id);

		string code = sql.generateProgramCode(generator.getHeader(), string(""), generator.getFooter(), lang);
		compiler.compile(code, true, LangCompiler::convertFromName(lang), 1);
		string errors = compiler.getWarningErr();

		int lang_int = jSON.getAsIntS("lang");

		if (errors.size() == 0)
		{

			if (lang_int == (int) LangCompiler::Flag_JS)
			{
				errors = compiler.getResult();
				if (errors.find("error") == -1)
					errors = "";
			}
		}



		if (errors.size() )
		{
			error = "failed code compilation: " + errors ;
			//res["status"] = "failed";
			res["status"] = error;
			stream << res.toStyledString();
			stream.close();

			need_stream = false;
			return false;
			/*
			res["status"] = "failed 0000";
			res["table"] = table;
						res["id"] = to_string(id);
			stream << res.toStyledString();
			stream.close();
			return true;*/
		}

		string footer = generator.getFooter();
		if (lang_int != LangCompiler::Flag_Java)
			footer.erase(0,  footer.find("\n"));


		int valuesCount = 0;
		temp.insert( { valuesCount++, std::to_string(id) });
		temp.insert( { valuesCount++, (generator.getHeader())});
		temp.insert( { valuesCount++, (generator.getEtalon())});
		DEBUG("qwe33");
		temp.insert( { valuesCount++, (footer)});
		temp.insert({valuesCount++, (jSON.getJson())});
		DEBUG("temp.insert");




		map<int,string> where;
		where.insert({0,temp[0]});
		int status = generator.getStatus();

		if (status == 0 && sql.addRecordsInToTable(temp))
		{
			res["status"] = "success";
			res["table"] = table;
			res["id"] = to_string(id);
		}
		else
			if (generator.getStatus() == 0 && sql.updateRecordsInToTable(temp, where))
			{
				res["status"] = "updated";
				res["table"] = table;
				res["id"] = to_string(id);
			}
			else res["status"] = "failed";

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
