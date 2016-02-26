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

string TaskCodeGenerator::addBracketsToStr(string value)
{
	return "\"" + value + "\"";
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
	//l12("etalon");

	Value functionValue = jSON.getObject("function",false);

	functionData.etalon = etalon;
	functionData.lang = LangCompiler::convertFromName(jSON.getObject("lang", false).asString());
	functionData.returnValueType = jSON.getAsInt(functionValue["type"]);//  functionValue["type"].asInt(); 555

	functionData.functionName = "function_main";//@BAG@

	functionData.isArray =  jSON.getAsInt(functionValue["array_type"]);//.asInt();//functionValue["results"][0].isArray();
	functionData.unit_tests_nums = jSON.getAsInt(functionValue["unit_test_num"]);//.asInt();//functionValue["results"][0].size();
	functionData.isRange = jSON.isResultsRange();

	if (functionData.isArray)
		functionData.result_array_size =  jSON.getAsInt(functionValue["size"]);
	else
		functionData.result_array_size = 0;

	for (Value arg_indexes_pares_arr : functionValue["checkable_args_indexes"])
	{
		vector<pair<int,int>> testConditionPares;
		for (Value arg_indexes_pair : arg_indexes_pares_arr )
		{
			Value f_value = arg_indexes_pair["first"];
			int first = jSON.getAsInt(f_value);
			int second = jSON.getAsInt(arg_indexes_pair["second"]);
			pair<int,int> indexPare = std::make_pair(first, second);

			testConditionPares.push_back(indexPare);
		}
		functionData.checkableArgsIndexes.push_back(testConditionPares);

	}


	for (Value arg_compare_mark: functionValue["compare_mark"])
	{
		CompareMark cmp = (CompareMark)jSON.getAsInt(arg_compare_mark);//.asInt();
		functionData.compare_marks.push_back(cmp);
	}


	if ((etalon.find_first_not_of("\t\n\r ") == string::npos)) //if etalon not empty
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
				//functionData.result.push_back(value.asString());  //___opo
			{
				for (int k = 0; k < functionData.unit_tests_nums; k++)
				{
					if (functionData.isArray)
					{
						vector<string> res;
						for (int b = 0; b < functionData.result_array_size; b++)
						{
							string as_str = jsonParser::getAsString(functionValue[FIELD_RESULTS][k][b]);
							if (functionData.returnValueType == FunctionData::RET_VAL_STRING)
								as_str = addBracketsToStr(as_str);
							res.push_back( as_str);
							//functionValue[FIELD_RESULTS][k][b].asString() );
						}

						functionData.result_array.push_back(res);
					}
					else
					{
						string as_str = jsonParser::getAsString(functionValue[FIELD_RESULTS][k]);
						if (functionData.returnValueType == FunctionData::RET_VAL_STRING)
							as_str = addBracketsToStr(as_str);
						functionData.result.push_back( as_str);
					}
				}
			}
		}

	for(JsonValue value:functionValue["tests_code"])
	{
		functionData.tests_code.push_back(value.asString());
	}


	Value functionArgs = functionValue["args"];



	for (int i=0; i < functionArgs.size(); i++)
	{
		Value argumentValue = functionArgs.get(i,false);
		FunctionArgument functionArgument;
		functionArgument.isArray = jSON.getAsInt(argumentValue["is_array"]);//[0].isArray();
		if (functionArgument.isArray)
			functionArgument.size = jSON.getAsInt(argumentValue["size"]);
		else
			functionArgument.size = 0;
		functionArgument.type = jSON.getAsInt(argumentValue[FIELD_TYPE]);//argumentValue["type"].asInt();
		functionArgument.name = FunctionArgument::getName(argumentValue["arg_name"].asString(), functionData.lang);


		bool is_etalon_value = !(argumentValue[FIELD_ETALON_VALUE].isNull());
		if (is_etalon_value)
			is_etalon_value = argumentValue[FIELD_ETALON_VALUE].size() > 0;
		/*for (Value arg_compare_mark: argumentValue["compare_mark"])
		{
			functionArgument.compare_marks.push_back( (CompareMark) arg_compare_mark.asInt());
		}*/
		//Json::Value args_i_value = jSON.getParsedFromString()[FUNCTION][FIELD_ARGS][ i ][FIELD_VALUE];

		int etalon_value_counter = 0;

		for(JsonValue value:argumentValue["value"])
		{
			if (functionArgument.isArray)
			{
				vector<string> value_arr;
				for (int y = 0; y < functionArgument.size; y++)
				{
					//string value_s = jsonParser::getAsString(value);
					string value_s = jSON.getAsString(value[y]);
					//jSON.getAsString(value);
					if (functionArgument.type == FunctionData::RET_VAL_STRING)
						value_s = addBracketsToStr(value_s);
					value_arr.push_back(value_s); //_opo
				}
				functionArgument.value_array.push_back(value_arr);
				if (is_etalon_value)
				{
					vector<string> etalon_value_arr;
					int arg_size = functionArgument.size;
					for (int y = 0; y < arg_size; y++)
					{
						//string value_s = jsonParser::getAsString(value);
						string value_s = jSON.getAsString(argumentValue["etalon_value"][i][y]);
						//getAsString(argumentValue[FIELD_ETALON_VALUE][y]);
						//jSON.getAsString(value);
						if (value_s.size())
						{
							if (functionArgument.type == FunctionData::RET_VAL_STRING)
								value_s = addBracketsToStr(value_s);
							etalon_value_arr.push_back(value_s); //_opo
						}
					}
					functionArgument.etalon_value_array.push_back(etalon_value_arr);
				}
			}
			else
			{
				string value_s = jsonParser::getAsString(value);
				functionArgument.value.push_back(value_s); //_opo
				if (is_etalon_value)
				{
					//string value_s = jsonParser::getAsString(argumentValue[FIELD_ETALON_VALUE]);
					value_s = jsonParser::getAsString(argumentValue[FIELD_ETALON_VALUE][etalon_value_counter++]);
					//if (value_s.size())
					{
						if (functionArgument.type == FunctionData::RET_VAL_STRING)
							value_s = addBracketsToStr(value_s);
						functionArgument.etalonValue.push_back(value_s); //_opo
					}
					//functionArgument.etalonValue.insert(functionArgument.etalonValue.end(), value_s);
				}
			}
		}
		int etalonValueArgsCount = 0;
		/*for(JsonValue modvalue:argumentValue["etalon_value"])
		{
			if (modvalue.isArray())
			{

			}
			else
			{

			}


			if (!modvalue.isNull()){
				functionArgument.etalonValue[etalonValueArgsCount] = jsonParser::getAsString(modvalue);
				//modvalue.asString(); //_opo
			}
			etalonValueArgsCount++;
		}*/

		functionData.args.push_back(functionArgument);
	}
	return functionData;
}

