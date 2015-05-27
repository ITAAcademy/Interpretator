#include "inc/cLang.h"
#include "inc/SQLconnector.h"

LangCompiler::LangCompiler(int ID){
	thID = ID;
}

LangCompiler::~LangCompiler(){

}

string LangCompiler::compile(char *code, bool show, compilerFlag flags)
{
	string res = "\0";
	if(!generetionSample(code, flags))
		return "Canot open file";
	cout.flush();

	string in = "./build.sh "  + to_string(thID);
	string kompill = getStdoutFromCommand(in);
	if(show)
	{
		res.append("<form><textarea style=\"width: 100%; height: 400px;\">");
		res.append(kompill);
		if(kompill.size() <= 1)
			res.append("=======OK=======");
		res.append("</textarea></form>");
		return res;
	}
	return kompill;

	/*cout << "Content-type: text/html\r\n"
						 << "\r\n"
						 << "<html>\n"
						 << "  <head>\n"
						 << "    <title>Result!</title>\n"
						 << "  </head>\n"
						 << "  <body>\n";*/
						 	 //cout << "<form><textarea style=\"width: 100%; height: 400px;\">"  << k<< "</textarea></form>";
						 /*cout << "  </body>\n"
						 << "</html>\n";*/
}

bool LangCompiler::generetionSample(char *code, compilerFlag flags)
{
	// in the future
	if(flags == Flag_TYPE1)
	{
		ofstream file;
		char str[50];
		sprintf(str, "/var/www/fcgi/srs/code%d.cpp", thID);
		file.open(str, fstream::out);
		if(!file.is_open())
			return false;
		file << code;
		file.close();
	}
	return true;
}

char* LangCompiler::getSystemOutput(char* cmd){
	int buff_size = 32;
	char buff[buff_size+1]; memset((char*)&buff, 0, buff_size+1);

	char* ret = NULL;
	string str = "";

    int fd[2];
    int old_fd[3];
    pipe(fd);


	old_fd[0] = !STDIN_FILENO;
	old_fd[1] = !STDOUT_FILENO;
	old_fd[2] = !STDERR_FILENO;

	old_fd[0] = dup(STDIN_FILENO);
	old_fd[1] = dup(STDOUT_FILENO);
	old_fd[2] = dup(STDERR_FILENO);

	int pid = fork();
	switch(pid){
		case 0:
			close(fd[0]);
			close(STDOUT_FILENO);
			close(STDERR_FILENO);
			dup2(fd[1], STDOUT_FILENO);
			dup2(fd[1], STDERR_FILENO);
			system(cmd);
			close (fd[1]);
			exit(1);
			break;
		case -1:
			cerr << "GetSystemOutput/fork() error\n" << endl;
			exit(1);
		default:
			close(fd[1]);
			dup2(fd[0], STDIN_FILENO);

			while (read(fd[0], buff, buff_size)){
				str.append(buff);
				memset(buff, 0, buff_size);
			}

			ret = new char (strlen((char*)str.c_str()));

			strcpy(ret, (char*)str.c_str());

			waitpid(pid, NULL, 0);
			close(fd[0]);
	}

	dup2(STDIN_FILENO, old_fd[0]);
	dup2(STDOUT_FILENO, old_fd[1]);
	dup2(STDERR_FILENO, old_fd[2]);

    return ret;
}

string LangCompiler::getStdoutFromCommand(string cmd) {

   string data;
   FILE * stream;
   const int max_buffer = 256;
   char buffer[max_buffer];
   cmd.append(" 2>&1");
   const long double sysTime = time(0);
   printf("%lf", sysTime);
 //  const long double sysTimeMS = sysTime*1000;
   stream = popen(cmd.c_str(), "r");
   if (stream) {
   while (!feof(stream))
   {
	   if (fgets(buffer, max_buffer, stream) != NULL)
		   data.append(buffer);
	   if (sysTime - time(0) > 1,200)
		   break;
   }
   pclose(stream);
   }
   return data;
   }
