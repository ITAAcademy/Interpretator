/*
 * FStream.h
 *
 *  Created on: May 8, 2015
 *      Author: root
 */
#include "includes.h"
#include "fcgio.h"

using namespace std;

#ifndef FSTREAM_H_
#define FSTREAM_H_

class FCGI_Stream {
private:
	streambuf *cin_streambuf ;
	streambuf *cout_streambuf;
	streambuf *cerr_streambuf;

    fcgi_streambuf *cin_fcgi_streambuf;
    fcgi_streambuf *cout_fcgi_streambuf;
    fcgi_streambuf *cerr_fcgi_streambuf;
    char *buffer;
    bool status;
	FCGX_Request *request;
public:
	const char * null = "NULL";
	FCGI_Stream( int socketId );
	FCGI_Stream(FCGX_Request *req);
	~FCGI_Stream();

	void initFCGI_Stream();
	void initSTD_Stream();
	char *getRequestMethod();
	char* getRequesBuffer();
	void reInitRequesBuffer();
	char *getFormParam(string name);
	bool IsRequest();
	bool multiIsRequest();
	int getRequestSize();
	void close();
	int operator << ( char * str);
	int operator << ( int num);
	int operator << ( double num);
	void operator >> (char * res);
	FCGX_Request *getRequest() ;
private:
	char gethex(char ch);
	char upperchar(char ch);

};

#endif /* FSTREAM_H_ */
