/*
 * generateFooter.cpp
 *
 *  Created on: Apr 6, 2016
 *      Author: name
 */

#include "../inc/TaskCodeGenerator.h"



string TaskCodeGenerator::generateFooter(FunctionData functionData)
{
	vector<FunctionArgument> variables;
	//int lang, int returnValueType, int isArray

	string defaultReturnValue = generateDefaultReturnValue(functionData.lang, functionData.returnValueType, functionData.isArray);

	string footerBody = "";
	if (functionData.lang == LangCompiler::Flag_Java)
	{
		footerBody += "\n} catch (ArithmeticException e) {  System.err.print(\"*** \" + e.getMessage() + \" ***\" ); }\n";
	}

	footerBody += "return "+defaultReturnValue+";\n}\n";//Close function body

	footerBody += generateFunctionProtorype(functionData, "function_etalon"); //create prototype for etalon function
	footerBody += "{\n" ;//+ functionData.etalon;
	//+ "return "+defaultReturnValue+";\n}\n"; // add etalon function

	/*if ((functionData.etalon.find_first_not_of("\t\n\r ") == string::npos))
		footerBody += "return "+defaultReturnValue+";\n}\n";
	else
		footerBody += "\n}\n";*/

	if (functionData.lang == LangCompiler::Flag_Java)
	{
		footerBody += "try {\n" + functionData.etalon + "\n} catch (ArithmeticException e) {  System.err.print(\"*** \" + e.getMessage() + \" ***\" ); }\n";
	}
	else
		footerBody += functionData.etalon;

	footerBody += "return "+defaultReturnValue+";\n}\n";

	string space=" ";
	char divider=',';
	string results_arguments_comparing_after_main_func = FunctionArgument::generateType(ValueTypes::VAL_BOOL, false, functionData.lang) + " results_arguments_comparing_after_main_func = true";
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
		arrCompFuncStr = "alert = function() {};\n";
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
		footerBody+="#undef STUDENTCODE_23_23_90_0\n\
		int main()\n\
					{\n";
		break;
	case LangCompiler::Flag_Java: //@BAD@
		footerBody+="public static void main(String[] args)\n\
{\n";
		break;

	case LangCompiler::Flag_CS:
		footerBody+="public static void Main(String[] args)\n\
		{\n\
				TextReader textr_reader = new StringReader(\"wdfqwdfqwdfwqdfwqfeqwef\");\n\
				FileStream fs = new FileStream(\"cout.txt\", FileMode.Create);\n\
				TextWriter tmp = Console.Out;\n\
				TextWriter couta = Console.Out ;\n\
				StreamWriter sw = new StreamWriter(fs);\n";
		break;
	}

	string variable_s;
	generateVariables(variable_s, functionData, variables);

	footerBody += variable_s;
	if (functionData.lang == LangCompiler::Flag_CPP)
	{
		footerBody += "std::streambuf* cout_sbuf = std::cout.rdbuf(); // save original sbuf\n\
	    std::ofstream   fout(\"/dev/null\");\n";

		footerBody += "std::ofstream   fin(\"/dev/null\");\n\
	std::cin.rdbuf(fin.rdbuf()); // redirect 'cout' to a 'fout';\n\n";
	}

	string correctArgumentsConditionName = FunctionArgument::getName("variablesCorrect", functionData.lang);
	string argumentsEqualToEtalonConditionName = FunctionArgument::getName("variablesCorrectByEtalon", functionData.lang);

	string type_n = FunctionArgument::generateType(ValueTypes::VAL_BOOL, false, functionData.lang) + " ";

	/*	footerBody +=  type_n
			+  FunctionArgument::getName("isTrue", functionData.lang) + ";\n";//moved out from cicle to fix variable duplicates
	 */
	/*string conditionsVariableDeclaration = type_n +" "+
			argumentsEqualToEtalonConditionName+";\n" + type_n + " " + correctArgumentsConditionName+";\n";*/
	///+++
	string conditionsVariableDeclaration = FunctionArgument::generateDefinition( true,functionData.lang,
			correctArgumentsConditionName, ValueTypes::VAL_BOOL);

	footerBody+= conditionsVariableDeclaration;

	string conditionsVariableDeclarationEtalon = FunctionArgument::generateDefinition( true,functionData.lang,
			argumentsEqualToEtalonConditionName, ValueTypes::VAL_BOOL);

	footerBody+= conditionsVariableDeclarationEtalon;

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
				if ((functionData.lang == LangCompiler::Flag_CS) && (functionData.returnValueType == ValueTypes::VAL_FLOAT))
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
							argsString += " (" + FunctionArgument::generateType(ValueTypes::VAL_FLOAT, false, functionData.lang) + ") ";
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

				if (arg.type == ValueTypes::VAL_STRING)
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
							&& arg.type == ValueTypes::VAL_FLOAT)
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
						argsString += " (" + FunctionArgument::generateType(ValueTypes::VAL_FLOAT,
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
			string gg = "";
			if (functionData.lang == LangCompiler::Flag_CPP)
			{
				gg = "std::cout.rdbuf(fout.rdbuf()); // redirect 'cout' to a 'fout';\n\n"; //--1
				gg += "std::cerr.rdbuf(fout.rdbuf()); // redirect 'cout' to a 'fout'\n\n"; //--1
				string text = FunctionArgument::getName("result" + string(ETALON_FOR_FUNCTION_ENDING), functionData.lang)
				+  " = function"  + ETALON_ENDING + "(" + argForEtalonFunction +  ");\n";
				gg += text;
				gg += "std::cout.rdbuf(cout_sbuf); // restore the original stream buffer\n";
				gg += "std::cerr.rdbuf(cout_sbuf); // restore the original stream buffer\n";
			}
			else
				if (functionData.lang == LangCompiler::Flag_PHP)
				{
					gg += " ob_start();\n";
					gg += FunctionArgument::getName("result" + string(ETALON_FOR_FUNCTION_ENDING), functionData.lang)
					+  " = function"  + ETALON_ENDING + "(" + argForEtalonFunction +  ");\n";

					gg += " ob_end_clean();\n";
				}
				else
					if (functionData.lang == LangCompiler::Flag_JS)
					{
						gg += "var KGGKHhgkgkKhgGKkhjKgkgKgKHGkJGJKGkGJKKKGJkGJ98889888898988 = console.log;\n\
								console.log = function() {}\n";
						gg += FunctionArgument::getName("result" + string(ETALON_FOR_FUNCTION_ENDING), functionData.lang)
						+  " = function"  + ETALON_ENDING + "(" + argForEtalonFunction +  ");\n";
						gg += "console.log = KGGKHhgkgkKhgGKkhjKgkgKgKHGkJGJKGkGJKKKGJkGJ98889888898988;\n";
					}
					else
						if (functionData.lang == LangCompiler::Flag_CS)
						{
							gg += " Console.SetIn(textr_reader);\n\
							    Console.SetOut(sw);\n\
							    Console.SetError(sw);\n";
							gg += FunctionArgument::getName("result" + string(ETALON_FOR_FUNCTION_ENDING), functionData.lang)
							+  " = function"  + ETALON_ENDING + "(" + argForEtalonFunction +  ");\n";
							gg += "Console.SetOut(couta);\n";
						}
						else
							if (functionData.lang == LangCompiler::Flag_Java  && false)
							{
								gg = "try {\n\
					PrintStream stream = new PrintStream(new FileOutputStream(new File(\"cout.txt\")));\n\
				System.setOut(stream);\n\
				System.setErr(stream);\n\
				} \n\
				catch (FileNotFoundException e) {}\n";
								gg += FunctionArgument::getName("result" + string(ETALON_FOR_FUNCTION_ENDING), functionData.lang)
								+  " = function"  + ETALON_ENDING + "(" + argForEtalonFunction +  ");\n";
							}
							else
								gg += FunctionArgument::getName("result" + string(ETALON_FOR_FUNCTION_ENDING), functionData.lang)
			+  " = function"  + ETALON_ENDING + "(" + argForEtalonFunction +  ");\n";
			argsString += gg;
		}


		string gg = "";
		if (functionData.lang == LangCompiler::Flag_CPP)
		{
			gg = "std::cout.rdbuf(fout.rdbuf()); // redirect 'cout' to a 'fout';\n"; //--1
			gg += "std::cerr.rdbuf(fout.rdbuf()); // redirect 'cout' to a 'fout';\n"; //--1
			string text = FunctionArgument::getName("result", functionData.lang) +  " = " + functionData.functionName + "(" + argForMainFunction +  ");\n";
gg += text;
			gg += "std::cout.rdbuf(cout_sbuf); // restore the original stream buffer\n";
			gg += "std::cerr.rdbuf(cout_sbuf); // restore the original stream buffer\n";
		}
		else
			if (functionData.lang == LangCompiler::Flag_PHP)
			{
				gg += " ob_start();\n";
				gg += FunctionArgument::getName("result", functionData.lang) +  " = " + functionData.functionName + "(" + argForMainFunction +  ");\n";

				gg += " ob_end_clean();\n";
			}
			else
				if (functionData.lang == LangCompiler::Flag_CS )
				{
					gg += " Console.SetIn(textr_reader);\n\
				    Console.SetOut(sw);\n\
				    Console.SetError(sw);\n";
					gg += FunctionArgument::getName("result", functionData.lang) +  " = " + functionData.functionName + "(" + argForMainFunction +  ");\n";
					gg += "Console.SetOut(couta);\n";
				}
				else
					if (functionData.lang == LangCompiler::Flag_JS)
					{
						gg += "var KGGKHhgkgkKhgGKkhjKgkgKgKHGkJGJKGkGJKKKGJkGJ98889888898988 = console.log;\n\
								console.log = function() {}\n";
						gg += FunctionArgument::getName("result", functionData.lang) +  " = " + functionData.functionName + "(" + argForMainFunction +  ");\n";
						gg += "console.log = KGGKHhgkgkKhgGKkhjKgkgKgKHGkJGJKGkGJKKKGJkGJ98889888898988;\n";
					}
					else
						if (functionData.lang == LangCompiler::Flag_Java && is_etalon_func_empty && false)
						{
							gg = "try {\n\
								PrintStream stream = new PrintStream(new FileOutputStream(new File(\"cout.txt\")));\n\
							System.setOut(stream);\n\
							System.setErr(stream);\n\
							} \n\
							catch (FileNotFoundException e) {}\n";
							gg += FunctionArgument::getName("result", functionData.lang) +  " = " + functionData.functionName + "(" + argForMainFunction +  ");\n";
						}
						else
							gg += FunctionArgument::getName("result", functionData.lang) +  " = " + functionData.functionName + "(" + argForMainFunction +  ");\n";

		if (functionData.lang == LangCompiler::Flag_Java)
		{
			gg += "System.setOut(new PrintStream(new FileOutputStream(FileDescriptor.out)));\n";
		}


		argsString += gg;

		argsString += variablesCorrect + ";\n";
		//argsString += FunctionArgument::getName("isTrue", functionData.lang) + " = true;\n";
		argsString += variablesCorrectByEtalonPrefix+variablesCorrectByEtalonEnding;

		string ss = functionData.tests_code[i] + "\n";
		//cout << ss;
		argsString += "\n";

		//if (functionData.lang == LangCompiler::Flag_CPP && init_disable_cout)
		//argsString += "std::cout.rdbuf(cout_sbuf); // restore the original stream buffer\n"; //-2

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
			+ " && " + FunctionArgument::getName("variablesCorrectByEtalon", functionData.lang)
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
