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
struct FunctionArgument{
	enum ValueTypes {VAL_INT = 0,VAL_FLOAT  = 1,VAL_BOOL = 2,VAL_STRING = 3,VAL_RANGE = 4, VAL_Last = 5};
	int type=0;
	bool isArray = false;
	int size=0;
	vector<string> etalonValue;
	vector<string> value;
	string name;
	string getType(){
			switch(type){
			case VAL_INT:
				return "int";
				break;
			case VAL_FLOAT:
				return "float";
				break;
			case VAL_BOOL:
				return "bool";
				break;
			case VAL_STRING:
				return "string";
				break;
			case VAL_RANGE:
				return "range";
				break;
			}
			return "";
		}
	string generateDeclaration(bool isArgumentEtalonDeclaration=true, bool isForEtalonFunctionDeclaration=true);
};
struct FunctionData{
	enum ReturnValueTypes {RET_VAL_INT = 0,RET_VAL_FLOAT  = 1,RET_VAL_BOOL = 2,RET_VAL_STRING = 3,RET_VAL_RANGE = 4, Last = 5};
	int returnValueType = RET_VAL_INT;
	bool isArray = false;
	bool isRange = false;
	vector<int> checkableArgsIndexes;
	int result_array_size;
	int size=0;
	string functionName;
	vector<string> result;
	vector<string> tests_code;
	vector<FunctionArgument> args;
	string etalon;
	int getResultArraySize()
	{
		return result_array_size;
	}
	string getReturnType(){
		switch(returnValueType){
		case RET_VAL_INT:
			return "int";
			break;
		case RET_VAL_FLOAT:
			return "float";
			break;
		case RET_VAL_BOOL:
			return "bool";
			break;
		case RET_VAL_STRING:
			return "string";
			break;
		case RET_VAL_RANGE:
			return "range";
			break;
		}
		return "";
	}

};
class TaskCodeGenerator {
	FunctionData data;
	string header;
	string footer;

public:
	TaskCodeGenerator(jsonParser &jSON);
	virtual ~TaskCodeGenerator();
	static string generateHeader(FunctionData functionData);
	static string generateFooter(FunctionData functionData);
	static string generateType(int type, int lang);
	static string generateVar(int type, string name, int lang, string value = string());

	static 	string convertStringToType(string argStringValue, int type, int lang);
	static string convertTypeToString(int type, int lang);
	static bool to_bool(std::string const& s);
	static string getStandartInclude(int lang);
	static string generateFunctionProtorype(FunctionData functionData, LangCompiler::compilerFlag = LangCompiler::Flag_CPP, string name = "function", char divider = ',', char space = ' ');
	static FunctionData parseTask(jsonParser &jSON);

	bool updateData(jsonParser &jSON);
	string getHeader();
	string getFooter();

	const string& getEtalon() const ;
};

} /* namespace code */

#endif /* TASKCODEGENERATOR_H_ */
