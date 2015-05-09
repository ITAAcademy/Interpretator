#include "inc/test.h"

using namespace std;
//using namespace boost;
using namespace Json;

int main(void) {
    // Backup the stdio streambufs

    FCGX_Request *request;
    FCGI_Stream stream;
    request = stream.getRequest();

  //  char j = ~(27-1);

    while (stream.IsRequest()) {
        stream.initFCGI_Stream();
        char * content_length_str = FCGX_GetParam("CONTENT_LENGTH",  request->envp);
		int content_length = 0;
		if(content_length_str != 0)
			content_length = strtol(content_length_str, &content_length_str, 10);
		char *str;
		if( content_length <= 0 )
			content_length = 100;
		str =  new char[content_length + 1];
		cin.read(str, content_length);
		str[content_length] = '\0';

        if( strcmp(stream.getRequestMethod(), "GET") == 0 )
        {
        	show404();
//        	print(pt);
        //	cout << pt.get_child("boolean").begin()->first;

        	//return 0;
        }
        else{
        	Json::Value parsedFromString;
        	Json::Reader reader;
        	bool parsingSuccessful = reader.parse( str, parsedFromString, false);

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
					 << "  <body>\n"
					 << "    <h1>Hellgdfgdfgfdo, World!</h1>\n";
			//	cout << parsedFromString.toStyledString();
					if(!parsedFromString["root"].isNull())
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

					cout << "  </body>\n"
					 << "</html>\n";

        	}
        	else
        		{
        			show404();
        			cout << "?" << str << "?";
        			//break;
        		}
        	}
        stream.initSTD_Stream();
        delete []str;
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
		 << "<h1>Not Found</h1>"
		 << "<p>The requested URL /localhost was not found on this server.</p>"
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


