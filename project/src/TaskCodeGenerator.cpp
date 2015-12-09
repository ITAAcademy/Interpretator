/*
 * TaskCodeGenerator.cpp
 *
 *  Created on: Dec 4, 2015
 *      Author: root
 */

#include "inc/TaskCodeGenerator.h"

namespace code {

TaskCodeGenerator::TaskCodeGenerator(jsonParser &jSON)
{
	updateData(jSON);
}

TaskCodeGenerator::~TaskCodeGenerator()
{
	// TODO Auto-generated destructor stub
}
bool TaskCodeGenerator::updateData(jsonParser &jSON)
{
	data = parseTask(jSON);
	header = generateHeader(data);
	footer = generateFooter(data);
}

string TaskCodeGenerator::getHeader()
{
	return header;
}
string TaskCodeGenerator::getFooter()
{
	return footer;
}
const string& TaskCodeGenerator::getEtalon() const {
	return data.etalon;
}

FunctionData TaskCodeGenerator::parseTask(jsonParser &jSON)
{
	FunctionData functionData;
	string etalon = jSON.getObject("etalon", false).asString();
	l12("etalon");

	Value functionValue = jSON.getObject("function",false);

	functionData.etalon = etalon;
	functionData.returnValueType = functionValue["type"].asInt();
	functionData.functionName = "function_main";//@BAG@

	functionData.isArray = functionValue["results"][0].isArray();
	functionData.size = functionValue["results"][0].size();
	functionData.isRange = jSON.isResultsRange();
	//if (functionValue["checkable_args_indexes"].isArray())
	bool compareEachArgWithEtalonSeparate=functionValue["checkable_args_indexes"][0].isArray();

	for (Value arg_indexes_pares_arr : functionValue["checkable_args_indexes"])
	{
		vector<pair<int,int>> testConditionPares;
		for (Value arg_indexes_pair : arg_indexes_pares_arr ){
			pair<int,int> indexPare=std::make_pair(arg_indexes_pair["first"].asInt(),
					arg_indexes_pair["second"].asInt());
			testConditionPares.push_back(indexPare);
		}
		functionData.checkableArgsIndexes.push_back(testConditionPares);

	}

//functionData.checkableArgsIndexes.push_back(arg_indexes.asInt());

	for (Value arg_compare_mark: functionValue["compare_mark"])
	{
		functionData.compare_marks.push_back((CompareMark)arg_compare_mark.asInt());
	}


	for(JsonValue value:functionValue["results"])
	{
		if (jSON.isResultsRange())
		{
			int val1 = jSON.getRangeFirst();
			int val2 = jSON.getRangeLast();

			string arrString="{";
			int elmCount =0;
			for (int j = val1; j <= val2; j++){
				if (elmCount>0)arrString+=",";
				arrString += to_string(j);

				elmCount++;
			}
			arrString+="}";
			functionData.result.push_back(arrString);  //___opo
			functionData.returnValueType = 0;
			functionData.isArray = true;
		}
		else
			functionData.result.push_back(value.toStyledString());  //___opo
	}

	for(JsonValue value:functionValue["tests_code"])
	{
		functionData.tests_code.push_back(value.asString());
	}


	Value functionArgs = functionValue["args"];
	for (int i=0; i<functionArgs.size(); i++)
	{
		Value argumentValue = functionArgs.get(i,false);
		FunctionArgument functionArgument;
		functionArgument.isArray = argumentValue["value"][0].isArray();
		functionArgument.size = argumentValue["value"][0].size();
		functionArgument.type = argumentValue["type"].asInt();
		functionArgument.name = argumentValue["arg_name"].asString();

		for (Value arg_compare_mark: argumentValue["compare_mark"])
		{
			functionArgument.compare_marks.push_back( (CompareMark) arg_compare_mark.asInt());
		}

		for(JsonValue value:argumentValue["value"])
		{
			functionArgument.value.push_back(value.toStyledString()); //_opo
		}
		for(JsonValue modvalue:argumentValue["etalon_value"])
		{
			functionArgument.etalonValue.push_back(modvalue.toStyledString()); //_opo
		}



		functionData.args.push_back(functionArgument);
	}
	return functionData;
}

string TaskCodeGenerator::generateFunctionProtorype(FunctionData functionData, LangCompiler::compilerFlag, string name , char divider, char space)
{
	string functionStr = generateType(functionData.returnValueType, 0);
	if (functionData.isArray)
		functionStr += "* ";

	functionStr	+= name + "(";

	int argCount = 0;
	int array_cnt = 0;

	for(FunctionArgument arg : functionData.args){
		if (argCount>0)
			functionStr += divider;
		string type = generateType(arg.type, 0);// 0 == C++
		functionStr += type + space;


		if ( arg.isArray )
		{
			functionStr += "*" + arg.name;
		}
		else
		{
			functionStr += "&" + arg.name;
		}
		argCount++;
	}
	//close prototype and open body of function
	functionStr += ")\n";
	return functionStr;
}

string TaskCodeGenerator::generateHeader(FunctionData functionData){

	string headerStr = getStandartInclude(LangCompiler::Flag_CPP) + "\n";
	headerStr += generateFunctionProtorype(functionData, LangCompiler::Flag_CPP, "function_etalon"); //create prototype for etalon function
	headerStr += "{\n" + functionData.etalon + "return NULL;\n}\n"; // add etalon function
	headerStr += generateFunctionProtorype(functionData, LangCompiler::Flag_CPP, functionData.functionName) + "{\n";
	/*l12("Yura: 2202:");
	l12(headerStr);*/
	return headerStr;
}

string TaskCodeGenerator::generateFooter(FunctionData functionData){

	vector<FunctionArgument> variables;
	string footerBody = "return 0;\n}\n";//Close function body

	string space=" ";
	char divider=',';
	string results_arguments_comparing_after_main_func = "bool results_arguments_comparing_after_main_func = true";
	string modifiedArgComparsion;
	//C++//need out this code
	string arrCompFuncStr="template<typename T,int size>\n\
	bool compareArrs(T arr1[size],T arr2[size])\n\
		{\n\
		for (int i=0;i<size;i++)\n\
		{\n\
		//if (strcmp(typeid(T).name(), \"f\") == 0)\n\
		//{\n	\
		//if (fabs(arr1[i]) - arr2[i] ) > 0.009) \n\
		//	return false;\n\
		//}\n \
		//else	\n\
			if (arr1[i] != arr2[i])\n\
				return false;\n\
			}\n\
			return true;\n\
	}\n";
	footerBody+=arrCompFuncStr;
	footerBody+="int main()\n\
			{\n";

	footerBody += functionData.getReturnType() + " result_etalon";
	if (functionData.isArray )
	{
		footerBody  += "[" + to_string(functionData.size) + "]";
	}
	footerBody += ";\n";
	/*
	 *
	 *
	 */
	footerBody += functionData.getReturnType();
	if (functionData.isArray )
	{
		footerBody  += " *";
	}
	FunctionArgument resultVar;
	resultVar.name="result";
	resultVar.isArray=functionData.isArray;
	resultVar.size=functionData.size;
	resultVar.type=functionData.isArray;

	variables.push_back(resultVar);
	resultVar.name+=ETALON_ENDING;
	variables.push_back(resultVar);
	resultVar.name="result"+ string(ETALON_FOR_FUNCTION_ENDING);
	variables.push_back(resultVar);

	footerBody += " result;\n";

	footerBody += functionData.getReturnType();
	if (functionData.isArray )
	{
		footerBody  += " *";
	}
	footerBody += " result" + string(ETALON_FOR_FUNCTION_ENDING) + ";\n";

	/*
	 *
	 *
	 *
	 */

	string correctArgumentsConditionName = "variablesCorrect";
	string argumentsEqualToEtalonConditionName = "variablesCorrectByEtalon";

	for(FunctionArgument arg : functionData.args)
	{
		string argumentDeclaration="",argumentEtalonDeclaration="",argumentForEtalonFunctionDeclaration="";

		FunctionArgument etalonArg = arg;
		etalonArg.name+=ETALON_ENDING;

		FunctionArgument etalonForFunctionArg = arg;
		etalonForFunctionArg.name +=string(ETALON_FOR_FUNCTION_ENDING);
		variables.push_back(arg);
		variables.push_back(etalonArg);
		variables.push_back(etalonForFunctionArg);


		argumentDeclaration = generateType(arg.type, 0) + " " +  arg.name;
		argumentEtalonDeclaration =  generateType(arg.type,0) + " " + arg.name + ETALON_ENDING;
		argumentForEtalonFunctionDeclaration =  generateType(arg.type,0) + " " + arg.name + string(ETALON_FOR_FUNCTION_ENDING);
		//footerBody +=
		if ( arg.isArray )
		{
			argumentDeclaration  += "[" + to_string(arg.size) + "]";
			argumentEtalonDeclaration += "[" + to_string(arg.size) + "]";
			argumentForEtalonFunctionDeclaration += "[" + to_string(arg.size) + "]";
			/*
			 * @NEED REFACTOR@
			 *
			 */
		}
		argumentDeclaration += ";\n";
		argumentEtalonDeclaration += ";\n";
		argumentForEtalonFunctionDeclaration+= ";\n";

		//add etalon variables
		footerBody += argumentDeclaration + argumentEtalonDeclaration + argumentForEtalonFunctionDeclaration;


	}
	footerBody += "bool isTrue;\n";//moved out from cicle to fix variable duplicates
	string conditionsVariableDeclaration = "bool " +argumentsEqualToEtalonConditionName+","
			+correctArgumentsConditionName+";\n";
	footerBody+= conditionsVariableDeclaration;



	string argsString;
	string etalongArgsString;

	bool is_float = (functionData.returnValueType == ValueTypes::VAL_FLOAT);
	for(int i = 0; i < functionData.result.size(); i++)
	{

		if ( !functionData.isArray)
		{
			footerBody += /*"result" + string(ETALON_FOR_FUNCTION_ENDING) + " = " + */"result_etalon = " + functionData.result[i] + ";\n";
		}
		else
		{
			//footerBody += arg.name +"[" + to_string(i) + "] = " + arg.value[i] + ";\n";
			Reader reader;
			JsonValue values_u;
			JsonValue etalons_values_u;
			reader.parse(functionData.result[i], values_u);


			for (int h = 0; h < values_u.size(); h++)
			{
				footerBody += /*"result" + string(ETALON_FOR_FUNCTION_ENDING) + "[" + to_string(rez_size) + "] = " +*/ "result[" + to_string(h) + "] = ";
				if (is_float)
					footerBody += " (float) ";
				footerBody += values_u[h].toStyledString() + ";\n";
			}


		}
		/*if (functionData.isRange )//@WHAT@
		{

		}
		else*/

		string argumentDefinition;
		string argumentEtalonDefinition;
		string argForMainFunction;
		string argForEtalonFunction;

		int argCount = 0;
		string variablesCorrect = ""+correctArgumentsConditionName+" = ";
		string variablesCorrectByEtalonPrefix = ""+argumentsEqualToEtalonConditionName+" = ";
		string variablesCorrectByEtalonEnding = "";

		vector<CompareMark> compare_marks = functionData.compare_marks;

		vector<vector<pair<int,int>>> checkableArgsIndexes = functionData.checkableArgsIndexes;

		int checkableArgsCount = 0;
		int currentArgumentIndex=-1;
		for(FunctionArgument arg : functionData.args) //8787
		{
			currentArgumentIndex++;
			vector<string> args_results;
			vector<string> args_results_must_be_after_main_func;
			if ( !arg.isArray )
			{
				/*
				 int indexOfTest;
				if (functionData.isCompareEachArgWithEtalonSeparate)indexOfTest=i;
				else indexOfTest=0;
				if (std::find(checkableArgsIndexes[indexOfTest].begin(),checkableArgsIndexes[indexOfTest].end(),currentArgumentIndex)!=checkableArgsIndexes[indexOfTest].end())
				{
					if (checkableArgsCount>0)variablesCorrectByEtalonEnding+=" && ";
					//variablesCorrectByEtalonEnding += arg.name +  "=="	+ arg.name + ETALON_FOR_FUNCTION_ENDING;
					variablesCorrectByEtalonEnding += getCompareString(arg.name,(ValueTypes) arg.type, arg.name + string(ETALON_FOR_FUNCTION_ENDING),(ValueTypes) arg.type, CompareMark::Equial);
					checkableArgsCount++;
				}
				 */
				string currentArgDef = arg.name + string(ETALON_FOR_FUNCTION_ENDING) + " = " + arg.name + " = " + arg.value[i] + ";\n";
				string currentArgEtalonDef = arg.name + string(ETALON_ENDING) + string(" = ") +
						arg.etalonValue[i] + string(";\n"); //etalon value for argument
				argumentDefinition += currentArgDef;
				argumentEtalonDefinition += currentArgEtalonDef;

				//variablesCorrect += "(" + arg.name + " == "	+ arg.name + string(ETALON_ENDING) + ")";
				variablesCorrect += getCompareString(arg.name,(ValueTypes) arg.type, arg.name + string(ETALON_ENDING), (ValueTypes)arg.type, CompareMark::Equial);

				//variablesCorrect += "("+arg.name+"=="+arg.name + string(ETALON_FOR_FUNCTION_ENDING)+")";
				//variablesCorrectByEtalonEnding += 1;

				if (argCount != functionData.args.size() - 1 )
					variablesCorrect += " && ";
				//else
				//variablesCorrect+=";\n";
			}
			else
			{
				/*int indexOfTest;
					if (functionData.isCompareEachArgWithEtalonSeparate)indexOfTest=i;
					else indexOfTest=0;*/

				/*if (std::find(checkableArgsIndexes[indexOfTest].begin(),checkableArgsIndexes[indexOfTest].end(),currentArgumentIndex)!=
						checkableArgsIndexes[indexOfTest].end())
				{
					if (checkableArgsCount>0)variablesCorrectByEtalonEnding += " && ";
					/*variablesCorrectByEtalonEnding+="compareArrs<"+arg.getType()+","+
							std::to_string(arg.size)+">("+arg.name+","+arg.name+ETALON_FOR_FUNCTION_ENDING+")";*/
					variablesCorrect += getArrayCompareString(arg.name,arg.size, (ValueTypes) arg.type, arg.name + string(ETALON_FOR_FUNCTION_ENDING),
							arg.size, (ValueTypes) arg.type, CompareMark::Equial);

					checkableArgsCount++;


				}*/
				//footerBody += arg.name +"[" + to_string(i) + "] = " + arg.value[i] + ";\n";
				Reader reader;
				JsonValue values_u;
				JsonValue etalons_values_u;
				reader.parse(arg.value[i], values_u);
				reader.parse(arg.etalonValue[i], etalons_values_u);

				for(int i = 0; i < values_u.size(); i++)
				{
					argumentDefinition += arg.name + string(ETALON_FOR_FUNCTION_ENDING) + "[" + to_string(i) + "] = " + arg.name +"[" + to_string(i) + "] = " + values_u[i].toStyledString() + ";\n";
					argumentEtalonDefinition += arg.name + ETALON_ENDING + "[" + to_string(i) + "] = " + etalons_values_u[i].toStyledString() + ";\n";
				}

				/*variablesCorrect+= "compareArrs<"+arg.getType()+","+
						std::to_string(arg.size) + ">(" + arg.name + "," + arg.name + ETALON_ENDING + ")";*/
				variablesCorrect += getArrayCompareString(arg.name,arg.size, (ValueTypes) arg.type, arg.name + string(ETALON_ENDING),
						 arg.size, (ValueTypes) arg.type, CompareMark::Equial);

				if ( argCount != functionData.args.size() - 1 )
					variablesCorrect+=" && ";
			}


			if(argCount > 0)
			{
				argForMainFunction += divider;
				argForEtalonFunction += divider;
			}

			string argStringValue = arg.value[i];
			string etalonStringValue = arg.etalonValue[i];
			string arrName = arg.name;//    "array"+std::to_string(arraysCount);

			string etalonArrName = arrName + ETALON_FOR_FUNCTION_ENDING;
			argForMainFunction += arrName;
			argForEtalonFunction += etalonArrName;

			argCount++;
			//for (int k=0;k<variables.size();k++)

		}
		if (i<checkableArgsIndexes.size())
		{
			for (int l = 0; l < checkableArgsIndexes[i].size();l++)
			{
				//if (std::find(checkableArgsIndexes[indexOfTest].begin(),checkableArgsIndexes[indexOfTest].end(),
				int firstCheckableVariableIndex=checkableArgsIndexes[i][l].first;
				int secondCheckableVariableIndex=checkableArgsIndexes[i][l].second;
				FunctionArgument *firstGlobalVariable = &variables[firstCheckableVariableIndex];
				FunctionArgument *secondGlobalVariable = &variables[secondCheckableVariableIndex];

				if (checkableArgsCount>0)variablesCorrectByEtalonEnding+=" && ";
				if (firstGlobalVariable->isArray)
				{
					//false result of comparsion because of inconsistency of types or different sizes
					if (!secondGlobalVariable->isArray || secondGlobalVariable->size !=firstGlobalVariable->size
							|| secondGlobalVariable->type!=firstGlobalVariable->type)
						variablesCorrectByEtalonEnding += "false";
					//
					else
						variablesCorrectByEtalonEnding+="compareArrs<"+firstGlobalVariable->getType()+","+
						std::to_string(firstGlobalVariable->size)+">("+firstGlobalVariable->name+
						","+secondGlobalVariable->name+")";
				}
				else
				{
					if (secondGlobalVariable->type!=firstGlobalVariable->type)
						variablesCorrectByEtalonEnding += "false";
					else
						variablesCorrectByEtalonEnding+=firstGlobalVariable->name + "=="+secondGlobalVariable->name;
				}
				checkableArgsCount++;

			}
		}

		if (variablesCorrectByEtalonEnding.length()>1)//if comparsion conditions excists (our_func arg[i] == etalon_func arg[i])
			variablesCorrectByEtalonEnding += ";";
		else
			variablesCorrectByEtalonEnding+="true;";//condition try if comparsion need no.

		argsString += argumentDefinition;
		argsString += argumentEtalonDefinition;

		argsString += variablesCorrect+";\n";
		argsString += " result" + string(ETALON_FOR_FUNCTION_ENDING) +  " = function_etalon(" + argForEtalonFunction +  ");\n";
		argsString += " result = " + functionData.functionName + "(" + argForMainFunction +  ");\n";

		argsString += "isTrue = true;\n";
		argsString += variablesCorrectByEtalonPrefix+variablesCorrectByEtalonEnding;
		argsString += functionData.tests_code[i] + "\n";

		if (functionData.isArray )
		{
			//string arrType = functionData.getReturnType();
			int arrType = functionData.returnValueType;
			/*argsString += "if (compareArrs<"+arrType+","+
					std::to_string(functionData.size)+">(result_etalon, result)";*/
			argsString += "if ("  + getArrayCompareString(string("result_etalon") ,functionData.size, (ValueTypes) arrType, string("result") ,
					functionData.size, (ValueTypes) arrType, CompareMark::Equial);


		}
		else
			argsString += "if ( result_etalon == result";//open function call body;


		//if (functionData.isArray)//@WHAT@
		{
			argsString+=" && variablesCorrect && isTrue)\n";
			//TODO
		}

		argsString += "std::cout << \" @" + to_string(i) + "@\";\n";
		argsString += "else\n";
		argsString += "std::cout << \" @" + to_string(i) + "!@\";\n";


	}
	footerBody+=argsString;
	footerBody += "\n}";
	//C++

