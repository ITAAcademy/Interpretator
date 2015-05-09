/*
 * FStream.cpp
 *
 *  Created on: May 8, 2015
 *      Author: root
 */

#include "inc/FCGI_Stream.h"

FCGI_Stream::FCGI_Stream() {
	FCGX_Init();
	request = new FCGX_Request();
	FCGX_InitRequest(request, 0, 0);

    cin_streambuf  = cin.rdbuf();
    cout_streambuf = cout.rdbuf();
    cerr_streambuf = cerr.rdbuf();

    /*cin_fcgi_streambuf = NULL;
    cout_fcgi_streambuf = NULL;
    cerr_fcgi_streambuf = NULL;*/
}

FCGI_Stream::~FCGI_Stream() {
	/*delete cin_fcgi_streambuf;
	delete cout_fcgi_streambuf;
	delete cerr_fcgi_streambuf;*/
}

char *FCGI_Stream::getRequestMethod()
{
	return FCGX_GetParam("REQUEST_METHOD", request->envp);
}

void FCGI_Stream::initFCGI_Stream()
{
	//if(request != NULL)
	//{
		cin_fcgi_streambuf = new fcgi_streambuf(request->in);
		cout_fcgi_streambuf = new fcgi_streambuf(request->out);
		cerr_fcgi_streambuf = new fcgi_streambuf(request->err);

		cin.rdbuf(cin_fcgi_streambuf);
		cout.rdbuf(cout_fcgi_streambuf);
		cerr.rdbuf(cerr_fcgi_streambuf);
	///}
}
void FCGI_Stream::initSTD_Stream()
{
    cin.rdbuf(cin_streambuf);
    cout.rdbuf(cout_streambuf);
    cerr.rdbuf(cerr_streambuf);
}

FCGI_Stream::FCGI_Stream(FCGX_Request* req) {

	request = req;
	    cin_streambuf  = cin.rdbuf();
	    cout_streambuf = cout.rdbuf();
	    cerr_streambuf = cerr.rdbuf();
}

bool FCGI_Stream::IsRequest() {
	return !FCGX_Accept_r(request);
}
