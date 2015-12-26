/*
 * jsonParser.cpp
 *
 *  Created on: Jun 3, 2015
 *      Author: root
 */

#include "inc/jsonParser.h"
#include "inc/TaskCodeGenerator.h"

jsonParser::jsonParser(string json)
{
	bJsonValid = setJson(json);
	max_uint_value = to_string (std::numeric_limits<unsigned int>::max());
}

bool jsonParser::sizeEqualSizeOfUnitTests(Json::Value object, string name)
{
	int object_size = object.size();
	if ( unit_test_num != object_size )
	{
		last_error = "error: json format is not correct. " + name + " array size = " +
				to_string(object_size) + " , but unit_test_num = " + to_string(unit_test_num);
		return false;
	}
	return true;
}

bool jsonParser::mustHaveSizeMoreZeroAndBeNotTwoDimensionalArray(Json::Value object, string name , string ps, string ps2)
{
	if (!mustHaveSizeMoreZero(object ,name , ps))
		return false;
	if (object[0].isArray())
		if (!mustBeNotArray(object[0][0] , string(name + "[0][0]") , ps2))
			return false;
	return true;
}

bool jsonParser::isStringInt(string value)
{
	regex regStr("^[-0-9][0-9]{0,}");
	return  std::regex_match( value, regStr );

}

bool jsonParser::isStringBool(string value)
{
	std::transform(value.begin(), value.end(), value.begin(), ::tolower);
	return (value == "false" || value == "true" );
}

bool jsonParser::isStringFloat(string value)
{
	string range_no_quotes = value.substr(1, value.size() - 3);
	regex regStr("^[-0-9][0-9]{0,}.?[0-9]{1,}");
	//regex regStr("[0-9]{0,}");
	return  std::regex_match( value, regStr );
}

bool jsonParser::rangeValidation(bool &range_size_inited, int &range_size, string range, string field_name)
{
	string range_no_quotes = range.substr(1, range.size() - 3);
	regex regStr("^[-0-9][0-9]{0,}..[-0-9][0-9]{0,}");
	if (!std::regex_match( range_no_quotes, regStr ))
	{
		last_error = "error: json format is not correct. " + field_name + " range format invalid "; //
		last_error += range;
		return false;
	}
	is_results_range = true;
	sscanf(range_no_quotes.c_str(),"%d..%d", &range_first, &range_last);

	if (range_first > range_last)
	{
		int temp = range_first;
		range_first = range_last;
		range_last = temp;
	}
	int range_i_size = abs(range_first - range_last);
	if ( !range_size_inited )
	{
		range_size = range_i_size;
		range_size_inited = true;
	}
	else
		if (range_i_size != range_size)
		{
			last_error = "error: json format is not correct. " + field_name +
					" range size (" + to_string(range_i_size) +
					") != results[0] range size ("  +
					to_string(range_size) + ")";
			return false;
		}
	return true;
}

bool jsonParser::mustBeArrayFloat(Json::Value object, string name , string ps, string ps2 )
{
	if (!mustBeArray(object,name,ps))
		return false;
	for (int i = 0; i < object.size(); i++)
		if (!mustBeFloat(object[i], name + stringInScobcah(i), ps2))
			return false;
	return true;
}

bool jsonParser::mustBeArrayInt(Json::Value object, string name , string ps, string ps2 )
{
	if (!mustBeArray(object,name,ps))
		return false;
	for (int i = 0; i < object.size(); i++)
		if (!mustBeInt(object[i], name + stringInScobcah(i), ps2))
			return false;
	return true;
}

bool jsonParser::mustBeArrayString(Json::Value object, string name , string ps, string ps2 )
{
	if (!mustBeArray(object,name,ps))
		return false;
	for (int i = 0; i < object.size(); i++)
		if (!mustBeString(object[i], name + stringInScobcah(i), ps2))
			return false;
	return true;
}

bool jsonParser::jsonParser::mustBeArrayBool(Json::Value object, string name , string ps, string ps2 )
{
	if (!mustBeArray(object,name,ps))
		return false;
	for (int i = 0; i < object.size(); i++)
		if (!mustBeBool(object[i], name + stringInScobcah(i), ps2))
			return false;
	return true;
}


bool jsonParser::mustBeNotArrayFloat(Json::Value object, string name , string ps, string ps2 )
{
	if (!mustBeNotArray(object,name,ps))
		return false;
	if (!mustBeFloat(object,name,ps2))
		return false;
	return true;
}

