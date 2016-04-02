#include "../inc/jsonParser.h"
#include "../inc/TaskCodeGenerator.h"


bool jsonParser::parseAddUtest(Value &pres_task)
{
	if (parsedFromString[FIELD_OPERATION]=="addUtest" || parsedFromString[FIELD_OPERATION]=="u")
	{

		Value lang = parsedFromString[FIELD_CODE_LANGUAGE];
		Value field_function = parsedFromString[FUNCTION];
		Value fiedl_chakable_arg_indexes = field_function["checkable_args_indexes"];
		Value field_unit_test_num = field_function[FIELD_UNIT_TESTS_NUM];
		Value field_args = field_function[FIELD_ARGS];
		Value field_results = field_function[FIELD_RESULTS];
		Value field_compare_mark = field_function[FIELD_COMPARE_MARK];

		Value pres_task_etalon = pres_task[FIELD_ETALON]; //999
		Value pres_task_lang = pres_task[FIELD_CODE_LANGUAGE]; //999
		Value pres_task_result_type = pres_task[FUNCTION][FIELD_TYPE];
		Value pres_task_result_is_array = pres_task[FUNCTION][FIELD_ARRAY_TYPE];
		Value pres_task_result_array_size = pres_task[FUNCTION][FIELD_SIZE];



		if (!mustExistBeString(lang,"lang"))
			return false;



		if (!parseChekableArgIndexes(field_function))
			return false;

		//Json::Value field_compare_mark = parsedFromString[FUNCTION][FIELD_COMPARE_MARK];



		string lang_s = getAsString(lang);

		if( !mustExistBeInt(field_unit_test_num, "unit_test_num"))
			return false;

		unit_test_num = getAsInt(field_unit_test_num);//.asInt();




		bool is_results_exist;

		int args_size =  field_args.size();

		if( !mustExistBeArray(field_args, "args", -1, true))
			return false;





		string ss = getAsString(pres_task[FUNCTION]);


		string pres_task_lang_s = getAsString(pres_task_lang);
		string pres_task_etalon_s = getAsString(pres_task_etalon);

		//chek result
		int p_res_type = getAsInt(pres_task_result_type);
		int p_res_is_array = getAsInt(pres_task_result_is_array);
		int p_res_array_size ;
		if (p_res_is_array == 0)
			p_res_array_size = 0;
		else
			p_res_array_size = getAsInt(pres_task_result_array_size);

		if (!mustExistBeArrayOf(field_results, p_res_type, p_res_is_array, string("result" ),
				unit_test_num, p_res_array_size))
			return false;




		/*if (p_res_is_array)
		{
		if ( !mustExistBeArray(field_results, "results", p_res_array_size, false))
			return false;


		}
		else
		{
			if ( !mustexi)
		}*/




		//chek lang
		if (pres_task_lang_s != lang_s)
		{
			last_error =  "ERROR: json format is not correct. lang of unit tests (" + lang_s +
					") != lang of task (" + pres_task_lang_s + ")";
			return false;
		}

		if (pres_task_etalon_s.size() > 0 && !(pres_task_etalon_s.find_first_not_of("\t\n\r ") == string::npos))
		{
			is_results_exist = false;
		}
		else
		{
			if (!mustExist(field_results, "results"))
				return false;
			is_results_exist = true;
		}


		if( !mustExistBeArrayInt(field_compare_mark, "compare_mark",unit_test_num, false,"", "",0, CompareMark::Last - 1))
			return false;

		Value field_array_type = parsedFromString[FUNCTION][FIELD_ARRAY_TYPE];
		Value field_result_type = parsedFromString[FUNCTION][FIELD_TYPE];
		Value field_result_size = parsedFromString[FUNCTION][FIELD_SIZE];

		is_results_array = getAsInt(pres_task[FUNCTION][FIELD_ARRAY_TYPE]);
		//pres_task.getFieldInt(field_array_type); //878

		int result_type = getAsInt(pres_task[FUNCTION][FIELD_TYPE]);
		//pres_task.getFieldInt(field_result_type);

		int result_array_size = -1;

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

				result_array_size = getAsInt(pres_task[FUNCTION][FIELD_SIZE]);
			//pres_task.getFieldInt(field_result_size);

			if (!mustExistBeArrayOf(field_results, result_type, is_results_array, string("result" ),
					unit_test_num, result_array_size))
				return false;
		}


		if( !mustExistBeArrayInt(field_compare_mark, "compare_mark",unit_test_num, false,"", "",0, CompareMark::Last - 1))
			return false;



		int pres_task_args_size = pres_task[FUNCTION][FIELD_ARGS][0][FIELD_VALUE].size();   //pres_task.getFieldInt();

		if ( args_size != pres_task_args_size)
		{
			last_error = "ERROR: json format is not correct. args size (" + to_string(args_size) +
					") != " +  to_string(pres_task_args_size);
			return false;
		}

		vector <string> arg_names;

		for (int i=0; i < args_size; i++)
		{

			Json::Value args_i = parsedFromString[FUNCTION][FIELD_ARGS][ i ];
			Value args_i_is_array = parsedFromString[FUNCTION][FIELD_ARGS][ i ][FIELD_IS_ARRAY];
			Value args_i_arg_name = parsedFromString[FUNCTION][FIELD_ARGS][ i ][FIELD_ARG_NAME];
			Json::Value args_i_value = args_i[FIELD_VALUE];
			Json::Value arg_i_field_compare_mark = args_i[FIELD_COMPARE_MARK];
			Json::Value args_i_etalon_value = args_i[FIELD_ETALON_VALUE];

			Value args_i_field_type = pres_task[FUNCTION][FIELD_ARGS][ i ][FIELD_TYPE];
			Value args_i_field_is_array = pres_task[FUNCTION][FIELD_ARGS][ i ][FIELD_IS_ARRAY];
			Value args_i_field_size = pres_task[FUNCTION][FIELD_ARGS][ i ][FIELD_SIZE];
			Value pres_task_args_i_arg_name = pres_task[FUNCTION][FIELD_ARGS][ i ][FIELD_ARG_NAME];


			if( !mustExistBeArrayInt(arg_i_field_compare_mark, "compare_mark",unit_test_num, false,"", "",0, CompareMark::Last - 1))
						return false;


			int args_i_type = getAsInt(args_i_field_type);
			//	pres_task.getFieldInt(args_i_field_type);   //[FUNCTION][FIELD_ARGS][ i ][FIELD_TYPE]);

			//	Json::Value args_i_compare_mark = parsedFromString[FUNCTION][FIELD_ARGS][ i ][FIELD_COMPARE_MARK];



			int args_i_is_array_int = getAsInt(args_i_is_array);
			//pres_task.getFieldInt(args_i_is_array);

			string pres_task__i_arg_name = getAsString(pres_task_args_i_arg_name);
			//pres_task.getFieldS(args_i_arg_name);




			int pres_task_value_type = getAsInt(args_i_field_type);

			int arg_is_array = getAsInt(args_i_field_is_array);
			//…///getAsInt(args_i_is_array);

			int arg_i_array_size = getAsInt(args_i_field_size); //					…///-1;

			if (!mustExistBeArrayOf(args_i_value, args_i_type, arg_is_array,
					string("value of args[" + to_string(i) + "]" ), unit_test_num, arg_i_array_size))
				return false;

			bool is_args_i_etalon_value = false;
			if (mustExist(args_i_etalon_value, string("etalon_value of args[" + to_string(i) + "]" )))
			{
				int siz = args_i_etalon_value.size();
				if (siz  > 0)
				{
					if (!mustExistBeArrayOf(args_i_etalon_value, args_i_type, arg_is_array,
							string("etalon_value of args[" + to_string(i) + "]" ), unit_test_num, arg_i_array_size, true))
						return false;
					is_args_i_etalon_value = true;
				}
			}

			if(!mustExistBeString(args_i_arg_name, string("arg_name of args[" + to_string(i) + "]" )))
				return false;

			string cur_arg_name = getAsString(args_i_arg_name);

			if ( cur_arg_name != pres_task__i_arg_name)
			{
				last_error = "ERROR: json format is not correct. args " + to_string(i) +
						" name(" + cur_arg_name + ") != " +  pres_task__i_arg_name;
				return false;
			}

			arg_names.push_back(cur_arg_name);

			/*if(!mustExistBeArrayInt(args_i_compare_mark, string("compare_mark of args[" +
					to_string(i) + "]" ), unit_test_num))
				return false;*/

			//int args_i_compare_mark_size = args_i_compare_mark.size();


			int values_size = args_i_value.size();

			if ( values_size != unit_test_num )
			{
				last_error = "ERROR: json format is not correct. Args[" + to_string(i) +
						"] values size (" + to_string(values_size) + ") != unit_test_num (" +
						to_string(unit_test_num) + ")";
				return false;
			}


			int etalon_values_size = args_i_etalon_value.size();

			if (is_args_i_etalon_value)
				if ( etalon_values_size != unit_test_num )
				{
					last_error = "ERROR: json format is not correct. Args[" + to_string(i) +
							"] etalon_value size (" + to_string(etalon_values_size) + ") != runit_test_num(" +
							to_string(unit_test_num) + ")";
					return false;
				}


		}
		return true;
	}
}
