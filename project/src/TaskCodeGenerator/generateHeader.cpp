/*
 * generateHeader.cpp
 *
 *  Created on: Apr 6, 2016
 *      Author: name
 */

#include "../inc/TaskCodeGenerator.h"


string TaskCodeGenerator::generateHeader(FunctionData functionData){

	string headerStr = getStandartInclude(functionData.lang) + "\n";

	if (functionData.lang == LangCompiler::Flag_CPP)
	{
		headerStr += "#define STUDENTCODE_23_23_90_0 66\n";
		headerStr += "#ifdef STUDENTCODE_23_23_90_0\n";

		headerStr += "#define printf(fmt, ...) (0)\n";
		headerStr += "#define fprintf(fmt, ...) (0)\n";
		headerStr += "#define scanf(fmt, ...) (0)\n";
		headerStr += "#define fcanf(fmt, ...) (0)\n";

		headerStr += "#define puts(fmt, ...) (0)\n";
		headerStr += "#define perror(fmt, ...) (0)\n";
		headerStr += "#define fgetc(fmt, ...) (0)\n";
		headerStr += "#define putchar(fmt, ...) (0)\n";
		headerStr += "#define fputs(fmt, ...) (0)\n";
		headerStr += "#define cin(fmt, ...) (0)\n";
		headerStr += "#define system 33\n";
		headerStr += "#define popen 33\n";
		headerStr += "#define fopen 33\n";
		headerStr += "#define pipe 33\n";
		//headerStr += "#define fstream 33\n";
		//headerStr += "#define ifstream 33\n";
		headerStr += "#endif\n";
	}
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
	if (functionData.lang == LangCompiler::Flag_Java)
	{
		headerStr += "try {\n";
	}

	/*l12("Yura: 2202:");
	//l12(headerStr);*/
	return headerStr;
}


