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
	if (SqlConnectionPool::getInstance().connectToTable("history", labl))
	{
		string s_datime = getDateTime(); //'YYYY-MM-DD HH:MM:SS'
		map<int, string> temp;
		temp.insert( { 1, userIp });
		temp.insert( { 2, str_with_spec_character(code) });
		temp.insert( { 3, s_datime });
		SqlConnectionPool::getInstance().addRecordsInToTable(temp);
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
	logfile::addLog("before code empty check");
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
		logfile::addLog("Before connect to results");
		//logfile::addLog("Connection to results successful");
		if (SqlConnectionPool::getInstance().connectToTable("results", labl))
		{
			string s_datime = getDateTime(); //'YYYY-MM-DD HH:MM:SS'
			map<int, string> temp;
			temp.insert( { 1, job.session });
			temp.insert( { 2, std::to_string(job.jobid) });
			temp.insert( { 3, "in proccess"});
			temp.insert( { 4, s_datime });
			temp.insert( { 5, "" });
			temp.insert( { 6, "" });
			SqlConnectionPool::getInstance().addRecordsInToTable(temp);

			////////////////
			labl.clear();
			labl.push_back("ID");
			labl.push_back("name");
			labl.push_back("header");
			labl.push_back("etalon");
			labl.push_back("footer");

			string table;
			if (job.lang == "c++" || job.lang == "C++")
				table = "assignment_cpp"; //Config::getInstance().getTaskJavaTableName();
			else if (job.lang == "Java" || job.lang == "java")
				table = "assignment_java";
			else if (job.lang == "Js" || job.lang == "js")
				table = "assignment_js";
			else if (job.lang == "PHP" || job.lang == "php")
				table = "assignment_php";
			else if (job.lang == "C#" || job.lang == "c#" )
				table = "assignment_cs";
			else
				table = "assignment_cpp";
			if (SqlConnectionPool::getInstance().connectToTable(table, labl))
			{
				job.code =
						SqlConnectionPool::getInstance().getCustomCodeOfProgram(
								to_string(job.task), job.code, id,job.lang);
				logfile::addLog(job.code);
			}

			logfile::addLog(to_string(id)+ " Start compiler");
			JsonValue res;

			compiler.compile(job.code, true, LangCompiler::convertFromName(job.lang));


			string date = logfile::getDateStamp();
			res["date"] = date;
			res["result"] = compiler.getResult();
			res["warnings"] = compiler.getWarningErr();
			logfile::addLog( res.toStyledString());


			labl.clear();
			//UPDATE COMPILING INFO IN DB
			labl.push_back("id");
			labl.push_back("session");
			labl.push_back("jobid");
			labl.push_back("status");
			labl.push_back("date");
			labl.push_back("result");
			labl.push_back("warning");
			if (SqlConnectionPool::getInstance().connectToTable("results", labl))
			{
				string s_datime = getDateTime(); //'YYYY-MM-DD HH:MM:SS'
				map<int, string> temp;
				temp.insert( { 1, job.session });
				temp.insert( { 2, to_string(job.jobid) });
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
				where.insert({2,to_string(job.jobid)});
				//ConnectorSQL::getInstance().updateRecordsInToTable(temp,wher);
				SqlConnectionPool::getInstance().updateRecordsInToTable(temp,where);

			}


			logfile::addLog(to_string(id) + " Stop compiler");
		}
		else {

			string error = to_string(id)+"Error: Can`t connect to results table \n";
			logfile::addLog(error);
		}
	}
}


void *receiveTask(void *a)
{
	l12("void *receiveTask(void *a) ");
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
			logfile::addLog(request);
			if (strcmp(stream.getRequestMethod(), "GET") == 0)
			{
				logfile::addLog(id, "Request Method don't POST !!!");
				errorResponder.showError(404);
				logfile::addLog("session closed");
				stream.close();
				continue;
			}
			if(!SqlConnectionPool::getInstance().isConnected()  )
			{

				errorResponder.showError(505, "DataBaseERR");
				l12("Try reconect to DB");
				stream.close();
				SqlConnectionPool::getInstance().reconect(); //124
				continue;  //////////////////////////////
			}
			logfile::addLog("Before jsonParser jSON(stream.getRequestBuffer());");
			jsonParser jSON(stream.getRequestBuffer());

			logfile::addLog("Before parsing successful check");
			bool parsingSuccessful = jSON.isJson() && jSON.isValidFields();
			logfile::addLog("Before jSON.isJson()");
			if (parsingSuccessful)
				logfile::addLog("Before jSON.isValidFields()");
			//parsingSuccessful = jSON.isValidFields(); //reader.parse( str, parsedFromString, false);// IsJSON
			logfile::addLog("Before parsing");
			/*
			 * ALL OK STARTif (SqlConnectionPool::getInstance().connectToTable(string("results"), labl))
			 */

			if (parsingSuccessful)
			{
				string ip_usera = FCGX_GetParam("REMOTE_ADDR", request->envp);
				cout.flush();
				logfile::addLog("Parsing successful");

				string operation = jSON.getObject("operation", false).asString();
				bool succsesful = true;
				/*
				 * OPERATION ADDTASK
				 */
				if (operation == "addtask")
				{
					if(!addNewtask(stream, jSON))
						succsesful = false;
				}
				else
					if (operation == "start")
					{
						if(!start(stream, jSON, FCGX_GetParam("REMOTE_ADDR", request->envp)))
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
										if (operation == "result" || operation == "status")
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
					string error = jSON.getLastError();
					errorResponder.showError(400, error);
					stream.close();
					continue;
				}

			}
			else
			{
				logfile::addLog(id,	"Json format is not correct!!! \n::::::::::::::::::::::::\n" + stream.getRequestBuffer() + "\n::::::::::::::::::::::::");
				errorResponder.showError(400, jSON.getLastError());
				stream.close();
				continue;
			}

		}
	}
	//close session
	logfile::addLog("session closed");
	stream.close();
	return NULL;
}

