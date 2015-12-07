#include "inc/includes.h"


string getCompareString(string name1,  ValueTypes type1,string name2,  ValueTypes type2, CompareMark mark)
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

		case VAL_STRING: case VAL_INT:
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

string getArrayCompareString(string name1, int arr1_size, ValueTypes type1,string name2, int arr2_size, ValueTypes type2, CompareMark mark)
{
	if (arr1_size != arr2_size)
		return "false";
	if ( arr1_size < 0  )
		return "false";

	if (type1 != type2) //equial type
	{
		name1 = "to_string( " + name1 + " )";
		name2 = "to_string( " + name2 + " )";
		type1 = (ValueTypes)::VAL_STRING;
	}

	if ( arr1_size == 0  )
	{
		return getCompareString(name1, type1, name2, type2, mark);
	}
	else
	{
		return string( " compareArrs<" + std::to_string(type1) + "," +
				std::to_string(arr1_size) + " > ( " + name1 + ", "+ name2 + " )");
	}


}
