/*
 * generateFunctionProtorype.cpp
 *
 *  Created on: Apr 6, 2016
 *      Author: name
 */
#include "../inc/TaskCodeGenerator.h"


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
