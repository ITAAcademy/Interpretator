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


#define	FIELD_TASK_ID  "task"
#define FIELD_CODE_TEXT  "code"
#define FIELD_CODE_LANGUAGE  "lang"
#define FIELD_OPERATION "operation"
#define FIELD_SESSION "session"
#define FIELD_JOBID "jobid"
#define FIELD_TOKEN "token"
#define JsonValue Value
#define FIELD_HEADER "header"
#define FIELD_ETALON "etalon"
#define FIELD_FOOTER "footer"
#define FIELD_NAME "name"
#define FIELD_FUNCTION_NAME "function_name"
#define FIELD_ARGS "args"
#define FIELD_IS_ARRAY "is_array"
#define FIELD_SIZE "size"
#define FIELD_TYPE "type"
#define FIELD_ARG_NAME "arg_name"
#define FIELD_VALUE "value"
#define FUNCTION "function"
#define ARGS "args"
/*


/*{
"code" : " System.out.println(\"Hello World!\"); ",

"task": "7",
"lang": "java"
}*/

/*
{
"code" : " std::cout << \"Hello World!\" << std::endl;",
"task": "2",
"lang": "c++"
}

 */



class jsonParser {

	Json::Value parsedFromString;
	Reader reader;
	string json;
	bool bJsonValid;
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
	bool isJson();
	bool isValidFields();
	virtual ~jsonParser();
private:
	/*
	 *  no check is array? problem with find elemet // crash // not use
	 */
	Value findInArray(Value &array, string &name);
};

#endif /* JSONPARSER_H_ */
