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
	initKeywords();
}

bool jsonParser::sizeEqualSizeOfUnitTests(Json::Value object, string name)
{
	int object_size = object.size();
	if ( unit_test_num != object_size )
	{
		last_error = "ERROR: json format is not correct. " + name + " array size = " +
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

bool jsonParser::isStringInt(string value, bool enable_zero_len)
{
	/*regex regStr("^[-0-9][0-9]{0,}");
	return  std::regex_match( value, regStr );*/
	if (value.size() == 0)
	{
		if (enable_zero_len)
			return true;
		else
			return false;
	}
	char cymbl = value[0];
	if (cymbl == '-' && value.size() == 1)
		return false;
	else
		if (cymbl != '-' && (cymbl < '0' || cymbl > '9'))
			return false;

	for (int i = 1; i < value.size(); i++)
	{
		cymbl = value[i];
		if (cymbl < '0' || cymbl > '9')
			return false;
	}
	return true;
}

bool jsonParser::isStringUnsignedInt(string value, bool enable_zero_len)
{
	regex regStr("^[0-9][0-9]{0,}");
	return  std::regex_match( value, regStr );
}

bool jsonParser::isStringBool(string value, bool enable_zero_len)
{
	if (value.size() == 0)
	{
		if (enable_zero_len)
			return true;
		else
			return false;
	}
	std::transform(value.begin(), value.end(), value.begin(), ::tolower);
	return (value == "false" || value == "true" || value == "1" || value == "0" );
}

bool jsonParser::isStringFloat(string value, bool enable_zero_len)
{
	/*string range_no_quotes = value.substr(1, value.size() - 3);
	regex regStr("^[-0-9][0-9]{0,}.?[0-9]{1,}");
	//regex regStr("[0-9]{0,}");
	return  std::regex_match( value, regStr );*/
	bool no_point = true;

	if (value.size() == 0)
	{
		if (enable_zero_len)
			return true;
		else
			return false;
	}
	char cymbl = value[0];
	if (cymbl != '-' && (cymbl < '0' || cymbl > '9'))
		return false;

	for (int i = 1; i < value.size(); i++)
	{
		cymbl = value[i];
		if (cymbl == '.')
		{
			if (no_point)
				no_point = false;
			else
				return false;
		}
		else
			if (cymbl < '0' || cymbl > '9')
				return false;
	}
	return true;
}

bool jsonParser::rangeValidation(bool &range_size_inited, int &range_size, string range, string field_name)
{
	string range_no_quotes = range.substr(1, range.size() - 3);
	regex regStr("^[-0-9][0-9]{0,}..[-0-9][0-9]{0,}");
	if (!std::regex_match( range_no_quotes, regStr ))
	{
		last_error = "ERROR: json format is not correct. " + field_name + " range format invalid "; //
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
			last_error = "ERROR: json format is not correct. " + field_name +
					" range size (" + to_string(range_i_size) +
					") != results[0] range size ("  +
					to_string(range_size) + ")";
			return false;
		}
	return true;
}

bool jsonParser::mustBeArrayFloat(Json::Value object, string name , int size, bool enable_zero_len , string ps, string ps2 )
{
	if (!mustBeArray(object,name,size,ps))
		return false;
	int obj_size = object.size();
	for (int i = 0; i < obj_size ; i++)
		if (!mustBeFloat(object[i], name + stringInScobcah(i), ps2,enable_zero_len))
			return false;
	return true;
}

bool jsonParser::mustBeArrayInt(Json::Value object, string name , int size, bool enable_zero_len , string ps, string ps2 )
{
	if (!mustBeArray(object,name ,size ,ps))
		return false;
	for (int i = 0; i < object.size(); i++)
		if (!mustBeInt(object[i], name + stringInScobcah(i), ps2,enable_zero_len))
			return false;
	return true;
}

bool jsonParser::mustBeArrayString(Json::Value object, string name, int size, bool enable_zero_len  , string ps, string ps2 )
{
	if (!mustBeArray(object,name,size ,ps))
		return false;
	for (int i = 0; i < object.size(); i++)
		if (!mustBeString(object[i], name + stringInScobcah(i), ps2))
			return false;
	return true;
}

bool jsonParser::mustBeArrayBool(Json::Value object, string name , int size, bool enable_zero_len , string ps, string ps2 )
{
	if (!mustBeArray(object,name,size ,ps))
		return false;
	for (int i = 0; i < object.size(); i++)
		if (!mustBeBool(object[i], name + stringInScobcah(i), ps2,enable_zero_len))
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
		last_error = "ERROR: json format is not correct. " + name + " can`t be array " + ps;
		return false;
	}
	return true;
}

bool jsonParser::mustBeArray(Json::Value object, string name, int size, string ps )
{
	if ( !object.isArray())
	{
		last_error = "ERROR: json format is not correct. " + name + " must be array " + ps;
		return false;
	}
	if (size > -1)
	{
		if (object.size() != size)
		{
			last_error = "ERROR: json format is not correct. " + name +" array size (" +
					to_string(object.size()) + ") != " + to_string(size);
			return false;
		}
	}
	else
		if (!mustHaveSizeMoreZero(object,name,ps))
			return false;
	return true;
}


bool jsonParser::mustHaveSizeMoreZero(Json::Value object, string name , string ps)
{
	if ( object.size() < 1)
	{
		last_error = "ERROR: json format is not correct. " + name + " size < 1 " + ps;
		return false;
	}
	return true;
}

bool jsonParser::mustBeInt(Json::Value object, string name , string ps , bool enable_zero_len)
{
	if ( object.isString())
	{
		if (!isStringInt(object.asString(), enable_zero_len))
		{
			last_error = "ERROR: json format is not correct. " + name +" isn`t convertible to int " + ps;
			return false;
		}
		return true;
	}
	if ( !object.isInt())
	{
		last_error = "ERROR: json format is not correct. " + name +" isn`t integer " + ps;
		return false;
	}
	return true;
}

bool jsonParser::mustBeUnsignedInt(Json::Value object, string name , string ps )
{
	if ( object.isString())
	{
		if (!isStringUnsignedInt(object.asString()))
		{
			last_error = "ERROR: json format is not correct. " + name +" isn`t convertible to unsigned int " + ps;
			return false;
		}
		return true;
	}
	if ( !object.isInt() && !object.isUInt())
	{
		last_error = "ERROR: json format is not correct. " + name +" isn`t unsigned integer " + ps;
		return false;
	}
	string obg_string = object.toStyledString();
	obg_string = obg_string.substr(0, obg_string.size() - 1 );

	unsigned int obj_str_size = obg_string.size();

	if (obj_str_size < max_uint_value.size())
		return true;

	if (obg_string.size() > max_uint_value.size())
	{
		last_error = "ERROR: json format is not correct. " + name +" out of range of unsigned integer (max value = " + max_uint_value + ")" + ps;
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
			last_error = "ERROR: json format is not correct. " + name +" out of range of unsigned integer (max value = " + max_uint_value + ")" + ps;
			return false;
		}
	}

	return true;
}

