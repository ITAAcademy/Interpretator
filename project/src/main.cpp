#include "inc/main.h"

#include <ctime>
#include "inc/ctpl_stl.h"
#include "inc/SQLConnectionPool.h"
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

class Later
{
public:
	template <class callable, class... arguments>
	Later(int after, bool async, callable&& f, arguments&&... args)
	{
		std::function<typename std::result_of<callable(arguments...)>::type()> task(std::bind(std::forward<callable>(f), std::forward<arguments>(args)...));

		if (async)
		{
			std::thread([after, task]() {
				std::this_thread::sleep_for(std::chrono::milliseconds(after));
				task();
			}).detach();
		}
		else
		{
			std::this_thread::sleep_for(std::chrono::milliseconds(after));
			task();
		}
	}

};
/*
 *  need insert into SQL
 */

 void l12(string ll) {
	logfile::addLog(ll);
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
			temp.insert( { 2, to_string(job.jobid) });
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

			if (job.lang == "c++" || job.lang == "C++")
				compiler.compile(job.code, true, LangCompiler::Flag_CPP);
			else if (job.lang == "Java" || job.lang == "java")
				compiler.compile(job.code, true, LangCompiler::Flag_Java);
			else if (job.lang == "JS" || job.lang == "js")
				compiler.compile(job.code, true, LangCompiler::Flag_JS);
			else if (job.lang == "PHP" || job.lang == "php")
				compiler.compile(job.code, true, LangCompiler::Flag_PHP);
			else
				compiler.compile(job.code, true);

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
			logfile::addLog(to_string(id)+" Json format is not correct!!! \n::::::::::::::::::::::::\n");
		}
	}
}


static map<string, Token> TokenList;

void *receiveTask(void *a)
{
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

			jsonParser jSON(stream.getRequestBuffer());
			bool parsingSuccessful = jSON.isValidFields(); //reader.parse( str, parsedFromString, false);// IsJSON
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
				if (operation == "start")
				{
					if(!start(stream, jSON, FCGX_GetParam("REMOTE_ADDR", request->envp)))
						succsesful = false;
				}
				if (operation == "result" || operation == "status")
				{
					if(!result_status(stream, jSON, operation))
						succsesful = false;
				}

				if (operation == "getToken")
				{
					if(!generationToken(stream, jSON, TokenList))
						succsesful = false;
				}
				if (operation == "getFromToken")
				{
					if(!getFromToken(stream, jSON, TokenList))
						succsesful = false;
				}

				if(!succsesful)
				{
					errorResponder.showError(505, "DataBaseERR");
					stream.close();
					continue;
				}

			}
			else
			{
				logfile::addLog(id,	"Json format is not correct!!! \n::::::::::::::::::::::::\n" + stream.getRequestBuffer() + "\n::::::::::::::::::::::::");
				errorResponder.showError(400, " ");
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
	if (SqlConnectionPool::getInstance().connectToTable(table, labl))
	{
		map<int, string> temp;
		string header = jSON.getObject("header", false).asString();
		l12("header ");
		string etalon = jSON.getObject("etalon", false).asString();
		l12("etalon");
		string footer = jSON.getObject("footer", false).asString();
		l12("footer");
		string name = jSON.getObject("name", false).asString();
		l12("name");
		int task = jSON.getObject("task", false).asInt();
		int id = jSON.getObject("task",false).asInt();
		l12("task");
		l12(std::to_string(task));
		//	if (task)
		temp.insert( { 0, std::to_string(task) });
		temp.insert( { 1, name }); //str_with_spec_character(
		temp.insert( { 2, str_with_spec_character(header)});
		temp.insert( { 3, str_with_spec_character(etalon )});
		temp.insert( { 4, str_with_spec_character(footer) });
		l12("temp.insert");
		stream << "Status: 200\r\n Content-type: text/html\r\n" << "\r\n";
		JsonValue res;
		if (SqlConnectionPool::getInstance().addRecordsInToTable(temp))
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
	int jobid = jSON.getObject("jobid", false).asInt();
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

/*
 *
 * 					RESULT_STATUS
 *
 */
bool result_status(FCGI_Stream &stream, jsonParser &jSON, string operation)
{
	string session = jSON.getObject("session", false).asString();
	int jobid = jSON.getObject("jobid", false).asInt();
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
				res["result"] = records[0][5];
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

//GENERATION TOKEN
bool generationToken(FCGI_Stream &stream, jsonParser &jSON, map<string, Token> &token)
{
	string session = jSON.getObject("session", false).asString();
	int jobid = jSON.getObject("jobid", false).asInt();
	Token tok;
	tok.session = session;
	tok.jobId = jobid;
	hash<string> hash_fn;
	long hash = hash_fn(session)^(hash_fn(to_string(jobid)) << 1)^(hash_fn(to_string(time(0))) << 2);
	string value = to_string(hash);
	token[value] = tok;
	JsonValue res;

	res["token"] = value;
	stream << "Status: 200\r\n Content-type: text/html\r\n" << "\r\n";
	stream << res.toStyledString();

	Later later_delete(Config::getInstance().getTokenTimeOut(), true, &deleteToken, value);
	 //Later later_test2(1000, false, &test2, 101);

	return true;

}

bool getFromToken(FCGI_Stream &stream, jsonParser &jSON, map<string, Token> &tokenList)
{
	JsonValue res;
	string strToken = jSON.getObject("token", false).asString();
	Token value;
	if(tokenList.count( strToken ) == 0)
	{
		res["status"] = "Token time out";
		stream << "Status: 200\r\n Content-type: text/html\r\n" << "\r\n";
		stream << res.toStyledString();
		logfile::addLog("Token time out");
		l12( "GET FROM TOKEN" );
			l12( to_string(tokenList.size()) );
		cout.flush();
		return true;
	}
	value =  tokenList[strToken];

	string session = value.session;
	int jobid = value.jobId;
	l12( "GET FROM TOKEN" );
	l12( to_string(jobid) );
	l12( session );
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


		if(records.size() > 0)
		{
			res["status"] = records[0][3];
			{
				res["date"] = records[0][4];
				res["warning"] = records[0][6];
				res["result"] = records[0][5];
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
void deleteToken(string tok)
{
	TokenList.erase(tok);
}
