#include "inc/main.h"

//extern Con(hash<string>()(jobid)^hash<string>()(jobid))fig *config;
using namespace std;
using namespace Json;

void ReplaceAll(std::string &str, const std::string& from, const std::string& to){
	size_t start_pos = 0;
	while((start_pos = str.find(from, start_pos)) != std::string::npos) {
		str.replace(start_pos, from.length(), to);
		start_pos += to.length(); // Handles case where 'to' is a substring of 'from'
	}
}
struct ThreadArguments {
	int id;
};

ctpl::thread_pool tasksPool(4);

/*
 *  need insert into SQL
 */

void l12(string ll) {
	logfile::addLog(ll);
}

void l12(int ll) {
	logfile::addLog(to_string(ll));
}



void addUserToHistory(string userIp, string code) {
	vector<string> labl;
	labl.push_back("ID");
	labl.push_back("ip");
	labl.push_back("code");
	labl.push_back("date_time");
	SqlConnectionPool sql;
	if (sql.connectToTable("history", labl))
	{
		string s_datime = getDateTime(); //'YYYY-MM-DD HH:MM:SS'
		map<int, string> temp;
		temp.insert( { 1, userIp });
		temp.insert( { 2, str_with_spec_character(code) });
		temp.insert( { 3, s_datime });
		sql.addRecordsInToTable(temp);
	}
}


void processTask(int id,Job job) {

	//	logfile::addLog("Connection");
	// ConnectorSQL connector ;

	// int id = ((int *)a)[0];


	//char * inputSTR;
	LangCompiler compiler(id);
	/*
	 * input from PHP form // not use
	 *
	 * 	stream >> inputSTR; // test input
	 char *code = stream.getFormParam("text");
	 char *name = stream.getFormParam("name");
	 */

	/*
	 * problem with CodeClear need fix
	 *
	 CodeClear clr;
	 string outStr = code;
	 clr.ClearText(outStr);*/
	DEBUG("before code empty check");
	if (!job.code.empty())
	{

		vector<string> labl;
		//ADD NEW STARTED COMPILING INFO TO DATABASE
		labl.push_back("id");
		labl.push_back("session");
		labl.push_back("jobid");
		labl.push_back("status");
		labl.push_back("date");
		labl.push_back("result");
		labl.push_back("warning");
		DEBUG("Before connect to results");
		SqlConnectionPool sql;
		//logfile::addLog("Connection to results successful");
		if (sql.connectToTable("results", labl))
		{
			string s_datime = getDateTime(); //'YYYY-MM-DD HH:MM:SS'
			map<int, string> temp;
			temp.insert( { 1, job.session });
			temp.insert( { 2, (job.jobid) });
			temp.insert( { 3, "in proccess"});
			temp.insert( { 4, s_datime });
			temp.insert( { 5, "" });
			temp.insert( { 6, "" });
			sql.addRecordsInToTable(temp);

			////////////////
			labl.clear();
			labl.push_back("ID");
			labl.push_back("header");
			labl.push_back("etalon");
			labl.push_back("footer");

			string table;
			table = ConnectorSQL::getAssignmentTable(job.lang);
			if (sql.connectToTable(table, labl))
			{
				job.code =
						sql.getCustomCodeOfProgram(
								to_string(job.task), job.code, id,job.lang);
				DEBUG(job.code);
			}

			INFO(to_string(id)+ " Start compiler");
			JsonValue res;

			compiler.compile(job.code, true, LangCompiler::convertFromName(job.lang));


			string date = logfile::getDateStamp();
			res["date"] = date;
			res["result"] = compiler.getResult();
			res["warnings"] = compiler.getWarningErr();
			DEBUG( res.toStyledString());


			labl.clear();
			//UPDATE COMPILING INFO IN DB
			labl.push_back("id");
			labl.push_back("session");
			labl.push_back("jobid");
			labl.push_back("status");
			labl.push_back("date");
			labl.push_back("result");
			labl.push_back("warning");
			if (sql.connectToTable("results", labl))
			{
				string s_datime = getDateTime(); //'YYYY-MM-DD HH:MM:SS'
				map<int, string> temp;
				temp.insert( { 1, job.session });
				temp.insert( { 2, (job.jobid) });
				if(compiler.getResult().size() == 0)
					temp.insert( { 3, "failed"});
				else
					temp.insert( { 3, "done"});
				temp.insert( { 4, s_datime });
				temp.insert( { 5, compiler.getResult()});
				temp.insert( { 6, compiler.getWarningErr() });
				//4j
				//string where = "`results`.`jobid`='"+to_string(job.jobid)+"' AND `results`.`session`='"+job.session+"'";
				map<int,string> where;
				where.insert({1,job.session});
				where.insert({2,(job.jobid)});
				//ConnectorSQL::getInstance().updateRecordsInToTable(temp,wher);
				sql.updateRecordsInToTable(temp,where);

			}


			INFO(to_string(id) + " Stop compiler");
		}
		else {

			string error = to_string(id)+"Error: Can`t connect to results table \n";
			ERROR(error);
		}
	}
}