bool jsonParser::mustExist(Json::Value object, string name  , string ps)
{
	if ( object.isNull())
	{
		last_error = "ERROR: json format is not correct. " + name +" don`t exist " + ps;
		return false;
	}
	return true;
}

bool jsonParser::mustExistBeInt(Json::Value object, string name  , string ps , string ps2)
{
	if ( object.isNull())
	{
		last_error = "ERROR: json format is not correct. " + name +" don`t exist " + ps;
		return false;
	}
	if (!mustBeInt(object, name, ps2))
		return false;
	return true;
}

bool jsonParser::mustExistBeIntMin(Json::Value object, string name, int min_value)
{
	if (!mustExistBeInt(object, name))
		return false;
	int value = getAsInt(object);
	if (value < min_value)
	{
		last_error = "ERROR: json format is not correct. " + name +" value( " + to_string(value) + ") less then min(" + to_string(min_value) + ")";
		return false;
	}
	return true;
}

bool jsonParser::mustExistBeUnsignedInt(Json::Value object, string name  , string ps , string ps2)
{
	if ( object.isNull())
	{
		last_error = "ERROR: json format is not correct. " + name +" don`t exist " + ps;
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
		last_error = "ERROR: json format is not correct. " + name +" don`t exist " + ps;
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
		last_error = "ERROR: json format is not correct. " + name +" don`t exist " + ps;
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
		last_error = "ERROR: json format is not correct. " + name +" don`t exist " + ps;
		return false;
	}
	if (!mustBeBool(object, name, ps2))
		return false;
	return true;
}

bool jsonParser::mustExistBeArray(Json::Value object, string name,  int array_size  , string ps , string ps2)
{
	if ( object.isNull())
	{
		last_error = "ERROR: json format is not correct. " + name +" don`t exist " + ps;
		return false;
	}
	if (!mustBeArray(object, name, array_size,  ps2))
		return false;
	return true;
}

bool jsonParser::mustExistBeArrayString(Json::Value object, string name,  int array_size , string ps, string ps2 )
{
	if (!mustExistBeArray(object, name, array_size, ps,ps2))
		return false;
	for (int i = 0; i < object.size(); i++)
		if (!mustBeString(object[i], name + stringInScobcah(i)))
			return false;
	return true;
}
bool jsonParser::mustExistBeArrayInt(Json::Value object, string name ,  int array_size, bool enable_zero_len , string ps, string ps2 )
{
	if (!mustExistBeArray(object, name, array_size, ps,ps2))
		return false;
	for (int i = 0; i < object.size(); i++)
		if (!mustBeInt(object[i], name + stringInScobcah(i),"",enable_zero_len))
			return false;
	return true;
}

