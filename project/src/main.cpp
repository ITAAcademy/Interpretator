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

			compiler.compile(job.code, true, LangCompiler::convertFromName(job.lang),0);


			string date = logfile::getDateStamp();
			res["date"] = date;

			string rezulta = compiler.getResult();
			res["result"] = rezulta;
			string warning = compiler.getWarningErr();
			res["warnings"] = warning;
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

			bool need_stream = true;

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
					addNewtask(stream, jSON, id, errora, need_stream);
				}
				else
					if (operation == "getJson")
					{
						if(!getJson(stream, jSON, id))
							succsesful = false;
					}
					else
						if (operation == "copyTask")
						{
							if(!copyTask(stream, jSON, id, errora, need_stream))
								succsesful = false;
						}
						else
							if (operation == "start" || operation == "s")
							{
								if(!start(stream, jSON, FCGX_GetParam("REMOTE_ADDR", request->envp), errora, need_stream))
									succsesful = false;
							}
							else
								if (operation == "addUtest" || operation == "u")
								{
									addTestsToTask(stream, jSON, id, errora, need_stream);
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
					if (need_stream)
					{
						JsonValue res;
						stream << "Status: 200\r\n Content-type: text/html\r\n" << "\r\n";
						string error = jSON.getLastError() + "\n" + errora;
						/*	errorResponder.showError(400, error);
					stream.close();*/

						res["status"] = error;
						stream << res.toStyledString();
						stream.close();
					}
					continue;
				}

			}
			else
			{
				if (need_stream)
				{
					JsonValue res;
					stream << "Status: 200\r\n Content-type: text/html\r\n" << "\r\n";
					//logfile::addLog(id,	"Json format is not correct!!! \n::::::::::::::::::::::::\n" + stream.getRequestBuffer() + "\n::::::::::::::::::::::::");
					/*errorResponder.showError(400, jSON.getLastError());
				stream.close();*/

					res["status"] = jSON.getLastError();
					stream << res.toStyledString();
					stream.close();
				}

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



string removeDoubleBrackets(string value)
{
	char prev_char = ' ';
	int val_size = value.size();
	char * res = new char[val_size];
	int y = 0;

	for (int i = 0; i < val_size; i++)
	{
		char cur_char = value[i];


		if (cur_char == '\"' )
		{
			if (prev_char != '\\')
			{
				res[y++] = prev_char;
			}
			res[y++] = cur_char;
		}
		else
			if (cur_char == '\\' )
			{
				prev_char = cur_char;
			}
			else
				res[y++] = cur_char;
		/*
		if (!(prev_char == '\\' + cur_char == '\"' ) )
			res[y++] = cur_char;
		prev_char = cur_char;*/
	}
	for (int i = y; i < val_size; i++)
		res[i] = '\0';

	string s_result(res);
	return s_result;
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
