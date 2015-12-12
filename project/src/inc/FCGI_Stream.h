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
	int socketId;
public:
	const char * null = "NULL";
	FCGI_Stream( int socketId );
	FCGI_Stream(FCGX_Request *req);
	~FCGI_Stream();
	/*
	 *  init STDIO for Apatche **not actual
	 */
	void initFCGI_Stream();
	/*
	 *  restore STDIO
	 */
	void initSTD_Stream();
	/*
	 * get type of request
	 */
	char *getRequestMethod();
	/*
	 * return request content from this session
	 */
	string getRequestBuffer();
	/*
	 *  Apatche version **not actual
	 */
	void reInitRequesBuffer();
	/*
	 * return parameter from request generation by PHP form
	 */
	char *getFormParam(string name);
	/*
	 *  checks for request // Apatche version **not actual
	 */
	bool IsRequest();
	/*
	 *  checks for request
	 */
	bool multiIsRequest();
	/*
	 *  return length of request content
	 */
	int getRequestSize();
	/*
	 * close session
	 */
	void close();
	FCGX_Request *getRequest() ;
	/*
	 * IO functions
	 */
	FCGI_Stream& operator << ( const char * const str);
	FCGI_Stream& operator << ( const string str);
	FCGI_Stream& operator << ( const int num);
	FCGI_Stream& operator << ( const double num);
	void operator >> (char *res);
	string toString();

	//void getRequestContent();
private:
	char gethex(char ch);
	char upperchar(char ch);
	void updateBuffer();

};

#endif /* FSTREAM_H_ */
