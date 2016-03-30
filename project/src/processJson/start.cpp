/*
 * start.cpp
 *
 *  Created on: Mar 30, 2016
 *      Author: name
 */


#include "../inc/main.h"


ctpl::thread_pool tasksPool(4);


/*
 *
 * 					START
 *
 */
bool start(FCGI_Stream &stream, jsonParser &jSON, string ip_user, string &error, bool &need_stream )
{
	error = "";
	string session = jSON.getAsStringS("session");
	string jobid = jSON.getAsStringS("jobid");//		jSON.getObject("jobid", false).asUInt();
	string code = jSON.getAsStringS("code");
	int task = jSON.getAsIntS("task"); //jSON.getObject("task", false).asInt();
	string lang = jSON.getAsStringS("lang");
	int lang_int = jSON.getAsIntS("lang");
	vector<string> resLabel;
	resLabel.push_back("ID");
	resLabel.push_back("header");
	resLabel.push_back("etalon");
	resLabel.push_back("footer");
	resLabel.push_back("json");
	string tableName = ConnectorSQL::getAssignmentTable(lang);
	SqlConnectionPool sql;
	JsonValue res;

	stream << "Status: 200\r\n Content-type: text/html\r\n" << "\r\n";

	if (sql.connectToTable(tableName, resLabel))
	{
		vector<map<int, string> > records =	sql.getAllRecordsFromTable(
				"`ID`='"+std::to_string(task)+"'");
		if ((int)records.size() == 1)
		{
			string json_str = records.at(0).at(4);
			cout << json_str;
			jsonParser task_json(json_str);
			cout << "\n\n\n" << task_json.getJson();
			string task_lang = task_json.getAsStringS("lang");
			if (task_lang != lang)
			{
				error = "Task " + to_string(task) + " in lang " + lang + " not exist";
				res["status"] = error;
				stream << res.toStyledString();
				stream.close();
				need_stream = false;
				return false;
			}
		}
		else
		{
			error = "Task " + to_string(task) + " in lang " + lang + " not exist";
			res["status"] = error;
			stream << res.toStyledString();
			stream.close();
			need_stream = false;
			return false;
		}
	}
	else
		return false;

	Job requestedTask;
	requestedTask.code = code;
	requestedTask.jobid = jobid;
	requestedTask.lang = lang;
	requestedTask.session = session;
	requestedTask.task = task;
	DEBUG("no threa22");
	/*
	 * BAD NEED FIX @BUDLO@ INCLUDE INTO sql
	 */

	vector<string> labl;
	labl.push_back("id");
	labl.push_back("session");
	labl.push_back("jobid");
	labl.push_back("status");
	labl.push_back("date");
	labl.push_back("result");
	labl.push_back("warning");

	bool taskComp = false;
	if (sql.connectToTable(string("results"), labl))
	{
		DEBUG("no threa2");
		vector<map<int, string> > records =	sql.getAllRecordsFromTable(
				"`session`='"+session+"' AND `jobid`='"+(jobid)+"'");
		if ((int)records.size()==0)
			tasksPool.push(processTask,requestedTask);
		//processTask(0, requestedTask);
		else
			taskComp = true;
		//stream << "this job is already excist";

		//addUserToHistory(ip_usera, code);
		labl.clear();
		labl.push_back("ID");
		labl.push_back("ip");
		labl.push_back("code");
		labl.push_back("date_time");
		if (sql.connectToTable("history", labl))
		{
			string s_datime = getDateTime(); //'YYYY-MM-DD HH:MM:SS'
			vector <map<int, string> > rec;
			map<int, string> temp;
			temp.insert( { 1, ip_user});
			temp.insert( { 2, str_with_spec_character(code) });
			temp.insert( { 3, s_datime });
			rec.push_back(temp);

			//MyConnectionPool::getInstance().getAllRecordsFromTable();
			sql.addRecordsInToTable(temp);
			//MyConnectionPool::getInstance().tt();
			if(taskComp)
			{
				//stream << "Status: 200\r\n Content-type: text/html\r\n" << "\r\n";

				res["status"] = "already exist";
				stream << res.toStyledString();
				stream.close();

				need_stream = false;
				return false;
			}
			else
			{
				//stream << "Status: 200\r\n Content-type: text/html\r\n" << "\r\n";
				JsonValue res;
				res["status"] = "Added to compile";
				stream << res.toStyledString();
				stream.close();

				need_stream = false;
				return true;
			}
		}
		else
		{
			return false;
		}
	}
	else
	{
		return false;
	}
	return true;
	// string ip_usera = FCGX_GetParam( "REMOTE_ADDR", request->envp );

}