/*
 *
 *  				NEW TASK
 *
 */
bool addNewtask( FCGI_Stream &stream, jsonParser &jSON)
{
	if ( !jSON.isValidFields() )
	{
		//string error = jSON.getLastError();
		//stream << error;
		//stream.close();
		return false;
	}
	string lang = jSON.getObject("lang", false).asString();
	string table;
	if (lang == "c++" || lang == "C++")
		table = "assignment_cpp"; //Config::getInstance().getTaskJavaTableName();
	else if (lang == "Java" || lang == "java")
		table = "assignment_java";
	else if (lang == "PHP" || lang == "php")
		table = "assignment_php";
	else if (lang == "Js" || lang == "js")
		table = "assignment_js";
	else
		table = "assignment_cpp";

	vector<string> labl;
	labl.push_back("ID");
	labl.push_back("name");
	labl.push_back("header");
	labl.push_back("etalon");
	labl.push_back("footer");
	labl.push_back("json");

	l12("before connectToTable");
	if (SqlConnectionPool::getInstance().connectToTable(table, labl))
	{
		l12("connectedToTable");
		map<int, string> temp;

		//new code for testcases part
		string name = jSON.getObject("name", false).asString();
		l12("name");
		int id = jSON.getObject("task",false).asInt();
		l12("task");
		l12(std::to_string(id));

		TaskCodeGenerator generator(jSON);

		int valuesCount = 0;
		temp.insert( { valuesCount++, std::to_string(id) });
		temp.insert( { valuesCount++, name }); //str_with_spec_character(
		temp.insert( { valuesCount++, str_with_spec_character(generator.getHeader())});
		temp.insert( { valuesCount++, str_with_spec_character(generator.getEtalon())});
		l12("qwe33");
		temp.insert( { valuesCount++, str_with_spec_character(generator.getFooter())});
		temp.insert({valuesCount++, str_with_spec_character(jSON.getJson())});
		l12("temp.insert");
		stream << "Status: 200\r\n Content-type: text/html\r\n" << "\r\n";
		JsonValue res;
		if (generator.getStatus() == 0 && SqlConnectionPool::getInstance().addRecordsInToTable(temp))
		{
			res["status"] = "success";
			res["table"] = table;
			res["id"] = to_string(id);
		}
		else res["status"] = "failed";
		stream << res.toStyledString();
		stream.close();
		return true;
	}
	else
		return false;
}

/*
 *
 * 					START
 *
 */
