/*
 * TokenSystem.h
 *
 *  Created on: Dec 4, 2015
 *      Author: root
 */

#ifndef TOKENSYSTEM_H_
#define TOKENSYSTEM_H_

#include "includes.h"
#include "fcgio.h"
#include <sstream>
#include "cLang.h"
#include "codeclear.h"
#include "errorresponder.h"
#include "logfile.h"
#include "jsonParser.h"
#include "SQLconnector.h"
#include "SQLConnectionPool.h"
#include "config.h"
#include "ctpl_stl.h"
#include <iostream>
#include <string>
#include <regex>
#include <algorithm>
#include <ctime>
//#include <pstream.h>

#include <cassert>
#include <exception>
#include "FCGI_Stream.h"

//TIMER
#include <functional>
#include <chrono>
#include <future>
#include <cstdio>
#include <ctime>
#include "ctpl_stl.h"
#include <unistd.h>

namespace code {

class TokenSystem {
	map<string, Token> tokenList;
	vector<thread> threads;
	static TokenSystem *obj;
public:
	static TokenSystem *getObject();
	bool generationToken(FCGI_Stream &stream, jsonParser &jSON);// generate new token => add to list + run deleteToken in new thread //return #200
	bool getFromToken(FCGI_Stream &stream, jsonParser &jSON);// return result if token good //return #200
	void deleteToken(string tok, int timeOut);//delete token after timeOut

private:
	TokenSystem();
	virtual ~TokenSystem();
};

//test class for new thread
class Later
{
public:
	template <class callable, class... arguments>
	Later(int after, bool async, callable&& f, arguments&&... args)
	{
		std::function<typename std::result_of<callable(arguments...)>::type()> task(std::bind(std::forward<callable>(f), std::forward<arguments>(args)...));

		if (async)
		{
			std::thread([after, task]() {
				std::this_thread::sleep_for(std::chrono::milliseconds(after));
				task();
			}).detach();
		}
		else
		{
			std::this_thread::sleep_for(std::chrono::milliseconds(after));
			task();
		}
	}

};
} /* namespace code */

#endif /* TOKENSYSTEM_H_ */
