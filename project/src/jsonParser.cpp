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

bool jsonParser::isValidFields()
{

	l12("before parsedFromString==nullValue");
	if ((parsedFromString==nullValue) || (parsedFromString.size()==0) || !isJson())
		return false;

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


	if (parsedFromString[FIELD_OPERATION]=="addtask" || parsedFromString[FIELD_OPERATION]=="edittask")
	{


		if(parsedFromString[FIELD_ETALON].isNull() || !parsedFromString[FIELD_ETALON].isConvertibleTo(Json::stringValue))
			return false;
		l12("FIELD_ETALON");
		if(parsedFromString[FIELD_CODE_LANGUAGE].isNull() || !parsedFromString[FIELD_CODE_LANGUAGE].isConvertibleTo(Json::stringValue))
			return false;
		l12("FIELD_CODE_LANGUAGE");
		if(parsedFromString[FIELD_NAME].isNull() || !parsedFromString[FIELD_NAME].isConvertibleTo(Json::stringValue))
			return false;
		l12("FIELD_NAME");
		if(parsedFromString[FUNCTION][FIELD_FUNCTION_NAME].isNull() || !parsedFromString[FUNCTION][FIELD_FUNCTION_NAME].isConvertibleTo(Json::stringValue))
			return false;
		l12("FIELD_FUNCTION_NAME");
		//if(parsedFromString[FIELD_ARGS].isNull() || !parsedFromString[FIELD_ARGS].isArray())
			//return false;//TODO
		//l12("FIELD_ARGS");
		if(parsedFromString[FUNCTION][ARGS][FIELD_IS_ARRAY].isNull() || !parsedFromString[FIELD_IS_ARRAY].isConvertibleTo(Json::booleanValue))
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
			return false;


		return true;
	}


	if (parsedFromString[FIELD_OPERATION]=="start")
	{

		if(parsedFromString[FIELD_CODE_TEXT].isNull() || !parsedFromString[FIELD_CODE_TEXT].isConvertibleTo(Json::stringValue))
			return false;
		if(parsedFromString[FIELD_CODE_LANGUAGE].isNull() || !parsedFromString[FIELD_CODE_LANGUAGE].isConvertibleTo(Json::stringValue))
			return false;
		if(parsedFromString[FIELD_TASK_ID].isNull() || !parsedFromString[FIELD_TASK_ID].isConvertibleTo(Json::intValue))
			return false;
	}
	else if (parsedFromString[FIELD_OPERATION]=="status"){

	}
	else if (parsedFromString[FIELD_OPERATION]=="result"){

	}
	else if (parsedFromString[FIELD_OPERATION]=="getToken"){

	}
	else if (parsedFromString[FIELD_OPERATION]=="getFromToken"){
		if(parsedFromString[FIELD_TOKEN].isNull() || !parsedFromString[FIELD_TOKEN].isConvertibleTo(Json::stringValue))
			return false;
	}
	else return false ;
	/*
	 *  conver test  add
	 */

	return true;
}


