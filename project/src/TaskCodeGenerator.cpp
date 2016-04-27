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
							if (functionData.returnValueType == ValueTypes::VAL_STRING)
								as_str = addBracketsToStr(as_str);
							res.push_back( as_str);
							//functionValue[FIELD_RESULTS][k][b].asString() );
						}

						functionData.result_array.push_back(res);
					}
					else
					{
						string as_str = jsonParser::getAsString(functionValue[FIELD_RESULTS][k]);
						if (functionData.returnValueType == ValueTypes::VAL_STRING)
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
					if (functionArgument.type == ValueTypes::VAL_STRING)
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
							if (functionArgument.type ==  ValueTypes::VAL_STRING)
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
						if (functionArgument.type == ValueTypes::VAL_STRING && value_s.size() > 0)
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




string TaskCodeGenerator::generateDefaultReturnValue(int lang, int returnValueType, int isArray)
{
	string defaultReturnValue = "";
	if (lang==LangCompiler::Flag_Java)//What
	{
		defaultReturnValue = "";
		switch (returnValueType)
		{
		case ValueTypes::VAL_BOOL:
			if (isArray == 0)
				defaultReturnValue +=" false";
			else
				if (isArray == 1)
					defaultReturnValue +=" new boolean[]{false}";
			break;

		case ValueTypes::VAL_FLOAT:
			if (isArray == 0)
				defaultReturnValue +=" 98989.9898889898";
			else
				if (isArray == 1)
					defaultReturnValue +=" new float[]{0}";
			break;

		case ValueTypes::VAL_INT:
			if (isArray == 0)
				defaultReturnValue +=" 65533";
			else
				if (isArray == 1)
					defaultReturnValue +=" new int[]{0}";
			break;

		case ValueTypes::VAL_STRING:
			if (isArray == 0)
				defaultReturnValue +=" \"qhejih34213	ed	qe013413\"";
			else
				if (isArray == 1)
					defaultReturnValue +=" new string[]{\"asdfasdaq4rrea\"}";
			break;
		case ValueTypes::VAL_CHAR:
			if (isArray == 0)
				defaultReturnValue +=" '?'";
			else
				if (isArray == 1)
					defaultReturnValue +=" new char[]{'?'}";
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
				name1 = "std::to_string(" + name1 + ")";
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

		case VAL_INT: case VAL_CHAR:
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
						result += "new String(" + name1 + ").equals(" + name2 +"))";///
						break;
					case CompareMark::NotEquial:
						result += "!(new String(" + name1 + ").equals(" + name2 +")))";
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

	string res_def = resultVar.generateDefinition(false, functionData.lang); //if false, it will be "type * result;", else "type result[size];"
	output += res_def;
	variables.push_back(resultVar);

	resultVar.name += ETALON_ENDING;
	output += resultVar.generateDefinition(true, functionData.lang);
	variables.push_back(resultVar);

	resultVar.name = FunctionArgument::getName("result", functionData.lang) +  string(ETALON_FOR_FUNCTION_ENDING);
	output += resultVar.generateDefinition(false, functionData.lang);
	variables.push_back(resultVar);


	for(FunctionArgument arg : functionData.args)
	{
		output += arg.generateDefinition(true, functionData.lang);
		variables.push_back(arg);

		FunctionArgument etalonArg = arg;
		etalonArg.name+=ETALON_ENDING;
		output += etalonArg.generateDefinition(true, functionData.lang);
		variables.push_back(etalonArg);

		FunctionArgument etalonForFunctionArg = arg;
		etalonForFunctionArg.name +=string(ETALON_FOR_FUNCTION_ENDING);
		output += etalonForFunctionArg.generateDefinition(true, functionData.lang);
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
		include = "#include <cstdlib>\n\
		#include <algorithm>\n using namespace std;\n\
		#include <cxxabi.h>\n\
		#include <cmath>\n\
		#include <stdio.h>\n\
		#include <string.h>\n";
		break;
	}
	case LangCompiler::Flag_Java:{
		include = "import java.util.Arrays;\n\
		import java.io.File;\n\
		import java.io.FileDescriptor;\n\
		import java.io.FileNotFoundException;\n\
		import java.io.FileOutputStream;\n\
		import java.io.IOException;\n\
		import java.io.PrintStream;\n";
		//...
		break;
	}
	case LangCompiler::Flag_CS:
		include = "using System;\n\
				using System.Collections.Generic;\n\
				using System.Collections;\n\
				using System.IO;\n\
				using System.Text;\n";
		break;
	}
	return include + "\n";

}

string TaskCodeGenerator::convertStringToType(string argStringValue, int type, int lang)
{
	string result;
	switch(type){
	case ValueTypes::VAL_BOOL:
			result += to_bool(argStringValue);
			break;
		case ValueTypes::VAL_FLOAT:
			result += argStringValue.c_str();
			break;
		case ValueTypes::VAL_INT:
			result += argStringValue.c_str();
			break;
		case ValueTypes::VAL_STRING:
			result += argStringValue;
			break;
		case ValueTypes::VAL_CHAR:
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
	case ValueTypes::VAL_BOOL:
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
		case ValueTypes::VAL_FLOAT:
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
		case ValueTypes::VAL_INT:
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
		case ValueTypes::VAL_STRING:
			if (lang == (int) LangCompiler::Flag_Java)
			{
				result +=  "String";
			}
			else
				result += "string";
			break;
		case ValueTypes::VAL_CHAR:
						result += "char";
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



}
