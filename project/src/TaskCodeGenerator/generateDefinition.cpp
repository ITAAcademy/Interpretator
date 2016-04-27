/*
 * generateDefinition.cpp
 *
 *  Created on: Apr 6, 2016
 *      Author: name
 */


#include "../inc/TaskCodeGenerator.h"

string FunctionArgument::generateDefinition(bool return_or_param, int lang ,string name, int type)
{
	FunctionArgument arg;
	arg.name = name;
	arg.type = type;
	string definition =  arg.generateDefinition(return_or_param,lang);
	return definition;
}


string FunctionArgument::generateDefinition(bool return_or_param, int lang )
{
	string stype = generateType(type, false, lang,return_or_param);
	string result = stype;
	switch( lang)
	{
	case LangCompiler::Flag_CPP:
		if (isArray)
		{
			if (!return_or_param)
				result += " *" + name + " = new " + stype + "[" +  std::to_string(size) + "]";
			else
				result += " " + name + " [" + std::to_string(size) + "]";
		}
		else
		{
			result += " " +  name;
			switch(type)
			{
			case ValueTypes::VAL_BOOL:
				result += " = true";
				break;
			}
		}
		break;


	case LangCompiler::Flag_Java: case LangCompiler::Flag_CS:
		if (isArray)
		{
			result += " [] " + name;
			if ( !return_or_param )
				result += " = new " + stype + " [" + std::to_string(size) + "]";
		}
		else
		{
			result += " " +  name;
			switch(type)
			{
			case ValueTypes::VAL_BOOL:
				result += " = true";
				break;
			case ValueTypes::VAL_STRING:
				result += " = \"\"";
				break;
			case ValueTypes::VAL_CHAR:
				result += " = ''";
				break;
			case ValueTypes::VAL_FLOAT:
				result += " = 0";
				break;
			case ValueTypes::VAL_INT:
				result += " = 0";
				break;
			}
		}
		break;

	case LangCompiler::Flag_JS:
		result += " " + name;
		if (isArray)result += "=[]";
		else
		{
			switch(type)
			{
			case ValueTypes::VAL_BOOL:
				result += " = true";
				break;

			}
			break;
		}
	case LangCompiler::Flag_PHP:
		result += " " + name;
		if (isArray)
			result += " = []";
		else
			result += " = 1";
		//if (isArray)result += "=[]";
		break;


	}
	result += ";\n";
	return result;
}




