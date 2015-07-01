#include "inc/main.h"

#include <ctime>
#include <boost/date_time.hpp>

#include "inc/ctpl_stl.h"
//extern Config *config;
using namespace std;
//using namespace boost;
using namespace Json;

struct Thread2Arguments {
	int id;
	//ConnectorSQL connector;
};
ctpl::thread_pool tasksPool(4);
/*
 *  need insert into SQL
 */
void addUserToHistory(string userIp, string code) {
	if (ConnectorSQL::getInstance().connectToHost(
			Config::getInstance().getDataBaseHost(),
			Config::getInstance().getUserName(),
			Config::getInstance().getPassword()) == true)

	{

		if (ConnectorSQL::getInstance().connectToDataBase(
				Config::getInstance().getDataBaseName()) == true) {
			logfile::addLog("Connection to database successful");
			vector<string> labl;
			labl.push_back("ID");
			labl.push_back("ip");
			labl.push_back("code");
			labl.push_back("date_time");
			if (ConnectorSQL::getInstance().connectToTable("History", labl)
					== true) {
				string s_datime = getDateTime(); //'YYYY-MM-DD HH:MM:SS'
				map<int, string> temp;
				temp.insert( { 1, userIp });
				temp.insert( { 2, str_with_spec_character(code) });
				temp.insert( { 3, s_datime });
				ConnectorSQL::getInstance().addRecordsInToTable(temp);
			}
		}
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
		if (ConnectorSQL::getInstance().connectToHost(
				Config::getInstance().getDataBaseHost(),
				Config::getInstance().getUserName(),
				Config::getInstance().getPassword()) == true)

		{

		if (ConnectorSQL::getInstance().connectToDataBase( Config::getInstance().getDataBaseName())	== true)
		{
			logfile::addLog("Connection to database successful");
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
			logfile::addLog("Connection to results successful");
			if (ConnectorSQL::getInstance().connectToTable("results", labl)	== true)
			{
				logfile::addLog("Connection to table results correct");
				string s_datime = getDateTime(); //'YYYY-MM-DD HH:MM:SS'
				map<int, string> temp;
				temp.insert( { 1, job.session });
				temp.insert( { 2, to_string(job.jobid) });
				temp.insert( { 3, "proccess"});
				temp.insert( { 4, s_datime });
				temp.insert( { 5, "..." });
				temp.insert( { 6, "..." });
				ConnectorSQL::getInstance().addRecordsInToTable(temp);
			}

			////////////////
			labl.clear();
			labl.push_back("ID");
			labl.push_back("name");
			labl.push_back("header");
			labl.push_back("etalon");
			labl.push_back("footer");

			string table;
			if (job.lang == "c++" || job.lang == "C++")
				table = "Assignment_CPP"; //Config::getInstance().getTaskJavaTableName();
			else if (job.lang == "Java" || job.lang == "java")
				table = "Assignment_JAVA";
			else
				table = "Assignment_CPP";
			if (ConnectorSQL::getInstance().connectToTable(
					table, labl) == true) {
				job.code =
						ConnectorSQL::getInstance().getCustomCodeOfProgram(
								to_string(job.task), job.code, id);
				logfile::addLog(job.code);
			}

			logfile::addLog(to_string(id)+ " Start compiler");
			JsonValue res;

			if (job.lang == "c++" || job.lang == "C++")
				compiler.compile(job.code, true, LangCompiler::Flag_CPP);
			else if (job.lang == "Java" || job.lang == "java")
				compiler.compile(job.code, true, LangCompiler::Flag_Java);
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
				if (ConnectorSQL::getInstance().connectToTable("results", labl)	== true)
				{
					string s_datime = getDateTime(); //'YYYY-MM-DD HH:MM:SS'
					map<int, string> temp;
					temp.insert( { 1, job.session });
					temp.insert( { 2, to_string(job.jobid) });
					temp.insert( { 3, "updated"});
					temp.insert( { 4, s_datime });
					temp.insert( { 5, "..." });
					temp.insert( { 5, "..." });
					//4
					string where = "`results`.`jobid`='"+to_string(job.jobid)+"' AND `results`.`session`='"+job.session+"'";
					ConnectorSQL::getInstance().updateRecordsInToTable(temp,labl,where);
				}
			}
		}
		logfile::addLog(to_string(id) + " Stop compiler");
	}
	else {
	logfile::addLog(to_string(id)+" Json format is not correct!!! \n::::::::::::::::::::::::\n");
	}
}
void *receiveTask(void *a) {
	Thread2Arguments argumento = ((Thread2Arguments *) a)[0];
	int rc, i;
	int id = argumento.id;
	char * inputSTR;
	FCGX_Request *request;
	FCGI_Stream stream(socketId);
	ErrorResponder errorResponder(&stream);
	request = stream.getRequest();
	string lang;

	for (;;)
	{
		if (!stream.multiIsRequest()) {
			break;
		}
		logfile::addLog(request);

		if (strcmp(stream.getRequestMethod(), "GET") == 0)
		{
			logfile::addLog(id, "Request Method don't POST !!!");
			errorResponder.showError(404);
		}
		else
		{
			jsonParser jSON(stream.getRequestBuffer());
			bool parsingSuccessful = jSON.isValidFields(); //reader.parse( str, parsedFromString, false);// IsJSON
			logfile::addLog("Before parsing");
			/*
			 * ALL OK START
			 */
			if (parsingSuccessful)
			{
				string ip_usera = FCGX_GetParam("REMOTE_ADDR", request->envp);
				stream << "Content-type: text/html\r\n" << "\r\n";/* << "<html>\n" << "  <head>\n"
						<< "    <title>Receiver	" << id << "</title>\n" // show ID thread in title
						<< "  </head>\n" << "  <body>\n";*/
				cout.flush();
				logfile::addLog("Parsing successful");
				//cout.flush();
				string operation = jSON.getObject("operation", false).asString();
				string session = jSON.getObject("session", false).asString();
				int jobid = jSON.getObject("jobid", false).asInt();
				if (operation == "send") {
				string code = jSON.getObject("code", false).asString();
				int task = jSON.getObject("task", false).asInt();
				string lang = jSON.getObject("lang", false).asString();
				Job requestedTask;
				requestedTask.code = code;
				requestedTask.jobid = jobid;
				requestedTask.lang = lang;
				requestedTask.session = session;
				requestedTask.task = task;

				/*
				 * BAD NEED FIX @BUDLO@ INCLUDE INTO sql
				 */
				if (ConnectorSQL::getInstance().connectToHost(
							Config::getInstance().getDataBaseHost(),
							Config::getInstance().getUserName(),
							Config::getInstance().getPassword()) == true)
				{

					if (ConnectorSQL::getInstance().connectToDataBase(
							Config::getInstance().getDataBaseName()) == true)
					{
						logfile::addLog("Connection to database successful");
						vector<string> labl;
						labl.push_back("id");
						labl.push_back("session");
						labl.push_back("jobid");
						labl.push_back("status");
						labl.push_back("date");
						labl.push_back("result");
						labl.push_back("warning");
						if (ConnectorSQL::getInstance().connectToTable("results", labl) ){
							vector<map<int, string> > records = ConnectorSQL::getInstance().getAllRecordsFromTable("`session`='"+session+"' AND `jobid`='"+to_string(jobid)+"'");
							logfile::addLog("overlap:"+(int)records.size());
							if ((int)records.size()==0)
								tasksPool.push(processTask,requestedTask);
							else
								stream << "this job is already excist";
						}
					}
				}
				addUserToHistory(ip_usera, code);
				// string ip_usera = FCGX_GetParam( "REMOTE_ADDR", request->envp );
			}
			else if (operation == "status")
				{
					//TO BE CONTINUED ...
					if (ConnectorSQL::getInstance().connectToHost(
							Config::getInstance().getDataBaseHost(),
							Config::getInstance().getUserName(),
							Config::getInstance().getPassword()) == true)
					{

						if (ConnectorSQL::getInstance().connectToDataBase(Config::getInstance().getDataBaseName()) == true)
						{
							logfile::addLog("Connection to database successful");
							vector<string> labl;

							labl.push_back("id");
							labl.push_back("session");
							labl.push_back("jobid");
							labl.push_back("status");
							labl.push_back("date");
							labl.push_back("result");
							labl.push_back("warning");
							if (ConnectorSQL::getInstance().connectToTable("results", labl)	== true)
							{
								string s_datime = getDateTime(); //'YYYY-MM-DD HH:MM:SS'
								map<int, string> temp;
								temp.insert( { 1, session });
								temp.insert( { 2, to_string(jobid) });
								//3,skip
								temp.insert( { 4, s_datime });
								//4
								vector<map<int, string> > records =
										ConnectorSQL::getInstance().getAllRecordsFromTable(
												"`session` =" + session + " AND `jobid` ="+to_string(jobid));

								for (int i = 0; i < (int) records.size(); i++)
								{
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
									stream << "status:" + records[i][3] << "\n";
									/*Cool code no delete
									 stream << "date:"+records[i][4] << "\n";
									 stream << "result:"+records[i][5] << "\n";
									 stream << "warning:"+records[i][6] << "\n";
									 */
								}
								logfile::addLog("Table 'results' outputed");

								//cout.flush();
							}
						}
					}
				}
			/*res["date"] = date;
			 res["result"] = compiler.getResult();
			 res["warnings"] = compiler.getWarningErr();
			 stream << res.toStyledString();
			 */

			/*
			 * test Json class // don't delete
			 */
			/*
			 stream << code << "\r\n" << name << "\r\n";
			 jsonParser parser(code);
			 stream << parser.getObject(name, true).toStyledString();
			 */

			}
			else
			{
				logfile::addLog(id,
						"Json format is not correct!!! \n::::::::::::::::::::::::\n"
								+ stream.getRequestBuffer() + "\n::::::::::::::::::::::::");
				errorResponder.showError(400);
			}
		}
	//close session
	logfile::addLog("session closed");
	stream.close();
	}
	return NULL;
}

	int main(void) {
	int i;

	 //config = new Config();
	Config::getInstance().makeValueStructure();
	Config::getInstance().scanConfigFile();
	pthread_t *id = new pthread_t[Config::getInstance().getThreadCount()];
	FCGX_Init();
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

	 //create thread
	for (i = 0; i < Config::getInstance().getThreadCount(); i++) {
		Thread2Arguments argumento;
	argumento.id = i;
	//argumento.connector = connector;
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

	/*
	 *  Apache main function
	 */
	int Apache(void) {
	 // Backup the stdio streambufs
	FCGX_Init();
	FCGX_Request *request;
	FCGI_Stream stream(socketId);
	request = stream.getRequest();

	 //  char j = ~(27-1);

	while (stream.IsRequest()) {
	stream.initFCGI_Stream();
	stream.reInitRequesBuffer();

	if (strcmp(stream.getRequestMethod(), "GET") == 0) {
	show404();
	} else {
	Json::Value parsedFromString;
	Json::Reader reader;
	bool parsingSuccessful = true; //reader.parse( str, parsedFromString, false);// IsJSON

	 // print(pt);
	if (parsingSuccessful) {

	//	char ** envp = request->envp;
	cout << "Content-type: text/html\r\n" << "\r\n" << "<html>\n" << "  <head>\n"
			<< "    <title>Hello, World!</title>\n" << "  </head>\n"
			<< "  <body>\n";
	LangCompiler compiler(0);
	char * code = stream.getFormParam("text");
	cout << code;
	cout << compiler.compile(code, true);
	/*					if(!parsedFromString["root"].isNull())
	 {
	 Value v1 = parsedFromString["root"];
	 Value v = v1["values"];
	 if(v.isArray())
	 {
	 for(unsigned int index=0; index<v.size(); ++index)
	 {
	 cout << v[index].toStyledString();
	 }
	 }
	 }
	 else cout << "==============================================NULL";
	 */
	cout << "  </body>\n" << "</html>\n";

	} else {
	show404();
	}
	}
	stream.initSTD_Stream();

	//		{ "root": { "values": [1, 2, 3, 4, 5 ] } }
	/*
	 for ( ; *envp; ++envp)
	 {
	 cout << *envp << "\n";
	 }*/
	}

	return 0;
}

