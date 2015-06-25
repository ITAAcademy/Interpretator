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

void logfile::AddLog(FCGX_Request *request, string addStr)
{
    std::ofstream write;
	pthread_mutex_t accept_mutex = PTHREAD_MUTEX_INITIALIZER;
	pthread_mutex_lock(&accept_mutex);

    write.open("log.txt", std::ios_base::app);
    string out;
	out += FCGX_GetParam( "REMOTE_ADDR", request->envp );
	out += " ";
	out +=  FCGX_GetParam( "CONTENT_LENGTH", request->envp );


	write << out << setw(100 - out.length()) << getDateStamp();
	write.close();

	pthread_mutex_unlock(&accept_mutex);
}

void logfile::AddLog(string str)
{
    std::ofstream write;
	pthread_mutex_t accept_mutex = PTHREAD_MUTEX_INITIALIZER;
	pthread_mutex_lock(&accept_mutex);

    write.open("log.txt", std::ios_base::app);
    write << str <<  setw(100 - str.length()) << getDateStamp();
	write.close();

	pthread_mutex_unlock(&accept_mutex);
}

char *logfile::getDateStamp()
{
	time_t result = time(nullptr);
	return asctime(localtime(&result));
}

