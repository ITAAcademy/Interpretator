#include "inc/logfile.h"

logfile::logfile(FCGX_Request *request)
{
    Request = request;
}

logfile::~logfile()
{

}

void logfile::AddLog()
{
	AddLog(Request);
}

void logfile::AddLog(FCGX_Request *request)
{
    std::ofstream write;
	pthread_mutex_t accept_mutex = PTHREAD_MUTEX_INITIALIZER;
	pthread_mutex_lock(&accept_mutex);

    write.open("log.txt", std::ios_base::app);
	write << FCGX_GetParam( "REMOTE_ADDR", request->envp ) << " -- ";
//	write << FCGX_GetParam("DATA", request->envp) << "; "; // NULL
//	write << FCGX_GetParam( "USER_AGENT", request->envp ) << "; "; // NULL
	write << FCGX_GetParam( "CONTENT_LENGTH", request->envp ) << "\n";

	write.close();

	pthread_mutex_unlock(&accept_mutex);
}