bool jsonParser::mustBeNotArrayInt(Json::Value object, string name , string ps , string ps2)
{
	if (!mustBeNotArray(object,name,ps))
		return false;
	if (!mustBeInt(object,name,ps2))
		return false;
	return true;
}

bool jsonParser::mustBeNotArrayString(Json::Value object, string name , string ps, string ps2)
{
	if (!mustBeNotArray(object,name,ps))
		return false;
	if (!mustBeString(object,name,ps2))
		return false;
	return true;
}

bool jsonParser::mustBeNotArrayBool(Json::Value object, string name , string ps , string ps2)
{
	if (!mustBeNotArray(object,name,ps))
		return false;
	if (!mustBeBool(object,name,ps2))
		return false;
	return true;
}

bool jsonParser::mustBeNotArray(Json::Value object, string name , string ps)
{
	if (object.isNull())
		return true;
	if ( object.isArray())
	{
		last_error = "error: json format is not correct. " + name + " can`t be array " + ps;
		return false;
	}
	return true;
}

bool jsonParser::mustBeArray(Json::Value object, string name , string ps )
{
	if ( !object.isArray())
	{
		last_error = "error: json format is not correct. " + name + " must be array " + ps;
		return false;
	}
	if (!mustHaveSizeMoreZero(object,name,ps))
		return false;
	return true;
}


bool jsonParser::mustHaveSizeMoreZero(Json::Value object, string name , string ps)
{
	if ( object.size() < 1)
	{
		last_error = "error: json formatu = reader.parse is not correct. " + name + " size < 1 " + ps;
		return false;
	}
	return true;
}

bool jsonParser::mustBeInt(Json::Value object, string name , string ps )
{
	if ( object.isString())
	{
		if (!isStringInt(object.asString()))
		{
			last_error = "error: json format is not correct. " + name +" isn`t convertible to int " + ps;
			return false;
		}
		return true;
	}
	if ( !object.isInt())
	{
		last_error = "error: json format is not correct. " + name +" isn`t integer " + ps;
		return false;
	}
	return true;
}

bool jsonParser::mustBeUnsignedInt(Json::Value object, string name , string ps )
{
	if ( !object.isInt() && !object.isUInt())
	{
		last_error = "error: json format is not correct. " + name +" isn`t unsigned integer " + ps;
		return false;
	}
	string obg_string = object.toStyledString();
	obg_string = obg_string.substr(0, obg_string.size() - 1 );

	unsigned int obj_str_size = obg_string.size();

	if (obj_str_size < max_uint_value.size())
		return true;

	if (obg_string.size() > max_uint_value.size())
	{
		last_error = "error: json format is not correct. " + name +" out of range of unsigned integer (max value = " + max_uint_value + ")" + ps;
		return false;
	}

	for(int i = 0; i < obj_str_size; i++)
	{
		char num = obg_string[i];
		char m_num = max_uint_value[i];
		if (num < m_num)
			return true;
		if ( num > m_num )
		{
			last_error = "error: json format is not correct. " + name +" out of range of unsigned integer (max value = " + max_uint_value + ")" + ps;
			return false;
		}
	}

	return true;
}

bool jsonParser::mustExist(Json::Value object, string name  , string ps)
{
	if ( object.isNull())
	{
		last_error = "error: json format is not correct. " + name +" don`t exist " + ps;
		return false;
	}
	return true;
}

bool jsonParser::mustExistBeInt(Json::Value object, string name  , string ps , string ps2)
{
	if ( object.isNull())
	{
		last_error = "error: json format is not correct. " + name +" don`t exist " + ps;
		return false;
	}
	if (!mustBeInt(object, name, ps2))
		return false;
	return true;
}

bool jsonParser::mustExistBeUnsignedInt(Json::Value object, string name  , string ps , string ps2)
{
	if ( object.isNull())
	{
		last_error = "error: json format is not correct. " + name +" don`t exist " + ps;
		return false;
	}
	if (!mustBeUnsignedInt(object, name, ps2))
		return false;
	return true;
}

bool jsonParser::mustExistBeFloat(Json::Value object, string name  , string ps , string ps2)
{
	if ( object.isNull())
	{
		last_error = "error: json format is not correct. " + name +" don`t exist " + ps;
		return false;
	}
	if (!mustBeFloat(object, name, ps2))
		return false;
	return true;
}

