#include "inc/main.h"

using namespace std;
//using namespace boost;
using namespace Json;


void *doit(void *a)
{
    int rc, i;
    int id = ((int *)a)[0];
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

        if( strcmp(stream.getRequestMethod(), "GET") == 0 )
		{
        	errorResponder.showError(404);
		}
		else{
			Json::Value parsedFromString;
			Json::Reader reader;
			bool parsingSuccessful = true;//reader.parse( str, parsedFromString, false);// IsJSON
			if(parsingSuccessful)
			{
				logfile::AddLog(request);
				stream << "Content-type: text/html\r\n"	<< "\r\n"
				<< "<html>\n" << "  <head>\n"
				<< "    <title>CLang==Compiler	" << id << "</title>\n" // show ID thread in title
				<< "  </head>\n" << "  <body>\n";

				LangCompiler compiler(id);
				stream >> inputSTR; // test input
				char * code = stream.getFormParam("text");
				CodeClear clr;
				string outStr = code;
				clr.ClearText(outStr);
				if(code != NULL)
				{
					//stream << code;
					stream << (char *)compiler.compile(code, true).c_str();
				}

	/*	JSOOOOOOOOOOON
	 * 				if(!parsedFromString["root"].isNull())

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
				stream << "  </body>\n </html>\n";

			}
			else
			{
				errorResponder.showError(400);
			}
		}
        //закрыть текущее соединение
        stream.close();

    }

    return NULL;
}

int main(void)
{
    int i;
    pthread_t *id = new pthread_t[THREAD_COUNT];

    FCGX_Init();
    logfile::AddLog("Start server ==== Lib is inited");
    system("mkdir -m 777 src");
    // open socket unix or TCP
    socketId = FCGX_OpenSocket(SOCKET_PATH, 2000);
    string socket = SOCKET_PATH;
    if(socketId < 0)
    {

    	logfile::AddLog(string("Cannot open socket	" + socket));
        return 1;
    }
    logfile::AddLog("Socket is opened " + socket +"...  create " + to_string(THREAD_COUNT) + " threads");

    //create thread
    for(i = 0; i < THREAD_COUNT; i++)
    {
        pthread_create(&id[i], NULL, doit, (void *)&i);
    }

    // wait threads
    for(i = 0; i < THREAD_COUNT; i++)
    {
        pthread_join(id[i], NULL);
    }
    delete [] id;
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