bool start(FCGI_Stream &stream, jsonParser &jSON, string ip_user)
{
	string session = jSON.getObject("session", false).asString();
	unsigned int jobid = jSON.getObject("jobid", false).asUInt();
	string code = jSON.getObject("code", false).asString();
	int task = jSON.getObject("task", false).asInt();
	string lang = jSON.getObject("lang", false).asString();
	Job requestedTask;
	requestedTask.code = code;
	requestedTask.jobid = jobid;
	requestedTask.lang = lang;
	requestedTask.session = session;
	requestedTask.task = task;
	l12("no threa22");
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
	if (SqlConnectionPool::getInstance().connectToTable(string("results"), labl))
	{
		l12("no threa2");
		vector<map<int, string> > records =	SqlConnectionPool::getInstance().getAllRecordsFromTable(
				"`session`='"+session+"' AND `jobid`='"+to_string(jobid)+"'");
		if ((int)records.size()==0)
			tasksPool.push(processTask,requestedTask);
		else
			taskComp = true;
		//stream << "this job is already excist";

		//addUserToHistory(ip_usera, code);
		labl.clear();
		labl.push_back("ID");
		labl.push_back("ip");
		labl.push_back("code");
		labl.push_back("date_time");
		if (SqlConnectionPool::getInstance().connectToTable("history", labl))
		{
			string s_datime = getDateTime(); //'YYYY-MM-DD HH:MM:SS'
			vector <map<int, string> > rec;
			map<int, string> temp;
			temp.insert( { 1, ip_user});
			temp.insert( { 2, str_with_spec_character(code) });
			temp.insert( { 3, s_datime });
			rec.push_back(temp);

			//MyConnectionPool::getInstance().getAllRecordsFromTable();
			SqlConnectionPool::getInstance().addRecordsInToTable(temp);
			//MyConnectionPool::getInstance().tt();
			if(taskComp)
			{
				stream << "Status: 200\r\n Content-type: text/html\r\n" << "\r\n";
				JsonValue res;
				res["status"] = "already exist";
				stream << res.toStyledString();
			}
			else
				stream << "Status: 204\r\n Content-type: text/html\r\n" << "\r\n";
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
	int task = jSON.getObject("task", false).asInt();
	string lang = jSON.getObject("lang", false).asString();
	//string signature = jSON.getObject("tests_signatures",false).asString();
	string etalon = jSON.getObject("etalon",false).asString();
	Json::FastWriter fastWriter;
	Json::Value signatureValue = jSON.getObject("signature",false);
	std::string signature = fastWriter.write(signatureValue);
	vector<string> labl;
	labl.push_back("task_id");
	labl.push_back("lang");
	labl.push_back("signature");
	labl.push_back("etalon");

	bool taskComp = true;
	if (SqlConnectionPool::getInstance().connectToTable(string("tests_signatures"), labl))
	{
		l12("no threa2");
		vector<map<int, string> > records =	SqlConnectionPool::getInstance().getAllRecordsFromTable(
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
		bool res = SqlConnectionPool::getInstance().addRecordsInToTable(temp);
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
	int task = jSON.getObject("task", false).asInt();
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

	bool taskComp = true;
	if (SqlConnectionPool::getInstance().connectToTable(string("tests_values"), labl))
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
		bool res = SqlConnectionPool::getInstance().addRecordsInToTable(temp);
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
	int task = jSON.getObject("task", false).asInt();
	Json::FastWriter fastWriter;
	Json::Value jsonValue = jSON.getRoot();
	std::string json = fastWriter.write(jsonValue);
	vector<string> labl;
	labl.push_back("task_id");
	labl.push_back("json");

	bool taskComp = true;
	if (SqlConnectionPool::getInstance().connectToTable(string("tests"), labl))
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
		bool res = SqlConnectionPool::getInstance().addRecordsInToTable(temp);
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
	int task = jSON.getObject("task", false).asInt();
	vector<string> labl;
	labl.push_back("task_id");

	bool taskComp = true;
	if (SqlConnectionPool::getInstance().connectToTable(string("tests"), labl))
	{
		/*l12("no threa2");
				vector<map<int, string> > records =	SqlConnectionPool::getInstance().getAllRecordsFromTable(
						"`task_id`='"+std::to_string(task)+"'");
				if ((int)records.size()==0)
					taskComp=true;
				else
					taskComp = false;
		 */

		vector<map<int, string> > records = SqlConnectionPool::getInstance().getAllRecordsFromTable("`task_id`='"+std::to_string(task)+"'");
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

/*
 *
 * 					RESULT_STATUS
 *
 */
bool result_status(FCGI_Stream &stream, jsonParser &jSON, string operation)
{
	string session = jSON.getObject("session", false).asString();
	unsigned int jobid = jSON.getObject("jobid", false).asUInt();
	//TO BE CONTINUED ...
	vector<string> labl;

	labl.push_back("id");
	labl.push_back("session");
	labl.push_back("jobid");
	labl.push_back("status");
	labl.push_back("date");
	labl.push_back("result");
	labl.push_back("warning");
	if (SqlConnectionPool::getInstance().connectToTable("results", labl)	== true)
	{
		string s_datime = getDateTime(); //'YYYY-MM-DD HH:MM:SS'
		map<int, string> temp;
		temp.insert( { 1, session });
		temp.insert( { 2, to_string(jobid) });
		//3,skip
		temp.insert( { 4, s_datime });
		//4
		vector<map<int, string> > records =	SqlConnectionPool::getInstance().getAllRecordsFromTable(
				"`session`='"+session+"' AND `jobid`='"+to_string(jobid)+"'");
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

		stream << "Status: 200\r\n Content-type: text/html\r\n" << "\r\n";

		JsonValue res;
		if(records.size() > 0)
		{
			res["status"] = records[0][3];
			if (operation == "result")
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
		logfile::addLog("Table 'results' outputed");
		cout.flush();
	}
	else
		return false;
	return true;
}

int main(void)
{
	Config::getInstance().makeValueStructure();
	Config::getInstance().scanConfigFile();

	//config = new Config();

	pthread_t *id = new pthread_t[Config::getInstance().getThreadCount()];
	FCGX_Init();
	logfile::clear();
	logfile::addLog("\n\n\n\nStart server ==== Lib is inited");
	// system("mkdir -m 777 src");
	// open socket unix or TCP
	string socket = "127.0.0.1:" + Config::getInstance().getPort();
	socketId = FCGX_OpenSocket(socket.c_str(), 2000);
	if (socketId < 0) {
		logfile::addLog(string("Cannot open socket	" + socket));
		return 1;
	}
	logfile::addLog(
			"Socket is opened " + socket + "...  create "
			+ to_string(Config::getInstance().getThreadCount()) + " threads");
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
	logfile::addLog("Server stoped successful");
	return 0;
}