string TaskCodeGenerator::generateFunctionProtorype(FunctionData functionData, string name , char divider, char space, string modifiers)
{
	//if (functionData.lang==LangCompiler::Flag_JS) return string("");//prototypes don't needed in js
	string functionStr ="";
	switch(functionData.lang)
	{
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
		functionStr += modifiers + " " + FunctionArgument::generateType(functionData.returnValueType,
				functionData.isArray, functionData.lang, true);

	if (functionData.lang == LangCompiler::Flag_CS && functionData.isArray == FunctionData::ARRAY)
		functionStr += " [] ";

	functionStr	+= name + "(";

	int argCount = 0;
	int array_cnt = 0;

	for(FunctionArgument arg : functionData.args){
		if (argCount>0)
			functionStr += divider;
		string type="";
		if ( functionData.lang != LangCompiler::Flag_JS)
			type = FunctionArgument::generateType(arg.type, arg.isArray, functionData.lang, true);// 0 == C++
		//functionStr += type + space;


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
		{
			functionStr += type + space;
			// maybe out add?
			functionStr += arg.name;
			break;
		}
		case LangCompiler::Flag_JS:
		case LangCompiler::Flag_PHP:
			functionStr += arg.name;
			break;
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
		defaultReturnValue=" \"	2zgi	1e6o	818oe83r2\"";
		break;

	case LangCompiler::Flag_CS:
		headerStr+="public class MainClass {\n";
		//int type = functionData.returnValueType;
		defaultReturnValue = "default(" + FunctionArgument::generateType(functionData.returnValueType,
				false, functionData.lang);
		if (functionData.isArray == FunctionData::ARRAY)
			defaultReturnValue += " [] ";
		defaultReturnValue += ")";
		break;

	case LangCompiler::Flag_JS:
		//defaultReturnValue=" \"	2zgi	1e6o	818oe83r2\"";
		break;

	case LangCompiler::Flag_CPP:
		defaultReturnValue=" null";
		break;
	}


	/*headerStr += generateFunctionProtorype(functionData, "function_etalon"); //create prototype for etalon function
	headerStr += "{\n" + functionData.etalon + "return "+defaultReturnValue+";\n}\n"; // add etalon function*/
	headerStr += generateFunctionProtorype(functionData, functionData.functionName) + "{\n";
	/*l12("Yura: 2202:");
	//l12(headerStr);*/
	return headerStr;
}

string TaskCodeGenerator::generateDefaultReturnValue(int lang, int returnValueType, int isArray)
{
	string defaultReturnValue = "";
	if (lang==LangCompiler::Flag_Java)//What
	{
		defaultReturnValue = "";
		switch (returnValueType)
		{
		case FunctionData::RET_VAL_BOOL:
			if (isArray == 0)
				defaultReturnValue +=" false";
			else
				if (isArray == 1)
					defaultReturnValue +=" new boolean[]{false}";
			break;

		case FunctionData::RET_VAL_FLOAT:
			if (isArray == 0)
				defaultReturnValue +=" 98989.9898889898";
			else
				if (isArray == 1)
					defaultReturnValue +=" new float[]{0}";
			break;

		case FunctionData::RET_VAL_INT:
			if (isArray == 0)
				defaultReturnValue +=" 65533";
			else
				if (isArray == 1)
					defaultReturnValue +=" new int[]{0}";
			break;

		case FunctionData::RET_VAL_STRING:
			if (isArray == 0)
				defaultReturnValue +=" \"qhejih34213	ed	qe013413\"";
			else
				if (isArray == 1)
					defaultReturnValue +=" new string[]{\"asdfasdaq4rrea\"}";
			break;
		default:
			defaultReturnValue = "null";
			break;
		}
	}
	else
		if (lang==LangCompiler::Flag_CS)
		{
			defaultReturnValue = "default(" + FunctionArgument::generateType(returnValueType, false, lang);
			if (isArray == FunctionData::ARRAY)
				defaultReturnValue += " [] ";
			defaultReturnValue += ")";
		}
		else
			if (lang==LangCompiler::Flag_PHP)// || lang==LangCompiler::Flag_JS)
			{
				defaultReturnValue = " \"fG13791323`02y13`132/4-28*2\"";
			}
			else
				if (lang==LangCompiler::Flag_CPP)
				{
					defaultReturnValue = " NULL";
				}

	return defaultReturnValue;
}

string TaskCodeGenerator::generateFooter(FunctionData functionData)
{
	vector<FunctionArgument> variables;
	//int lang, int returnValueType, int isArray

	string defaultReturnValue = generateDefaultReturnValue(functionData.lang, functionData.returnValueType, functionData.isArray);

	string footerBody = "";
	footerBody += "return "+defaultReturnValue+";\n}\n";//Close function body

	footerBody += generateFunctionProtorype(functionData, "function_etalon"); //create prototype for etalon function
	footerBody += "{\n" + functionData.etalon;
	//+ "return "+defaultReturnValue+";\n}\n"; // add etalon function

	if ((functionData.etalon.find_first_not_of("\t\n\r ") == string::npos))
		footerBody += "return "+defaultReturnValue+";\n}\n";
	else
		footerBody += "\n}\n";

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

	case LangCompiler::Flag_JS:
		//arrCompFuncStr =
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

	string variable_s;
	generateVariables(variable_s, functionData, variables);

	footerBody += variable_s;

	string correctArgumentsConditionName = FunctionArgument::getName("variablesCorrect", functionData.lang);
	string argumentsEqualToEtalonConditionName = FunctionArgument::getName("variablesCorrectByEtalon", functionData.lang);

	string type_n = FunctionArgument::generateType(FunctionData::RET_VAL_BOOL, false, functionData.lang) + " ";

	/*	footerBody +=  type_n
			+  FunctionArgument::getName("isTrue", functionData.lang) + ";\n";//moved out from cicle to fix variable duplicates
	 */
	string conditionsVariableDeclaration = type_n +" "+
			argumentsEqualToEtalonConditionName+";\n" + type_n + " " + correctArgumentsConditionName+";\n";
	footerBody+= conditionsVariableDeclaration;



	string argsString;
	string etalongArgsString;

	bool is_float = (functionData.returnValueType == ValueTypes::VAL_FLOAT);
	//if (!(functionData.etalon.find_first_not_of("\t\n\r ") == string::npos)) //if etalon empty

	bool is_etalon_func_empty = (functionData.etalon.find_first_not_of("\t\n\r ") == string::npos);

	for(int i = 0; i < functionData.unit_tests_nums; i++)
	{
		//if(functionData.result.size() > 0)
		/*if (!is_etalon_func_empty)
		{
			argsString +=  FunctionArgument::getName("result_etalon", functionData.lang) + " = ";
			if (functionData.lang!=LangCompiler::Flag_JS && functionData.lang!=LangCompiler::Flag_PHP && is_float)
				argsString += " (" + FunctionArgument::generateType(FunctionData::RET_VAL_FLOAT, false, functionData.lang) + ") ";

			//argsString += " function_etalon(" + argForEtalonFunction +  ");\n";//---
		}
		else*/
		if (is_etalon_func_empty)
		{
			if ( functionData.isArray != FunctionData::ARRAY)
			{
				argsString += /*"result" + string(ETALON_FOR_FUNCTION_ENDING) + " = " + */	FunctionArgument::getName("result_etalon", functionData.lang) + " = ";
				if ((functionData.lang == LangCompiler::Flag_CS) && (functionData.returnValueType == FunctionData::RET_VAL_FLOAT))
					argsString += "(float) ";
				argsString += functionData.result[i] + ";\n";
			}
			else
			{
				//footerBody += arg.name +"[" + to_string(i) + "] = " + arg.value[i] + ";\n";
				/*Reader reader;
				JsonValue values_u;
				JsonValue etalons_values_u;
				reader.parse(functionData.result[i], values_u);*/

				{
					vector <string> r_array = functionData.result_array[i];

					for (int h = 0; h < r_array.size(); h++)
					{
						argsString += /*"result" + string(ETALON_FOR_FUNCTION_ENDING) + "[" + to_string(rez_size) + "] = " +*/ FunctionArgument::getName("result_etalon", functionData.lang) + "[" + to_string(h) + "] = ";
						if (functionData.lang!=LangCompiler::Flag_JS && functionData.lang!=LangCompiler::Flag_PHP && is_float)
							argsString += " (" + FunctionArgument::generateType(FunctionData::RET_VAL_FLOAT, false, functionData.lang) + ") ";
						argsString += r_array[h] + ";\n";
					}
				}



			}
		}


		/*if (functionData.isRange )//@WHAT@
		{

		}
		else*/

		string argumentDefinition;
		string argumentEtalonDefinition;
		string argForMainFunction = " ";
		string argForEtalonFunction = " ";

		int argCount = 0;
		int etalongArgCountChecks = 0;
		string variablesCorrect = correctArgumentsConditionName + " = ";
		string variablesCorrectByEtalonPrefix = "" + argumentsEqualToEtalonConditionName + " = ";
		string variablesCorrectByEtalonEnding = "";

		vector<CompareMark> compare_marks = functionData.compare_marks;

		vector<vector< pair<int,int> > > checkableArgsIndexes = functionData.checkableArgsIndexes;

		int checkableArgsCount = 0;
		int currentArgumentIndex=-1;

		bool wasEtalonComparation = false;

		for(FunctionArgument arg : functionData.args)
		{
			bool isEtalonValueComparsion ;

			string arr_nama = arg.name;

			//count(i);//etalon value excist for
			//cerr <<"argCount:"<<+argCount<< "isEtalonValueComparsion:"<<isEtalonValueComparsion<<endl;
			currentArgumentIndex++;
			vector<string> args_results;
			vector<string> args_results_must_be_after_main_func;
			if ( !arg.isArray )
			{
				isEtalonValueComparsion = arg.etalonValue.size();

				if ( isEtalonValueComparsion )
					wasEtalonComparation = true;

				const string castToFloat="(float)" ;
				string currentArgDef;
				string currentArgEtalonDef;


				currentArgDef += arg.name + string(ETALON_FOR_FUNCTION_ENDING) + " = " +arg.name + " = " ;
				if (isEtalonValueComparsion)
				{
					currentArgEtalonDef += arg.name + string(ETALON_ENDING) + string(" = ") ; //etalon value for argument
				}
				if ( (functionData.lang == LangCompiler::Flag_Java || functionData.lang == LangCompiler::Flag_CS) && arg.type == ValueTypes::VAL_FLOAT)
				{
					currentArgDef+=castToFloat;
					if (isEtalonValueComparsion){
						currentArgEtalonDef+=castToFloat;
					}
				}
				string ar_value = arg.value[i];

				if (arg.type == FunctionData::RET_VAL_STRING)
					ar_value = addBracketsToStr(ar_value);

				currentArgDef +=  ar_value +";\n";
				argumentDefinition += currentArgDef;

				if (isEtalonValueComparsion)
				{
					//-`-`-`-
					string etal_val = arg.etalonValue[i];
					if (etal_val.size())
					{
						//currentArgDef += arg.name + string(ETALON_FOR_FUNCTION_ENDING) + " = " +arg.name + " = " ;
						currentArgEtalonDef += etal_val + string(";\n"); //etalon value for argu
						argumentEtalonDefinition += currentArgEtalonDef;
						if (etalongArgCountChecks > 0 )
						{//If checking of etalon already performed
							string chek_temp = variablesCorrect;
							chek_temp.erase(0, chek_temp.find("variablesCorrect = ") + 19);

							if (chek_temp.find_first_not_of("\t\n\r ") != string::npos)
								variablesCorrect += " && ";
						}
						variablesCorrect += getCompareString(arg.name,(ValueTypes) arg.type, arg.name +
								string(ETALON_ENDING), (ValueTypes)arg.type, CompareMark::Equial,
								functionData.lang);
					}
					/*else
						variablesCorrect += "true;\n";*/
				}/*
				else
				{
					variablesCorrect += "true;\n";
				}*/

			}
			else
			{

				//cerr<< "etalon_value is array\n";
				Reader reader;
				//JsonValue values_u;
				/*				JsonValue etalons_values_u;
				//reader.parse(arg.value[i], values_u);
				reader.parse(arg.etalonValue[i], etalons_values_u);
				 */

				isEtalonValueComparsion = arg.etalon_value_array.size();
				if (isEtalonValueComparsion)
					isEtalonValueComparsion = arg.etalon_value_array[i].size();

				int values_u_size = arg.size;

				//999
				for(int k = 0; k < values_u_size ; k++)
				{
					bool isEtalonValueComparsion_k  = false;
					if (isEtalonValueComparsion)
						isEtalonValueComparsion_k = (arg.etalon_value_array[i].size() > k);

					string value_i = arg.value_array[i][k];
					argumentDefinition += arg.name + string(ETALON_FOR_FUNCTION_ENDING) +
							"[" + to_string(k) + "] = " + arg.name +"[" + to_string(k) + "] = ";
					if ((functionData.lang == LangCompiler::Flag_CS || functionData.lang == LangCompiler::Flag_Java)
							&& arg.type == FunctionData::RET_VAL_FLOAT)
						argumentDefinition += " (float) ";

					argumentDefinition	+= value_i + ";\n";

					if (isEtalonValueComparsion_k)
					{
						string value = arg.etalon_value_array[i][k];
						argumentEtalonDefinition += arg.name + ETALON_ENDING + "[" + to_string(k) +
								"] = " + value + ";\n";
					}
					//"]getAllRecordsFromTable = " + etalons_values_u[i].asString() + ";\n";
				}

				if (isEtalonValueComparsion){
					if (etalongArgCountChecks > 0 )
					{//If checking of etalon already performed
						string chek_temp = variablesCorrect;
						chek_temp.erase(0, chek_temp.find("variablesCorrect = ") + 19);

						if (chek_temp.find_first_not_of("\t\n\r ") != string::npos)
							variablesCorrect += " && ";
					}
					variablesCorrect += getArrayCompareString(arg.name,arg.size, (ValueTypes) arg.type, arg.name + string(ETALON_ENDING),
							arg.size, (ValueTypes) arg.type, CompareMark::Equial, functionData.lang);

				}/*
				else
					variablesCorrect += "true;\n";*/
			}


			if(argCount>0)
			{
				argForMainFunction += divider;
				argForEtalonFunction += divider;

			}


			//string argStringValue = arg.value[i];
			string arrName = arg.name;//    "array"+std::to_string(arraysCount);

			string etalonArrName = arrName + string(ETALON_FOR_FUNCTION_ENDING);
			if (functionData.lang == LangCompiler::Flag_CS)
			{
				argForMainFunction += "ref ";
				argForEtalonFunction += "ref ";
			}
			argForMainFunction += arrName;
			argForEtalonFunction += etalonArrName;

			if (isEtalonValueComparsion){
				etalongArgCountChecks++;
			}
			argCount++;
			//for (int k=0;k<variables.size();k++)

		}

		if (variablesCorrect == correctArgumentsConditionName + " = ")
			variablesCorrect += "true;\n";

		/*if (!wasEtalonComparation)
			variablesCorrect += "true;\n";*/


		if (i<checkableArgsIndexes.size())
		{
			for (int l = 0; l < checkableArgsIndexes[i].size();l++)
			{

				//if (std::find(checkableArgsIndexes[indexOfTest].begin(),checkableArgsIndexes[indexOfTest].end(),
				int firstCheckableVariableIndex=checkableArgsIndexes[i][l].first;
				int secondCheckableVariableIndex=checkableArgsIndexes[i][l].second;
				//if (firstCheckableVariableIndex <)

				if(variables.size() < firstCheckableVariableIndex || variables.size() < secondCheckableVariableIndex)
				{
					status = (int)COMPARE_VALUE_FROM_TH;
					break;
				}
				FunctionArgument *firstGlobalVariable = &variables[firstCheckableVariableIndex];
				FunctionArgument *secondGlobalVariable = &variables[secondCheckableVariableIndex];

				if ( checkableArgsCount > 0 )
					variablesCorrectByEtalonEnding+=" && ";

				ValueTypes type1 = (ValueTypes) firstGlobalVariable->type;
				ValueTypes type2 = (ValueTypes) secondGlobalVariable->type;




				bool isFirstArray = firstGlobalVariable->isArray;
				/*ableIndex == 0)
					isFirstArray = functionData.isArray;
				else
					isFirstArray = functionData.args[firstCheckableVariableIndex].isArray;*/

				bool isSecondArray  = secondGlobalVariable->isArray;
				/*if (secondCheckableVariableIndex == 0)
					isSecondArray = functionData.isArray;
				else
					isSecondArray = functionData.args[secondCheckableVariableIndex].isArray;*/


				if (isFirstArray  && isSecondArray)
				{
					variablesCorrectByEtalonEnding += getArrayCompareString(firstGlobalVariable->name, firstGlobalVariable->size , type1,
							secondGlobalVariable->name , secondGlobalVariable->size, type2,
							CompareMark::Equial, functionData.lang);
				}
				else
				{
					variablesCorrectByEtalonEnding += getCompareString(firstGlobalVariable->name,  type1,	secondGlobalVariable->name , type2,	CompareMark::Equial, functionData.lang);
				}

				checkableArgsCount++;

			}
		}

		if (variablesCorrectByEtalonEnding.length()>1)//if comparsion conditions excists (our_func arg[i] == etalon_func arg[i])
			variablesCorrectByEtalonEnding += ";";
		else
			variablesCorrectByEtalonEnding+="true;";//condition try if comparsion need no.

		argsString += argumentDefinition;
		if (etalongArgCountChecks>0)
			argsString += argumentEtalonDefinition;



		/*if (functionData.lang == LangCompiler::Flag_Java)
			argsString+=")";*/
		//argsString +=
		string result_for_etalon = FunctionArgument::getName("result", functionData.lang) + string(ETALON_FOR_FUNCTION_ENDING);
		string etalon_s = functionData.etalon;
		bool is_etalon_func_empty = (etalon_s.find_first_not_of("\t\n\r ") == string::npos);

		if (is_etalon_func_empty)
			/*argsString += result_for_etalon + " = function_etalon(" + argForEtalonFunction +  ");\n";
		else*/
		{
			if (functionData.isArray)
			{
				//argsString += dele
				vector<string> res = functionData.result_array[i];
				for (int u = 0; u < res.size() ; u++)
				{
					string num = "[" + to_string(u) + "]";
					argsString += result_for_etalon + num + " = ";

					if (functionData.lang!=LangCompiler::Flag_JS && functionData.lang!=LangCompiler::Flag_PHP && is_float)
						argsString += " (" + FunctionArgument::generateType(FunctionData::RET_VAL_FLOAT,
								false, functionData.lang) + ") ";

					argsString += res[u] + ";\n";
				}
			}
			else
			{
				if (functionData.lang == LangCompiler::Flag_PHP)
					argsString += "$";
				argsString += "result_etalon = " + functionData.result[i] + ";\n"; //888
			}
		}
		else
		{
			string gg = FunctionArgument::getName("result" + string(ETALON_FOR_FUNCTION_ENDING), functionData.lang) +  " = function"  + ETALON_ENDING + "(" + argForEtalonFunction +  ");\n";
			argsString += gg;
		}



		string gg = FunctionArgument::getName("result", functionData.lang) +  " = " + functionData.functionName + "(" + argForMainFunction +  ");\n";
		argsString += gg;

		argsString += variablesCorrect + ";\n";
		//argsString += FunctionArgument::getName("isTrue", functionData.lang) + " = true;\n";
		argsString += variablesCorrectByEtalonPrefix+variablesCorrectByEtalonEnding;

		string ss = functionData.tests_code[i] + "\n";
		//cout << ss;
		argsString += "\n";

		ValueTypes arrType = (ValueTypes) functionData.returnValueType;
		CompareMark cmp = functionData.compare_marks[i];

		/*
		 *  HAVE RESULT?
		 */
		string true_result_name = "result_etalon";
		if(functionData.result.empty())
			true_result_name = "result_for_etalon";

		if (functionData.isArray == FunctionData::ARRAY)
		{
			string temp = "if ("  + getArrayCompareString(
					FunctionArgument::getName("result",
							functionData.lang) ,functionData.result_array_size, (ValueTypes) arrType,
							FunctionArgument::getName(true_result_name, functionData.lang),
							functionData.result_array_size, (ValueTypes) arrType,
							cmp,
							functionData.lang);
			argsString += temp;

		}
		else
		{
			string temp = "if ("  + getCompareString(FunctionArgument::getName("result ", functionData.lang)  ,	arrType,
					FunctionArgument::getName(true_result_name, functionData.lang) , arrType,
					cmp, functionData.lang);
			argsString += temp;
		}


		//if (functionData.isArray)//@WHAT@
		{
			argsString += " && " + FunctionArgument::getName("variablesCorrect", functionData.lang)
			/*+ " && " + FunctionArgument::getName("isTrue", functionData.lang)*/ + ")\n";// IF END
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

	//l12("Yura:: 00001");
	//l12(footerBody);
	return footerBody;
}

string TaskCodeGenerator::getStrToCompareTypes(string name1, string name2,  int lang)
{
	if (lang == LangCompiler::Flag_Java)
	{
		//name1 = "to_string( " + name1 + " )";
		//name1 += ".getClass().equals(" + name2 +".getClass())";
		name1 = "true";
	}
	else
		if (lang == LangCompiler::Flag_CPP)
		{
			name1 = "typeid(" + name1 + ").name() == typeid(" + name2 + ").name()";
		}
		else
			if (lang == LangCompiler::Flag_CS)
			{///***
				name1 = "Object.ReferenceEquals("+ name1 + ".GetType(), "+ name2 + ".GetType())";
			}
			else
				if (lang == LangCompiler::Flag_JS)
				{
					name1 = "typeof  " + name1 + " == typeof "+ name2 + " ";
				}
				else
					if (lang == LangCompiler::Flag_PHP)
					{
						name1 = "gettype(" + name1 + ") == gettype("+ name2 + ")";
					}
	return name1;
}

string TaskCodeGenerator::convertAnyToString(string name1,  ValueTypes type1, int lang)
{
	if (lang == LangCompiler::Flag_Java)
	{
		//name1 = "to_string( " + name1 + " )";
		name1 = "String.valueOf(" + name1 + " )";

	}
	else
		if (lang == LangCompiler::Flag_CPP)
		{
			if (type1 != ValueTypes::VAL_STRING)
				name1 = "to_string(" + name1 + ")";
		}
		else
			if (lang == LangCompiler::Flag_CS)
			{
				name1 = "Convert.ToString(" + name1 + ")";
			}
			else
				if (lang == LangCompiler::Flag_JS)
				{
					name1 = "safeToString(" + name1 + ")";
				}
				else
					if (lang == LangCompiler::Flag_PHP)
					{
						name1 = "(string)" + name1;
					}
	return name1;
}

string TaskCodeGenerator::getCompareString(string name1,  ValueTypes type1,string name2,  ValueTypes type2, CompareMark mark, int lang)
{
	string result = "( ";
	if ((int)type1 != (int) type2) //equial type
	{
		name1 = convertAnyToString(name1, type1, lang);
		name2 = convertAnyToString(name2, type2, lang);
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
		result += floorFuncName+"(" + name1 + " * 100 ) - "+floorFuncName+"(" + name2 + " * 100 )  ";
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
				result +=  name1 + " == " + name2 + " )";//////////////////////
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
					result = "String.Compare(" + name1 + ", " + name2 + ", StringComparison.CurrentCulture) <= 0";
					//result = name1 + ".Compare(" + name2 +") <= 0";
					break;
				case CompareMark::Less:
					//result += name1 + ".Compare(" + name2 +") < 0";
					result = "String.Compare(" + name1 + ", " + name2 + ", StringComparison.CurrentCulture) < 0";
					break;
				case CompareMark::Equial: default:
					result += "String.Equals (" + name1 + ", " + name2 +"))";
					//result = "String.Compare(" + name1 + ", " + name2 + ", StringComparison.CurrentCulture) == 0";
					break;
				case CompareMark::NotEquial:
					result = "!String.Equals (" + name1 + ", " + name2 +", StringComparison.Ordinal)"; //,
					//result = "String.Compare(" + name1 + ", " + name2 + ", StringComparison.CurrentCulture) != 0";
					break;
				case CompareMark::More:
					//result += name1 + ".Compare(" + name2 +") > 0";
					result = "String.Compare(" + name1 + ", " + name2 + ", StringComparison.CurrentCulture) > 0";
					break;
				case CompareMark::MoreEquial:
					//result += name1 + ".Compare(" + name2 +") >= 0";
					result = "String.Compare(" + name1 + ", " + name2 + ", StringComparison.CurrentCulture) >= 0";
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
						result += "(new String(" + name1 + ").compareTo(" + name2 +")) <= 0)";
						break;
					case CompareMark::Less:
						result += "(new String(" + name1 + ").compareTo(" + name2 +")) < 0)";
						break;
					case CompareMark::Equial: default:
						result += "new String(" + name1 + ").equals(" + name2 +"))";
						break;
					case CompareMark::NotEquial:
						result += "!(new String(" + name1 + ").equals(" + name2 +"))";
						break;
					case CompareMark::More:
						result += "(new String(" + name1 + ").compareTo(" + name2 +")) > 0)";
						break;
					case CompareMark::MoreEquial:
						result += "(new String(" + name1 + ").compareTo(" + name2 +")) >= 0)";
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
	return result += " && " + getStrToCompareTypes(name1,name2,lang);
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
			//return " ( is_array(" + name1 + ") && is_array (" + name2 + ") && count(array_diff(" + name1 + "," + name2 + ")) == 0)";
			return " " + name1 + " === " + name2 + " ";
		case LangCompiler::Flag_CS:
			return string( "ArraysEqual(" + name1 + ", " +  name2 + ")");
			break;

		}

	}
}

bool TaskCodeGenerator::generateVariables(string &output, FunctionData functionData, vector<FunctionArgument> &variables)
{
	bool is_result_array = functionData.isArray;
	int result_array_size = 0;
	if (is_result_array)
		result_array_size = functionData.result_array_size;

	FunctionArgument resultVar;
	resultVar.name=FunctionArgument::getName("result", functionData.lang);
	resultVar.isArray=functionData.isArray;
	resultVar.size = functionData.result_array_size;
	resultVar.type = functionData.returnValueType;

	string res_def = resultVar.generateDefinition(true, functionData.lang); //if true, it will be "type * result;", else "type result[size];"
	output += res_def;
	variables.push_back(resultVar);

	resultVar.name += ETALON_ENDING;
	output += resultVar.generateDefinition(false, functionData.lang);
	variables.push_back(resultVar);

	resultVar.name = FunctionArgument::getName("result", functionData.lang) +  string(ETALON_FOR_FUNCTION_ENDING);
	output += resultVar.generateDefinition(false, functionData.lang);
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

string TaskCodeGenerator::generateInputParametersString(FunctionData functionData)
{
	string inputParam = "";

	return inputParam;

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
		#include <string.h>\n";
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

string FunctionArgument::generateType(int type, int arrayType, int lang,  bool return_or_param)
{
	if (lang==LangCompiler::Flag_PHP) return " ";//arg types specify not in PHP
	if (lang==LangCompiler::Flag_JS) return "var";//arg types specify not in js
	string result = "";

	switch(type)
	{
	case FunctionData::RET_VAL_BOOL:
		if (lang == (int) LangCompiler::Flag_Java)
		{
			result +=  "boolean";
			/*if (return_or_param)
				result +=  "boolean";
			else
				result +=  "Boolean";*/
		}
		else
			result += "bool";
		break;
	case FunctionData::RET_VAL_FLOAT:
		if (lang == (int) LangCompiler::Flag_Java)
		{
			result +=  "float";
			/*if (return_or_param)
				result +=  "float";
			else
				result +=  "Float";*/
		}
		else
			result += "float";
		break;
	case FunctionData::RET_VAL_INT:
		if (lang == (int) LangCompiler::Flag_Java)
		{
			result +=  "int";
			/*if (return_or_param)
				result +=  "int";
			else
				result +=  "Integer";*/
		}
		else
			result += "int";
		break;
	case FunctionData::RET_VAL_STRING:
		if (lang == (int) LangCompiler::Flag_Java)
		{
			result +=  "String";
			/*	if (return_or_param)
				result +=  "string";
			else
				result +=  "String";*/
		}
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

string FunctionArgument::generateDefinition(bool is_result, int lang, bool return_or_param)
{
	string stype = generateType(type, false, lang,return_or_param);
	string result = stype;
	switch( lang)
	{
	case LangCompiler::Flag_CPP:
		if (isArray)
		{
			if (is_result)
				result += " *" + name + " = new " + stype + "[" +  std::to_string(size) + "]";
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

