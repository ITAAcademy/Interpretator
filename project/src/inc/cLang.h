#ifndef CLangCompiler_H_
#define CLangCompiler_H_

#include "includes.h"
#include <sys/types.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "logfile.h"
using namespace std;
//using namespace std::chrono;

class LangCompiler{
	int thID;
	long double timeOut;
	string result;
	string warning_err;

public:
	enum compilerFlag{ Flag_TYPE1, Flag_TYPE2, Flag_TYPE3 };// future type of compiler

	LangCompiler(int ID);

	~LangCompiler();
	/*
	 * Compile __ if all ok return app result else return CLang compiler error
	 *
	 *  show == include in textEdit
	 *
	 */
	string compile(string code, bool show, compilerFlag flags = Flag_TYPE1);

	long double getTimeOut()const;

	void setTimeOut(long double timeOut) ;

	const string& getResult() const ;

	int getThId() const ;

	const string& getWarningErr() const;

private:
	/*
	 * first version of get command function // more bugs ** not actual
	 */
	char* getSystemOutput(char* cmd);
	/*
	 * second version of get command function // more stable
	 * cmd === input string with command
	 */
	string getStdoutFromCommand(string cmd);
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