void *receiveTask(void *a)
{
	DEBUG("void *receiveTask(void *a) ");
	ThreadArguments argumento = ((ThreadArguments *) a)[0];

	int rc, i;
	int id = argumento.id;
	char * inputSTR;
	FCGX_Request *request;
	FCGI_Stream stream(socketId);
	ErrorResponder errorResponder(&stream);
	request = stream.getRequest();
	//string lang;

	for (;;)
	{
		if (stream.multiIsRequest()) { /////////////!!!!!!!!!!!!!!!!!!!
			//	break;
			DEBUG(request);
			if (strcmp(stream.getRequestMethod(), "GET") == 0)
			{
				//logfile::addLog(id, "Request Method don't POST !!!");
				errorResponder.showError(404);
				//INFO("session closed");
				stream.close();
				continue;
			}

			if(!SqlConnectionPool::getInstance().isConnected()  )
			{

				errorResponder.showError(505, "DataBaseERR");
				INFO("Try reconect to DB");
				stream.close();
				SqlConnectionPool::getInstance().reconect(); //124
				continue;  //////////////////////////////
			}
			DEBUG("Before jsonParser jSON(stream.getRequestBuffer());");
			jsonParser jSON(stream.getRequestBuffer());

			DEBUG("Before parsing successful check");
			bool isValidFields = jSON.isValidFields();
			bool parsingSuccessful = jSON.isJson() && isValidFields;
			DEBUG("Before jSON.isJson()");
			if (parsingSuccessful)
				DEBUG("Before jSON.isValidFields()");
			//parsingSuccessful = jSON.isValidFields(); //reader.parse( str, parsedFromString, false);// IsJSON
			DEBUG("Before parsing");
			/*
			 * ALL OK STARTif (SqlConnectionPool::getInstance().connectToTable(string("results"), labl))
			 */

			string errora = "";
			if (parsingSuccessful)
			{
				string ip_usera = FCGX_GetParam("REMOTE_ADDR", request->envp);
				cout.flush();
				INFO("Parsing successful");

				string operation = jSON.getAsStringS("operation");
				bool succsesful = true;
				/*
				 * OPERATION ADDTASK
				 */
				if (operation == "addtask")
				{
					/*if(!addNewtask(stream, jSON, id, errora))
						succsesful = false;*/
					addNewtask(stream, jSON, id, errora);
				}
				else
					if (operation == "getJson")
					{
						if(!getJson(stream, jSON, id))
							succsesful = false;
					}
					else
						if (operation == "start" || operation == "s")
						{
							if(!start(stream, jSON, FCGX_GetParam("REMOTE_ADDR", request->envp), errora))
								succsesful = false;
						}
						else
							if (operation == "addtestsig")
							{
								if(!addTestSignature(stream, jSON))
									succsesful = false;
							}
							else
								if (operation == "addtestval")
								{
									if (!addTestValues(stream,jSON))
										succsesful = false;
								}
								else
									if (operation == "add_tests")
									{
										if (!addTests(stream,jSON))
											succsesful = false;
									}
									else
										if (operation == "retreive_tests")
										{
											if (!retreiveTests(stream,jSON))
												succsesful = false;
										}
										else
											if (operation == "result" || operation == "status" || operation == "r" )
											{
												if(!result_status(stream, jSON, operation))
													succsesful = false;
											}
											else
												if (operation == "getToken")
												{
													if(!TokenSystem::getObject()->generationToken(stream, jSON))
														succsesful = false;
												}
												else
													if (operation == "getFromToken")
													{
														if(!TokenSystem::getObject()->getFromToken(stream, jSON))
															succsesful = false;
													}
													else
													{
														errorResponder.showError(505, "operation is invalid");
													}

				if(!succsesful)
				{
					JsonValue res;
					stream << "Status: 200\r\n Content-type: text/html\r\n" << "\r\n";
					string error = jSON.getLastError() + "\n" + errora;
					/*	errorResponder.showError(400, error);
					stream.close();*/

					res["status"] = error;
					stream << res.toStyledString();
					stream.close();
					continue;
				}

			}
			else
			{
				JsonValue res;
				stream << "Status: 200\r\n Content-type: text/html\r\n" << "\r\n";
				//logfile::addLog(id,	"Json format is not correct!!! \n::::::::::::::::::::::::\n" + stream.getRequestBuffer() + "\n::::::::::::::::::::::::");
				/*errorResponder.showError(400, jSON.getLastError());
				stream.close();*/

				res["status"] = jSON.getLastError();
				stream << res.toStyledString();
				stream.close();

				continue;
			}

		}
	}
	//close session
	INFO("session closed");
	stream.close();
	return NULL;
}

