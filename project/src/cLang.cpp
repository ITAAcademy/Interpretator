#include "inc/cLang.h"
#include "inc/SQLconnector.h"

LangCompiler::LangCompiler(int ID){
	thID = ID;
	timeOut = 2000/1000;
}

LangCompiler::~LangCompiler(){

}

string LangCompiler::compile(char *code, bool show, compilerFlag flags)
{
	string res = "\0";
	if(!generetionSample(code, flags))
	{
		logfile::addLog("Canot open file with generation source code, maybe permission denied	");
		return "Canot open file with generation source code, maybe permission denied	";
	}
	cout.flush();
	string code_file_name = "prog" + to_string(thID) + ".out";
	string build_str = "cd src; clang++ -Wall -stdlib=libc++ code" + to_string(thID) + ".cpp -o prog" + to_string(thID) + ".out";
	string run_str = "cd src; ./prog" + to_string(thID) + ".out;  rm prog" + to_string(thID) + ".out";
	/*in.append("cd /var/www/fcgi/srs/; clang++ -Wall -stdlib=libc++ code$1.cpp -o prog$1.out; if [ -f /var/www/fcgi/srs/prog$1.out ]; then  ./prog$1.out;  rm prog$1.out; fi");
	in.append("cd /var/www/fcgi/srs/;");
	in.append("clang++ -Wall -stdlib=libc++ code" + to_string(thID) + ".cpp -o prog" + to_string(thID) + ".out;");
	in.append("if [ -f /var/www/fcgi/srs/" + code_file_name + " ]; then ./" + code_file_name) + ";";
	in.append("rm prog.out;");
	in.append("fi;");*/

	string kompill = getStdoutFromCommand(build_str);
	if(fileExist("srs/" + code_file_name))
		kompill.append(getStdoutFromCommand(run_str));
	if(show)
	{
		//res.append(in);
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
	cout.flush();
	if(flags == Flag_TYPE1)
	{
		ofstream file;
		char str[50];
		sprintf(str, "src/code%d.cpp", thID);
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
	   if (sysTime - time(0) > timeOut)
		   break;
   }
   pclose(stream);
   }
   return data;
   }

long double LangCompiler::getTimeOut() const{
	return timeOut*1000;
}

void LangCompiler::setTimeOut(long double timeOut) {
	this->timeOut = timeOut/1000;
}

bool LangCompiler::fileExist( string name )
{
    return ifstream(name);
}

bool LangCompiler::fileRemove ( string name )
{
	remove(name.c_str() );
}
