#ifndef CLangCompiler_H_
#define CLangCompiler_H_

#include "includes.h"
#include <sys/types.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
using namespace std;

class LangCompiler{
public:
	LangCompiler();
	~LangCompiler();
	string compile(char *code, bool show);
private:
	char* GetSystemOutput(char* cmd);
	string GetStdoutFromCommand(string cmd);
	bool generetionSample(char *code);
};


#endif /* CLangCompiler_H_ */
