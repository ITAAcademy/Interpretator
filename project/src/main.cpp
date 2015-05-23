#include "inc/main.h"

using namespace std;
//using namespace boost;
using namespace Json;


static void *doit(void *a)
{
    int rc, i;
    FCGX_Request *request;
    char *server_name;
    FCGI_Stream stream(socketId);
    request = stream.getRequest();
    /*
    if(FCGX_InitRequest(&request, socketId, 0) != 0)
    {
        //ошибка при инициализации структуры запроса
        printf("Can not init request\n");
        return NULL;
    }
    printf("Request is inited\n");
*/
    for(;;)
    {

        if(!stream.multiIsRequest())
        	break;

        if( strcmp(stream.getRequestMethod(), "GET") == 0 )
               {
        			stream << "qwe";
               }
               else{
               	Json::Value parsedFromString;
               	Json::Reader reader;
               	bool parsingSuccessful = true;//reader.parse( str, parsedFromString, false);// IsJSON

               	// print(pt);
               	if(parsingSuccessful)
               	{

       			//	char ** envp = request->envp;
               		stream << "Content-type: text/html\r\n";
					stream << "\r\n";
					stream << "<html>\n";
					stream << "  <head>\n";
					stream << "    <title>Hello, World!</title>\n";
					stream << "  </head>\n";
					stream << "  <body>\n";
					LangCompiler compiler;
					char * inputSTR = new char[stream.getRequestSize()];
					stream >> inputSTR;
					//sleep(5);
					//stream << inputSTR;
					char * code = stream.getFormParam("text");
					CodeClear clr;
					string str = code;
					clr.ClearText(str);
					if(code != NULL)
					{
						//stream << code;
						stream << (char *)compiler.compile(code, true).c_str();
					}

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
					stream << "  </body>\n </html>\n";

               	}
               	else
               		{
               			//show404();
               		stream << "qwe";
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
    pthread_t id[THREAD_COUNT];

    //инициализация библилиотеки
    FCGX_Init();
    printf("Lib is inited\n");

    //открываем новый сокет
    socketId = FCGX_OpenSocket(SOCKET_PATH, 24);
    if(socketId < 0)
    {
        //ошибка при открытии сокета
        return 1;
    }
    printf("Socket is opened\n");

    //создаём рабочие потоки
    for(i = 0; i < THREAD_COUNT; i++)
    {
        pthread_create(&id[i], NULL, doit, NULL);
    }

    //ждем завершения рабочих потоков
    for(i = 0; i < THREAD_COUNT; i++)
    {
        pthread_join(id[i], NULL);
    }

    return 0;
}


/*void print(boost::property_tree::ptree const& pt)
{
    using boost::property_tree::ptree;
    ptree::const_iterator end = pt.end();
 //   if(strcmp((char*)it->first, 0))
    cout << "<p style=\"margin-LEFT: 50px\">";
    for (ptree::const_iterator it = pt.begin(); it != end; ++it) {
        std::cout << it->first << ": " << it->second.get_value<std::string>() << std::endl;

        print(it->second);

    }
    cout << "</p>";

}*/


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
					 LangCompiler compiler;
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