bool jsonParser::mustExistBeString(Json::Value object, string name  , string ps , string ps2)
{
	if ( object.isNull())
	{
		last_error = "error: json format is not correct. " + name +" don`t exist " + ps;
		return false;
	}
	if (!mustBeString(object, name, ps2))
		return false;
	return true;
}

bool jsonParser::mustExistBeBool(Json::Value object, string name  , string ps , string ps2)
{
	if ( object.isNull())
	{
		last_error = "error: json format is not correct. " + name +" don`t exist " + ps;
		return false;
	}
	if (!mustBeBool(object, name, ps2))
		return false;
	return true;
}

bool jsonParser::mustExistBeArray(Json::Value object, string name  , string ps , string ps2)
{
	if ( object.isNull())
	{
		last_error = "error: json format is not correct. " + name +" don`t exist " + ps;
		return false;
	}
	if (!mustBeArray(object, name, ps2))
		return false;
	return true;
}

bool jsonParser::mustExistBeArrayString(Json::Value object, string name , string ps, string ps2 )
{
	if (!mustExistBeArray(object, name, ps,ps2))
		return false;
	for (int i = 0; i < object.size(); i++)
		if (!mustBeString(object[i], name + stringInScobcah(i)))
			return false;
	return true;
}
bool jsonParser::mustExistBeArrayInt(Json::Value object, string name , string ps, string ps2 )
{
	if (!mustExistBeArray(object, name, ps,ps2))
		return false;
	for (int i = 0; i < object.size(); i++)
		if (!mustBeInt(object[i], name + stringInScobcah(i)))
			return false;
	return true;
}

bool jsonParser::mustExistBeArrayInt(Json::Value object, string name , string ps, string ps2 , int min_val, int max_val)
{
	if (!mustExistBeArray(object, name, ps,ps2))
		return false;
	for (int i = 0; i < object.size(); i++)
	{
		if (!mustBeInt(object[i], name + stringInScobcah(i)))
			return false;
		int int_obj = getAsInt(object[i]);//.asInt();
		if (int_obj < min_val || int_obj > max_val)
		{
			last_error = "error: json format is not correct. " +  name + stringInScobcah(i) +" value(" + to_string(int_obj) +
					") out of range(" + to_string(min_val) + ", " + to_string(max_val) + ")";
			return false;
		}
	}
	return true;
}

string jsonParser::stringInScobcah(string inp)
{
	return string("[" + inp + "]");
}

string jsonParser::stringInScobcah(int inp)
{
	return stringInScobcah( to_string(inp));
}



bool jsonParser::mustBeFloat(Json::Value object, string name  , string ps)
{
	if ( object.isString())
	{
		if (!isStringFloat(object.asString()))
		{
			last_error = "error: json format is not correct. " + name +" isn`t convertible to float " + ps;
			return false;
		}
		return true;
	}
	if ( !object.isDouble())
	{
		last_error = "error: json format is not correct. " + name +" isn`t float " + ps;
		return false;
	}
	return true;
}
bool jsonParser::mustBeString(Json::Value object, string name , string ps )
{
	if ( !object.isString())
	{
		last_error = "error: json format is not correct. " + name +" isn`t string " + ps;
		return false;
	}
	return true;
}

bool jsonParser::mustBeBool(Json::Value object, string name , string ps )
{
	if ( object.isString())
	{
		if (!isStringBool(object.asString()))
		{
			last_error = "error: json format is not correct. " + name +" isn`t convertible to bool " + ps;
			return false;
		}
		return true;
	}
	if ( !object.isBool())
	{
		last_error = "error: json format is not correct. " + name +" isn`t boolean " + ps;
		return false;
	}
	return true;
}

bool jsonParser::isResultsArray()
{
	return is_results_array;
}

int jsonParser::getResultsArraySize()
{
	return results_array_size;
}

bool jsonParser::isResultsRange()
{
	return is_results_range;
}