bool jsonParser::mustExistBeArrayBool(Json::Value object, string name ,  int array_size, bool enable_zero_len , string ps, string ps2 )
{
	if (!mustExistBeArray(object, name, array_size, ps,ps2))
		return false;
	for (int i = 0; i < object.size(); i++)
		if (!mustBeBool(object[i], name + stringInScobcah(i),"", enable_zero_len))
			return false;
	return true;
}



bool jsonParser::mustExistBeArrayOfBoolArrays(Json::Value object, string name,  int array_size , int size_i_array , bool enable_zero_len, string ps, string ps2 )
{
	if (!mustExistBeArray(object, name, array_size, ps,ps2))
		return false;
	for (int i = 0; i < object.size(); i++)
		if (!mustBeArrayBool(object[i], name + stringInScobcah(i),size_i_array,enable_zero_len))
			return false;
	return true;
}

bool jsonParser::mustExistBeArrayOfStringArrays(Json::Value object, string name,  int array_size , int size_i_array , bool enable_zero_len, string ps, string ps2 )
{
	if (!mustExistBeArray(object, name, array_size, ps,ps2))
		return false;
	for (int i = 0; i < object.size(); i++)
		if (!mustBeArrayString(object[i], name + stringInScobcah(i),size_i_array,enable_zero_len))
			return false;
	return true;
}

bool jsonParser::mustExistBeArrayOfIntArrays(Json::Value object, string name,  int array_size  , int size_i_array, bool enable_zero_len, string ps, string ps2 )
{
	if (!mustExistBeArray(object, name, array_size, ps,ps2))
		return false;
	for (int i = 0; i < object.size(); i++)
		if (!mustBeArrayInt(object[i], name + stringInScobcah(i),size_i_array, enable_zero_len))
			return false;
	return true;
}

bool jsonParser::mustExistBeArrayOfFloatArrays(Json::Value object, string name,  int array_size , int size_i_array, bool enable_zero_len , string ps, string ps2 )
{
	if (!mustExistBeArray(object, name, array_size, ps,ps2))
		return false;
	for (int i = 0; i < object.size(); i++)
		if (!mustBeArrayFloat(object[i], name + stringInScobcah(i), size_i_array, enable_zero_len))
			return false;
	return true;
}

bool jsonParser::mustExistBeArrayFloat(Json::Value object, string name ,  int array_size, bool enable_zero_len, string ps, string ps2 )
{
	if (!mustExistBeArray(object, name, array_size, ps,ps2))
		return false;
	for (int i = 0; i < object.size(); i++)
		if (!mustBeFloat(object[i], name + stringInScobcah(i),"",enable_zero_len))
			return false;
	return true;
}

