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
	int type=0;
	int isArray = false;
	int size=0;
	//map<int,string> etalonValue;
	vector<string> etalonValue;
	vector<vector<string>> etalon_value_array;
	vector<string> value;
	vector<vector<string>> value_array;
	//vector<CompareMark> compare_marks;
	string name;
	/*string getTypeInt(int lang );
	string getTypeFloat(int lang );
	string getTypeString(int lang );
	string getTypeBool(int lang );
	string getType(int lang );*/
	string generateDefinition(bool return_or_param, int lang );
	static string generateDefinition(bool return_or_param, int lang , string name, int type);
	static string generateType(int type, int arrayType, int lang, bool return_or_param = false);
	static string getName(string name, int lang);
	string getName(int lang);
};
struct FunctionData{
	//enum ReturnValueTypes {RET_VAL_INT = 0,RET_VAL_FLOAT  = 1,RET_VAL_BOOL = 2,RET_VAL_STRING = 3,RET_VAL_RANGE = 4, Last = 5};
	enum ArrType {NOT_ARRAY = 0, ARRAY = 1};
	int returnValueType = ValueTypes::VAL_INT;
	int isArray = false;
	bool isRange = false;
	vector<vector<pair<int,int>>> checkableArgsIndexes;
	int result_array_size;
	int unit_tests_nums = 0;
	string functionName;
	vector<string> result;
	vector<vector<string>> result_array;
	vector<string> tests_code;
	vector<CompareMark> compare_marks;
	vector<FunctionArgument> args;
	string etalon;
	int lang;
	int thread_id;
	int getResultArraySize()
	{
		return result_array_size;
	}
	string getReturnType()
	{
		switch(returnValueType){
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
		case VAL_CHAR:
			return "char";
			break;
		case VAL_RANGE:
			return "range";
			break;
		}
		return "";
	}

};

enum ERR{
	COMPARE_VALUE_FROM_TH = 1114
};
class TaskCodeGenerator {
	FunctionData data;
	string header;
	string footer;
	static int status;
	/*string argForMainFunction = "";
	string argForEtalonFunction = "";*/
public:
	static string convertAnyToString(string name1,  ValueTypes type1, int lang);
	static string getStrToCompareTypes(string name1,  string name2,   int lang);
	static string generateDefaultReturnValue(int lang, int returnValueType, int isArray);
	static string getArrayCompareString(string name1, int arr1_size, ValueTypes type1,string name2, int arr2_size, ValueTypes type2, CompareMark mark, int lang);
	static string getCompareString(string name1,  ValueTypes type1,string name2, ValueTypes type2, CompareMark mark, int lang);
	TaskCodeGenerator(jsonParser &jSON, int thread_id);
	virtual ~TaskCodeGenerator();
	static bool generateVariables(string &output, FunctionData functionData, vector<FunctionArgument> &variables);
	static string generateHeader(FunctionData functionData);
	/*static*/ string generateFooter(FunctionData functionData);
	static string generateVar(int type, string name, int lang, string value = string());
	static string generateInputParametersString(FunctionData functionData);

	static 	string convertStringToType(string argStringValue, int type, int lang);
	static string convertTypeToString(int type, int lang);
	static bool to_bool(std::string const& s);
	static string getStandartInclude(int lang);
	static string generateFunctionProtorype(FunctionData functionData,  string name = "function", char divider = ',', char space = ' ',  string modifiers = "");
	static FunctionData parseTask(jsonParser &jSON);

	bool updateData(jsonParser &jSON, int thread_id);
	string getHeader();
	string getFooter();
	static string addBracketsToStr(string value);

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