jsonParser::jsonParser()
{
	json.clear();
	max_uint_value = to_string (std::numeric_limits<unsigned int>::max());
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

int jsonParser::getAsInt(Value obj)
{
	if (obj.isInt())
		return obj.asInt();
	int rez;
	string as_str = obj.asString(); //1313
	if (isStringInt(as_str))
		sscanf(as_str.c_str(),"%d", &rez);
	return rez;
}

int jsonParser::getAsIntS(string obj) //889
{
	if (parsedFromString[obj].isInt())
		return parsedFromString[obj].asInt();
	int rez;
	string as_str = parsedFromString[obj].asString(); //1313
	if (isStringInt(as_str))
		sscanf(as_str.c_str(),"%d", &rez);
	return rez;
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
		ERROR("Error Json parse, input string is empty");
}

Value jsonParser::findInArray(Value &array, string &name)
{
	const Value null = "NULL";
	Value res = array.get(name, Value::null);

	if(!res.isNull())
		return res;
	int size = array.size();

	DEBUG("ARR " + name + "size" + to_string(array.size()));
	/*string stt;
	stt.append("ALL NUMBERS::	\n");
	for(int i = 0; i < array.getMemberNames().size(); i++)
	{
		stt.append(array.getMemberNames()[i] + "	\\\\\\\\\n");
value": [[1,2], [3,4]]
	}
	logfile::addLog(stt);*/
	if(size != 0)
	{
		DEBUG("in_lof");
		vector<string> memss = array.getMemberNames();
		for(int i = 0; i < array.size(); ++i)
		{
			Value get = array.get(memss[i], Value::null);
			if( !get.isNull() && get.size() != 0)
				t_find.push_back(array.get(memss[i], Value::null));
		}
	}
	DEBUG("size of t_find: " + to_string(t_find.size()));

	if(t_find.front() == array)
		t_find.pop_front();

	DEBUG("size of t_find: " + to_string(t_find.size()));

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

int jsonParser::getRangeFirst()
{
	return range_first;

}
int jsonParser::getRangeLast()
{
	return range_last;
}

bool jsonParser::isValidFields()
{
	is_results_range = false;
	is_results_array = false;
	DEBUG("before parsedFromString==nullValue");
	if ((parsedFromString == nullValue) || (parsedFromString.size() == 0) || !isJson())
	{
		last_error = "error: json format is not correct - it empty or isn*t json";//+
		return false;
	}
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
	if( !mustExistBeInt(parsedFromString[FIELD_TASK_ID], "task"))
		return false;




	if( !mustExistBeString(parsedFromString[FIELD_OPERATION], "operation"))
		return false;


	if (parsedFromString[FIELD_OPERATION]=="addtask" || parsedFromString[FIELD_OPERATION]=="edittask")
	{
		if( !mustExistBeString(parsedFromString[FIELD_ETALON], "etalon"))
			return false;


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

		/*	if ( parsedFromString[FIELD_NAME].isNull())
		{
			last_error = "error: json format is not correct. Field \"name\" not exist"; //
			return false;
		}
		if (!parsedFromString[FIELD_NAME].isString())
		{
			last_error = "error: json format is not correct. Field \"name\" not string";
			return false;
		}
		 */
		Json::Value field_tests_code = parsedFromString[FUNCTION][FIELD_TESTS_CODE];
		Json::Value field_args = parsedFromString[FUNCTION][FIELD_ARGS];
		Json::Value field_results = parsedFromString[FUNCTION][FIELD_RESULTS];
		Json::Value field_type = parsedFromString[FUNCTION][FIELD_TYPE];
		Json::Value field_compare_mark = parsedFromString[FUNCTION][FIELD_COMPARE_MARK];
		Json::Value field_array_type = parsedFromString[FUNCTION][FIELD_ARRAY_TYPE];
		Json::Value field_unit_test_num = parsedFromString[FUNCTION][FIELD_UNIT_TESTS_NUM];

		if( !mustExist(parsedFromString[FUNCTION], "function"))
			return false;

		bool is_results_exist = mustExist(field_results, "results");

		if (is_results_exist)
			if( !mustExistBeArray(field_results, "results"))
				return false;

		if( !mustExistBeArrayString(field_tests_code, "tests_code"))
			return false;

		if( !mustExistBeArrayInt(field_compare_mark, "compare_mark","", "",0, CompareMark::Last - 1))
			return false;

		if( !mustExistBeInt(field_unit_test_num, "unit_test_num"))
			return false;

		if( !mustExistBeInt(field_array_type, "array_type"))
			return false;

		unit_test_num = getAsInt(field_unit_test_num);//.asInt();
		is_results_array = getAsInt(field_array_type);//.asInt();

		if( !mustExistBeArray(field_args, "args"))
			return false;

		/*if(parsedFromString[FUNCTION][FIELD_FUNCTION_NAME].isNull())
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
		l12("___105");*/
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

		if( !mustExistBeInt(field_type, "type"))
			return false;

		int type_rezult = getAsInt(field_type) ;//"type"); //	field_type.asInt();
		/*
		vector<string> rezults_array = parsedFromString[FUNCTION][FIELD_RESULTS].
		l12("1___111");
		vector<string> args_array = parsedFromString[FUNCTION][FIELD_ARGS].getMemberNames();
		 */

		if (is_results_exist)
			results_array_size = field_results.size();
		else
			results_array_size = 0;

		int field_tests_code_size = field_tests_code.size();

		if (is_results_exist)
			if ( !sizeEqualSizeOfUnitTests(field_results, "results"))
				return false;

		if ( !sizeEqualSizeOfUnitTests(field_tests_code, "tests_code"))
			return false;


		int args_size =  field_args.size();

		/*if ( results_size != args_size)
		{
			last_error = "error: json format is not correct. Size of results (" + to_string(results_size) +
					") != size of args (" + to_string(args_size) + ")"
					;
			return false;
		}*/

		/*is_results_array = field_results[0].isArray();
		unit_test_num = field_results.size();*/


		if (is_results_exist)
		{
			if ( is_results_array == FunctionData::NOT_ARRAY )
			{
				switch(type_rezult)
				{
				case code::FunctionData::RET_VAL_RANGE:

					int range_size;
					bool range_size_inited;
					range_size_inited = false;
					for (int i=0; i < results_array_size; i++)
					{
						if( !mustBeNotArrayString(field_results[i],
								string("results[" + to_string(i) + "]"), " of ranges", ", thats why can`t be range"))
							return false;

						string range = parsedFromString[FUNCTION][FIELD_RESULTS][i ].toStyledString();
						rangeValidation(range_size_inited, range_size, range, string("results[" + to_string(i) +"]"));
					}
					break;
				case code::FunctionData::RET_VAL_BOOL:
					for (int i=0; i < results_array_size; i++)
					{
						if( !mustBeNotArrayBool(field_results[i],string("results[" + to_string(i) + "]"), ", cuz results[0] isn`t"))
							return false;
					}
					break;
				case code::FunctionData::RET_VAL_FLOAT	:
					for (int i=0; i < results_array_size; i++)
					{
						if( !mustBeNotArrayFloat(field_results[i], string("results[" + to_string(i) + "]"), ", cuz results[0] isn`t"))
							return false;
					}
					break;
				case code::FunctionData::RET_VAL_INT	:
					for (int i=0; i < results_array_size; i++)
					{
						if( !mustBeNotArrayInt(field_results[i], string("results[" + to_string(i) + "]"), ", cuz results[0] isn`t"))
							return false;
					}
					break;
				case code::FunctionData::RET_VAL_STRING:
					for (int i=0; i < results_array_size ; i++)
					{
						if( !mustBeNotArrayString(field_results[i],	string("results[" + to_string(i) + "]"), ", cuz results[0] isn`t"))
							return false;
					}
					break;
				default:
				{
					last_error = "error: json format is not correct. Result type don`t recognized";
					return false;
				}
				}
			}
			else
				if ( is_results_array == FunctionData::ARRAY )
				{
					int results_0_array_size  = field_results[0].size();
					//results_array_size = results_0_array_size;

					if(!mustHaveSizeMoreZero(field_results[0],"results[0]","Where results[0] values?"))
						return false;

					if ( field_results[0][0].isArray())
					{
						if( !mustBeNotArray(field_results[0][0],"results[0][0][0]"))
							return false;
					}


					for (int k=0; k < results_array_size; k++)
					{
						Json::Value result_k = field_results[k];

						if( !mustBeArray(result_k, string("results[" + to_string(k) +	"]"), ", cuz results[0] is array"))
							return false;

						int results_k_array_size  = result_k.size();

						if ( results_k_array_size != results_0_array_size)
						{
							last_error = "error: json format is not correct. Results[" + to_string(k) +
									"] size = "+ to_string(results_k_array_size) +
									", but results[0] size = " + to_string(results_0_array_size);
							return false;
						}
						{
							switch(type_rezult)
							{
							case code::FunctionData::RET_VAL_RANGE:

								last_error = "error: json format is not correct. results[" + to_string(k) +
								"] can`t be array of ranges";					;
								return false;
								break;
							case code::FunctionData::RET_VAL_BOOL:
								for (int i=0; i < results_k_array_size; i++)
								{
									if (!mustBeNotArrayBool(result_k[i], string("results[" + to_string(k) +	"][" + to_string(i) + "]")))
										return false;
								}
								break;
							case code::FunctionData::RET_VAL_FLOAT	:
								for (int i=0; i < results_k_array_size; i++)
								{
									if (!mustBeNotArrayFloat(result_k[i], string("results[" + to_string(k) +	"][" + to_string(i) + "]")))
										return false;
								}
								break;
							case code::FunctionData::RET_VAL_INT	:
								for (int i=0; i < results_k_array_size; i++)
								{
									if (!mustBeNotArrayInt(result_k[i], string("results[" + to_string(k) +	"][" + to_string(i) + "]")))
										return false;
								}
								break;
							case code::FunctionData::RET_VAL_STRING:
								for (int i=0; i < results_k_array_size ; i++)
								{
									if (!mustBeNotArrayString(result_k[i], string("results[" + to_string(k) +	"][" + to_string(i) + "]")))
										return false;
								}
								break;
							default:
								last_error = "error: json format is not correct. Result type don*t recognized";
								return false;
							}
						}
					}
				}
		}


		//bool args_0_values_is_array =


		/*bool values_0_is_array_seted = false;
		bool args_0_values_0_is_array;
		int args_0_value_type;
		int args_0_values_size;*/

		for (int i=0; i < args_size; i++)
		{

			Json::Value args_i = parsedFromString[FUNCTION][FIELD_ARGS][ i ];
			Json::Value args_i_type = parsedFromString[FUNCTION][FIELD_ARGS][ i ][FIELD_TYPE];

			if(!mustExistBeInt(args_i_type, string("type of args[" + to_string(i) + "]" )))
				return false;

			int value_type = getAsInt(args_i_type);//.asInt();

			if ( value_type >= code::FunctionData::Last)
			{
				last_error = "error: json format is not correct. Field \"type\" of args[" +
						to_string(i) + "] out of types"; //
				return false;
			}

			Json::Value args_i_arg_name = args_i[FIELD_ARG_NAME];

			if(!mustExistBeString(args_i_arg_name, string("arg_name of args[" + to_string(i) + "]" )))
				return false;

			Json::Value args_i_value = args_i[FIELD_VALUE];

			if(!mustExistBeArray(args_i_value, string("value of args[" + to_string(i) + "]" )))
				return false;

			int values_size = args_i_value.size();

			if ( values_size != unit_test_num )
			{
				last_error = "error: json format is not correct. Args[" + to_string(i) +
						"] values size (" + to_string(values_size) + ") != unit_test_num (" +
						to_string(unit_test_num) + ")";
				return false;
			}

			//////////1
			Json::Value args_i_etalon_value = args_i[FIELD_ETALON_VALUE];
			//Json::Value args_i_compare_mark = args_i[FIELD_COMPARE_MARK];

			if(!mustExistBeArray(args_i_etalon_value, string("etalon_value of args[" + to_string(i) + "]" )))
				return false;

			/*if(!mustExistBeArrayInt(args_i_compare_mark, string("compare_mark of args[" + to_string(i) + "]" ),"","",0, CompareMark::Last - 1))
				return false;*/

			int etalon_values_size = args_i_etalon_value.size();

			if ( etalon_values_size != unit_test_num )
			{
				last_error = "error: json format is not correct. Args[" + to_string(i) +
						"] etalon_value size (" + to_string(values_size) + ") != runit_test_num(" +
						to_string(unit_test_num) + ")";
				return false;
			}

			////////////2

			/*if (!values_0_is_array_seted)
			{
				args_0_values_0_is_array = parsedFromString[FUNCTION][FIELD_ARGS][i][FIELD_VALUE][0].isArray();
				values_0_is_array_seted = true;
				args_0_value_type = value_type;
			}*/
			/*if ( value_type != args_0_value_type)
			{
				last_error = "error: json format is not correct. Args[" + to_string(i) +
						"] type (" + to_string(value_type) + ") != args[0] type (" + to_string(args_0_value_type)+ ")";
				return false;
			}*/

			bool values_0_is_array = args_i_value[0].isArray();

			/*if ( args_0_values_0_is_array != values_0_is_array)
			{
				last_error = "error: json format is not correct. Args[" + to_string(i) +
						"] values[0].isArray() = " + to_string(values_0_is_array) + "), but args[0] values[0].isArray() = " + to_string(args_0_values_0_is_array);
				return false;
			}*/


			if ( !values_0_is_array )
			{
				switch(value_type)
				{
				////// 2
				case code::FunctionData::RET_VAL_RANGE:

					int range_size;
					bool range_size_inited;
					range_size_inited = false;
					for (int j=0; j < values_size; j++)
					{
						if(!mustBeNotArrayString(args_i_value[j],
								string("args[" + to_string(i) +	"] values[" + to_string(j)+ "]" ), " of ranges", " cuz it range"))
							return false;

						string range = args_i_value[j].toStyledString();
						rangeValidation(range_size_inited, range_size, range, string("args[" + to_string(i) +	"]"));
					}
					break;
				case code::FunctionData::RET_VAL_INT	:
					for (int j=0; j < values_size; j++)
					{
						if(!mustBeNotArrayInt(args_i_value[j],
								string("args[" + to_string(i) +	"] values[" + to_string(j)+ "]" ),
								string(", cuz args[" + to_string(i) + "] values[0] isn`t")))
							return false;

						if(!mustBeNotArray(args_i_etalon_value[j],
								string("args[" + to_string(i) +	"] etalon_values[" + to_string(j)+ "]" ),
								string(", cuz args[" + to_string(i) + "] etalon_values[0] isn`t")))
							return false;
					}
					break;
				case code::FunctionData::RET_VAL_FLOAT	:
					for (int j=0; j < values_size; j++)
					{
						if(!mustBeNotArrayFloat(args_i_value[j],
								string("args[" + to_string(i) +	"] values[" + to_string(j)+ "]" ),
								string(", cuz args[" + to_string(i) + "] values[0] isn`t")))
							return false;

						if(!mustBeNotArray(args_i_etalon_value[j],
								string("args[" + to_string(i) +	"] etalon_values[" + to_string(j)+ "]" ),
								string(", cuz args[" + to_string(i) + "] etalon_values[0] isn`t")))
							return false;

					}
					break;
				case code::FunctionData::RET_VAL_BOOL	:
					for (int j=0; j < values_size; j++)
					{
						if(!mustBeNotArrayBool(args_i_value[j],
								string("args[" + to_string(i) +	"] values[" + to_string(j)+ "]" ),
								string(", cuz args[" + to_string(i) + "] values[0] isn`t")))
							return false;

						if(!mustBeNotArray(args_i_etalon_value[j],
								string("args[" + to_string(i) +	"] etalon_values[" + to_string(j)+ "]" ),
								string(", cuz args[" + to_string(i) + "] etalon_values[0] isn`t")))
							return false;
					}
					break;
				case code::FunctionData::RET_VAL_STRING	:
					for (int j=0; j < values_size; j++)
					{
						if(!mustBeNotArrayString(args_i_value[j],
								string("args[" + to_string(i) +	"] values[" + to_string(j)+ "]" ),
								string(", cuz args[" + to_string(i) + "] values[0] isn`t")))
							return false;

						if(!mustBeNotArray(args_i_etalon_value[j],
								string("args[" + to_string(i) +	"] etalon_values[" + to_string(j)+ "]" ),
								string(", cuz args[" + to_string(i) + "] etalon_values[0] isn`t")))
							return false;
					}
					break;

				default:
					last_error = "error: json format is not correct. Args[" + to_string(i) + "] type don*t recognized";
					return false;
				}
			}
			else
			{
				//1569
				int values_0_array_size  = args_i_value[0].size();
				if (!mustHaveSizeMoreZeroAndBeNotTwoDimensionalArray(args_i_value[0],string("args[" + to_string(i) +"] values[0]")))
					return false;

				/*if (!mustHaveSizeMoreZero(args_i_value[0],string("args[" + to_string(i) +"] values[0]")))
					return false;
				if ( args_i_value[0][0].isArray())
				{
					if (!mustBeNotArray(args_i_value[0][0][0].isArray(),string("args[" + to_string(i) +"] values[0][0]")))
						return false;
				}*/

				if (!mustHaveSizeMoreZeroAndBeNotTwoDimensionalArray(args_i_etalon_value[0],string("args[" + to_string(i) +"] etalon_values[0]")))
					return false;

				/*int etalon_values_0_array_size  = args_i_etalon_value[0].size();
				if (!mustHaveSizeMoreZero(args_i_etalon_value[0],string("args[" + to_string(i) +"] etalon_values[0]")))
					return false;
				if ( args_i_etalon_value[0][0].isArray())
				{
					if (!mustBeNotArray(args_i_etalon_value[0][0][0].isArray(),string("args[" + to_string(i) +"] etalon_values[0][0]")))
						return false;
				}*/


				//9969
				for (int k=0; k < values_size; k++)
				{
					Json::Value field_value_k = args_i_value[k];
					Json::Value field_etalon_value_k = args_i_etalon_value[k];
					string s_value_k = "args[" + to_string(i) +"] values[" + to_string(k) + "]";
					string s_etalon_value_k = "args[" + to_string(i) +"] etalon_value[" + to_string(k) + "]";

					if ( !mustBeArray(field_value_k, s_value_k , ", cuz args[0] values[0] is array") )
						return false;
					int values_k_array_size  = field_value_k.size();

					if ( values_k_array_size != values_0_array_size)
					{
						last_error = "error: json format is not correct. " + s_value_k +
								" size = "+ to_string(values_k_array_size) +
								", but args[" + to_string(i) +"] values[0] size = " + to_string(values_0_array_size);
						return false;
					}

					if ( !mustBeArray(field_etalon_value_k, s_etalon_value_k,", cuz args[0] etalon_value[0] is array") )
						return false;

					if ( field_etalon_value_k.size() != values_0_array_size)
					{
						last_error = "error: json format is not correct. " + s_etalon_value_k +
								" size = "+ to_string(values_k_array_size) +
								", but args[" + to_string(i) +"] values[0] size = " + to_string(values_0_array_size);
						return false;
					}

					{
						switch(value_type)
						{
						///////// 1
						case code::FunctionData::RET_VAL_RANGE:

							last_error = "error: json format is not correct. " + s_value_k +
							" can`t be array of ranges";					;
							return false;
							break;
						case code::FunctionData::RET_VAL_INT	: //6565
							for (int j=0; j < values_k_array_size; j++)
							{
								string s_value_k_j = s_value_k + "[" + to_string(i) + "]";
								string s_etalon_value_k_j = s_etalon_value_k + "[" + to_string(i) + "]";

								if ( !mustBeNotArrayInt(field_value_k[j], s_value_k_j ) )
									return false;

								if ( !mustBeNotArray(field_etalon_value_k[j], s_etalon_value_k_j ) )
									return false;
							}
							break;
						case code::FunctionData::RET_VAL_FLOAT	:
							for (int j=0; j < values_k_array_size; j++)
							{
								string s_value_k_j = s_value_k + "[" + to_string(i) + "]";
								string s_etalon_value_k_j = s_etalon_value_k + "[" + to_string(i) + "]";

								if ( !mustBeNotArrayFloat(field_value_k[j], s_value_k_j ) )
									return false;

								if ( !mustBeNotArray(field_etalon_value_k[j], s_etalon_value_k_j ) )
									return false;
							}
							break;
						case code::FunctionData::RET_VAL_BOOL	:
							for (int j=0; j < values_k_array_size; j++)
							{
								string s_value_k_j = s_value_k + "[" + to_string(i) + "]";
								string s_etalon_value_k_j = s_etalon_value_k + "[" + to_string(i) + "]";

								if ( !mustBeNotArrayBool(field_value_k[j], s_value_k_j ) )
									return false;

								if ( !mustBeNotArray(field_etalon_value_k[j], s_etalon_value_k_j ) )
									return false;
							}
							break;
						case code::FunctionData::RET_VAL_STRING:
							for (int j=0; j < values_k_array_size; j++)
							{
								string s_value_k_j = s_value_k + "[" + to_string(i) + "]";
								string s_etalon_value_k_j = s_etalon_value_k + "[" + to_string(i) + "]";

								if ( !mustBeNotArrayString(field_value_k[j], s_value_k_j ) )
									return false;

								if ( !mustBeNotArray(field_etalon_value_k[j], s_etalon_value_k_j ) )
									return false;
							}
							break;

						default:
							last_error = "error: json format is not correct. Args[" + to_string(i) +" type don*t recognized";
							return false;
						}
					}
				}
			}
		}
		return true;
	}

	if (parsedFromString[FIELD_OPERATION]=="start")
	{

		if( !mustExistBeUnsignedInt(parsedFromString[FIELD_JOBID], "jobid"))
			return false;

		if( !mustExistBeString(parsedFromString[FIELD_CODE_TEXT], "code"))
			return false;
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

	}
	else if (parsedFromString[FIELD_OPERATION]=="status"){

	}
	else if (parsedFromString[FIELD_OPERATION]=="result"){

		if( !mustExistBeUnsignedInt(parsedFromString[FIELD_JOBID], "jobid"))
			return false;

	}
	else if (parsedFromString[FIELD_OPERATION]=="getToken"){

	}
	else if (parsedFromString[FIELD_OPERATION]=="getFromToken"){
		if( !mustExistBeString(parsedFromString[FIELD_TOKEN], "token"))
			return false;
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


