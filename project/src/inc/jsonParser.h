/*
 * jsonParser.h
 *
 *  Created on: Jun 3, 2015
 *      Author: root
 */




#ifndef JSONPARSER_H_
#define JSONPARSER_H_

#include "includes.h"
#include "logfile.h"

using namespace Json;

#define	 FIELD_TASK_ID  "task"
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
#define FIELD_ARRAY_TYPE "array_type"
#define FIELD_UNIT_TESTS_NUM "unit_test_num"

#define FIELD_IS_ARRAY "is_array"
#define FIELD_SIZE "size"
#define FIELD_TYPE "type"
#define FIELD_CMP_ARG "compare_argument"
#define FIELD_ARG_NAME "arg_name"
#define FIELD_VALUE "value"
#define FIELD_RESULTS "results"
#define FUNCTION "function"
#define ARGS "args"
#define FIELD_ETALON_VALUE "etalon_value"
#define FIELD_TESTS_CODE "tests_code"
#define FIELD_COMPARE_MARK "compare_mark"



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

	vector<string> keywords_cpp ;
	vector<string> keywords_java ;
	vector<string> keywords_cs ;
	vector<string> keywords_js ;
	vector<string> keywords_php ;

	string max_uint_value ; //for parsing uint in json

	Json::Value parsedFromString;
	Reader reader;
	string json;
	bool bJsonValid;
	list <Value> t_find;
	string last_error;

	int range_first;
	int range_last;

	bool is_results_array;
	int results_array_size;
	bool is_results_range;

	int unit_test_num;
