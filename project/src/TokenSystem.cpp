/*
 * TokenSystem.cpp
 *
 *  Created on: Dec 4, 2015
 *      Author: root
 */

#include "inc/TokenSystem.h"

namespace code {

TokenSystem *TokenSystem::obj = NULL;
//GENERATION TOKEN
bool TokenSystem::generationToken(FCGI_Stream &stream, jsonParser &jSON)
{
	string session = jSON.getObject("session", false).asString();
	int jobid = jSON.getObject("jobid", false).asInt();
	Token tok;
	tok.session = session;
	tok.jobId = jobid;
	hash<string> hash_fn;
	long hash = hash_fn(session)^(hash_fn(to_string(jobid)) << 1)^(hash_fn(to_string(time(0))) << 2);
	string value = to_string(hash);
	tokenList[value] = tok;
	JsonValue res;

	res["token"] = value;
	stream << "Status: 200\r\n Content-type: text/html\r\n" << "\r\n";
	stream << res.toStyledString();

	//Later later_delete(Config::getInstance().getTokenTimeOut(), true, &this->deleteToken, value);
	auto f1 = std::thread(&TokenSystem::deleteToken, this,  value, Config::getInstance().getTokenTimeOut());
	f1.detach();
	return true;

}

bool TokenSystem::getFromToken(FCGI_Stream &stream, jsonParser &jSON)
{
	JsonValue res;
	string strToken = jSON.getObject("token", false).asString();
	Token value;
	if(tokenList.count( strToken ) == 0)
	{
		res["status"] = "Token time out";
		stream << "Status: 200\r\n Content-type: text/html\r\n" << "\r\n";
		stream << res.toStyledString();
		logfile::addLog("Token time out");
		l12( "GET FROM TOKEN" );
		l12( to_string(tokenList.size()) );
		cout.flush();
		return true;
	}
	value =  tokenList[strToken];

	string session = value.session;
	int jobid = value.jobId;
	l12( "GET FROM TOKEN" );
	l12( to_string(jobid) );
	l12( session );
	//TO BE CONTINUED ...
	vector<string> labl;

	labl.push_back("id");
	labl.push_back("session");
	labl.push_back("jobid");
	labl.push_back("status");
	labl.push_back("date");
	labl.push_back("result");
	labl.push_back("warning");
	if (SqlConnectionPool::getInstance().connectToTable("results", labl)	== true)
	{
		string s_datime = getDateTime(); //'YYYY-MM-DD HH:MM:SS'
		map<int, string> temp;
		temp.insert( { 1, session });
		temp.insert( { 2, to_string(jobid) });
		//3,skip
		temp.insert( { 4, s_datime });
		//4
		vector<map<int, string> > records =	SqlConnectionPool::getInstance().getAllRecordsFromTable(
				"`session`='"+session+"' AND `jobid`='"+to_string(jobid)+"'");
		//	logfile::addLog(std::to_string(records.size()));
		/*
		 * RESULT
		 */

		stream << "Status: 200\r\n Content-type: text/html\r\n" << "\r\n";


		if(records.size() > 0)
		{
			res["status"] = records[0][3];
			{
				res["date"] = records[0][4];
				res["warning"] = records[0][6];
				res["result"] = records[0][5];
			}
		}
		else
			res["status"] = "not found";

		stream << res.toStyledString();

		//	stream << "status:" + records[0][3] << "\n\n";
		/*Cool code no delete
 		 stream << "date:"+records[i][4] << "\n";
 		 stream << "result:"+records[i][5] << "\n";
 		 stream << "warning:"+records[i][6] << "\n";
		 */
		logfile::addLog("Table 'results' outputed");
		cout.flush();
	}
	else
		return false;
	return true;
}

void TokenSystem::deleteToken(string tok, int timeOut)
{
	cout << "start thread sleep	" + to_string(timeOut);

	std::this_thread::sleep_for(std::chrono::milliseconds(timeOut));
	cout << "start thread after";
	tokenList.erase(tok);
}

TokenSystem *TokenSystem::getObject()
{
	if(obj == NULL)
		obj = new TokenSystem();

	return obj;
}

TokenSystem::TokenSystem() {
	// TODO Auto-generated constructor stub

}

TokenSystem::~TokenSystem() {
	// TODO Auto-generated destructor stub
}
} /* namespace code */