/*
 *
 *  				NEW TASK
 *
 */


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



bool addNewtask( FCGI_Stream &stream, jsonParser &jSON, int thread_id, string &error)//***
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
		compiler.compile(code, true, LangCompiler::convertFromName(lang));
		string errors = compiler.getWarningErr();
		if (errors.size() == 0)
		{
			int lang_int = jSON.getAsIntS("lang");
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
		return true;
	}
	else
	{
		res["status"] = "failed";

		stream << res.toStyledString();
		stream.close();
		return false;
	}
}

/*
 *
 * 					START
 *
 */
bool start(FCGI_Stream &stream, jsonParser &jSON, string ip_user, string &error )
{
	error = "";
	string session = jSON.getAsStringS("session");
	string jobid = jSON.getAsStringS("jobid");//		jSON.getObject("jobid", false).asUInt();
	string code = jSON.getAsStringS("code");
	int task = jSON.getAsIntS("task"); //jSON.getObject("task", false).asInt();
	string lang = jSON.getAsStringS("lang");
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

	if (sql.connectToTable(tableName, resLabel)){
		vector<map<int, string> > records =	sql.getAllRecordsFromTable(
				"`ID`='"+std::to_string(task)+"'");
		if ((int)records.size()==0)
		{
			error = "Task " + to_string(task) + " in lang " + lang + " not exist";
			res["status"] = error;
			stream << res.toStyledString();
			stream.close();
			return false;
		}
	}
	else return false;

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
				return false;
			}
			else
			{
				//stream << "Status: 200\r\n Content-type: text/html\r\n" << "\r\n";
				JsonValue res;
				res["status"] = "Added to compile";
				stream << res.toStyledString();
				stream.close();
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

bool addTestSignature(FCGI_Stream &stream, jsonParser &jSON)
{
	//string session = jSON.getObject("session", false).asString();
	int task = jSON.getAsIntS("task");//jSON.getObject("task", false).asInt();
	string lang = jSON.getAsString("lang");
	//string signature = jSON.getObject("tests_signatures",false).asString();
	string etalon = jSON.getAsString("etalon");
	Json::FastWriter fastWriter;
	Json::Value signatureValue = jSON.getObject("signature",false);
	std::string signature = fastWriter.write(signatureValue);
	vector<string> labl;
	labl.push_back("task_id");
	labl.push_back("lang");
	labl.push_back("signature");
	labl.push_back("etalon");
	SqlConnectionPool sql;
	bool taskComp = true;
	if (sql.connectToTable(string("tests_signatures"), labl))
	{
		DEBUG("no threa2");
		vector<map<int, string> > records =	sql.getAllRecordsFromTable(
				"`task_id`='"+std::to_string(task)+"'");
		if ((int)records.size()==0)
			taskComp=true;
		else
			taskComp = false;


		vector <map<int, string> > rec;
		map<int, string> temp;
		temp.insert( { 0, std::to_string(task)});
		temp.insert( { 1, lang});
		temp.insert( { 2, str_with_spec_character(signature) });
		temp.insert( { 3, etalon });
		//rec.push_back(temp);

		//MyConnectionPool::getInstance().getAllRecordsFromTable();
		bool res = sql.addRecordsInToTable(temp);
		//MyConnectionPool::getInstance().tt();
		if(!taskComp)
		{
			stream << "Status: 200\r\n Content-type: text/html\r\n" << "\r\n";
			JsonValue res;
			res["status"] = "already exist";
			stream << res.toStyledString();
		}
		else //204
			stream << "Status: 200\r\n Content-type: text/html\r\n" << "\r\n"
			<<"success:"<<to_string(res)<<"signature:"<<signature;


	}
	else
	{
		return false;
	}
	return true;
	// string ip_usera = FCGX_GetParam( "REMOTE_ADDR", request->envp );

}
bool addTestValues(FCGI_Stream &stream, jsonParser &jSON)
{
	//string session = jSON.getObject("session", false).asString();
	int task = jSON.getAsIntS("task");//jSON.getObject("task", false).asInt();
	Json::FastWriter fastWriter;
	Json::Value returnVal = jSON.getObject("return_val", false);
	string returnStr = fastWriter.write(returnVal);
	Json::Value argsValue = jSON.getObject("args",false);
	std::string args = fastWriter.write(argsValue);
	vector<string> labl;
	labl.push_back("id");
	labl.push_back("task_id");
	labl.push_back("return_value");
	labl.push_back("arguments");
	SqlConnectionPool sql;
	bool taskComp = true;
	if (sql.connectToTable(string("tests_values"), labl))
	{
		/*l12("no threa2");
				vector<map<int, string> > records =	SqlConnectionPool::getInstance().getAllRecordsFromTable(
						"`task_id`='"+std::to_string(task)+"'");
				if ((int)records.size()==0)
					taskComp=true;
				else
					taskComp = false;
		 */

		vector <map<int, string> > rec;
		map<int, string> temp;
		temp.insert( { 1, std::to_string(task)});
		temp.insert( { 2, str_with_spec_character(returnStr)});
		temp.insert( { 3, str_with_spec_character(args) });

		//rec.push_back(temp);

		//MyConnectionPool::getInstance().getAllRecordsFromTable();
		bool res = sql.addRecordsInToTable(temp);
		//MyConnectionPool::getInstance().tt();
		/*if(!taskComp)
			{
				stream << "Status: 200\r\n Content-type: text/html\r\n" << "\r\n";
				JsonValue res;
				res["status"] = "already exist";
				stream << res.toStyledString();
			}
			else *///204
		stream << "Status: 200\r\n Content-type: text/html\r\n" << "\r\n" <<"success:"<<res;


	}
	else
	{
		return false;
	}
	return true;
	// string ip_usera = FCGX_GetParam( "REMOTE_ADDR", request->envp );

}

bool addTests(FCGI_Stream &stream, jsonParser &jSON)
{
	//string session = jSON.getObject("session", false).asString();
	int task = jSON.getAsIntS("task");//jSON.getObject("task", false).asInt();
	Json::FastWriter fastWriter;
	Json::Value jsonValue = jSON.getRoot();
	std::string json = fastWriter.write(jsonValue);
	vector<string> labl;
	labl.push_back("task_id");
	labl.push_back("json");

	bool taskComp = true;
	SqlConnectionPool sql;
	if (sql.connectToTable(string("tests"), labl))
	{
		/*l12("no threa2");
				vector<map<int, string> > records =	SqlConnectionPool::getInstance().getAllRecordsFromTable(
						"`task_id`='"+std::to_string(task)+"'");
				if ((int)records.size()==0)
					taskComp=true;
				else
					taskComp = false;
		 */

		vector <map<int, string> > rec;
		map<int, string> temp;
		temp.insert( { 0, std::to_string(task)});
		temp.insert( { 1, str_with_spec_character(json)});
		//rec.push_back(temp);
		//MyConnectionPool::getInstance().getAllRecordsFromTable();
		bool res = sql.addRecordsInToTable(temp);
		//MyConnectionPool::getInstance().tt();
		/*if(!taskComp)
			{
				stream << "Status: 200\r\n Content-type: text/html\r\n" << "\r\n";
				JsonValue res;
				res["status"] = "already exist";
				stream << res.toStyledString();
			}
			else *///204
		stream << "Status: 200\r\n Content-type: text/html\r\n" << "\r\n" <<"success:"<<res;


	}
	else
	{
		return false;
	}
	return true;
	// string ip_usera = FCGX_GetParam( "REMOTE_ADDR", request->envp );

}

bool retreiveTests(FCGI_Stream &stream, jsonParser &jSON)
{
	//string session = jSON.getObject("session", false).asString();
	int task = jSON.getAsIntS("task");//jSON.getObject("task", false).asInt();
	vector<string> labl;
	labl.push_back("task_id");

	bool taskComp = true;
	SqlConnectionPool sql;
	if (sql.connectToTable(string("tests"), labl))
	{
		/*l12("no threa2");
				vector<map<int, string> > records =	SqlConnectionPool::getInstance().getAllRecordsFromTable(
						"`task_id`='"+std::to_string(task)+"'");
				if ((int)records.size()==0)
					taskComp=true;
				else
					taskComp = false;
		 */

		vector<map<int, string> > records = sql.getAllRecordsFromTable("`task_id`='"+std::to_string(task)+"'");
		//MyConnectionPool::getInstance().tt();
		bool recordsEmpty = records.size() == 0;
		if (recordsEmpty)stream << "Status: 204\r\n Content-type: text/html\r\n" << "\r\n" <<"task with this id doesn't excist";
		else
		{
			stream << "Status: 200\r\n Content-type: text/html\r\n" << "\r\n";
			JsonValue res;
			res["json"] = records[0][1];
			stream << res.toStyledString();
		}

	}
	else
	{
		return false;
	}
	return true;
	// string ip_usera = FCGX_GetParam( "REMOTE_ADDR", request->envp );

}
void replaceAll( string &s, const string &search, const string &replace ) {
	for( size_t pos = 0; ; pos += replace.length() ) {
		// Locate the substring to replace
		pos = s.find( search, pos );
		if( pos == string::npos ) break;
		// Replace by erasing and inserting
		s.erase( pos, search.length() );
		s.insert( pos, replace );
	}
}
void show404()
{
	cout << "Status: 404\r\n"
			<< "Content-type: text/html\r\n"
			<< "\r\n"
			<< " <html><head>"
			<< "<title>404 Not Found</title>"
			<< "</head><body>"
			<< "<h1>Not Found</h1>";
	cout << "<p>The requested URL /localhost was not found on this server.</p>"
			<< "<hr>"
			<< "</body></html>";
	/*
	 * ERR
	 */
	/*cout << "Status: 404\r\n"
	                 << "Content-type: text/html\r\n"
	                 << "\r\n"
	                 << "<html><body><h1>404	Not Found	:(</h1></body></html>\n";

	 */
}

/*
 *
 * 					RESULT_STATUS
 *
 */
bool result_status(FCGI_Stream &stream, jsonParser &jSON, string operation)
{
	string session = jSON.getAsStringS("session");
	string jobid = jSON.getAsStringS("jobid");//			Object("jobid", false).asUInt();578565
	//TO BE CONTINUED ...
	vector<string> labl;

	labl.push_back("id");
	labl.push_back("session");
	labl.push_back("jobid");
	labl.push_back("status");
	labl.push_back("date");
	labl.push_back("result");
	labl.push_back("warning");
	SqlConnectionPool sql;
	if (sql.connectToTable("results", labl)	== true)
	{
		string s_datime = getDateTime(); //'YYYY-MM-DD HH:MM:SS'
		map<int, string> temp;
		temp.insert( { 1, session });
		temp.insert( { 2, (jobid) });
		//3,skip
		temp.insert( { 4, s_datime });
		//4
		vector<map<int, string> > records =	sql.getAllRecordsFromTable(
				"`session`='"+session+"' AND `jobid`='"+(jobid)+"'");
		//	logfile::addLog(std::to_string(records.size()));
		//for (int i=0; i< records.size(); i++)

		/*Cool start for future code, NO delete
		 * logfile::addLog("Id:"+records[i][0]);
			 logfile::addLog("Session:"+records[i][1]);
			 logfile::addLog("jobId:"+records[i][2]);
			 logfile::addLog("requested status for session:"+session+":"+records[i][3]);
			 logfile::addLog("date:"+records[i][4]);
			 logfile::addLog("result:"+records[i][5]);
			 logfile::addLog("warning:"+records[i][6]);
		 */
		/*Cool code no delete
			 stream << "Id:"+records[i][0] << "\n";
			 stream << "Session:"+records[i][1] << "\n";
			 stream << "jobId:"+records[i][2] << "\n";
		 */
		//stream << "status:" +	 records[i].find(keys[r])->second ;
		/*
		 * RESULT
		 */
		//cerr << "before write to stream";

		stream << "Status: 200\r\n Content-type: text/html\r\n" << "\r\n";

		//cerr << "after write to stream";

		JsonValue res;
		if(records.size() > 0)
		{
			res["status"] = records[0][3];
			if (operation == "result" || operation == "r")
			{
				res["date"] = records[0][4];
				res["warning"] = records[0][6];
				//////////////////////////////////////////////////NEW//17.11.15

				/*		string result = records[0][5];
				  smatch m;
				  regex e ("\\b(sub)([^ ]*)");   // matches words beginning by "sub"


				  while (std::regex_search (result,m,e)) {
				    for (auto x:m) std::cout << x << " ";
				    std::cout << std::endl;
				    result = m.suffix().str();
				  }
				 */
				res["testResult"] = JsonValue(arrayValue);

				string part = records[0][5];
				int start = part.find('@');

				if(start == string::npos)
				{
					int position = records[0][5].find("exception");
					if( string::npos != position)
					{
						int p = records[0][5].substr(0, position).find_last_of("\n");
						res["result"] = records[0][5].substr(p + 1);//records[0][5].substr(0, p - 1);
						res["done"] = false;//records[0][5].substr(p);
					}
					else
						res["result"] = records[0][5];

				}
				else
				{
					res["result"] = part.substr(0, start);
					int count = 0;
					bool done = true;
					while(start++ != string::npos)// need test after first fail?
					{
						int next = part.substr(start).find('@');
						string number;
						if(next != string::npos)
						{
							if(next -1 >= 0 && part[start + next - 1] == '!')
							{
								number = part.substr(start, next - 1);
								res["testResult"][count] = JsonValue(false);
								done = false;
							}
							else
							{
								number = part.substr(start, next );
								res["testResult"][count] = JsonValue(true);
							}
						}
						part = part.substr(start + next + 1);
						count++;
						start = part.find('@');
					}
					res["done"] = JsonValue(done);
				}
			}
		}
		else
			res["status"] = "not found";

		stream << res.toStyledString();

		//	stream << "status:" + records[0][3] << "\n\n";
		/*Cool code no delete
		 stream << "date:"+records[i][4] << "\n";
		 stream << "result:"+records[i][5] << "\n";
		 stream << "warning:"+records[i][6] << "\n";
		 */
		//logfile::addLog("Table 'results' outputed");
		cout.flush();
	}
	else
		return false;
	return true;
}

int main(void)
{
	logfile::putLogInArchiveTar();

	Config::getInstance().makeValueStructure();
	Config::getInstance().scanConfigFile();

	//config = new Config();

	pthread_t *id = new pthread_t[Config::getInstance().getThreadCount()];
	FCGX_Init();
	logfile::clear();
	DEBUG("\n\n\n\nStart server ==== Lib is inited");
	// system("mkdir -m 777 src");
	// open socket unix or TCP
	string socket = "127.0.0.1:" + Config::getInstance().getPort();
	socketId = FCGX_OpenSocket(socket.c_str(), 2000);
	if (socketId < 0) {
		ERROR(string("Cannot open socket	" + socket));
		return 1;
	}
	/*INFO(
			"Socket is opened " + socket + "...  create "
			+ to_string(Config::getInstance().getThreadCount()) + " threads");*/
	int i;
	//create thread
	for (i = 0; i < Config::getInstance().getThreadCount(); i++) {
		ThreadArguments argumento;
		argumento.id = i;
		pthread_create(&id[i], NULL, receiveTask, (void *) &argumento);
		// pthread_create(&id[i], NULL, doit, (void *)&i);
	}

	// wait threads
	for (i = 0; i < Config::getInstance().getThreadCount(); i++) {
		pthread_join(id[i], NULL);
	}
	delete[] id;
	INFO("Server stoped successful");
	return 0;
}