public:
	bool isStrKeyWord(string str, int lang);
	bool isStrInVector(string str, vector<string> vec);
	void initKeywords();
	bool isResultsArray();
	int getResultsArraySize();
	bool isResultsRange();
	string getLastError();
	jsonParser(string json);
	jsonParser();
	bool setJson(string in_json);

	int getRangeFirst();
	int getRangeLast();
	/*
	 *  not wooooorking
	 */
	static Value getRoot(string json);
	Value getRoot();
	 int getAsIntS(string obj);
	static int getAsInt(Value obj);

	int getFieldInt(string field);
	int getFieldInt(Value field);
	Value getField(string field);
	//string getFieldS(string field);
	string getFieldS(Value value);
	Value getJsonValue();

	static string getAsString(Value obj);
	string getAsStringS(string obj);
	unsigned int getAsUIntS(string obj);
	static unsigned int getAsUInt(Value obj);
	Value getObject(string name, bool everyWhere);
	static bool isJson(string in_json);
	bool isJson();
	bool isValidFields();
	virtual ~jsonParser();

	static bool isStringInt(string value, bool enable_zero_len = false);
	static bool isStringUnsignedInt(string value, bool enable_zero_len = false);
	static bool isStringBool(string value, bool enable_zero_len = false);
	static bool isStringFloat(string value, bool enable_zero_len = false);


	bool parseChekableArgIndexes(Value function );
	bool rangeValidation(bool &range_size_inited, int &range_size, string range, string field_name);
	//size need if its array of arrays
	bool mustExistBeArrayOf(Json::Value object, int type,  bool is_array, string name, int array_size ,
			int size_i_array, bool enable_zero_len = false);
	bool mustBeArrayFloat(Json::Value object, string name ,int size, bool enable_zero_len = false , string ps = "", string ps2 = "");
	bool mustBeArrayInt(Json::Value object, string name ,int size, bool enable_zero_len = false , string ps = "", string ps2 = "");
	bool mustBeArrayString(Json::Value object, string name  ,int size, bool enable_zero_len = false, string ps = "", string ps2 = "");
	bool mustBeArrayChar(Json::Value object, string name  ,int size, bool enable_zero_len = false, string ps = "", string ps2 = "");
	bool mustBeArrayBool(Json::Value object, string name  ,int size, bool enable_zero_len = false , string ps = "", string ps2 = "");

	bool mustBeNotArrayFloat(Json::Value object, string name , string ps = "", string ps2 = "");
	bool mustBeNotArrayInt(Json::Value object, string name , string ps = "", string ps2 = "");
	bool mustBeNotArrayString(Json::Value object, string name , string ps = "", string ps2 = "");
	bool mustBeNotArrayBool(Json::Value object, string name , string ps = "", string ps2 = "");

	bool mustBeNotArray(Json::Value object, string name , string ps = "");
	bool mustBeArray(Json::Value object, string name, int size, bool able_have_zero_size = false , string ps = "");
	bool mustHaveSizeMoreZero(Json::Value object, string name , string ps = "");
	bool mustBeInt(Json::Value object, string name , string ps = "" , bool enable_zero_len = false);
	bool mustBeUnsignedInt(Json::Value object, string name , string ps = "");

	bool mustBeBool(Json::Value object, string name , string ps = "", bool enable_zero_len = false);
	bool mustBeFloat(Json::Value object, string name , string ps = "", bool enable_zero_len = false);
	bool mustBeString(Json::Value object, string name , string ps = "", bool enable_zero_len = false);
	bool mustBeChar(Json::Value object, string name , string ps = "", bool enable_zero_len = false);
	bool mustBeRange(Json::Value object, string name , string ps = "");
	bool mustExist(Json::Value object, string name , string ps = "");

	bool mustExistBeInt(Json::Value object, string name , string ps = "", string ps2 = "");
	bool mustExistBeIntMin(Json::Value object, string name, int min_value);
	bool mustExistBeUnsignedInt(Json::Value object, string name , string ps = "", string ps2 = "");

	bool mustExistBeFloat(Json::Value object, string name , string ps = "", string ps2 = "");
	bool mustExistBeString(Json::Value object, string name , string ps = "", string ps2 = "");
	bool mustBeNotKeyword(Json::Value object, string name, int lang);
	bool mustExistBeBool(Json::Value object, string name , string ps = "", string ps2 = "");
	bool mustExistBeArray(Json::Value object, string name,  int array_size, bool able_have_zero_size = false , string ps = "", string ps2 = "");
	bool mustExistBeArrayChar(Json::Value object, string name, int array_size , bool able_have_zero_size = false, string ps = "", string ps2 = "");
	bool mustExistBeArrayString(Json::Value object, string name, int array_size , bool able_have_zero_size = false, string ps = "", string ps2 = "");
	bool mustExistBeArrayRanges(Json::Value object, string name ,  int array_size, string ps = "", string ps2 = "");
	bool mustExistBeArrayInt(Json::Value object, string name,  int array_size, bool enable_zero_len = false , string ps = "", string ps2 = "");
	bool mustExistBeArrayBool(Json::Value object, string name ,  int array_size, bool enable_zero_len = false , string ps = "", string ps2 = "");
	bool mustExistBeArrayOfBoolArrays(Json::Value object, string name ,  int array_size, int size_i_array, bool enable_zero_len = false, string ps = "", string ps2 = "");
	bool mustExistBeArrayOfStringArrays(Json::Value object, string name ,  int array_size , int size_i_array, bool enable_zero_len = false, string ps = "", string ps2 = "");
	bool mustExistBeArrayOfCharArrays(Json::Value object, string name ,  int array_size , int size_i_array, bool enable_zero_len = false, string ps = "", string ps2 = "");
	bool mustExistBeArrayOfIntArrays(Json::Value object, string name,  int array_size  , int size_i_array, bool enable_zero_len = false, string ps = "", string ps2 = "");
	bool mustExistBeArrayOfFloatArrays(Json::Value object, string name ,  int array_size , int size_i_array, bool enable_zero_len = false, string ps = "", string ps2 = "");
	bool mustExistBeArrayFloat(Json::Value object, string name ,  int array_size, bool enable_zero_len = false, string ps = "", string ps2 = "");
	bool mustExistBeArrayInt(Json::Value object, string name ,  int array_size , bool enable_zero_len , string ps, string ps2, int min_val, int max_val);

	bool mustHaveSizeMoreZeroAndBeNotTwoDimensionalArray(Json::Value object, string name , string ps = "", string ps2 = "");

	bool sizeEqualSizeOfUnitTests(Json::Value object, string name);

	bool parseAddUtest(Value &pres_task);

	string stringInScobcah(string inp);
	string stringInScobcah(int inp);

	const string& getJson() const {
		return json;
	}

	const Json::Value& getParsedFromString() const {
		return parsedFromString;
	}

	void setParsedFromString(const Json::Value& parsedFromString) {
		this->parsedFromString = parsedFromString;
	}

private:
	/*
	 *  no check is array? problem with find elemet // crash // not use
	 */
	Value findInArray(Value &array, string &name);
};

#endif /* JSONPARSER_H_ */
