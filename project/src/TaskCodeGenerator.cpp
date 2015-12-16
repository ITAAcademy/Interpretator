/*
 * TaskCodeGenerator.cpp
 *
 *  Created on: Dec 4, 2015
 *      Author: root
 */

#include "inc/TaskCodeGenerator.h"

namespace code {
int TaskCodeGenerator::status = 0;

TaskCodeGenerator::TaskCodeGenerator(jsonParser &jSON, int thread_id)
{
	updateData(jSON, thread_id);
}

TaskCodeGenerator::~TaskCodeGenerator()
{
	// TODO Auto-generated destructor stub
}
bool TaskCodeGenerator::updateData(jsonParser &jSON, int thread_id)
{
	status = 0;
	data = parseTask(jSON);
	data.thread_id = thread_id;
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
	functionData.lang = LangCompiler::convertFromName(jSON.getObject("lang", false).asString());
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


	for (Value arg_compare_mark: functionValue["compare_mark"])
	{
		CompareMark cmp = (CompareMark)arg_compare_mark.asInt();
		functionData.compare_marks.push_back(cmp);
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
				arrString += std::to_string(j);

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
		functionArgument.name = FunctionArgument::getName(argumentValue["arg_name"].asString(), functionData.lang);

		/*for (Value arg_compare_mark: argumentValue["compare_mark"])
		{
			functionArgument.compare_marks.push_back( (CompareMark) arg_compare_mark.asInt());
		}*/

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

string TaskCodeGenerator::generateFunctionProtorype(FunctionData functionData, string name , char divider, char space, string modifiers)
{
	//if (functionData.lang==LangCompiler::Flag_JS) return string("");//prototypes don't needed in js
	string functionStr ="";
	switch(functionData.lang){
	case LangCompiler::Flag_Java:
	case LangCompiler::Flag_CS:
		functionStr += "static ";
		break;
	case LangCompiler::Flag_JS:
	case LangCompiler::Flag_PHP:
		functionStr += "function ";
	}
	if (functionData.lang==LangCompiler::Flag_JS)
		functionStr += modifiers + " ";
	else
	functionStr += modifiers + " " + FunctionArgument::generateType(functionData.returnValueType, functionData.isArray, functionData.lang);

	if (functionData.lang == LangCompiler::Flag_CS && functionData.isArray == FunctionData::ARRAY)
		functionStr += " [] ";

	functionStr	+= name + "(";

	int argCount = 0;
	int array_cnt = 0;

	for(FunctionArgument arg : functionData.args){
		if (argCount>0)
			functionStr += divider;
		string type="";
		if (!functionData.lang==LangCompiler::Flag_JS)
		type = FunctionArgument::generateType(arg.type, arg.isArray, functionData.lang);// 0 == C++
		functionStr += type + space;


		switch(functionData.lang)
		{
		case LangCompiler::Flag_CPP:
		{
			functionStr += type + space;
			if ( arg.isArray != FunctionData::ARRAY)
				functionStr += "&" + arg.name;
			else
				functionStr += arg.name;
			break;
		}
		case LangCompiler::Flag_CS:
			functionStr += "ref " + type + " " ;
			if ( arg.isArray == FunctionData::ARRAY)
				functionStr += "[]" + arg.name;
			else
				functionStr += arg.name;
			break;
		case LangCompiler::Flag_Java:
		case LangCompiler::Flag_JS:
		case LangCompiler::Flag_PHP:
		{
			functionStr += type + space;
			// maybe out add?
			functionStr += arg.name;
			break;
		}
		}
		argCount++;
	}
	//close prototype and open body of function
	functionStr += ")\n";
	return functionStr;
}

string TaskCodeGenerator::generateHeader(FunctionData functionData){

	string headerStr = getStandartInclude(functionData.lang) + "\n";

	string defaultReturnValue = "0";

	switch(functionData.lang)
	{
	case LangCompiler::Flag_Java: //@BAD@
		headerStr+="public class Main{{thId}}{\n";
		defaultReturnValue="null";
		break;
	case LangCompiler::Flag_PHP:
		headerStr += "<?php \n";// php ID
		break;
	case LangCompiler::Flag_CS:
		headerStr+="public class MainClass {\n";
		int type = functionData.returnValueType;
		defaultReturnValue = "default(" + FunctionArgument::generateType(type, false, functionData.lang);
		if (functionData.isArray == FunctionData::ARRAY)
			defaultReturnValue += " [] ";
		defaultReturnValue += ")";
		break;
	}


	headerStr += generateFunctionProtorype(functionData, "function_etalon"); //create prototype for etalon function
	headerStr += "{\n" + functionData.etalon + "return "+defaultReturnValue+";\n}\n"; // add etalon function
	headerStr += generateFunctionProtorype(functionData, functionData.functionName) + "{\n";
	/*l12("Yura: 2202:");
	l12(headerStr);*/
	return headerStr;
}

string TaskCodeGenerator::generateFooter(FunctionData functionData){

	vector<FunctionArgument> variables;
	string defaultReturnValue = "0";
	if (functionData.lang==LangCompiler::Flag_Java)//What
		defaultReturnValue="null";
	else
		if (functionData.lang==LangCompiler::Flag_CS)
		{
			defaultReturnValue = "default(" + FunctionArgument::generateType(functionData.returnValueType, false, functionData.lang);
			if (functionData.isArray == FunctionData::ARRAY)
				defaultReturnValue += " [] ";
			defaultReturnValue += ")";
		}
	//999
	string footerBody = "return "+defaultReturnValue+";\n}\n";//Close function body

	string space=" ";
	char divider=',';
	string results_arguments_comparing_after_main_func = FunctionArgument::generateType(FunctionData::RET_VAL_BOOL, false, functionData.lang) + " results_arguments_comparing_after_main_func = true";
	string modifiedArgComparsion;
	//C++//need out this code
	string arrCompFuncStr;

	switch(functionData.lang)
	{
	case LangCompiler::Flag_CPP:
		arrCompFuncStr="template<typename T,int size>\n\
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
		break;

	case LangCompiler::Flag_CS:
		arrCompFuncStr = "static bool ArraysEqual<T>(T[] a1, T[] a2)\n\
		{\n\
		    if (a1 == a2)\n\
		        return true;\n\
		    if (a1 == null || a2 == null)\n\
		        return false;\n\
		    if (a1.Length != a2.Length)\n\
		        return false;\n\
			EqualityComparer<T> comparer = EqualityComparer<T>.Default;\n\
		    for (int i = 0; i < a1.Length; i++)\n\
		        if (!comparer.Equals(a1[i], a2[i]))\n\
		            return false;\n\
		    return true;\n}\n";
		break;
	}
	footerBody += arrCompFuncStr;
	/*
	 * MAIN FUNCTION START
	 */
	switch(functionData.lang)
	{
	//in JS main function is absense, so we don't append it when our lang is js
	case LangCompiler::Flag_CPP:
		footerBody+="int main()\n\
					{\n";
		break;
	case LangCompiler::Flag_Java: //@BAD@
		footerBody+="public static void main(String[] args)\n\
{\n";
		break;

	case LangCompiler::Flag_CS:
		footerBody+="public static void Main(String[] args)\n\
		{\n";
		break;
	}

	generateVariables(footerBody, functionData, variables);

	string correctArgumentsConditionName = FunctionArgument::getName("variablesCorrect", functionData.lang);
	string argumentsEqualToEtalonConditionName = FunctionArgument::getName("variablesCorrectByEtalon", functionData.lang);

	footerBody +=  FunctionArgument::generateType(FunctionData::RET_VAL_BOOL, false, functionData.lang)
	+  FunctionArgument::getName("isTrue", functionData.lang) + ";\n";//moved out from cicle to fix variable duplicates
	string conditionsVariableDeclaration = FunctionArgument::generateType(
			FunctionData::RET_VAL_BOOL, false,functionData.lang) +" "+
					argumentsEqualToEtalonConditionName+";"+correctArgumentsConditionName+";\n";
	footerBody+= conditionsVariableDeclaration;



	string argsString;
	string etalongArgsString;

	bool is_float = (functionData.returnValueType == ValueTypes::VAL_FLOAT);
	for(int i = 0; i < functionData.result.size(); i++)
	{

		if ( functionData.isArray != FunctionData::ARRAY)
		{
			argsString += /*"result" + string(ETALON_FOR_FUNCTION_ENDING) + " = " + */	FunctionArgument::getName("result_etalon", functionData.lang) + " = ";
			if (functionData.lang == LangCompiler::Flag_CS && functionData.returnValueType == FunctionData::RET_VAL_FLOAT)
				argsString += "(float) ";
			argsString += functionData.result[i] + ";\n";
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
				argsString += /*"result" + string(ETALON_FOR_FUNCTION_ENDING) + "[" + to_string(rez_size) + "] = " +*/ FunctionArgument::getName("result_etalon", functionData.lang) + "[" + to_string(h) + "] = ";
				if (functionData.lang!=LangCompiler::Flag_JS && is_float)
					argsString += " (" + FunctionArgument::generateType(FunctionData::RET_VAL_FLOAT, false, functionData.lang) + ") ";
				argsString += values_u[h].toStyledString() + ";\n";
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
		string variablesCorrect = "" + correctArgumentsConditionName + " = ";
		string variablesCorrectByEtalonPrefix = "" + argumentsEqualToEtalonConditionName + " = ";
		string variablesCorrectByEtalonEnding = "";

		vector<CompareMark> compare_marks = functionData.compare_marks;

		vector<vector< pair<int,int> > > checkableArgsIndexes = functionData.checkableArgsIndexes;

		int checkableArgsCount = 0;
		int currentArgumentIndex=-1;
		for(FunctionArgument arg : functionData.args)
		{
			currentArgumentIndex++;
			vector<string> args_results;
			vector<string> args_results_must_be_after_main_func;
			if ( !arg.isArray )
			{
				const string castToFloat="(float)" ;
				string currentArgDef;
				string currentArgEtalonDef;

				currentArgDef += arg.name + string(ETALON_FOR_FUNCTION_ENDING) + " = " +arg.name + " = " ;
				currentArgEtalonDef += arg.name + string(ETALON_ENDING) + string(" = ") ; //etalon value for argument
				if ( (functionData.lang == LangCompiler::Flag_Java || functionData.lang == LangCompiler::Flag_CS) && arg.type == ValueTypes::VAL_FLOAT)
				{
					currentArgDef+=castToFloat;
					currentArgEtalonDef+=castToFloat;
				}

				currentArgDef +=  arg.value[i]+";\n";
				currentArgEtalonDef += arg.etalonValue[i] + string(";\n"); //etalon value for argu

				argumentDefinition += currentArgDef;
				argumentEtalonDefinition += currentArgEtalonDef;
				variablesCorrect += getCompareString(arg.name,(ValueTypes) arg.type, arg.name +
						string(ETALON_ENDING), (ValueTypes)arg.type, CompareMark::Equial,
						functionData.lang);

				if (argCount != functionData.args.size() - 1 )
					variablesCorrect += " && ";

			}
			else
			{
				Reader reader;
				JsonValue values_u;
				JsonValue etalons_values_u;
				reader.parse(arg.value[i], values_u);
				reader.parse(arg.etalonValue[i], etalons_values_u);

				for(int i = 0; i < values_u.size(); i++)
				{
					argumentDefinition += arg.name + string(ETALON_FOR_FUNCTION_ENDING) +
							"[" + to_string(i) + "] = " + arg.name +"[" + to_string(i) + "] = "
							+ values_u[i].toStyledString() + ";\n";
					argumentEtalonDefinition += arg.name + ETALON_ENDING + "[" + to_string(i) +
							"] = " + etalons_values_u[i].toStyledString() + ";\n";
					//"]getAllRecordsFromTable = " + etalons_values_u[i].toStyledString() + ";\n";
				}

				variablesCorrect += getArrayCompareString(arg.name,arg.size, (ValueTypes) arg.type, arg.name + string(ETALON_ENDING),
						arg.size, (ValueTypes) arg.type, CompareMark::Equial, functionData.lang);

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
			if (functionData.lang == LangCompiler::Flag_CS)
			{
				argForMainFunction += "ref ";
				argForEtalonFunction += "ref ";
			}
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
				if(variables.size() < firstCheckableVariableIndex || variables.size() < secondCheckableVariableIndex)
				{
					status = (int)COMPARE_VALUE_FROM_TH;
					break;
				}
				FunctionArgument *firstGlobalVariable = &variables[firstCheckableVariableIndex];
				FunctionArgument *secondGlobalVariable = &variables[secondCheckableVariableIndex];

				if ( checkableArgsCount>0 )
					variablesCorrectByEtalonEnding+=" && ";

				ValueTypes type1 = (ValueTypes) firstGlobalVariable->type;
				ValueTypes type2 = (ValueTypes) secondGlobalVariable->type;

				variablesCorrectByEtalonEnding += getArrayCompareString(firstGlobalVariable->name, firstGlobalVariable->size , type1,
						secondGlobalVariable->name , secondGlobalVariable->size, type2,
						CompareMark::Equial, functionData.lang);

				checkableArgsCount++;

			}
		}

		if (variablesCorrectByEtalonEnding.length()>1)//if comparsion conditions excists (our_func arg[i] == etalon_func arg[i])
			variablesCorrectByEtalonEnding += ";";
		else
			variablesCorrectByEtalonEnding+="true;";//condition try if comparsion need no.

		argsString += argumentDefinition;
		argsString += argumentEtalonDefinition;


		argsString += variablesCorrect;
		if (functionData.lang == LangCompiler::Flag_Java)
			argsString+=")";
		argsString += ";\n";//NEED BRACKET
		argsString +=  FunctionArgument::getName("result", functionData.lang) + string(ETALON_FOR_FUNCTION_ENDING) +  " = function_etalon(" + argForEtalonFunction +  ");\n";
		argsString += FunctionArgument::getName("result", functionData.lang) +  " = " + functionData.functionName + "(" + argForMainFunction +  ");\n";

		argsString += FunctionArgument::getName("isTrue", functionData.lang) + " = true;\n";
		argsString += variablesCorrectByEtalonPrefix+variablesCorrectByEtalonEnding;
		argsString += functionData.tests_code[i] + "\n";

		ValueTypes arrType = (ValueTypes) functionData.returnValueType;
		CompareMark cmp = functionData.compare_marks[i];
		if (functionData.isArray == FunctionData::ARRAY)
		{
			//string arrType = functionData.getReturnType();

			/*argsString += "if (compareArrs<"+arrType+","+
					std::to_string(functionData.size)+">(result_etalon, result)";*/
			argsString += "if ("  + getArrayCompareString(FunctionArgument::getName("result_etalon", functionData.lang), functionData.size, (ValueTypes) arrType, FunctionArgument::getName("result", functionData.lang) ,
					functionData.size, (ValueTypes) arrType, cmp, functionData.lang);

			// CompareMark::Equial);


		}
		else
			//argsString += "if ( result_etalon == result";//open function call body;
			argsString += "if ("  + getCompareString(FunctionArgument::getName("result_etalon", functionData.lang) , arrType, FunctionArgument::getName("result ", functionData.lang)  ,
					arrType, cmp, functionData.lang);


		//if (functionData.isArray)//@WHAT@
		{
			argsString += " && " + FunctionArgument::getName("variablesCorrect", functionData.lang) + " && " + FunctionArgument::getName("isTrue", functionData.lang) + ")\n";
			//TODO
		}
		switch(functionData.lang)
		{
		case LangCompiler::Flag_CPP:
			argsString += "std::cout << \" @" + to_string(i) + "@\";\n";
			argsString += "else\n";
			argsString += "std::cout << \" @" + to_string(i) + "!@\";\n";
			break;
		case LangCompiler::Flag_Java://@BAD@
			argsString += "System.out.println(\" @" + to_string(i) + "@\");\n";
			argsString += "else\n";
			argsString += "System.out.println(\" @" + to_string(i) + "!@\");\n";
			break;

		case LangCompiler::Flag_JS:
			argsString += "console.log(\" @" + to_string(i) + "@\");\n";
			argsString += "else\n";
			argsString += "console.log(\" @" + to_string(i) + "!@\");\n";
			break;
		case LangCompiler::Flag_PHP:
			argsString += "echo \" @" + to_string(i) + "@\";\n";
			argsString += "else\n";
			argsString += "echo \" @" + to_string(i) + "!@\";\n";
			break;


		case LangCompiler::Flag_CS:
			argsString += "System.Console.WriteLine(\" @" + to_string(i) + "@\");\n";
			argsString += "else\n";
			argsString += "System.Console.WriteLine(\" @" + to_string(i) + "!@\");\n";
			break;

		}



	}

	footerBody+=argsString;
	/*
	 * close footer
	 */
	switch(functionData.lang)
	{
	case LangCompiler::Flag_CPP:
		footerBody += "\nreturn 0;\n}";
		break;
	case LangCompiler::Flag_Java: 	case LangCompiler::Flag_CS://@BAD@
		footerBody += "}}";//"\nreturn 0;\n\t}\n}";
		break;
	case LangCompiler::Flag_PHP://@BAD@
		footerBody += "?>\n";
		break;
	}

	//C++

	l12("Yura:: 00001");
	l12(footerBody);
	return footerBody;
}

string TaskCodeGenerator::getCompareString(string name1,  ValueTypes type1,string name2,  ValueTypes type2, CompareMark mark, int lang)
{
	string result = "( ";
	if ((int)type1 != (int) type2) //equial type
	{
		name1 = "to_string( " + name1 + " )";
		name2 = "to_string( " + name2 + " )";
		type1 = ValueTypes::VAL_STRING;
	}
	string floorFuncName;
	switch (type1)
	{

	if (lang==LangCompiler::Flag_CPP)
		floorFuncName = "floor";
	else if (lang==LangCompiler::Flag_Java)
		floorFuncName = "Math.floor";
	else floorFuncName = "Math.floor";

	case ValueTypes::VAL_FLOAT:
		result += " (" +floorFuncName+"(" + name1 + " * 100 ) - "+floorFuncName+"(" + name2 + " * 100 ) ) ";
		switch (mark)
		{
		case CompareMark::LessEquial:
			result += "<= 0 )";
			break;
		case CompareMark::Less:
			result += " < 0 )";
			break;
		case CompareMark::Equial: default:
			result += " == 0 )";
			break;
		case CompareMark::NotEquial:
			result += " != 0 )";
			break;
		case CompareMark::More:
			result += " > 0 )";
			break;
		case CompareMark::MoreEquial:
			result += " >= 0 )";
			break;
		}
		break;

		case VAL_INT:
		{
			switch (mark)
			{
			case CompareMark::LessEquial:
				result +=  name1 + " <= " + name2 + " )";
				break;
			case CompareMark::Less:
				result +=  name1 + " < " + name2 + " )";
				break;
			case CompareMark::Equial: default:
				result +=  name1 + " == " + name2 + " )";
				break;
			case CompareMark::NotEquial:
				result +=  name1 + " != " + name2 + " )";
				break;
			case CompareMark::More:
				result +=  name1 + " > " + name2 + " )";
				break;
			case CompareMark::MoreEquial:
				result +=  name1 + " >= " + name2 + " )";
				break;
			}
		}
		break;

		case VAL_STRING:
		{
			if ( lang == (int) LangCompiler::Flag_CS)
			{
				switch (mark)
				{
				case CompareMark::LessEquial:
					result += name1 + ".Compare(" + name2 +") <= 0";
					break;
				case CompareMark::Less:
					result += name1 + ".Compare(" + name2 +") < 0";
					break;
				case CompareMark::Equial: default:
					result += "String.Equals (" + name1 + ", " + name2 +"))";
					break;
				case CompareMark::NotEquial:
					result += "!String.Equals (" + name1 + ", " + name2 +",  StringComparison.Ordinal)";
					break;
				case CompareMark::More:
					result += name1 + ".Compare(" + name2 +") > 0";
					break;
				case CompareMark::MoreEquial:
					result += name1 + ".Compare(" + name2 +") >= 0";
					break;
				}
			}
			else
				if ( lang != (int) LangCompiler::Flag_Java)
					switch (mark)
					{
					case CompareMark::LessEquial:
						result +=  name1 + " <= " + name2 + " )";
						break;
					case CompareMark::Less:
						result +=  name1 + " < " + name2 + " )";
						break;
					case CompareMark::Equial: default:
						result +=  name1 + " == " + name2 + " )";
						break;
					case CompareMark::NotEquial:
						result +=  name1 + " != " + name2 + " )";
						break;
					case CompareMark::More:
						result +=  name1 + " > " + name2 + " )";
						break;
					case CompareMark::MoreEquial:
						result +=  name1 + " >= " + name2 + " )";
						break;
					}
				else
				{
					switch (mark)
					{
					case CompareMark::LessEquial:
						result += "(new String(" + name1 + ").compareTo(" + name2 +")) <= 0";
						break;
					case CompareMark::Less:
						result += "(new String(" + name1 + ").compareTo(" + name2 +")) < 0";
						break;
					case CompareMark::Equial: default:
						result += "new String(" + name1 + ").equals(" + name2 +")";
						break;
					case CompareMark::NotEquial:
						result += "!(new String(" + name1 + ").equals(" + name2 +"))";
						break;
					case CompareMark::More:
						result += "(new String(" + name1 + ").compareTo(" + name2 +")) > 0";
						break;
					case CompareMark::MoreEquial:
						result += "(new String(" + name1 + ").compareTo(" + name2 +")) >= 0";
						break;
					}
				}
		}
		break;

		case ValueTypes::VAL_BOOL:
			switch (mark)
			{
			case CompareMark::Equial: default:
				result +=  name1 + " == " + name2 + " )";
				break;
			case CompareMark::NotEquial:
				result +=  name1 + " != " + name2 + " )";
				break;
			}
			break;
	}
	return result;
}

string TaskCodeGenerator::getArrayCompareString(string name1, int arr1_size, ValueTypes type1,string name2, int arr2_size, ValueTypes type2, CompareMark mark, int lang)
{
	if (arr1_size != arr2_size)
		return "false";
	if ( arr1_size < 0  )
		return "false";

	if (type1 != type2) //equial type
	{
		return "false";
	}

	if ( arr1_size == 0  )
	{
		return getCompareString(name1, type1, name2, type2, mark, lang);
	}
	else
	{

		switch(lang)
		{
		case LangCompiler::Flag_Java:

			return string( "Arrays.equals(" + name1 + ", " +  name2 + ")");
			break;

		case LangCompiler::Flag_JS:
			return ""+name1+".toString()=="+name2+".toString()";
			break;

		case LangCompiler::Flag_CPP:
			return string( " compareArrs<" + FunctionArgument::generateType(type1, false, lang) + 	"," +
					std::to_string(arr1_size) + " > ( " + name1 + ", "+ name2 + " )");
		case LangCompiler::Flag_PHP:
			return " !array_diff(" + name1 + "," + name2 + ")";
		case LangCompiler::Flag_CS:
		return string( "ArraysEqual(" + name1 + ", " +  name2 + ")");
			break;

		}

	}
}

bool TaskCodeGenerator::generateVariables(string &output, FunctionData functionData, vector<FunctionArgument> &variables)
{
	FunctionArgument resultVar;
	resultVar.name=FunctionArgument::getName("result", functionData.lang);
	resultVar.isArray=functionData.isArray;
	resultVar.size=functionData.size;
	resultVar.type=functionData.returnValueType;
	output += resultVar.generateDefinition(true, functionData.lang); //if true, it will be "type * result;", else "type result[size];"
	variables.push_back(resultVar);

	resultVar.name += ETALON_ENDING;
	output += resultVar.generateDefinition(false, functionData.lang);
	variables.push_back(resultVar);

	resultVar.name += string(ETALON_FOR_FUNCTION_ENDING);
	output += resultVar.generateDefinition(true, functionData.lang);
	variables.push_back(resultVar);


	for(FunctionArgument arg : functionData.args)
	{
		output += arg.generateDefinition(false, functionData.lang);
		variables.push_back(arg);

		FunctionArgument etalonArg = arg;
		etalonArg.name+=ETALON_ENDING;
		output += etalonArg.generateDefinition(false, functionData.lang);
		variables.push_back(etalonArg);

		FunctionArgument etalonForFunctionArg = arg;
		etalonForFunctionArg.name +=string(ETALON_FOR_FUNCTION_ENDING);
		output += etalonForFunctionArg.generateDefinition(false, functionData.lang);
		variables.push_back(etalonForFunctionArg);
	}

	return true;
}

string TaskCodeGenerator::generateVar(int type, string name, int lang, string value)
{
	return FunctionArgument::generateType(type, 0, lang) + name + " ";
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
		break;
	}
	case LangCompiler::Flag_Java:{
		include = "import java.util.Arrays;";
		//...
		break;
	}
	case LangCompiler::Flag_CS:
		include = "using System;\n\
				using System.Collections.Generic;\n\
				using System.Collections;";
		break;
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

/*
string FunctionArgument::getTypeInt(int lang )
{
	switch( lang)
	{
	case LangCompiler::Flag_CPP: case LangCompiler::Flag_Java:
		return "int";
		break;
	}
}

string FunctionArgument::getTypeFloat(int lang )
{
	switch( lang)
	{
	case LangCompiler::Flag_CPP: case LangCompiler::Flag_Java:
		return "float";
		break;
	}
}

string FunctionArgument::getTypeString(int lang )
{
	switch( lang)
	{
	case LangCompiler::Flag_CPP:
		return "string";
		break;

	case LangCompiler::Flag_Java:
		return "String";
		break;
	}
}

string FunctionArgument::getTypeBool(int lang )
{
	switch( lang)
	{
	case LangCompiler::Flag_CPP:
		return "bool";
		break;

	case LangCompiler::Flag_Java:
		return "boolean";
		break;
	}
}

string FunctionArgument::getType(int lang )
{
	switch( lang)
	{
	case VAL_INT:
		return getTypeInt(lang);
		break;
	case VAL_FLOAT:
		return getTypeFloat(lang);
		break;
	case VAL_BOOL:
		return getTypeBool(lang);
		break;
	case VAL_STRING:
		return getTypeString(lang);
		break;
	case VAL_RANGE:
		return "range";
		break;
	}
	return "";
}*/
string FunctionArgument::getName(string name, int lang)
{
	switch(lang)
	{
	case LangCompiler::Flag_PHP:
		return "$" + name;
	default:
		return name;
	}
}

string FunctionArgument::getName(int lang)
{
	return FunctionArgument::getName(name, lang);
}

string FunctionArgument::generateType(int type, int arrayType, int lang)
{
	if (lang==LangCompiler::Flag_PHP) return " ";//arg types specify not in PHP
	if (lang==LangCompiler::Flag_JS) return "var";//arg types specify not in js
	string result;

	switch(type)
	{
	case FunctionData::RET_VAL_BOOL:
		if (lang == (int) LangCompiler::Flag_Java)
			result +=  "boolean";
		else
			result += "bool";
		break;
	case FunctionData::RET_VAL_FLOAT:
		result += "float";
		break;
	case FunctionData::RET_VAL_INT:
		result += "int";
		break;
	case FunctionData::RET_VAL_STRING:
		if (lang == (int) LangCompiler::Flag_Java)
			result +=  "String";
		else
			result += "string";
		break;
	}

	result += " ";

	if (arrayType == FunctionData::ARRAY)
		switch(lang)
		{
		case LangCompiler::Flag_CPP:
			result += "* ";
			break;
		case LangCompiler::Flag_Java:
			result += "[]";
			break;
		}

	return result;
}

string FunctionArgument::generateDefinition(bool is_result, int lang)
{
	string stype = generateType(type, false, lang);
	string result = stype;
	switch( lang)
	{
	case LangCompiler::Flag_CPP:
		if (isArray)
		{
			if (is_result)
				result += " *" + name;
			else
				result += " " + name + " [" + std::to_string(size) + "]";
		}
		else
			result += " " +  name;
		break;

	case LangCompiler::Flag_Java: case LangCompiler::Flag_CS:
		if (isArray)
		{
			result += " [] " + name;
			if ( !is_result )
				result += " = new " + stype + " [" + std::to_string(size) + "]";
		}
		else
			result += " " +  name;
		break;

	case LangCompiler::Flag_JS:
		result += " " + name;
		if (isArray)result += "=[]";
		break;
	case LangCompiler::Flag_PHP:
		result += " " + name;
		//if (isArray)result += "=[]";
		break;


	}
	result += ";\n";
	return result;
}

} /* namespace code */

