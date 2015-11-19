/*
 * jsonParser.cpp
 *
 *  Created on: Jun 3, 2015
 *      Author: root
 */

#include "inc/jsonParser.h"

jsonParser::jsonParser(string json)
{
	bJsonValid = setJson(json);
}

jsonParser::jsonParser()
{
	json.clear();
}

jsonParser::~jsonParser() {
	// TODO Auto-generated destructor stub
}

bool jsonParser::setJson(string in_json)
{
	if(!reader.parse(in_json, parsedFromString) || in_json.find('{') == string::npos)
	{
		json.clear();
		bJsonValid = false;
		return false;
	}
	json = in_json;
	bJsonValid = true;
	return true;

}
Value jsonParser::getObject(string name, bool everyWhere = false)
{

	/*	JSOOOOOOOOOOON
	 * 				if(!parsedFromString["root"].isNull())

					Value v1 = parsedFromString["root"];
					Value v = v1["values"];
					if(v.isArray())
					{
						for(unsigned int index=0; index<v.size(); ++index)
						{
							cout << v[index].toStyledString();
						}
					}
				}
				else cout << "==============================================NULL";
	 */
	t_find.clear();
	if(!json.empty())
	{
		if(!everyWhere)
			return parsedFromString.get(name, Value::null);;
		return findInArray(parsedFromString, name);
	}
	else
		logfile::addLog("Error Json parse, input string is empty");
}

Value jsonParser::findInArray(Value &array, string &name)
{
	const Value null = "NULL";
	Value res = array.get(name, Value::null);

	if(!res.isNull())
		return res;
	int size = array.size();

	logfile::addLog("ARR " + name + "size" + to_string(array.size()));
	/*string stt;
	stt.append("ALL NUMBERS::	\n");
	for(int i = 0; i < array.getMemberNames().size(); i++)
	{
		stt.append(array.getMemberNames()[i] + "	\\\\\\\\\n");

	}
	logfile::addLog(stt);*/
	if(size != 0)
	{
		logfile::addLog("in_lof");
		vector<string> memss = array.getMemberNames();
		for(int i = 0; i < array.size(); ++i)
		{
			Value get = array.get(memss[i], Value::null);
			if( !get.isNull() && get.size() != 0)
				t_find.push_back(array.get(memss[i], Value::null));
		}
	}
	logfile::addLog("size of t_find: " + to_string(t_find.size()));

	if(t_find.front() == array)
		t_find.pop_front();

	logfile::addLog("size of t_find: " + to_string(t_find.size()));

	while(t_find.size() > 0)
	{
		return findInArray(t_find.front(), name);
	}
}

bool jsonParser::isJson(string in_json)
{
	Reader t_reader;
	Value temp;
	return t_reader.parse( in_json, temp, false);
}

bool jsonParser::isJson()
{
	return bJsonValid;
}

Value jsonParser::getRoot(string Json)
{
	Reader t_reader;
	Value temp;
	t_reader.parse( Json, temp, false);
	return temp;

}

Value jsonParser::getRoot()
{
	return parsedFromString;
}

string jsonParser::getLastError()
{
	return last_error;
}

