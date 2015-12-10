/*
 * TaskCodeGenerator.h
 *
 *  Created on: Dec 4, 2015
 *      Author: root
 */

#ifndef TASKCODEGENERATOR_H_
#define TASKCODEGENERATOR_H_

#define ETALON_ENDING "_etalon"
#define ETALON_FOR_FUNCTION_ENDING "_for_etalon"

#include "includes.h"
#include "fcgio.h"
#include <sstream>
#include "cLang.h"
#include "codeclear.h"
#include "errorresponder.h"
#include "logfile.h"
#include "jsonParser.h"
#include "ctpl_stl.h"
#include <iostream>
#include <string>
#include <regex>
#include <algorithm>

namespace code {

enum ERR{
	COMPARE_VALUE_FROM_TH = 1114
};
class TaskCodeGenerator {
	FunctionData data;
	string header;
	string footer;
	static int status;

public:
	TaskCodeGenerator(jsonParser &jSON, int thread_id);
	virtual ~TaskCodeGenerator();
	static bool generateVariables(string &output, FunctionData functionData, vector<FunctionArgument> &variables);
	static string generateHeader(FunctionData functionData);
	static string generateFooter(FunctionData functionData);
	static string generateType(int type, int arrayType, int lang);
	static string generateVar(int type, string name, int lang, string value = string());

	static 	string convertStringToType(string argStringValue, int type, int lang);
	static string convertTypeToString(int type, int lang);
	static bool to_bool(std::string const& s);
	static string getStandartInclude(int lang);
	static string generateFunctionProtorype(FunctionData functionData,  string name = "function", char divider = ',', char space = ' ',  string modifiers = "");
	static FunctionData parseTask(jsonParser &jSON);

	bool updateData(jsonParser &jSON, int thread_id);
	string getHeader();
	string getFooter();

	const string& getEtalon() const ;

	/*
	 * return 0 if all ok, else return ERR code
	 */
	static int getStatus() {
		return status;
	}
};

} /* namespace code */

#endif /* TASKCODEGENERATOR_H_ */
