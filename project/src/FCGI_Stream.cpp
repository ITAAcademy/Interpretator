/*
 * FStream.cpp
 *
 *  Created on: May 8, 2015
 *      Author: root
 */

#include "inc/FCGI_Stream.h"


FCGI_Stream::FCGI_Stream( int socketId = 0) {
	//FCGX_Init();
	request = new FCGX_Request();
	this->socketId = socketId;
	FCGX_InitRequest(request, socketId, 0);
    cin_streambuf  = cin.rdbuf();
    cout_streambuf = cout.rdbuf();
    cerr_streambuf = cerr.rdbuf();
    status = false;
    /*cin_fcgi_streambuf = NULL;
    cout_fcgi_streambuf = NULL;
    cerr_fcgi_streambuf = NULL;*/
}

FCGI_Stream::~FCGI_Stream() {
	delete cin_fcgi_streambuf;
	delete cout_fcgi_streambuf;
	delete cerr_fcgi_streambuf;
///	if(buffer  != NULL)
		//delete []buffer;
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
	if(!FCGX_Accept_r(request))
	{
		status = true;
		return true;
	}
}

bool FCGI_Stream::multiIsRequest() {
	pthread_mutex_t accept_mutex = PTHREAD_MUTEX_INITIALIZER;

	printf("Try to accept new request\n");
	pthread_mutex_lock(&accept_mutex);
	status = true;
	int rc;
	rc = FCGX_Accept_r(request);
	pthread_mutex_unlock(&accept_mutex);
	printf("hernia");
	if(rc < 0)
	{
		status = false;
		printf("Can not accept new request\n");
		return false;
	}
	printf("request is accepted\n");
	//////////////////////////////////////// get bufer
	updateBuffer();
	/// ok
	return true;
}

void FCGI_Stream::updateBuffer()
{
	int content_length = getRequestSize();
		bool contentNULL = false;
		if( content_length <= 0 )
		{
			content_length = 10;
		}
		/*if(buffer != NULL)
			delete []buffer;*/
		buffer = new char[content_length];
		if(!contentNULL)
		FCGX_GetStr(buffer, content_length*sizeof(char), request->in);
}

void FCGI_Stream::reInitRequesBuffer()
{
	if(!status)
		return;
	char * content_length_str = FCGX_GetParam("CONTENT_LENGTH",  request->envp);
	int content_length = 0;
	if(content_length_str != 0)
		content_length = strtol(content_length_str, &content_length_str, 10);

	if( content_length <= 0 )
		content_length = 100;
	buffer =  new char[content_length + 1];
	cin.read(buffer, content_length);
	buffer[content_length] = '\0';
}

char *FCGI_Stream::getFormParam(string name)
{
 if (buffer==NULL) return NULL;

 char *pos;
 long leng=strlen(buffer);
 long i=0,j=0;
 char h1,h2,Hex;

 char *p=(char *)malloc(leng*sizeof(char));
 name.append("=");
 pos=strstr(buffer,name.c_str());
 if (pos == NULL) return NULL;
 //pos++;
 if ((pos!=buffer) && (*(pos-1)!='&')) return NULL;

 pos+=strlen(name.c_str());

 while ( (*(pos+i)!='&')&&( *(pos+i)!='\0' ))
 {
  if ( *(pos+i)=='%' )
  {
    i++;
    h1=gethex(*(pos+i));
    i++;
    h2=gethex(*(pos+i));
    h1=h1<<4;
    *(p+j)=h1+h2;
  }
  else
  {
    if (*(pos+i)!='+') *(p+j)=*(pos+i);
     else *(p+j)=' ';
  };
  i++;
  j++;
  if (j >= leng) p=(char*)realloc(p,leng+20);
  leng+=20;
 };
 if (j < leng) p=(char*)realloc(p,j+1);

 *(p+j)='\0';
 return p;
};

char FCGI_Stream::gethex(char ch)
{
  ch=upperchar(ch);
  if ((ch>='0')&&(ch<= '9')) return (ch-'0');
  if ((ch>='A')&&( ch<='F')) return (ch-'A'+10);
};

char FCGI_Stream::upperchar(char ch)
{
  if ((ch>='a') && (ch<='z'))
  {
      ch='A'+(ch - 'a');
      return ch;
   }
  else return ch;
};

void FCGI_Stream::close()
{
	FCGX_Finish_r(request);
}


FCGI_Stream FCGI_Stream::operator << ( char * str)
{
	FCGX_PutS(str, request->out);
	return this[0];
}
FCGI_Stream FCGI_Stream::operator << ( int num)
{
//		atoi("12");
	char str[10];
	sprintf(str, "%d", num);
	FCGX_PutS(str, request->out);
	return this[0];
}

FCGI_Stream FCGI_Stream::operator << ( double num)
{
//		atoi("12");
	char str[10];
	sprintf(str, "%lf", num);
	FCGX_PutS(str, request->out);
	return this[0];
}

FCGI_Stream FCGI_Stream::operator << ( string str)
{
//		atoi("12");
	FCGX_PutS(str.c_str(), request->out);
	return this[0];
}


void FCGI_Stream::operator >> ( char *res)
{
	res = new char[getRequestSize() + 10];
	strcpy((char*)res, buffer);
}

FCGX_Request *FCGI_Stream::getRequest() {
	return request;
}
/*
 *  get FCGI_Request pointer
 */
int FCGI_Stream::getRequestSize()
{
	if(!status)
			return 0;
		char * content_length_str = FCGX_GetParam("CONTENT_LENGTH",  request->envp);
		int content_length = 0;
		if(content_length_str != 0)
			content_length = strtol(content_length_str, &content_length_str, 10);
		//operator <<(content_length);
		return content_length;
}
