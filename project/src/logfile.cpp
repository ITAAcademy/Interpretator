#include "inc/logfile.h"

logfile::logfile(FCGX_Request request)
{
    Request = request;
}

logfile::~logfile()
{

}

void logfile::AddLog()
{
    std::ofstream write;
    write.open("log.txt", std::ios_base::app);

        write << FCGX_GetParam( "REMOTE_ADDR", Request.envp ) << " -- "
              << FCGX_GetParam("DATA", Request.envp)
              << "; " << FCGX_GetParam( "USER_AGENT", Request.envp ) << ""; "
              << FCGX_GetParam( "CONTENT_LENGTH", Request.envp ) << endl;

        write.close();
}
