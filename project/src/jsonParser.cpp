/*
 * jsonParser.cpp
 *
 *  Created on: Jun 3, 2015
 *      Author: root
 */

#include "inc/jsonParser.h"

jsonParser::jsonParser(string json)
{
	setJson(json);
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
	if(!reader.parse(in_json, parsedFromString, false))
	{
		json.clear();
		return false;
	}
	json = in_json;
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
			return parsedFromString[name];
		return findInArray(parsedFromString, name);
	}
}

Value jsonParser::findInArray(Value &array, string &name)
{
	Value res = parsedFromString[name];
	if(!res.isNull())
		return res;

	for(int i = 0; i < array.size(); i++)
	{
		if( array[i].isArray() )
			t_find.push_back(array[i]);
	}
	while(t_find.size() > 0)
	{
		return findInArray(array, name);
	}
}

bool jsonParser::isJson(string in_json)
{
	Reader t_reader;
	Value temp;
	return t_reader.parse( in_json, temp, false);
}