bool jsonParser::isValidFields()
{

	l12("before parsedFromString==nullValue");
	if ((parsedFromString==nullValue) || (parsedFromString.size()==0) || !isJson())
	{
		last_error = "error: json format is not correct - it empty or isn*t json";//+
		return false;
	}
	l12("__1");
	/*l12("before FIELD_JOBID");
	if(parsedFromString[FIELD_JOBID].isNull() || !parsedFromString[FIELD_JOBID].isConvertibleTo(Json::intValue))
		return false;

	l12("after FIELD_JOBID check");
	if(parsedFromString[FIELD_SESSION].isNull() || !parsedFromString[FIELD_SESSION].isConvertibleTo(Json::stringValue))
		return false;
	l12("after FIELD_SESSION check");
	if(!bJsonValid || parsedFromString[FIELD_OPERATION].isNull())
		return false;
	l12("after FIELD_OPERATION check");*/

	if(parsedFromString[FIELD_TASK_ID].isNull())
	{
		last_error = "error: json format is not correct. Field \"task\" not exist"; //
		return false;
	}
	if (!parsedFromString[FIELD_TASK_ID].isInt())
	{
		last_error = "error: json format is not correct. Field \"task\" not string";
		return false;
	}
	if(parsedFromString[FIELD_OPERATION].isNull())
	{
		last_error = "error: json format is not correct. Field \"operation\" not exist"; //+
		return false;
	}
	if( !parsedFromString[FIELD_OPERATION].isString())//				isConvertibleTo(Json::stringValue))
	{
		l12("__2 cc");
		last_error = "error: json format is not correct. Field \"operation\" not string";
		return false;
	}

	if (parsedFromString[FIELD_OPERATION]=="addtask" || parsedFromString[FIELD_OPERATION]=="edittask")
	{
		if(parsedFromString[FIELD_ETALON].isNull())
		{
			last_error = "error: json format is not correct. Field \"etalon\" not exist"; //+
			return false;
		}
		l12("__2");
		if( !parsedFromString[FIELD_ETALON].isString())//				isConvertibleTo(Json::stringValue))
		{
			l12("__2 cc");
			last_error = "error: json format is not correct. Field \"etalon\" not string";
			return false;
		}
		l12("__3");

		/*if(parsedFromString[FIELD_CODE_LANGUAGE].isNull())
		{
			last_error = "error: json format is not correct. Field \"code\" not exist"; //
			return false;
		}

		if( !parsedFromString[FIELD_CODE_LANGUAGE].isString())
		{
			last_error = "error: json format is not correct. Field \"code\" not string";
			return false;
		}*/
		l12("__4");

		if ( parsedFromString[FIELD_NAME].isNull())
		{
			last_error = "error: json format is not correct. Field \"name\" not exist"; //
			return false;
		}
		if (!parsedFromString[FIELD_NAME].isString())
		{
			last_error = "error: json format is not correct. Field \"name\" not string";
			return false;
		}

		if(! parsedFromString.isMember(FUNCTION))
		{
			last_error = "error: json format is not correct. Field \"function\" not exist"; //
			return false;
		}

		l12("___101");
		if(! parsedFromString[FUNCTION].isMember(FIELD_RESULTS))
		{
			last_error = "error: json format is not correct. Field \"results\" not exist"; //
			return false;
		}
		l12("___102");
		if(! parsedFromString[FUNCTION].isMember(FIELD_ARGS))
		{
			last_error = "error: json format is not correct. Field \"args\" not exist"; //
			return false;
		}
		l12("___103");
		l12("FIELD_NAME");
		if(parsedFromString[FUNCTION][FIELD_FUNCTION_NAME].isNull())
		{
			last_error = "error: json format is not correct. Field \"function_name\" not exist"; //
			return false;
		}
		l12("___104");
		if ( !parsedFromString[FUNCTION][FIELD_FUNCTION_NAME].isString())
		{
			last_error = "error: json format is not correct. Field \"function_name\" not string";
			return false;
		}
		l12("___105");
		/*if(parsedFromString[FUNCTION][FIELD_IS_ARRAY].isNull())
		{
			last_error = "error: json format is not correct. Field \"is_array\" not exist"; //
			return false;
		}
		l12("___106");
		if ( !parsedFromString[FUNCTION][FIELD_IS_ARRAY].isBool())
		{
			last_error = "error: json format is not correct. Field \"is_array\" not boolean";
			return false;
		}
		l12("___107");*/
		/*if(parsedFromString[FUNCTION][FIELD_SIZE].isNull())
		{
			last_error = "error: json format is not correct. Field \"size\" not exist"; //
			return false;
		}
		l12("___108");
		if ( !parsedFromString[FUNCTION][FIELD_SIZE].isInt())
		{
			last_error = "error: json format is not correct. Field \"size\" not boolean";
			return false;
		}
		l12("___109");*/

		if(parsedFromString[FUNCTION][FIELD_TYPE].isNull())
		{
			last_error = "error: json format is not correct. Field \"type\" not exist"; //
			return false;
		}
		l12("___110");
		if ( !parsedFromString[FUNCTION][FIELD_TYPE].isInt())
		{
			last_error = "error: json format is not correct. Field \"type\" not integer";
			return false;
		}
		l12("___111");
		int type_rezult = parsedFromString[FUNCTION][FIELD_TYPE].asInt();

		l12("2___111");

		l12("3___111");

		/*
		vector<string> rezults_array = parsedFromString[FUNCTION][FIELD_RESULTS].
		l12("1___111");
		vector<string> args_array = parsedFromString[FUNCTION][FIELD_ARGS].getMemberNames();
		 */
		int results_size = parsedFromString[FUNCTION][FIELD_RESULTS].size();
		int args_size = parsedFromString[FUNCTION][FIELD_ARGS].size();
		l12("sizes: ");
		l12(results_size);
		l12(results_size);

		if ( results_size != args_size)
		{
			last_error = "error: json format is not correct. Size of results (" + to_string(results_size) +
					") != size of args (" + to_string(args_size) + ")"
					;
			return false;
		}
		l12("___112");

		switch(type_rezult)
		{

		case FunctionData::RET_VAL_BOOL:
			for (int i=0; i < results_size; i++)
			{
				if ( !parsedFromString[FUNCTION][FIELD_RESULTS][i ].isBool())
				{
					last_error = "error: json format is not correct. Results[" + to_string(i) + "] isn*t boolean"; //
					return false;
				}
			}
			break;
		case FunctionData::RET_VAL_FLOAT	:
			for (int i=0; i < results_size; i++)
			{
				if ( !parsedFromString[FUNCTION][FIELD_RESULTS][ i ].isDouble())
				{
					last_error = "error: json format is not correct. Results[" + to_string(i) + "] isn*t float"; //
					return false;
				}
			}
			break;
		case FunctionData::RET_VAL_INT	:
			for (int i=0; i < results_size; i++)
			{
				if ( !parsedFromString[FUNCTION][FIELD_RESULTS][ i ].isInt())
				{
					last_error = "error: json format is not correct. Results[" + to_string(i) + "] isn*t integer"; //
					return false;
				}
			}
			break;
		case FunctionData::RET_VAL_STRING:
			for (int i=0; i < results_size ; i++)
			{
				if ( !parsedFromString[FUNCTION][FIELD_RESULTS][ i ].isString())
				{
					last_error = "error: json format is not correct. Results[" + to_string(i) + "] isn*t string"; //
					return false;
				}
			}
			break;
		default:
			last_error = "error: json format is not correct. Result type don*t recognized";
			return false;
		}

		l12("___113");
		for (int i=0; i < args_size; i++)
		{
			/*if(parsedFromString[FUNCTION][FIELD_ARG_NAME][ i ][FIELD_SIZE].isNull())
			{
				last_error = "error: json format is not correct. Field \"size\" of args[" +
						to_string(i) + "] not exist"; //
				return false;
			}
			if ( !parsedFromString[FUNCTION][FIELD_ARG_NAME][ i][FIELD_SIZE].isInt())
			{
				last_error = "error: json format is not correct. Field \"size\" of args[" +
						to_string(i) + "] not integer"; //
				return false;
			}*/
			l12("___114");
			//if(!parsedFromString[FUNCTION][FIELD_ARGS][ i ].isMember(FIELD_TYPE))
			if(parsedFromString[FUNCTION][FIELD_ARGS][ i ][FIELD_TYPE].isNull())
			{
				last_error = "error: json format is not correct. Field \"type\" of args[" +
						to_string(i) + "] not exist"; //
				return false;
			}
			l12("___115");
			if ( !parsedFromString[FUNCTION][FIELD_ARGS][ i ][FIELD_TYPE].isInt())
			{
				last_error = "error: json format is not correct. Field \"type\" of args[" +
						to_string(i) + "] not integer"; //
				return false;
			}
			l12("___116");
			int value_type = parsedFromString[FUNCTION][FIELD_ARGS][ i ][FIELD_TYPE].asInt();
			if ( value_type >= FunctionData::Last)
			{
				last_error = "error: json format is not correct. Field \"type\" of args[" +
						to_string(i) + "] out of types"; //
				return false;
			}
			l12("___117");
			//if(!parsedFromString[FUNCTION][FIELD_ARGS][ i ].isMember(FIELD_ARG_NAME))
			if(parsedFromString[FUNCTION][FIELD_ARGS][ i ][FIELD_ARG_NAME].isNull())
			{
				last_error = "error: json format is not correct. Field \"arg_name\" of args[" +
						to_string(i) + "] not exist"; //
				return false;
			}
			l12("___118");
			if ( !parsedFromString[FUNCTION][FIELD_ARGS][ i ][FIELD_ARG_NAME].isString())
			{
				last_error = "error: json format is not correct. Field \"arg_name\" of args[" +
						to_string(i) + "] not string"; //
				return false;
			}
			l12("___119");
			//if (!parsedFromString[FUNCTION][FIELD_ARGS][ i ].isMember(FIELD_VALUE))
			if(parsedFromString[FUNCTION][FIELD_ARGS][ i ][FIELD_VALUE].isNull())
			{
				last_error = "error: json format is not correct. Field \"value\" of args[" +
						to_string(i) + "] not exist"; //
				return false;
			}
			l12("___120");

			switch (value_type)
			{
			case FunctionData::RET_VAL_BOOL :
				l12("___121");
				for (int j=0; j < parsedFromString[FUNCTION][FIELD_ARGS][ i ][FIELD_VALUE].size(); j++ )
				{
					if ( !parsedFromString[FUNCTION][FIELD_ARGS][ i ][FIELD_VALUE][j].isBool())
					{
						last_error = "error: json format is not correct. Args[" + to_string(i)
																			+ "]  value[" + to_string(j) + "] isn*t boolean"; //
						return false;
					}
				}
				break;
			case FunctionData::RET_VAL_INT :
				l12("___122");
				for (unsigned int j=0; j < parsedFromString[FUNCTION][FIELD_ARGS][ i ][FIELD_VALUE].size(); j++ )
				{
					l12("___122_00");
					if ( !parsedFromString[FUNCTION][FIELD_ARGS][ i ][FIELD_VALUE][j].isInt())
					{
						last_error = "error: json format is not correct. Args[" + to_string(i)
																					+ "]  value[" + to_string(j) + "] isn*t integer"; //
						return false;
					}
				}
				break;
			case FunctionData::RET_VAL_FLOAT :
				l12("___123");
				for (int j=0; j < parsedFromString[FUNCTION][FIELD_ARGS][ i ][FIELD_VALUE].size(); j++ )
				{
					if ( !parsedFromString[FUNCTION][FIELD_ARGS][ i ][FIELD_VALUE][j].isDouble())
					{
						last_error = "error: json format is not correct. Args[" + to_string(i)
																							+ "]  value[" + to_string(j) + "] isn*t float"; //
						return false;
					}
				}
				break;
			case FunctionData::RET_VAL_STRING :
				l12("___124");
				for (int j=0; j < parsedFromString[FUNCTION][FIELD_ARGS][ i ][FIELD_VALUE].size(); j++ )
				{
					if ( !parsedFromString[FUNCTION][FIELD_ARGS][ i ][FIELD_VALUE][j].isString())
					{
						last_error = "error: json format is not correct. Args[" + to_string(i)
																							+ "]  value[" + to_string(j) + "] isn*t string"; //
						return false;
					}
				}
				break;
			}
		}


		l12("FIELD_FUNCTION_NAME");
		//if(parsedFromString[FIELD_ARGS].isNull() || !parsedFromString[FIELD_ARGS].isArray())
		//return false;//TODO
		//l12("FIELD_ARGS");
		/*if(parsedFromString[FUNCTION][ARGS][FIELD_IS_ARRAY].isNull() || !parsedFromString[FIELD_IS_ARRAY].isConvertibleTo(Json::booleanValue))
			return false;
		l12("FIELD_IS_ARRAY");
		if(parsedFromString[FUNCTION][ARGS][FIELD_SIZE].isNull() || !parsedFromString[FIELD_SIZE].isConvertibleTo(Json::intValue))
			return false;
		l12("FIELD_SIZE");
		if(parsedFromString[FUNCTION][ARGS][FIELD_TYPE].isNull() || !parsedFromString[FIELD_TYPE].isConvertibleTo(Json::intValue))
			return false;
		if(parsedFromString[FUNCTION][ARGS][FIELD_ARG_NAME].isNull() || !parsedFromString[FIELD_ARG_NAME].isConvertibleTo(Json::stringValue))
			return false;
		if(parsedFromString[FUNCTION][ARGS][FIELD_VALUE].isNull() || !parsedFromString[FIELD_VALUE].isConvertibleTo(Json::stringValue))
			return false;*/

		return true;
	}


	if (parsedFromString[FIELD_OPERATION]=="start")
	{

		if(parsedFromString[FIELD_CODE_TEXT].isNull())
		{
			last_error = "error: json format is not correct. Field \"code\" not exist"; //
			return false;
		}
		if (!parsedFromString[FIELD_CODE_TEXT].isString())
		{
			last_error = "error: json format is not correct. Field \"code\" not string";
			return false;
		}
		/*if(parsedFromString[FIELD_CODE_LANGUAGE].isNull() )
		{
			last_error = "error: json format is not correct. Field \"lang\" not exist"; //
			return false;
		}
		if ( !parsedFromString[FIELD_CODE_LANGUAGE].isString())
		{
			last_error = "error: json format is not correct. Field \"lang\" not string";
			return false;
		}*/
		if(parsedFromString[FIELD_TASK_ID].isNull())
		{
			last_error = "error: json format is not correct. Field \"task\" not exist"; //
			return false;
		}
		if (!parsedFromString[FIELD_TASK_ID].isInt())
		{
			last_error = "error: json format is not correct. Field \"task\" not string";
			return false;
		}
	}
	else if (parsedFromString[FIELD_OPERATION]=="status"){

	}
	else if (parsedFromString[FIELD_OPERATION]=="result"){

	}
	else if (parsedFromString[FIELD_OPERATION]=="getToken"){

	}
	else if (parsedFromString[FIELD_OPERATION]=="getFromToken"){
		if(parsedFromString[FIELD_TOKEN].isNull() )
		{
			last_error = "error: json format is not correct. Field \"token\" not exist"; //
			return false;
		}
		if ( !parsedFromString[FIELD_TOKEN].isString())
		{
			last_error = "error: json format is not correct. Field \"token\" not string";
			return false;
		}
	}
	else
	{
		last_error = "error: json format is not correct. Operation ";
		last_error += parsedFromString[FIELD_OPERATION].toStyledString();
		last_error += " not exist";
		return false ;
	}
	/*
	 *  conver test  add
	 */

	return true;
}


