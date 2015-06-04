/*
 * jsonParser.h
 *
 *  Created on: Jun 3, 2015
 *      Author: root
 */

#include "includes.h"
#include "logfile.h"

using namespace Json;


#ifndef JSONPARSER_H_
#define JSONPARSER_H_

class jsonParser {
	Json::Value parsedFromString;
	Reader reader;
	string json;

	list <Value> t_find;
public:
	jsonParser(string json);
	jsonParser();
	bool setJson(string in_json);
	/*
	 *  not wooooorking
	 */
	static Value getRoot(string json);
	Value getRoot();
	Value getObject(string name, bool everyWhere);
	static bool isJson(string in_json);
	virtual ~jsonParser();
private:
	/*
	 *  no check is array? problem with find elemet // crash // not use
	 */
	Value findInArray(Value &array, string &name);
};

#endif /* JSONPARSER_H_ */
