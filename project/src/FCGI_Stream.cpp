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
    status = false;
    /*cin_fcgi_streambuf = NULL;
    cout_fcgi_streambuf = NULL;
    cerr_fcgi_streambuf = NULL;*/
}

FCGI_Stream::~FCGI_Stream() {
	delete cin_fcgi_streambuf;
	delete cout_fcgi_streambuf;
	delete cerr_fcgi_streambuf;
	delete []buffer;
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
char* FCGI_Stream::getRequesBuffer()
{
	return buffer;
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
char *FCGI_Stream::getFormParam(char *name)
{
 if (buffer==NULL) return NULL;

 char *pos;
 long leng=512,i=0,j=0;
 char h1,h2,Hex;

 char *p=(char *)malloc(leng);
 pos=strstr(buffer,name);
 if (pos == NULL) return NULL;
 //pos++;
 if ((pos!=buffer) && (*(pos-1)!='&')) return NULL;

 pos+=strlen(name) + 1;

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
