#include "../inc/jsonParser.h"
#include "../inc/TaskCodeGenerator.h"


bool jsonParser::isValidFields()
{
	is_results_range = false;
	is_results_array = false;

	cout.flush();
	//cout << parsedFromString.toStyledString();


	DEBUG("before parsedFromString==nullValue");
	if ((parsedFromString == nullValue) || (parsedFromString.size() == 0) || !isJson())
	{
		last_error = "ERROR: json format is not correct - it empty or isn*t json";//+
		return false;
	}
	if( !mustExistBeInt(parsedFromString[FIELD_TASK_ID], "task"))
		return false;


	Value field_operation = parsedFromString[FIELD_OPERATION];

	if (!mustExistBeString(field_operation, string("operation")))
		return false;

	if ( field_operation =="addUtest" || field_operation =="u")
		return true;

	if (parsedFromString[FIELD_OPERATION]=="addtask" || parsedFromString[FIELD_OPERATION]=="edittask")
	{
		Json::Value field_etalon = parsedFromString[FIELD_ETALON];



		Json::Value field_tests_code = parsedFromString[FUNCTION][FIELD_TESTS_CODE];
		Json::Value field_args = parsedFromString[FUNCTION][FIELD_ARGS];
		Json::Value field_lang = parsedFromString[FIELD_CODE_LANGUAGE];
		Json::Value field_results = parsedFromString[FUNCTION][FIELD_RESULTS];
		Json::Value field_type = parsedFromString[FUNCTION][FIELD_TYPE];
		Json::Value field_compare_mark = parsedFromString[FUNCTION][FIELD_COMPARE_MARK];
		Json::Value field_array_type = parsedFromString[FUNCTION][FIELD_ARRAY_TYPE];
		Json::Value field_unit_test_num = parsedFromString[FUNCTION][FIELD_UNIT_TESTS_NUM];
		Json::Value field_size = parsedFromString[FUNCTION][FIELD_SIZE];

		if( !mustExist(parsedFromString[FUNCTION], "function"))
			return false;

		if( !mustExistBeString(field_lang, "lang"))
			return false;

		string lang_s = getAsString(field_lang);
		std::transform(lang_s.begin(), lang_s.end(), lang_s.begin(), ::tolower);
		int lang_int = 0;

		if (lang_s == "c++")
			lang_int = LangCompiler::Flag_CPP;
		else
			if (lang_s == "cs" || lang_s == "c#")
				lang_int = LangCompiler::Flag_CS;
			else
				if (lang_s == "js")
					lang_int = LangCompiler::Flag_JS;
				else
					if (lang_s == "php")
						lang_int = LangCompiler::Flag_PHP;
					else
						if (lang_s == "java")
							lang_int = LangCompiler::Flag_Java;
						else
						{
							last_error = "ERROR: lang not defined";//+
							return false;
						}



		bool is_results_exist;


		string etalon  = "";// = field_etalon.asString();

		if (mustExist(field_etalon , "etalon"))
		{
			if( !mustBeString( field_etalon , "etalon"))
				return false;

			etalon = field_etalon.asString();
		}

		if (etalon.size() > 0 && !(etalon.find_first_not_of("\t\n\r ") == string::npos))
			is_results_exist = false;
		else
		{
			if (!mustExist(field_results, "results"))
				return false;
			is_results_exist = true;
		}

		if( !mustExistBeInt(field_unit_test_num, "unit_test_num"))
			return false;

		unit_test_num = getAsInt(field_unit_test_num);//.asInt();


		if( !mustExistBeArrayString(field_tests_code, "tests_code",unit_test_num))
			return false;

		if( !mustExistBeArrayInt(field_compare_mark, "compare_mark",unit_test_num, false,"", "",0, CompareMark::Last - 1))
			return false;

		if( !mustExistBeInt(field_array_type, "array_type"))
			return false;


		is_results_array = getAsInt(field_array_type);//.asInt();

		int result_type = getAsInt(field_type);

		int result_array_size = -1;

		if (is_results_array)
		{
			if( !mustExistBeIntMin(field_size, "size", 1))
				return false;

		}

		int compare_mark_size = field_compare_mark.size();
		if (  compare_mark_size != unit_test_num)
		{
			last_error = "ERROR: json format is not correct. field_compare_mark size = " + to_string(compare_mark_size) +
					", but unit_test_num = " +  to_string(unit_test_num);;					;
			return false;
		}

		if (is_results_exist)
		{
			if (is_results_array)
				result_array_size = getAsInt(field_size);
			/*if( !mustExistBeArray(field_results, "results", result_array_size))
				return false;*/
			if (!mustExistBeArrayOf(field_results, result_type, is_results_array, string("result" ),
					unit_test_num, result_array_size))
				return false;
		}

		if( !mustExistBeArray(field_args, "args", -1, true))
			return false;

		if( !mustExistBeInt(field_type, "type"))
			return false;

		int type_rezult = getAsInt(field_type) ;

		if (is_results_array)
			results_array_size = getAsInt(field_size);
		else
			results_array_size = -1;

		int field_tests_code_size = field_tests_code.size();

		/*if (is_results_exist)
			if ( !sizeEqualSizeOfUnitTests(field_results, "results"))
				return false;*/

		if ( !sizeEqualSizeOfUnitTests(field_tests_code, "tests_code"))
			return false;


		int args_size =  field_args.size();

		/*if ( results_size != args_size)
		{
			last_error = "ERROR: json format is not correct. Size of results (" + to_string(results_size) +
					") != size of args (" + to_string(args_size) + ")"
					;
			return false;
		}*/

		/*is_results_array = field_results[0].isArray();
		unit_test_num = field_results.size();*/


		if (is_results_exist)
		{



			/*if ( is_results_array == FunctionData::NOT_ARRAY )
			{
				switch(type_rezult)
				{
				case code::FunctionData::RET_VAL_RANGE:

					int range_size;
					bool range_size_inited;
					range_size_inited = false;
					for (int i=0; i < unit_test_num; i++)
					{
						if( !mustBeNotArrayString(field_results[i],
								string("results[" + to_string(i) + "]"), " of ranges", ", thats why can`t be range"))
							return false;

						string range = parsedFromString[FUNCTION][FIELD_RESULTS][i ].toStyledString();
						rangeValidation(range_size_inited, range_size, range, string("results[" + to_string(i) +"]"));
					}
					break;
				case code::FunctionData::RET_VAL_BOOL:
					for (int i=0; i < unit_test_num; i++)
					{
						if( !mustBeNotArrayBool(field_results[i],string("results[" + to_string(i) + "]"), ", cuz results[0] isn`t"))
							return false;
					}
					break;
				case code::FunctionData::RET_VAL_FLOAT	:
					for (int i=0; i < unit_test_num; i++)
					{
						if( !mustBeNotArrayFloat(field_results[i], string("results[" + to_string(i) + "]"), ", cuz results[0] isn`t"))
							return false;
					}
					break;
				case code::FunctionData::RET_VAL_INT	:
					for (int i=0; i < unit_test_num; i++)
					{
						if( !mustBeNotArrayInt(field_results[i], string("results[" + to_string(i) + "]"), ", cuz results[0] isn`t"))
							return false;
					}
					break;
				case code::FunctionData::RET_VAL_STRING:
					for (int i=0; i < unit_test_num ; i++)
					{
						if( !mustBeNotArrayString(field_results[i],	string("results[" + to_string(i) + "]"), ", cuz results[0] isn`t"))
							return false;
					}
					break;
				default:
				{
					last_error = "ERROR: json format is not correct. Result type don`t recognized";
					return false;
				}
				}
			}
			else
				if ( is_results_array == FunctionData::ARRAY )
				{
					//int results_0_array_size  = field_results[0].size();
					//results_array_size = results_0_array_size;

					if(!mustHaveSizeMoreZero(field_results[0],"results[0]","Where results[0] values?"))
						return false;

					if ( field_results[0][0].isArray())
					{
						if( !mustBeNotArray(field_results[0][0],"results[0][0][0]"))
							return false;
					}


					for (int k=0; k < unit_test_num; k++)
					{
						Json::Value result_k = field_results[k];

						if( !mustBeArray(result_k, string("results[" + to_string(k) +	"]"), ", cuz results[0] is array"))
							return false;

						int results_k_array_size  = result_k.size();

						if ( results_k_array_size != results_array_size)
						{
							last_error = "ERROR: json format is not correct. Results[" + to_string(k) +
									"] size = "+ to_string(results_k_array_size) +
									", but results_array_size = " + to_string(results_array_size);//555
							return false;
						}
						{
							switch(type_rezult)
							{
							case code::FunctionData::RET_VAL_RANGE:

								last_error = "ERROR: json format is not correct. results[" + to_string(k) +
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
								last_error = "ERROR: json format is not correct. Result type don*t recognized";
								return false;
							}
						}
					}
				}*/
		}


		//bool args_0_values_is_array =


		/*bool values_0_is_array_seted = false;
		bool args_0_values_0_is_array;
		int args_0_value_type;
		int args_0_values_size;*/

		vector <string> arg_names;

		for (int i=0; i < args_size; i++)
		{

			Json::Value args_i = parsedFromString[FUNCTION][FIELD_ARGS][ i ];
			Json::Value args_i_type = parsedFromString[FUNCTION][FIELD_ARGS][ i ][FIELD_TYPE];
			Json::Value args_i_compare_mark = parsedFromString[FUNCTION][FIELD_ARGS][ i ][FIELD_COMPARE_MARK];
			Json::Value args_i_is_array = parsedFromString[FUNCTION][FIELD_ARGS][ i ][FIELD_IS_ARRAY];
			Json::Value args_i_arg_name = args_i[FIELD_ARG_NAME];
			Json::Value args_i_value = args_i[FIELD_VALUE];
			Json::Value args_i_etalon_value = args_i[FIELD_ETALON_VALUE];
			Json::Value args_i_arg_size = args_i["size"];

			if(!mustExistBeInt(args_i_type, string("type of args[" + to_string(i) + "]" )))
				return false;

			if(!mustExistBeInt(args_i_is_array, string("is_array of args[" + to_string(i) + "]" )))
				return false;

			int value_type = getAsInt(args_i_type);

			if ( value_type >= ValueTypes::VAL_Last)
			{
				last_error = "ERROR: json format is not correct. Field \"type\" of args[" +
						to_string(i) + "] out of types"; //
				return false;
			}

			int arg_is_array =  getAsInt(args_i_is_array);

			int arg_i_array_size = -1;
			if (arg_is_array)
			{
				if (!mustExistBeInt(args_i_arg_size,string("size of args[" + to_string(i) + "]" )))
					return false;
				arg_i_array_size = getAsInt(args_i_arg_size);
			}

			if (!mustExistBeArrayOf(args_i_value, value_type, arg_is_array,
					string("value of args[" + to_string(i) + "]" ), unit_test_num, arg_i_array_size))
				return false;

			bool is_args_i_etalon_value = false;
			if (mustExist(args_i_etalon_value, string("etalon_value of args[" + to_string(i) + "]" )))
			{
				int siz = args_i_etalon_value.size();
				if (siz  > 0)
				{
					if (!mustExistBeArrayOf(args_i_etalon_value, value_type, arg_is_array,
							string("etalon_value of args[" + to_string(i) + "]" ), unit_test_num, arg_i_array_size, true))
						return false;
					is_args_i_etalon_value = true;
				}
			}

			if(!mustExistBeString(args_i_arg_name, string("arg_name of args[" + to_string(i) + "]" )))
				return false;

			string cur_arg_name = getAsString(args_i_arg_name);
			for (string temp_name : arg_names)
			{
				if (temp_name == cur_arg_name)
				{
					last_error = "ERROR: json format is not correct. arg_name of args[" + to_string(i) + "] value ("
							+ cur_arg_name + ") repeat second time";
					return false;
				}
			}
			arg_names.push_back(cur_arg_name);

			if (!mustBeNotKeyword(args_i_arg_name, string("arg_name of args[" + to_string(i) + "]" ), lang_int))
				return false;

			if(!mustExistBeArrayInt(args_i_compare_mark, string("compare_mark of args[" +
					to_string(i) + "]" ), unit_test_num))
				return false;
			/*	bool mustExistBeArrayInt(Json::Value object, string name,
					int array_size, bool enable_zero_len = false , string ps = "", string ps2 = "");*/
			int args_i_compare_mark_size = args_i_compare_mark.size();
			/*if ( args_i_compare_mark_size != unit_test_num )
			{
				last_error = "ERROR: json format is not correct. Args[" + to_string(i) +
						"] compare_mark size (" + to_string(args_i_compare_mark_size) + ") != unit_test_num (" +
						to_string(unit_test_num) + ")";
				return false;
			}*/

			int values_size = args_i_value.size();

			if ( values_size != unit_test_num )
			{
				last_error = "ERROR: json format is not correct. Args[" + to_string(i) +
						"] values size (" + to_string(values_size) + ") != unit_test_num (" +
						to_string(unit_test_num) + ")";
				return false;
			}

			//////////1


			/*if(!mustExistBeArrayInt(args_i_compare_mark, string("compare_mark of args[" + to_string(i) + "]" ),"","",0, CompareMark::Last - 1))
				return false;*/

			int etalon_values_size = args_i_etalon_value.size();

			if (is_args_i_etalon_value)
				if ( etalon_values_size != unit_test_num )
				{
					last_error = "ERROR: json format is not correct. Args[" + to_string(i) +
							"] etalon_value size (" + to_string(etalon_values_size) + ") != runit_test_num(" +
							to_string(unit_test_num) + ")";
					return false;
				}

			//666


			/*if ( !arg_is_array )
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

						string range = getAsString(args_i_value[j]);
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
					last_error = "ERROR: json format is not correct. Args[" + to_string(i) + "] type don*t recognized";
					return false;
				}
			}
			else
			{
				//1569
				int values_0_array_size  = args_i_value[0].size();
				if (!mustHaveSizeMoreZeroAndBeNotTwoDimensionalArray(args_i_value[0],string("args[" + to_string(i) +"] values[0]")))
					return false;

				if (!mustHaveSizeMoreZeroAndBeNotTwoDimensionalArray(args_i_etalon_value[0],string("args[" + to_string(i) +"] etalon_values[0]")))
					return false;
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
						last_error = "ERROR: json format is not correct. " + s_value_k +
								" size = "+ to_string(values_k_array_size) +
								", but args[" + to_string(i) +"] values[0] size = " + to_string(values_0_array_size);
						return false;
					}

					if ( !mustBeArray(field_etalon_value_k, s_etalon_value_k,", cuz args[0] etalon_value[0] is array") )
						return false;

					if ( field_etalon_value_k.size() != values_0_array_size)
					{
						last_error = "ERROR: json format is not correct. " + s_etalon_value_k +
								" size = "+ to_string(values_k_array_size) +
								", but args[" + to_string(i) +"] values[0] size = " + to_string(values_0_array_size);
						return false;
					}


					switch(value_type)
					{
					///////// 1
					case code::FunctionData::RET_VAL_RANGE:

						last_error = "ERROR: json format is not correct. " + s_value_k +
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
						last_error = "ERROR: json format is not correct. Args[" + to_string(i) +" type don*t recognized";
						return false;
					}

				}
			}*/
		}
		return true;
	}

	Value operation = parsedFromString[FIELD_OPERATION];
	if (operation == "start" || operation == "s")
	{
		if( !mustExist(parsedFromString[FIELD_JOBID], "token"))
			return false;

		if( !mustExist(parsedFromString[FIELD_JOBID], "session"))
			return false;

		if( !mustExist(parsedFromString[FIELD_JOBID], "jobid"))
			return false;

		if( !mustExistBeString(parsedFromString[FIELD_CODE_TEXT], "code"))
			return false;
		/*if(parsedFromString[FIELD_CODE_LANGUAGE].isNull() )
		{
			last_error = "ERROR: json format is not correct. Field \"lang\" not exist"; //
			return false;
		}
		if ( !parsedFromString[FIELD_CODE_LANGUAGE].isString())
		{
			last_error = "ERROR: json format is not correct. Field \"lang\" not string";
			return false;
		}*/

	}
	else if (operation =="status"){

	}
	else if (operation =="getJson"){
		/*if( !mustExistBeString(parsedFromString[FIELD_CODE_LANGUAGE], "lang"))
			return false;*/
		if( !mustExistBeInt(parsedFromString[FIELD_TASK_ID], "task"))
			return false;

	}
	else if (operation =="result" || operation =="r"){

		if( !mustExist(parsedFromString[FIELD_JOBID], "jobid"))
			return false;

	}
	else if (operation=="getToken"){

	}
	else if (operation=="getFromToken"){
		if( !mustExistBeString(parsedFromString[FIELD_TOKEN], "token"))
			return false;
	}
	else
	{
		last_error = "ERROR: json format is not correct. Operation ";
		last_error += parsedFromString[FIELD_OPERATION].toStyledString();
		last_error += " not exist";
		return false ;
	}
	/*
	 *  conver test  add
	 */

	return true;
}
