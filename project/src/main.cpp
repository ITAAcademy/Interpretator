#include "inc/main.h"
#include <ctime>
#include <boost/date_time.hpp>
using namespace std;
//using namespace boost;
using namespace Json;




struct Thread2Arguments {
	int id;
	//ConnectorSQL connector;
};

void *doit(void *a)
{
	 Thread2Arguments argumento = ((Thread2Arguments *)a)[0];
//	logfile::addLog("Connection");
	 ConnectorSQL connector ;

    int rc, i;
   // int id = ((int *)a)[0];

    int id  = argumento.id;
	char * inputSTR;
    FCGX_Request *request;
    FCGI_Stream stream(socketId);
    ErrorResponder errorResponder(&stream);
    request = stream.getRequest();


    for(;;)
    {

        if(!stream.multiIsRequest())
        {
        	break;
        }
        logfile::addLog(request);

        if( strcmp(stream.getRequestMethod(), "GET") == 0 )
		{
        	logfile::addLog( id, "Request Method don't POST !!!");
        	errorResponder.showError(404);
		}
		else{
			jsonParser jSON(stream.getRequestBuffer());
			bool parsingSuccessful = jSON.isValidFields();//reader.parse( str, parsedFromString, false);// IsJSON
			if(parsingSuccessful)
			{
				stream << "Content-type: text/html\r\n"	<< "\r\n"
				<< "<html>\n" << "  <head>\n"
				<< "    <title>CLang==Compiler	" << id << "</title>\n" // show ID thread in title
				<< "  </head>\n" << "  <body>\n";

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
				cout.flush();
				string code = jSON.getObject("code", true).asString();
				if(!code.empty())
				{
					 string ip_usera = FCGX_GetParam( "REMOTE_ADDR", request->envp );

					if (connector.connectToHost("127.0.0.1", "3306", "root", "testsql")==false)
					{
						logfile::addLog("Connection  to host failed");
					}
					else
					 {
						logfile::addLog("Connection to host successful");
						if ( connector.connectToDataBase("ITA-codeforce")==false)
							logfile::addLog("Connection to database failed");
						else {
							logfile::addLog("Connection to database successful");
							vector <string> labl;
							labl.push_back("ID");
					labl.push_back("ip");
					labl.push_back("code");
					labl.push_back("date_time");
					if ( connector.connectToTable("History",labl)==false)
					logfile::addLog("Connection to history`s table failed");
					else {
						logfile::addLog("Connection to history`s table successful");
						 time_t t = time(0);   // get time now
											struct tm * now = localtime( & t );
				string s_datime; //'YYYY-MM-DD HH:MM:SS'
				s_datime += std::to_string(now->tm_year + 1900)+ "-" +
				 std::to_string(now->tm_mon + 1) + "-" + std::to_string(now->tm_mday)+ " "+
				 std::to_string(now->tm_hour) + ":" +  std::to_string(now->tm_min) + ":" +
				 std::to_string(now->tm_sec) ;

				map<int,string> temp;
				temp.insert({1,ip_usera});
				temp.insert({2,str_with_spec_character(code)});
				temp.insert({3,s_datime});
				connector.addRecordsInToTable(temp);
					}
						}
					 }
					connector.resetConection();
				if (connector.connectToHost("127.0.0.1", "3306", "root", "testsql")==false)
				logfile::addLog("Connection  to host failed");
				else
				  {
					logfile::addLog("Connection to host successful");
					if ( connector.connectToDataBase("ITA-codeforce")==false)
						logfile::addLog("Connection to database failed");
					else {
						logfile::addLog("Connection to database successful");
						vector <string> labl;
						labl.push_back("ID");
			labl.push_back("name");
			labl.push_back("header");
			labl.push_back("etalon");
			labl.push_back("footer");
			if ( connector.connectToTable("Assignment",labl)==false) {
			logfile::addLog("Connection to assignment`s table failed");
			}
			else {
				logfile::addLog("Connection to assignment`s table successful");
					string task = jSON.getObject("task", true).asString();
				code = connector.getCustomCodeOfProgram(task, code);
				logfile::addLog(code);
			}
					}
				  }


					//stream << code; // show input code text
					logfile::addLog(id, "Start compiler");
					//logfile::addLog(id, "Compile text:\n" + code);
					JsonValue res;
					compiler.compile(code, true);
					string date = logfile::getDateStamp();
					date[date.size() - 1] = '\0';
					res["date"] = date;
					res["result"] = compiler.getResult();
					res["warnings"] = compiler.getWarningErr();
					stream << res.toStyledString();
					//stream << compiler.compile(code, true);
					logfile::addLog(id, "Stop compiler");

					/*
					 * test Json class // don't delete
					 */
					/*
					stream << code << "\r\n" << name << "\r\n";
					jsonParser parser(code);
					stream << parser.getObject(name, true).toStyledString();
					*/

				}
				stream << "  </body>\n </html>\n";
			}
			else
			{
				logfile::addLog( id, "Json format is not correct!!! \n::::::::::::::::::::::::\n" + stream.getRequestBuffer() + "\n::::::::::::::::::::::::");
				errorResponder.showError(400);
			}
		}
        //close session
        stream.close();

    }

    return NULL;
}

int main(void)
{
    int i;
    pthread_t *id = new pthread_t[THREAD_COUNT];

    FCGX_Init();
    logfile::addLog("\n\n\n\nStart server ==== Lib is inited");
   // system("mkdir -m 777 src");
    // open socket unix or TCP
    socketId = FCGX_OpenSocket(SOCKET_PATH, 2000);
    string socket = SOCKET_PATH;
    if(socketId < 0)
    {

    	logfile::addLog(string("Cannot open socket	" + socket));
        return 1;
    }
    logfile::addLog("Socket is opened " + socket +"...  create " + to_string(THREAD_COUNT) + " threads");



    //create thread
    for(i = 0; i < THREAD_COUNT; i++)
    {
	Thread2Arguments argumento;
    	argumento.id = i;
    	//argumento.connector = connector;
        pthread_create(&id[i], NULL, doit, (void *)&argumento);
       // pthread_create(&id[i], NULL, doit, (void *)&i);
    }

    // wait threads
    for(i = 0; i < THREAD_COUNT; i++)
    {
        pthread_join(id[i], NULL);
    }
    delete [] id;
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
    FCGI_Stream stream(socketId) ;
    request = stream.getRequest();

  //  char j = ~(27-1);

    while (stream.IsRequest()) {
        stream.initFCGI_Stream();
        stream.reInitRequesBuffer();

        if( strcmp(stream.getRequestMethod(), "GET") == 0 )
        {
        	show404();
        }
        else{
        	Json::Value parsedFromString;
        	Json::Reader reader;
        	bool parsingSuccessful = true;//reader.parse( str, parsedFromString, false);// IsJSON

        	// print(pt);
        	if(parsingSuccessful)
        	{

			//	char ** envp = request->envp;
				cout << "Content-type: text/html\r\n"
					 << "\r\n"
					 << "<html>\n"
					 << "  <head>\n"
					 << "    <title>Hello, World!</title>\n"
					 << "  </head>\n"
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
					cout << "  </body>\n"
					 << "</html>\n";

        	}
        	else
        		{
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


