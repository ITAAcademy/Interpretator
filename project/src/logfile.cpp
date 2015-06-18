#include "inc/logfile.h"

logfile::logfile(FCGX_Request *request)
{
    Request = request;
}

logfile::~logfile()
{

}

void logfile::addLog()
{
	addLog(Request);
}

void logfile::addLog(FCGX_Request *request, string addStr)
{
    std::ofstream write;
	pthread_mutex_t accept_mutex = PTHREAD_MUTEX_INITIALIZER;
	pthread_mutex_lock(&accept_mutex);

    write.open("log.txt", std::ios_base::app);
    string out;
	out += FCGX_GetParam( "REMOTE_ADDR", request->envp );
	out += " request length: ";
	out +=  FCGX_GetParam( "CONTENT_LENGTH", request->envp );


	write << out << setw(100 - legthClearnStr(out)) << getDateStamp();
	write.close();

	pthread_mutex_unlock(&accept_mutex);
}

void logfile::addLog(string str)
{
    std::ofstream write;
	pthread_mutex_t accept_mutex = PTHREAD_MUTEX_INITIALIZER;
	pthread_mutex_lock(&accept_mutex);
	cout.flush();
    write.open("log.txt", std::ios_base::app);
    write << str <<  setw(100 - legthClearnStr(str)) << getDateStamp();
	write.close();
	cout.flush();
	pthread_mutex_unlock(&accept_mutex);
}

void logfile::addLog(int threadID, string str)
{
	ostringstream  res;
	res << setw(2*threadID) << to_string(threadID) << string(" ");
	addLog(res.str() + str);
}

char *logfile::getDateStamp()
{
	time_t result = time(nullptr);
	return asctime(localtime(&result));
}

int logfile::legthClearnStr(string str)
{
	int length = str.length();
	int newLen = 0;
	for (int j = 0; j < length; j++) {
		if (str[j] >= ' ') {
			newLen++;
		}
		if(str[j] == '\n')
			newLen = 0;
	}
	return newLen;
}

