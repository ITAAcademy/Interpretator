/*
 * parseChekableArgIndexes.cpp
 *
 *  Created on: Mar 30, 2016
 *      Author: name
 */



#include "../inc/jsonParser.h"
#include "../inc/TaskCodeGenerator.h"


bool jsonParser::parseChekableArgIndexes(Value function )
{
	int i = 0;
	Value chekable = function["checkable_args_indexes"];
	if (!mustExist(chekable, "checkable_args_indexes"))
		return false;

	for (Value arg_indexes_pares_arr : chekable)
	{
		int j = 0;
		vector<pair<int,int>> testConditionPares;
		for (Value arg_indexes_pair : arg_indexes_pares_arr )
		{
			Value f_value = arg_indexes_pair["first"];
			Value s_value = arg_indexes_pair["second"];

			if (!mustExist(f_value, "first"))
			{
				last_error = "ERROR: json format is not correct. unit test[" + to_string(i) + "] pair[" + to_string(j) +
						"] first not exist";
				return false;
			}

			if (!mustExist(s_value, "second"))
			{
				last_error = "ERROR: json format is not correct. unit test[" + to_string(i) + "] pair[" + to_string(j) +
						"] second not exist";
				return false;
			}

			if (!mustBeInt(f_value, "first"))
			{
				last_error = "ERROR: json format is not correct. unit test[" + to_string(i) + "] pair[" + to_string(j) +
						"] first not convertible to int";
				return false;
			}

			if (!mustBeInt(s_value, "second"))
			{
				last_error = "ERROR: json format is not correct. unit test[" + to_string(i) + "] pair[" + to_string(j) +
						"] second not convertible to int";
				return false;
			}
			j++;
		}
		i++;
	}
	return true;
}