bool jsonParser::mustExistBeArrayInt(Json::Value object, string name ,  int array_size, bool enable_zero_len, string ps, string ps2 , int min_val, int max_val)
{
	if (!mustExistBeArray(object, name, array_size, ps,ps2))
		return false;
	for (int i = 0; i < object.size(); i++)
	{
		if (!mustBeInt(object[i], name + stringInScobcah(i),"", enable_zero_len))
			return false;
		int int_obj = getAsInt(object[i]);//.asInt();
		if (int_obj < min_val || int_obj > max_val)
		{
			last_error = "ERROR: json format is not correct. " +  name + stringInScobcah(i) +" value(" + to_string(int_obj) +
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



bool jsonParser::mustBeFloat(Json::Value object, string name  , string ps, bool enable_zero_len)
{
	if ( object.isString())
	{
		if (!isStringFloat(object.asString(),enable_zero_len))
		{
			last_error = "ERROR: json format is not correct. " + name +" isn`t convertible to float " + ps;
			return false;
		}
		return true;
	}
	if ( !object.isDouble())
	{
		last_error = "ERROR: json format is not correct. " + name +" isn`t float " + ps;
		return false;
	}
	return true;
}
bool jsonParser::mustBeString(Json::Value object, string name , string ps, bool enable_zero_len )
{
	if ( !object.isString())
	{
		last_error = "ERROR: json format is not correct. " + name +" isn`t string " + ps;
		return false;
	}
	return true;
}

bool jsonParser::mustBeNotKeyword(Json::Value object, string name, int lang)
{
	string str = object.asString();

	switch(lang)
	{
	case LangCompiler::Flag_CPP: case LangCompiler::Flag_CS: case LangCompiler::Flag_PHP:
		if (str[0] >= '0' && str[0] <= '9')
		{
			last_error = "ERROR: json format is not correct. " + name +" value[0] (\""+ str[0] + "\") out of avaible cymbols (A-Z,a-z, _ )";
			return false;
		}
		for(int i = 0; i < str.size(); i++)
		{
			char c = str[i];
			if ( !(c == '_' ||
					(c >= 'a' && c <='z') ||
					(c >= 'A' && c <='Z') ||
					c >= '0' && c <= '9'))
			{
				last_error = "ERROR: json format is not correct. " + name +" value (\""+ str + "\") out of avaible cymbols (A-Z,a-z, _ , 0-9)";
				return false;
			}
		}
		break;

	case LangCompiler::Flag_JS: case LangCompiler::Flag_Java:
		if (str[0] >= '0' && str[0] <= '9')
		{
			last_error = "ERROR: json format is not correct. " + name +" value[0] (\""+ str[0] + "\") out of avaible cymbols (A-Z,a-z, _ )";
			return false;
		}
		for(int i = 0; i < str.size(); i++)
		{
			char c = str[i];
			if ( !(c == '_' || c == '$' ||
					(c >= 'a' && c <='z') ||
					(c >= 'A' && c <='Z') ||
					c >= '0' && c <= '9'))
			{
				last_error = "ERROR: json format is not correct. " + name +" value (\""+ str + "\") out of avaible cymbols (A-Z,a-z, _ , $,  0-9)";
				return false;
			}
		}
		break;
	}

	if (isStrKeyWord(str, lang))
	{
		last_error = "ERROR: json format is not correct. " + name +" value (\""+ str + "\") match to keyword";
		return false;
	}
	return true;
}

bool jsonParser::mustBeBool(Json::Value object, string name , string ps, bool enable_zero_len )
{
	if ( object.isString())
	{
		if (!isStringBool(object.asString(), enable_zero_len))
		{
			last_error = "ERROR: json format is not correct. " + name +" isn`t convertible to bool " + ps;
			return false;
		}
		return true;
	}
	if ( !object.isBool())
	{
		if (object.isInt())
		{
			int asint = object.asInt();
			if (asint == 0 || asint == 1)
				return true;
		}
		last_error = "ERROR: json format is not correct. " + name +" isn`t boolean " + ps;
		return false;
	}
	return true;
}

bool jsonParser::isStrInVector(string str, vector<string> vec)
{
	int str_size = str.size();
	for(string temp: vec)
	{
		int temp_size = temp.size();
		if (temp_size == str_size)
		{
			bool is_overlap = true;
			for (int i = 0; i < temp_size; )
			{
				if (str[i] == temp[i])
					i++;
				else
				{
					is_overlap = false;
					break;
				}
			}
			if (is_overlap)
				return true;
		}
	}
	return false;
}

bool jsonParser::isStrKeyWord(string str,int lang)
{
	switch(lang)
	{
	case LangCompiler::Flag_CPP:
		return isStrInVector(str, keywords_cpp);

	case LangCompiler::Flag_CS:
		return isStrInVector(str, keywords_cs);

	case LangCompiler::Flag_JS:
		return isStrInVector(str, keywords_js);

	case LangCompiler::Flag_Java:
		return isStrInVector(str, keywords_java);

	case LangCompiler::Flag_PHP:
		return false;
	}
	return false;
}

void jsonParser::initKeywords()
{
	keywords_cpp.push_back("asm");
	keywords_cpp.push_back("auto");
	keywords_cpp.push_back("bool");
	keywords_cpp.push_back("break");
	keywords_cpp.push_back("case");
	keywords_cpp.push_back("catch");
	keywords_cpp.push_back("char");
	keywords_cpp.push_back("class");
	keywords_cpp.push_back("const");
	keywords_cpp.push_back("const_cast");
	keywords_cpp.push_back("continue");
	keywords_cpp.push_back("default");
	keywords_cpp.push_back("delete");
	keywords_cpp.push_back("do");
	keywords_cpp.push_back("double");
	keywords_cpp.push_back("dynamic_cast");
	keywords_cpp.push_back("else");
	keywords_cpp.push_back("enum");
	keywords_cpp.push_back("explicit");
	keywords_cpp.push_back("export");
	keywords_cpp.push_back("extern");
	keywords_cpp.push_back("false");
	keywords_cpp.push_back("float");
	keywords_cpp.push_back("for");
	keywords_cpp.push_back("friend");
	keywords_cpp.push_back("goto");
	keywords_cpp.push_back("goto");
	keywords_cpp.push_back("inline");
	keywords_cpp.push_back("int");
	keywords_cpp.push_back("long");
	keywords_cpp.push_back("mutable");
	keywords_cpp.push_back("namespace");
	keywords_cpp.push_back("new");
	keywords_cpp.push_back("operator");
	keywords_cpp.push_back("private");
	keywords_cpp.push_back("protected");
	keywords_cpp.push_back("public");
	keywords_cpp.push_back("register");
	keywords_cpp.push_back("reinterpret_cast");
	keywords_cpp.push_back("return");
	keywords_cpp.push_back("short");
	keywords_cpp.push_back("signed");
	keywords_cpp.push_back("sizeof");
	keywords_cpp.push_back("static");
	keywords_cpp.push_back("static_cast");
	keywords_cpp.push_back("short short");
	keywords_cpp.push_back("signed");
	keywords_cpp.push_back("sizeof");
	keywords_cpp.push_back("static");
	keywords_cpp.push_back("static_cast");
	keywords_cpp.push_back("struct");
	keywords_cpp.push_back("switch");
	keywords_cpp.push_back("template");
	keywords_cpp.push_back("this");
	keywords_cpp.push_back("throw");
	keywords_cpp.push_back("typedef");
	keywords_cpp.push_back("true");
	keywords_cpp.push_back("try");
	keywords_cpp.push_back("typeid");
	keywords_cpp.push_back("typename");
	keywords_cpp.push_back("union");
	keywords_cpp.push_back("voidunion");
	keywords_cpp.push_back("using");
	keywords_cpp.push_back("virtual");
	keywords_cpp.push_back("void");
	keywords_cpp.push_back("include");
	keywords_cpp.push_back("include");
	//keywords_cpp.push_back("ifndef");
	//keywords_cpp.push_back("ifdef");

	keywords_cpp.push_back("null");
	keywords_cpp.push_back("NULL");
	keywords_cpp.push_back("type");
	keywords_cpp.push_back("define");

	keywords_java.push_back("abstract");
	keywords_java.push_back("continue");
	keywords_java.push_back("for");
	keywords_java.push_back("new");
	keywords_java.push_back("switch");
	keywords_java.push_back("assert");
	keywords_java.push_back("default");
	keywords_java.push_back("goto");
	keywords_java.push_back("package");
	keywords_java.push_back("synchronized");
	keywords_java.push_back("boolean");
	keywords_java.push_back("do");
	keywords_java.push_back("if");
	keywords_java.push_back("private");
	keywords_java.push_back("this");
	keywords_java.push_back("break");
	keywords_java.push_back("double");
	keywords_java.push_back("implements");
	keywords_java.push_back("protected");
	keywords_java.push_back("throw");
	keywords_java.push_back("byte");
	keywords_java.push_back("else");
	keywords_java.push_back("import");
	keywords_java.push_back("public");
	keywords_java.push_back("throws");
	keywords_java.push_back("case");
	keywords_java.push_back("enum");
	keywords_java.push_back("instanceof");
	keywords_java.push_back("return");
	keywords_java.push_back("transient");
	keywords_java.push_back("catch");
	keywords_java.push_back("extends");
	keywords_java.push_back("int");
	keywords_java.push_back("short");
	keywords_java.push_back("try");
	keywords_java.push_back("char");
	keywords_java.push_back("final");
	keywords_java.push_back("interface");
	keywords_java.push_back("static");
	keywords_java.push_back("void");
	keywords_java.push_back("class");
	keywords_java.push_back("finally");
	keywords_java.push_back("long");
	keywords_java.push_back("strictfp");
	keywords_java.push_back("volatile");
	keywords_java.push_back("const");
	keywords_java.push_back("float");
	keywords_java.push_back("native");
	keywords_java.push_back("super");
	keywords_java.push_back("while");

	keywords_js.push_back("abstract");
	keywords_js.push_back("arguments");
	keywords_js.push_back("boolean");
	keywords_js.push_back("break");
	keywords_js.push_back("byte");
	keywords_js.push_back("case");
	keywords_js.push_back("catch");
	keywords_js.push_back("char");
	keywords_js.push_back("class");
	keywords_js.push_back("const");
	keywords_js.push_back("continue");
	keywords_js.push_back("debugger");
	keywords_js.push_back("default");
	keywords_js.push_back("delete");
	keywords_js.push_back("do");
	keywords_js.push_back("double");
	keywords_js.push_back("else");
	keywords_js.push_back("enum");
	keywords_js.push_back("eval");
	keywords_js.push_back("export");
	keywords_js.push_back("extends");
	keywords_js.push_back("false");
	keywords_js.push_back("final");
	keywords_js.push_back("finally");
	keywords_js.push_back("float");
	keywords_js.push_back("for");
	keywords_js.push_back("function");
	keywords_js.push_back("goto");
	keywords_js.push_back("if");
	keywords_js.push_back("implements");
	keywords_js.push_back("import");
	keywords_js.push_back("in");
	keywords_js.push_back("instanceof");
	keywords_js.push_back("int");
	keywords_js.push_back("interface");
	keywords_js.push_back("let");
	keywords_js.push_back("long");
	keywords_js.push_back("native");
	keywords_js.push_back("new");
	keywords_js.push_back("null");
	keywords_js.push_back("package");
	keywords_js.push_back("private");
	keywords_js.push_back("protected");
	keywords_js.push_back("public");
	keywords_js.push_back("return");
	keywords_js.push_back("short");
	keywords_js.push_back("static");
	keywords_js.push_back("super");
	keywords_js.push_back("switch");
	keywords_js.push_back("synchronized");
	keywords_js.push_back("this");
	keywords_js.push_back("throw");
	keywords_js.push_back("throws");
	keywords_js.push_back("transient");
	keywords_js.push_back("true");
	keywords_js.push_back("try");
	keywords_js.push_back("typeof");
	keywords_js.push_back("var");
	keywords_js.push_back("void");
	keywords_js.push_back("volatile");
	keywords_js.push_back("Array");
	keywords_js.push_back("Date");
	keywords_js.push_back("eval");
	keywords_js.push_back("function");
	keywords_js.push_back("hasOwnProperty");
	keywords_js.push_back("Infinity");
	keywords_js.push_back("isFinite");
	keywords_js.push_back("isNaN");
	keywords_js.push_back("isPrototypeOf");
	keywords_js.push_back("length");
	keywords_js.push_back("Math");
	keywords_js.push_back("NaN");
	keywords_js.push_back("name");
	keywords_js.push_back("Number");
	keywords_js.push_back("Object");
	keywords_js.push_back("prototype");
	keywords_js.push_back("String");
	keywords_js.push_back("toString");
	keywords_js.push_back("undefined");
	keywords_js.push_back("valueOf");
	keywords_js.push_back("getClass");
	keywords_js.push_back("java");
	keywords_js.push_back("JavaArray");
	keywords_js.push_back("javaClass");
	keywords_js.push_back("JavaObject");
	keywords_js.push_back("JavaPackage");
	keywords_js.push_back("alert");
	keywords_js.push_back("all");
	keywords_js.push_back("anchor");
	keywords_js.push_back("anchors");
	keywords_js.push_back("area");
	keywords_js.push_back("assign");
	keywords_js.push_back("blur");
	keywords_js.push_back("button");
	keywords_js.push_back("checkbox");
	keywords_js.push_back("clearInterval");
	keywords_js.push_back("clearTimeout");
	keywords_js.push_back("clientInformation");
	keywords_js.push_back("close");
	keywords_js.push_back("closed");
	keywords_js.push_back("confirm");
	keywords_js.push_back("constructor");
	keywords_js.push_back("crypto");
	keywords_js.push_back("decodeURI");
	keywords_js.push_back("decodeURIComponent");
	keywords_js.push_back("defaultStatus");
	keywords_js.push_back("document");
	keywords_js.push_back("element");
	keywords_js.push_back("elements");
	keywords_js.push_back("embed");
	keywords_js.push_back("embeds");
	keywords_js.push_back("encodeURI");
	keywords_js.push_back("encodeURIComponent");
	keywords_js.push_back("escape");
	keywords_js.push_back("event");
	keywords_js.push_back("fileUpload");
	keywords_js.push_back("focus");
	keywords_js.push_back("form");
	keywords_js.push_back("forms");
	keywords_js.push_back("frame");
	keywords_js.push_back("innerHeight");
	keywords_js.push_back("innerWidth");
	keywords_js.push_back("layer");
	keywords_js.push_back("layers");
	keywords_js.push_back("link");
	keywords_js.push_back("location");
	keywords_js.push_back("mimeTypes");
	keywords_js.push_back("navigate");
	keywords_js.push_back("navigator");
	keywords_js.push_back("frames");
	keywords_js.push_back("frameRate");
	keywords_js.push_back("hidden");
	keywords_js.push_back("history");
	keywords_js.push_back("image");
	keywords_js.push_back("images");
	keywords_js.push_back("offscreenBuffering");
	keywords_js.push_back("open");
	keywords_js.push_back("opener");
	keywords_js.push_back("option");
	keywords_js.push_back("outerHeight");
	keywords_js.push_back("outerWidth");
	keywords_js.push_back("packages");
	keywords_js.push_back("pageXOffset");
	keywords_js.push_back("pageYOffset");
	keywords_js.push_back("parent");
	keywords_js.push_back("parseFloat");
	keywords_js.push_back("parseInt");
	keywords_js.push_back("password");
	keywords_js.push_back("pkcs11");
	keywords_js.push_back("plugin");
	keywords_js.push_back("prompt");
	keywords_js.push_back("propertyIsEnum");
	keywords_js.push_back("radio");
	keywords_js.push_back("reset");
	keywords_js.push_back("screenX");
	keywords_js.push_back("screenY");
	keywords_js.push_back("scroll");
	keywords_js.push_back("secure");
	keywords_js.push_back("select");
	keywords_js.push_back("self");
	keywords_js.push_back("setInterval");
	keywords_js.push_back("setTimeout");
	keywords_js.push_back("status");
	keywords_js.push_back("submit");
	keywords_js.push_back("taint");
	keywords_js.push_back("text");
	keywords_js.push_back("textarea");
	keywords_js.push_back("top");
	keywords_js.push_back("unescape");
	keywords_js.push_back("untaint");
	keywords_js.push_back("window");
	keywords_js.push_back("onblur");
	keywords_js.push_back("onclick");
	keywords_js.push_back("onerror");
	keywords_js.push_back("onfocus");
	keywords_js.push_back("onkeydown");
	keywords_js.push_back("onkeypress");
	keywords_js.push_back("onkeyup");
	keywords_js.push_back("onmouseover");
	keywords_js.push_back("onload");
	keywords_js.push_back("onmouseup");
	keywords_js.push_back("onmousedown");
	keywords_js.push_back("onsubmit");

	keywords_cs.push_back("abstract");
	keywords_cs.push_back("as");
	keywords_cs.push_back("base");
	keywords_cs.push_back("bool");
	keywords_cs.push_back("break");
	keywords_cs.push_back("byte");
	keywords_cs.push_back("case");
	keywords_cs.push_back("catch");
	keywords_cs.push_back("char");
	keywords_cs.push_back("checked");
	keywords_cs.push_back("class");
	keywords_cs.push_back("const");
	keywords_cs.push_back("continue");
	keywords_cs.push_back("decimal");
	keywords_cs.push_back("default");
	keywords_cs.push_back("delegate");
	keywords_cs.push_back("do");
	keywords_cs.push_back("double");
	keywords_cs.push_back("else");
	keywords_cs.push_back("enum");
	keywords_cs.push_back("event");
	keywords_cs.push_back("explicit");
	keywords_cs.push_back("extern");
	keywords_cs.push_back("false");
	keywords_cs.push_back("finally");
	keywords_cs.push_back("fixed");
	keywords_cs.push_back("float");
	keywords_cs.push_back("for");
	keywords_cs.push_back("foreach");
	keywords_cs.push_back("goto");
	keywords_cs.push_back("if");
	keywords_cs.push_back("implicit");
	keywords_cs.push_back("in");
	keywords_cs.push_back("in (generic modifier)");
	keywords_cs.push_back("int");
	keywords_cs.push_back("interface");
	keywords_cs.push_back("internal");
	keywords_cs.push_back("is");
	keywords_cs.push_back("lock");
	keywords_cs.push_back("long");
	keywords_cs.push_back("namespace");
	keywords_cs.push_back("new");
	keywords_cs.push_back("null");
	keywords_cs.push_back("object");
	keywords_cs.push_back("operator");
	keywords_cs.push_back("out");
	keywords_cs.push_back("out");
	keywords_cs.push_back("override");
	keywords_cs.push_back("params");
	keywords_cs.push_back("private");
	keywords_cs.push_back("protected");
	keywords_cs.push_back("public");
	keywords_cs.push_back("readonly");
	keywords_cs.push_back("ref");
	keywords_cs.push_back("return");
	keywords_cs.push_back("sbyte");
	keywords_cs.push_back("sealed");
	keywords_cs.push_back("short");
	keywords_cs.push_back("sizeof");
	keywords_cs.push_back("stackalloc");
	keywords_cs.push_back("static");
	keywords_cs.push_back("string");
	keywords_cs.push_back("struct");
	keywords_cs.push_back("switch");
	keywords_cs.push_back("this");
	keywords_cs.push_back("throw");
	keywords_cs.push_back("true");
	keywords_cs.push_back("try");
	keywords_cs.push_back("typeof");
	keywords_cs.push_back("uint");
	keywords_cs.push_back("ulong");
	keywords_cs.push_back("unchecked");
	keywords_cs.push_back("unsafe");
	keywords_cs.push_back("ushort");
	keywords_cs.push_back("using");
	keywords_cs.push_back("virtual");
	keywords_cs.push_back("void");
	keywords_cs.push_back("volatile");
	keywords_cs.push_back("while");


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
	initKeywords();
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
	string as_str = getAsString(obj);
	if (isStringInt(as_str))
		sscanf(as_str.c_str(),"%d", &rez);
	return rez;
}

unsigned int jsonParser::getAsUInt(Value obj)
{
	if (obj.isUInt())
		return obj.asUInt();
	unsigned int rez;
	string as_str = obj.asString(); //1313
	if (isStringInt(as_str))
		sscanf(as_str.c_str(),"%ld", &rez);
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

string jsonParser::getAsStringS(string obj) //889
{
	if (parsedFromString[obj].isString()) return parsedFromString[obj].asString();
	else return "";
}

string jsonParser::getAsString(Value obj) //889
{
	if (obj.isString())
		return obj.asString();
	else
		if (obj.isBool())
			return to_string(obj.asBool());
		else
			if (obj.isDouble())
				return  to_string(obj.asDouble());
			else
				if (obj.isInt())
					return  to_string(obj.asInt());
				else
					if (obj.isUInt())
						return  to_string(obj.asUInt());
					else
						return "";
}

unsigned int jsonParser::getAsUIntS(string obj) //889
{
	if (parsedFromString[obj].isUInt())
		return parsedFromString[obj].asUInt();

	if (parsedFromString[obj].isInt())
		return parsedFromString[obj].asInt();

	int rez;
	string as_str = parsedFromString[obj].asString(); //1313
	if (isStringInt(as_str))
		sscanf(as_str.c_str(),"%d", &rez);
	return (rez < 0) ? -rez : rez;
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

bool jsonParser::mustExistBeArrayRanges(Json::Value object, string name,  int array_size , string ps , string  ps2)
{
	if (!mustExistBeArray(object, name, array_size, ps,ps2))
		return false;
	for (int i = 0; i < object.size(); i++)
		if (!mustBeRange(object[i], name + stringInScobcah(i)))
			return false;
	return true;
}

bool jsonParser::mustBeRange(Json::Value object, string name , string ps )
{
	if ( !object.isString())
	{
		last_error = "ERROR: json format is not correct. " + name +" isn`t string " + ps;
		return false;
	}

	string range = object.asString();
	int range_size;
	bool range_size_inited;
	range_size_inited = false;
	if (!rangeValidation(range_size_inited, range_size, range, name))
		return false;
	return true;
}

bool jsonParser::mustExistBeArrayOf(Json::Value object, int type,  bool is_array, string name, int array_size, int size_i_array, bool enable_zero_len  )
{
	if (is_array)
	{
		switch(type)
		{
		case FunctionData::RET_VAL_RANGE:
			last_error = "ERROR: json format is not correct. " + name +" can`t be array of ranges arrays ";
			return false;
			break;
		case FunctionData::RET_VAL_BOOL:
			if(!mustExistBeArrayOfBoolArrays(object, name,array_size , size_i_array , enable_zero_len))
				return false;
			break;
		case FunctionData::RET_VAL_FLOAT:
			if(!mustExistBeArrayOfFloatArrays(object, name,array_size , size_i_array, enable_zero_len))
				return false;
			break;
		case FunctionData::RET_VAL_STRING:
			if(!mustExistBeArrayOfStringArrays(object, name,array_size , size_i_array, enable_zero_len))
				return false;
			break;
		case FunctionData::RET_VAL_INT:
			if(!mustExistBeArrayOfIntArrays(object, name,array_size , size_i_array, enable_zero_len))
				return false;
			break;
		default:
			last_error = "ERROR: json format is not correct." + name + " type (" + to_string(type) + ") don*t recognized";
			return false;
		}
	}
	else
	{
		switch(type)
		{
		case FunctionData::RET_VAL_RANGE:
			if(!mustExistBeArrayRanges(object, name, array_size))
				return false;
			break;
		case FunctionData::RET_VAL_BOOL:
			if(!mustExistBeArrayBool(object, name, array_size,enable_zero_len))
				return false;
			break;
		case FunctionData::RET_VAL_FLOAT:
			if(!mustExistBeArrayFloat(object, name, array_size, enable_zero_len))
				return false;
			break;
		case FunctionData::RET_VAL_STRING:
			if(!mustExistBeArrayString(object, name, array_size))
				return false;
			break;
		case FunctionData::RET_VAL_INT:
			if(!mustExistBeArrayInt(object, name, array_size, enable_zero_len))
				return false;
			break;
		default:
			last_error = "ERROR: json format is not correct." + name + " type (" + to_string(type) + ") don*t recognized";
			return false;
		}
	}
	return true;
}

bool jsonParser::isValidFields()
{
	is_results_range = false;
	is_results_array = false;
	DEBUG("before parsedFromString==nullValue");
	if ((parsedFromString == nullValue) || (parsedFromString.size() == 0) || !isJson())
	{
		last_error = "ERROR: json format is not correct - it empty or isn*t json";//+
		return false;
	}
	if( !mustExistBeInt(parsedFromString[FIELD_TASK_ID], "task"))
		return false;

	if( !mustExistBeString(parsedFromString[FIELD_OPERATION], "operation"))
		return false;

	if (parsedFromString[FIELD_OPERATION]=="addtask" || parsedFromString[FIELD_OPERATION]=="edittask")
	{
		Json::Value field_etalon = parsedFromString[FIELD_ETALON];

		if( !mustExistBeString( field_etalon , "etalon"))
			return false;

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
		string etalon = field_etalon.asString();
		if (!(etalon.find_first_not_of("\t\n\r ") == string::npos))
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

		if( !mustExistBeArray(field_args, "args", -1))
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

			if ( value_type >= code::FunctionData::Last)
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


