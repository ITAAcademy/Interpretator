.PHONY: all 
all:
	sudo g++ -std=c++0x inc/TaskCodeGenerator.h inc/TokenSystem.h inc/cLang.h inc/codeclear.h inc/errorresponder.h inc/jsonParser.h inc/FCGI_Stream.h inc/includes.h inc/main.h inc/logfile.h inc/SQLconnector.h inc/SQLConnectionPool.h inc/config.h TaskCodeGenerator.cpp TokenSystem.cpp config.cpp cLang.cpp FCGI_Stream.cpp codeclear.cpp errorresponder.cpp logfile.cpp SQLconnector.cpp SQLConnectionPool.cpp jsonParser.cpp main.cpp  -o "test.fcgi" -lfcgi++ -lpthread -ljsoncpp -lfcgi -lmysqlcppconn -lmysqlpp -I/usr/include/mysql++ -I/usr/include/mysql #-lboost_system -lboost_thread

static:
	sudo g++ -w -std=c++0x inc/cLang.h inc/codeclear.h inc/errorresponder.h inc/jsonParser.h inc/FCGI_Stream.h inc/includes.h inc/main.h inc/logfile.h inc/SQLconnector.h inc/SQLConnectionPool.h inc/config.h config.cpp cLang.cpp FCGI_Stream.cpp codeclear.cpp errorresponder.cpp logfile.cpp SQLconnector.cpp SQLConnectionPool.cpp jsonParser.cpp main.cpp  -o "test.fcgi" -lpthread -ljsoncpp -lfcgi++ -lfcgi -lmysqlpp -I/usr/include/mysql++ -I/usr/include/mysql # -Wl,-Bstatic -lz -ldl -lmysqlcppconn -lboost_system -lboost_thread
