/*
 * mergeUtestsAndTask.cpp
 *
 *  Created on: Apr 1, 2016
 *      Author: name
 */


#include "../inc/main.h"


string mergeUtestsAndTask(Json::Value& tests, Json::Value& task) {
	Value task_unit_test_num = task[FUNCTION][FIELD_UNIT_TESTS_NUM];

	Value tests_unit_test_num = tests[FUNCTION][FIELD_UNIT_TESTS_NUM];


	int task_unit_test_num_int = jsonParser::getAsInt(task_unit_test_num);
	int tests_unit_test_num_int = jsonParser::getAsInt(tests_unit_test_num);

	task_unit_test_num_int += tests_unit_test_num_int;

	string checkable_args_indexes_task = task[FUNCTION]["checkable_args_indexes"].toStyledString();
	int length = checkable_args_indexes_task.size();
	checkable_args_indexes_task.erase(length - 2, length - 1);

	string checkable_args_indexes_tests = tests[FUNCTION]["checkable_args_indexes"].toStyledString();
	length = checkable_args_indexes_tests.size();
	checkable_args_indexes_tests.erase(0, 1);

	checkable_args_indexes_task += ","  + checkable_args_indexes_tests;

	/////////////////////

	string results_task = task[FUNCTION]["results"].toStyledString();
	length = results_task.size();
	results_task.erase(length - 2, length - 1);

	string results_tests = tests[FUNCTION]["results"].toStyledString();
	length = results_tests.size();
	results_tests.erase(0, 1);

	results_task +=  ","  +  results_tests;

	////////////////

	string compare_mark_task = task[FUNCTION]["compare_mark"].toStyledString();
	length = compare_mark_task.size();
	compare_mark_task.erase(length - 2, length - 1);

	string compare_mark_tests = tests[FUNCTION]["compare_mark"].toStyledString();
	length = compare_mark_tests.size();
	compare_mark_tests.erase(0, 1);

	compare_mark_task += ","  +  compare_mark_tests;

	//////////////////////////// args
	Value task_args = task[FUNCTION][FIELD_ARGS];
	Value tests_args = tests[FUNCTION][FIELD_ARGS];
	string args = "";
	for (int i = 0; i < task_args.size(); i++)
	{
		if (i > 0)
			args += ",\n";

		///values
		string task_value = jsonParser::getAsString(task_args[i][FIELD_VALUE]);
		length = task_value.size();
	//	task_value.erase(0, 1);
		task_value.erase(length - 2, length - 1);

		string tests_value = jsonParser::getAsString(tests_args[i][FIELD_VALUE]);
		length = tests_value.size();
		tests_value.erase(0, 1);

		task_value += ","  +  tests_value;

		//////////////

		string task_etalon_value = jsonParser::getAsString(task_args[i][FIELD_ETALON_VALUE]);
		length = task_etalon_value.size();
		task_etalon_value.erase(length - 2 , length - 1);

		string tests_etalon_value = jsonParser::getAsString(tests_args[i][FIELD_ETALON_VALUE]);
		length = tests_etalon_value.size();
		tests_etalon_value.erase(0, 1);

		task_etalon_value += ", " +  tests_etalon_value;

		/////////////////////
		string task_compare_mark = jsonParser::getAsString(task_args[i][FIELD_COMPARE_MARK]);
		length = task_compare_mark.size();
		task_compare_mark.erase(length - 2, length - 1);

		string tests_compare_mark = jsonParser::getAsString(tests_args[i][FIELD_COMPARE_MARK]);
		length = tests_compare_mark.size();
		tests_compare_mark.erase(0, 1);

		task_compare_mark += ","  +  tests_compare_mark;

		////////////////

		//string tests_value = jsonParser::getAsString(task_args[i][FIELD_VALUE]);


		args += "{ \n \"" + string(FIELD_TYPE) + "\": " + jsonParser::getAsString(task_args[i][FIELD_TYPE]) + ",\n";
		args += "\"" +  string(FIELD_SIZE) + "\": " + jsonParser::getAsString(task_args[i][FIELD_SIZE]) + ",\n";
		args += "\"" +  string(FIELD_ARG_NAME) + "\": \"" + jsonParser::getAsString(task_args[i][FIELD_ARG_NAME]) + "\",\n";
		args += "\"" +  string(FIELD_TYPE) + "\": " + jsonParser::getAsString(task_args[i][FIELD_TYPE]) + ",\n";
		args += "\"pattern\": {},\n";
		args += "\"" +  string( FIELD_VALUE) + "\": " +  task_value + ",\n";
		args += "\"" +  string(FIELD_IS_ARRAY) + "\": " + jsonParser::getAsString(task_args[i][FIELD_IS_ARRAY]) + ",\n";
		args += "\"" +  string(FIELD_ETALON_VALUE) + "\": " + task_etalon_value + ",\n";
		args += "\"" +  string(FIELD_COMPARE_MARK) + "\": " + task_compare_mark + "\n\}\n	";
	}

	//////////////////////////

	string temp_test_code = "\"\"";
	for (int i = 1; i < task_unit_test_num_int; i++)
	{
		temp_test_code += ", \"\"";
	}


	///////////////////////

	string output = "{\n \"" + string(FIELD_OPERATION) +  "\": \"addtask\", \n\
    	\"" + string(FIELD_ETALON) + "\" : \""	+ jsonParser::getAsString(task[FIELD_ETALON]) + "\", \n\
    	\"" + string(FIELD_TASK_ID) + "\" : \"3000\", \n";// //jsonParser::getAsString(task[FIELD_TASK_ID])
	output +=  "\"" + string(FIELD_CODE_LANGUAGE) + "\": \"" +	 jsonParser::getAsString(task[FIELD_CODE_LANGUAGE]);
	output +=  "\", \n\
    	\""  + string(FUNCTION) + "\": { \n\
    	\"" + string(FIELD_FUNCTION_NAME) + "\" : \"" + jsonParser::getAsString(task[FUNCTION][FIELD_FUNCTION_NAME]) + "\",\n";

	output += "\"" + string(FIELD_TYPE) + "\": " + jsonParser::getAsString(task[FUNCTION][FIELD_TYPE]) + ",\n";

	output += " \"" + string(FIELD_ARRAY_TYPE) + "\" : " + jsonParser::getAsString(task[FUNCTION][FIELD_ARRAY_TYPE]) + ",\n";

	output += "\"" + string(FIELD_SIZE) + "\" : " + jsonParser::getAsString(task[FUNCTION][FIELD_SIZE ]) + ",\n";
	output += "\"" + string(FIELD_UNIT_TESTS_NUM) + "\" : " + to_string(task_unit_test_num_int) + ",\n\
	\"checkable_args_indexes\" : " + checkable_args_indexes_task + ",\n\"" +
	string(FIELD_RESULTS) + "\" : " + results_task + ",\n\""
	+ string(FIELD_COMPARE_MARK) + "\" : " + compare_mark_task + ",\n\
	   \"tests_code\": [" + temp_test_code + "], \n\""
	   +string( FIELD_ARGS) + "\": [" + args + "]\n\
   },\n\"name\": " + task["name"].toStyledString() +  "}";


	//Value rezul_value(output);
	return output;
}