	l12("Yura:: 00001");
	l12(footerBody);
	return footerBody;
}

string TaskCodeGenerator::generateType(int type, int lang)
{
	string result;
	switch(type){
	case FunctionData::RET_VAL_BOOL:
		result += "bool";
		break;
	case FunctionData::RET_VAL_FLOAT:
		result += "float";
		break;
	case FunctionData::RET_VAL_INT:
		result += "int";
		break;
	case FunctionData::RET_VAL_STRING:
		result += "string";
		break;
	}
	result += " ";
	return result;
}

string TaskCodeGenerator::generateVar(int type, string name, int lang, string value)
{
	return generateType(type, lang) + name + " ";
}

string TaskCodeGenerator::getStandartInclude(int lang)
{
	string include;
	switch(lang)
	{
	case LangCompiler::Flag_CPP:{
		include = "#include <iostream>\n\
		#include <cstdlib>\n\
		#include <algorithm>\n using namespace std;\n\
		#include <cxxabi.h>\n\
		#include <cmath>\n\
		#include <stdio.h>\n\
		#include <string.h>";

	}
	case LangCompiler::Flag_Java:{
		//...
	}
	}
	return include + "\n";

}

string TaskCodeGenerator::convertStringToType(string argStringValue, int type, int lang)
{
	string result;
	switch(type){
	case FunctionData::RET_VAL_BOOL:
		result += to_bool(argStringValue);
		break;
	case FunctionData::RET_VAL_FLOAT:
		result += argStringValue.c_str();
		break;
	case FunctionData::RET_VAL_INT:
		result += argStringValue.c_str();
		break;
	case FunctionData::RET_VAL_STRING:
		result += argStringValue;
		break;
	}
	return result;
}

string TaskCodeGenerator::convertTypeToString(int type, int lang)
{

}
bool TaskCodeGenerator::to_bool(std::string const& s) {
	return s != "0";
}
} /* namespace code */
