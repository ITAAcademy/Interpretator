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
	vector<int> indexes;

	for (Value arg_indexes : functionValue["checkable_args_indexes"])
	{
		if (compareEachArgWithEtalonSeparate)
		{
			vector<int> indexes;
			//compareEachArgWithEtalonSeparate=true;
			for (Value index : arg_indexes)
			indexes.push_back(index.asInt());
			functionData.checkableArgsIndexes.push_back(indexes);

		}
		else
			indexes.push_back(arg_indexes.asInt());
	}
	if (compareEachArgWithEtalonSeparate)
	{
		functionData.isCompareEachArgWithEtalonSeparate=true;
	}
	else
	{
		functionData.checkableArgsIndexes.push_back(indexes);
	}
//functionData.checkableArgsIndexes.push_back(arg_indexes.asInt());
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
			if(functionData.isArray == false)///////////////@BAG@
			{
				functionData.result.push_back(value.toStyledString());

				/*switch(type_rezult)
				{
					case FunctionData::RET_VAL_BOOL:
						functionData.result.push_back(value.asBool());
											break;
					case FunctionData::RET_VAL_FLOAT:
						functionData.result.push_back(value.asFloat());
											break;
					case FunctionData::RET_VAL_INT:
						functionData.result.push_back(value.asInt());
											break;
					case FunctionData::RET_VAL_STRING:
					functionData.result.push_back(value.asString());
					break;

					l12("qwe");*/
			}
			else
			{
				string arrString="{";
				int elmCount =0;
				for (int j = 0; j < value.size(); j++){
					if (elmCount>0)arrString+=",";
					arrString+=value[j].toStyledString();

					elmCount++;
				}
				arrString+="}";
				functionData.result.push_back(arrString);  //___opo
			}
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

		for(JsonValue value:argumentValue["value"])
		{
			if(functionArgument.isArray == false)
			{
				functionArgument.value.push_back(value.toStyledString());
				l12("qwe2");
			}
			else{
				string arrString="{";
				int elmCount =0;
				for (int j = 0; j < value.size(); j++){
					if (elmCount>0)arrString+=",";
					arrString+=value[j].toStyledString();

					elmCount++;
				}
				arrString+="}";
				functionArgument.value.push_back(arrString); //_opo
			}
		}
		for(JsonValue modvalue:argumentValue["etalon_value"])
		{
			if(functionArgument.isArray == false)
				functionArgument.etalonValue.push_back(modvalue.toStyledString());
			else{
				string arrString="{";
				int elmCount =0;
				for (int j = 0; j < modvalue.size(); j++){
					if (elmCount>0)arrString+=",";
					arrString+=modvalue[j].toStyledString();

					elmCount++;
				}
				arrString+="}";
				functionArgument.etalonValue.push_back(arrString); //_opo
			}
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
	string footerBody = "return 0;\n}\n";//Close function body

	string space=" ";
	char divider=',';
	string results_arguments_comparing_after_main_func = "bool results_arguments_comparing_after_main_func = true";
	string modifiedArgComparsion;
	//C++
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

	bool is_float = (functionData.returnValueType == FunctionArgument::VAL_FLOAT);
	for(int i = 0; i < functionData.result.size(); i++)
	{

		if ( !functionData.isArray)
		{
			footerBody += /*"result" + string(ETALON_FOR_FUNCTION_ENDING) + " = " + */"result_etalon = " + functionData.result[i] + ";\n";
		}
		else
		{
			//footerBody += arg.name +"[" + to_string(i) + "] = " + arg.value[i] + ";\n";
			string values_u = functionData.result[i].substr(1, functionData.result[i].size() - 2 );
			string indiv_value = "";
			//values_u[0] = " ";
			int v_size = values_u.size();
			//values_u[v_size - 1] = " ";
			int rez_size = 0;
			for (int h = 0; h < v_size; h++)
			{
				if (values_u[h] != ',')
					indiv_value += values_u[h];
				else
				{
					footerBody += /*"result" + string(ETALON_FOR_FUNCTION_ENDING) + "[" + to_string(rez_size) + "] = " +*/ "result[" + to_string(rez_size) + "] = ";
					if (is_float)
						footerBody += " (float) ";
					footerBody += indiv_value + ";\n";
					indiv_value = "";
					rez_size++;
				}
			}
			if (indiv_value.size() != 0)
			{
				footerBody += /*"result" + string(ETALON_FOR_FUNCTION_ENDING) + "[" + to_string(rez_size) + "] = " + */ "result[" + to_string(rez_size) + "] = ";
				if (is_float)
					footerBody += " (float) ";
				footerBody += indiv_value + ";\n";
			}
			//for (int u=0; u < arg.value[i].size(); u++)		footerBody += arg.name +"[" + to_string(u) + "] = " + arg.value[i] + ";\n";
		}
		/*if (functionData.isRange )
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
		vector<vector<int>> checkableArgsIndexes = functionData.checkableArgsIndexes;
		int checkableArgsCount = 0;
		int currentArgumentIndex=-1;
		for(FunctionArgument arg : functionData.args) //8787
		{
			currentArgumentIndex++;
			vector<string> args_results;
				vector<string> args_results_must_be_after_main_func;
			if ( !arg.isArray )
			{
				int indexOfTest;
				if (functionData.isCompareEachArgWithEtalonSeparate)indexOfTest=i;
				else indexOfTest=0;
				if (std::find(checkableArgsIndexes[indexOfTest].begin(),checkableArgsIndexes[indexOfTest].end(),currentArgumentIndex)!=checkableArgsIndexes[indexOfTest].end())
				{
					if (checkableArgsCount>0)variablesCorrectByEtalonEnding+=" && ";
					variablesCorrectByEtalonEnding+=arg.name + "=="+arg.name+ETALON_FOR_FUNCTION_ENDING;
					checkableArgsCount++;
				}
				string currentArgDef = arg.name + string(ETALON_FOR_FUNCTION_ENDING) + " = " + arg.name + " = " + arg.value[i] + ";\n";
				string currentArgEtalonDef = arg.name + string(ETALON_ENDING) + string(" = ") +
						arg.etalonValue[i] + string(";\n"); //etalon value for argument
				argumentDefinition += currentArgDef;
				argumentEtalonDefinition += currentArgEtalonDef;

				variablesCorrect += "(" + arg.name + " == " + arg.name + string(ETALON_ENDING) + ")";
				//variablesCorrect += "("+arg.name+"=="+arg.name + string(ETALON_FOR_FUNCTION_ENDING)+")";
				//variablesCorrectByEtalonEnding += 1;

				if (argCount != functionData.args.size() - 1 )
					variablesCorrect += " && ";
				//else
					//variablesCorrect+=";\n";
			}
			else
			{
					int indexOfTest;
					if (functionData.isCompareEachArgWithEtalonSeparate)indexOfTest=i;
					else indexOfTest=0;

				if (std::find(checkableArgsIndexes[indexOfTest].begin(),checkableArgsIndexes[indexOfTest].end(),currentArgumentIndex)!=
						checkableArgsIndexes[indexOfTest].end())
				{
					if (checkableArgsCount>0)variablesCorrectByEtalonEnding+=" && ";
					variablesCorrectByEtalonEnding+="compareArrs<"+arg.getType()+","+
							std::to_string(arg.size)+">("+arg.name+","+arg.name+ETALON_FOR_FUNCTION_ENDING+")";
					checkableArgsCount++;


				}
				//footerBody += arg.name +"[" + to_string(i) + "] = " + arg.value[i] + ";\n";
				string values_u = arg.value[i].substr(1, arg.value[i].size() - 2 );
				string etalons_values_u = arg.etalonValue[i].substr(1, arg.etalonValue[i].size() - 2 );
				string indiv_value = "";
				string etal_value = "";
				//values_u[0] = " ";
				int v_size = values_u.size();
				int v_etalons_size = etalons_values_u.size();
				//values_u[v_size - 1] = " ";
				int arg_size = 0;
				int etalon_arg_size = 0;
				for (int h = 0; h < v_size; h++)
				{
					if (values_u[h] != ',')
						indiv_value += values_u[h];
					else
					{
						argumentDefinition += arg.name + string(ETALON_FOR_FUNCTION_ENDING) + "[" + to_string(arg_size) + "] = " + arg.name +"[" + to_string(arg_size) + "] = " + indiv_value + ";\n";
						indiv_value = "";
						arg_size++;
					}
				}
				for (int h = 0; h < v_etalons_size; h++)
				{
					if (etalons_values_u[h] != ',')
						etal_value += values_u[h];
					else
					{
						argumentEtalonDefinition += arg.name + ETALON_ENDING + "[" + to_string(etalon_arg_size) + "] = " + etal_value + ";\n";
						etal_value = "";
						etalon_arg_size++;
					}
				}
				variablesCorrect+= "compareArrs<"+arg.getType()+","+
						std::to_string(arg.size) + ">(" + arg.name + "," + arg.name + ETALON_ENDING + ")";
				if ( argCount != functionData.args.size() - 1 )
					variablesCorrect+=" && ";

				//	else variablesCorrect+=");";

				if (indiv_value.size() != 0)
				{
					argumentDefinition += arg.name +"[" + to_string(arg_size) + "] = " + indiv_value + ";\n";
				}
				if (etal_value.size() != 0){
					argumentEtalonDefinition  += arg.name + ETALON_ENDING +"[" + to_string(etalon_arg_size) + "] = " + etal_value + ";\n";
				}

				//for (int u=0; u < arg.value[i].size(); u++)		footerBody += arg.name +"[" + to_string(u) + "] = " + arg.value[i] + ";\n";
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
			switch(arg.type){
			case FunctionData::RET_VAL_BOOL:
				argForMainFunction += arrName;
				argForEtalonFunction += etalonArrName;

				break;
			case FunctionData::RET_VAL_FLOAT:
				argForMainFunction += arrName;
				argForEtalonFunction += etalonArrName;
				break;
			case FunctionData::RET_VAL_INT:
				argForMainFunction += arrName;
				argForEtalonFunction += etalonArrName;
				break;
			case FunctionData::RET_VAL_STRING:
				argForMainFunction += arrName;
				argForEtalonFunction += etalonArrName;
				break;

				/*case FunctionData::RET_VAL_RANGE
						if (arg.isArray){
							arrType="string";//add array type
							argsString += arrName;
						}
						else
							argsString += '"'+argStringValue+'"';

						break;*/
			}


			//footerBody+=arg.value[0];//@BAD@
			argCount++;
		}
		if (variablesCorrectByEtalonEnding.length()>1)//if comparsion conditions excists (our_func arg[i] == etalon_func arg[i])
			variablesCorrectByEtalonEnding += ";";
		else
			variablesCorrectByEtalonEnding+="true;";//condition try if comparsion need no.

		footerBody += argumentDefinition;
		footerBody += argumentEtalonDefinition;

		argsString += variablesCorrect+";\n";
		argsString += " result" + string(ETALON_FOR_FUNCTION_ENDING) +  " = function_etalon(" + argForEtalonFunction +  ");\n";
		argsString += " result = " + functionData.functionName + "(" + argForMainFunction +  ");\n";

		argsString += "isTrue = false;\n";
		argsString += variablesCorrectByEtalonPrefix+variablesCorrectByEtalonEnding;
		argsString += functionData.tests_code[i] + "\n";

		if (functionData.isArray )
		{
			string arrType = functionData.getReturnType();
			/*string arrayDeclaration=arrType+" "+arrName+"[]="+functionData.result[i];
			footerBody+=arrayDeclaration+";\n";*/

			//if (std::equal(std::begin(iar1), std::end(iar1), std::begin(iar2)))


			argsString += "if (compareArrs<"+arrType+","+
					std::to_string(functionData.size)+">(result_etalon, result)";

		}
		else
			argsString += "if ( result_etalon == result";//open function call body;

		//if (functionData.isArray)
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
	string result;
	result = generateType(type, lang) + name + " ";

	/*if(value.length() > 0)
	switch(type){
		case FunctionData::RET_VAL_BOOL:
			result += to_bool(argStringValue);
					break;
				case FunctionData::RET_VAL_FLOAT:
					result += std::atof(argStringValue.c_str());
					break;
				case FunctionData::RET_VAL_INT:
					result += argStringValue.c_str();
					break;
				case FunctionData::RET_VAL_STRING:
					result += '"'+argStringValue+'"';
					break;
		}*/
	return result;

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
