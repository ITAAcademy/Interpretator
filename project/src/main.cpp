#include "inc/main.h"

#include <ctime>
#include <boost/date_time.hpp>
//extern Config *config;
using namespace std;
//using namespace boost;
using namespace Json;




struct Thread2Arguments {
	int id;
	//ConnectorSQL connector;
};

//void *doit(void *a){};

void *doit(void *a)
{
	 Thread2Arguments argumento = ((Thread2Arguments *)a)[0];
//	logfile::addLog("Connection");
	// ConnectorSQL connector ;

    int rc, i;
   // int id = ((int *)a)[0];

    int id  = argumento.id;
	char * inputSTR;
    FCGX_Request *request;
    FCGI_Stream stream(socketId);
    ErrorResponder errorResponder(&stream);
    request = stream.getRequest();
    string lang;

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

				if (ConnectorSQL::getInstance().connectToHost(Config::getInstance().getDataBaseHost(),Config::getInstance().getUserName(), Config::getInstance().getPassword())==true)

					 {

						if (ConnectorSQL::getInstance().connectToDataBase(Config::getInstance().getDataBaseName())==true)
						{
							logfile::addLog("Connection to database successful");
							vector <string> labl;
							labl.push_back("ID");
					labl.push_back("ip");
					labl.push_back("code");
					labl.push_back("date_time");
					if ( ConnectorSQL::getInstance().connectToTable("History",labl)==true)
					{
				string s_datime = getDateTime(); //'YYYY-MM-DD HH:MM:SS'
				map<int,string> temp;
				temp.insert({1,ip_usera});
				temp.insert({2,str_with_spec_character(code)});
				temp.insert({3,s_datime});
				ConnectorSQL::getInstance().addRecordsInToTable(temp);
					}
				////////////////
				labl.clear();
							labl.push_back("ID");
				labl.push_back("name");
				labl.push_back("header");
				labl.push_back("etalon");
				labl.push_back("footer");

				 lang = jSON.getObject("lang", true).asString();
				string table;
				if (lang == "c++" || lang == "C++" )
				 table = "Assignment_CPP";//Config::getInstance().getTaskJavaTableName();
				else if (lang == "Java" || lang == "java")
					table = "Assignment_JAVA";
				if ( ConnectorSQL::getInstance().connectToTable(table,labl)==true) {
					string task = jSON.getObject("task", true).asString();

					code = ConnectorSQL::getInstance().getCustomCodeOfProgram(task, code,id);
					logfile::addLog(code);
				}
					}
						}



					//stream << code; // show input code text
					logfile::addLog(id, "Start compiler");
					//logfile::addLog(id, "Compile text:\n" + code);
					JsonValue res;

					if (lang == "c++" || lang == "C++" )
						compiler.compile(code, true, LangCompiler::Flag_CPP);
					else if (lang == "Java" || lang == "java")
					compiler.compile(code, true, LangCompiler::Flag_Java);
					else
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

    //config = new Config();
    Config::getInstance().makeValueStructure();
    Config::getInstance().scanConfigFile();
    pthread_t *id = new pthread_t[Config::getInstance().getThreadCount()];
    FCGX_Init();
    logfile::addLog("\n\n\n\nStart server ==== Lib is inited");
   // system("mkdir -m 777 src");
    // open socket unix or TCP
    string socket = "127.0.0.1:"+Config::getInstance().getPort();
    socketId = FCGX_OpenSocket(socket.c_str(), 2000);


    if(socketId < 0)
    {

    	logfile::addLog(string("Cannot open socket	" + socket));
        return 1;
    }
    logfile::addLog("Socket is opened " + socket +"...  create " + to_string(Config::getInstance().getThreadCount()) + " threads");



    //create thread
    for(i = 0; i < Config::getInstance().getThreadCount(); i++)
    {
	Thread2Arguments argumento;
    	argumento.id = i;
    	//argumento.connector = connector;
        pthread_create(&id[i], NULL, doit, (void *)&argumento);
       // pthread_create(&id[i], NULL, doit, (void *)&i);
    }

    // wait threads
    for(i = 0; i < Config::getInstance().getThreadCount(); i++)
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


