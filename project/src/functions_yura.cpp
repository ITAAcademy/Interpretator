#include "inc/includes.h"
#include "inc/cLang.h"


string getCompareString(string name1,  ValueTypes type1,string name2,  ValueTypes type2, CompareMark mark, int lang)
{
	string result = "( ";
	if ((int)type1 != (int) type2) //equial type
	{
		name1 = "to_string( " + name1 + " )";
		name2 = "to_string( " + name2 + " )";
		type1 = ValueTypes::VAL_STRING;
	}

	switch (type1)
	{
	case ValueTypes::VAL_FLOAT:
		result += " ( floor(" + name1 + " * 100 ) - floor(" + name2 + " * 100 ) ) ";
		switch (mark)
		{
		case CompareMark::LessEquial:
			result += "<= 0 )";
			break;
		case CompareMark::Less:
			result += " < 0 )";
			break;
		case CompareMark::Equial: default:
			result += " == 0 )";
			break;
		case CompareMark::NotEquial:
			result += " != 0 )";
			break;
		case CompareMark::More:
			result += " > 0 )";
			break;
		case CompareMark::MoreEquial:
			result += " >= 0 )";
			break;
		}
		break;

		case VAL_INT:
		{
			switch (mark)
			{
			case CompareMark::LessEquial:
				result +=  name1 + " <= " + name2 + " )";
				break;
			case CompareMark::Less:
				result +=  name1 + " < " + name2 + " )";
				break;
			case CompareMark::Equial: default:
				result +=  name1 + " == " + name2 + " )";
				break;
			case CompareMark::NotEquial:
				result +=  name1 + " != " + name2 + " )";
				break;
			case CompareMark::More:
				result +=  name1 + " > " + name2 + " )";
				break;
			case CompareMark::MoreEquial:
				result +=  name1 + " >= " + name2 + " )";
				break;
			}
		}
		break;

		case VAL_STRING:
		{
			if ( lang != (int) LangCompiler::Flag_Java)
				switch (mark)
				{
				case CompareMark::LessEquial:
					result +=  name1 + " <= " + name2 + " )";
					break;
				case CompareMark::Less:
					result +=  name1 + " < " + name2 + " )";
					break;
				case CompareMark::Equial: default:
					result +=  name1 + " == " + name2 + " )";
					break;
				case CompareMark::NotEquial:
					result +=  name1 + " != " + name2 + " )";
					break;
				case CompareMark::More:
					result +=  name1 + " > " + name2 + " )";
					break;
				case CompareMark::MoreEquial:
					result +=  name1 + " >= " + name2 + " )";
					break;
				}
			else
			{
				switch (mark)
				{
				case CompareMark::LessEquial:
					result += "(new String(" + name1 + ").compareTo(" + name2 +")) <= 0";
					break;
				case CompareMark::Less:
					result += "(new String(" + name1 + ").compareTo(" + name2 +")) < 0";
					break;
				case CompareMark::Equial: default:
					result += "new String(" + name1 + ").equals(" + name2 +")";
					break;
				case CompareMark::NotEquial:
					result += "!(new String(" + name1 + ").equals(" + name2 +"))";
					break;
				case CompareMark::More:
					result += "(new String(" + name1 + ").compareTo(" + name2 +")) > 0";
					break;
				case CompareMark::MoreEquial:
					result += "(new String(" + name1 + ").compareTo(" + name2 +")) >= 0";
					break;
				}
			}
		}
		break;

		case ValueTypes::VAL_BOOL:
			switch (mark)
			{
			case CompareMark::Equial: default:
				result +=  name1 + " == " + name2 + " )";
				break;
			case CompareMark::NotEquial:
				result +=  name1 + " != " + name2 + " )";
				break;
			}
			break;
	}
	return result;
}

string getArrayCompareString(string name1, int arr1_size, ValueTypes type1,string name2, int arr2_size, ValueTypes type2, CompareMark mark, int lang)
{
	if (arr1_size != arr2_size)
		return "false";
	if ( arr1_size < 0  )
		return "false";

	if (type1 != type2) //equial type
	{
		return "false";
	}

	if ( arr1_size == 0  )
	{
		return getCompareString(name1, type1, name2, type2, mark, lang);
	}
	else
	{
		FunctionArgument ar;
		ar.type = type1;

		return string( " compareArrs<" + ar.getType(lang) + "," +
				std::to_string(arr1_size) + " > ( " + name1 + ", "+ name2 + " )");
	}


}



string FunctionArgument::getTypeInt(int lang )
{
	switch( lang)
	{
	case LangCompiler::Flag_CPP: case LangCompiler::Flag_Java:
		return "int";
		break;
	}
}

string FunctionArgument::getTypeFloat(int lang )
{
	switch( lang)
	{
	case LangCompiler::Flag_CPP: case LangCompiler::Flag_Java:
		return "float";
		break;
	}
}

string FunctionArgument::getTypeString(int lang )
{
	switch( lang)
	{
	case LangCompiler::Flag_CPP:
		return "string";
		break;

	case LangCompiler::Flag_Java:
		return "String";
		break;
	}
}

string FunctionArgument::getTypeBool(int lang )
{
	switch( lang)
	{
	case LangCompiler::Flag_CPP:
		return "bool";
		break;

	case LangCompiler::Flag_Java:
		return "boolean";
		break;
	}
}

string FunctionArgument::getType(int lang )
{
	switch( lang)
	{
	case VAL_INT:
		return getTypeInt(lang);
		break;
	case VAL_FLOAT:
		return getTypeFloat(lang);
		break;
	case VAL_BOOL:
		return getTypeBool(lang);
		break;
	case VAL_STRING:
		return getTypeString(lang);
		break;
	case VAL_RANGE:
		return "range";
		break;
	}
	return "";
}
string FunctionArgument::generateDefinition(bool is_result, int lang)
{
	string type = getType(lang);
	string result = type;
	switch( lang)
	{
	case LangCompiler::Flag_CPP:
		if (isArray)
		{
			if (is_result)
				result += " * " + name;
			else
				result += " " + name + " [" + std::to_string(size) + "]";
		}
		else
			result += " " +  name;
		break;

	case LangCompiler::Flag_Java:
		result += " [] " + name;
		if (isArray)
			result += " = new " + type + " [" + std::to_string(size) + "]";
		break;
	}
	result += ";\n";
	return result;
}
