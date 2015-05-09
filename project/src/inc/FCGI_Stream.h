/*
 * FStream.h
 *
 *  Created on: May 8, 2015
 *      Author: root
 */
#include <iostream>
#include <stdio.h>
#include <string.h>
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

	FCGX_Request *request;
public:
	FCGI_Stream();
	FCGI_Stream(FCGX_Request *req);
	~FCGI_Stream();

	void initFCGI_Stream();
	void initSTD_Stream();
	char *getRequestMethod();
	bool IsRequest();
	FCGX_Request *getRequest() {
		return request;
	}

};

#endif /* FSTREAM_H_ */
