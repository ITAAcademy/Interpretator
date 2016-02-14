#ifndef CLangCompiler_H_
#define CLangCompiler_H_

#include "main.h"
#include "includes.h"
#include <sys/types.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "logfile.h"
#include <string>
#include <iostream>
#include <cstdio>
#include <memory>
#include <string>
#include <iostream>
#include <unistd.h>

using namespace std;
//using namespace std::chrono;

class LangCompiler{
	int thID;
	long double timeOut;
	string result;
	string warning_err;

#define TIME_OUT_NULL 0;

public:
	enum compilerFlag{ Flag_CPP = 0, Flag_Java = 1, Flag_JS = 2, Flag_PHP = 3, Flag_CS = 4 };// future type of compiler

	LangCompiler(int ID);

	~LangCompiler();


	static bool beautyErrorOutput(string &warning,compilerFlag flags );
	/*
	 * Compile __ if all ok return app result else return CLang compiler error
	 *
	 *  show == include in textEdit
	 *
	 */
	string compile(string code, bool show, compilerFlag flags = Flag_Java);

	long double getTimeOut()const;

	void setTimeOut(long double timeOut) ;

	const string& getResult() const ;

	int getThId() const ;

	const string& getWarningErr() const;
	static compilerFlag convertFromName(string name);

private:
	/*
	 * first version of get command function // more bugs ** not actual
	 */
	char* getSystemOutput(char* cmd);
	/*
	 * second version of get command function // more stable
	 * cmd === input string with command
	 */
	string getStdoutFromCommand(string cmd, int mTimeOut = 0, long double *executionTime = NULL);
	/*
	 * generation code file from head & footer
	 */
	bool generetionSample(string code, compilerFlag flags);
	/*
	 *  file operation functions
	 */
	bool fileExist( string name );
	bool fileRemove( string name );
};


#endif /* CLangCompiler_H_ */
