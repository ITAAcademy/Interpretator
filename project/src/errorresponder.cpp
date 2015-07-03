#include "inc/errorresponder.h"

ErrorResponder::ErrorResponder(FCGI_Stream *stream)
{
	this->stream = stream;
}

ErrorResponder::~ErrorResponder()
{

}

void ErrorResponder::selectStream(FCGI_Stream *stream)
{
	this->stream = stream;
}
void ErrorResponder::showError(int nErrorCode, str sMoreText)
{
    switch(nErrorCode)
    {
     case 400:
        stream->operator <<("Status: 400\r\n")
                 << "Content-type: text/html\r\n"
                 << "\r\n"
                 << " <html><head>"
                 << "<title>400 Bad Request</title>"
                 << "</head><body>"
                 << "<h1>Bad Request</h1>"
                 << "<p>"
                 << sMoreText
                 << "</p>"
                 << "<hr>"
                 << "</body></html>";
    break;
    case 401:
    	stream->operator <<("Status: 401\r\n")
             << "Content-type: text/html\r\n"
             << "\r\n"
             << " <html><head>"
             << "<title>401 Unauthorized</title>"
             << "</head><body>"
             << "<h1>Unauthorized</h1>"
             << "<p>"
             << sMoreText
             << "</p>"
             << "<hr>"
             << "</body></html>";
    break;
    case 402:
    	stream->operator <<( "Status: 402\r\n")
             << "Content-type: text/html\r\n"
             << "\r\n"
             << " <html><head>"
             << "<title>402 Payment Required</title>"
             << "</head><body>"
             << "<h1>Payment Required</h1>"
             << "<p>"
             << sMoreText
             << "</p>"
             << "<hr>"
             << "</body></html>";
    break;
    case 403:
    	stream->operator <<( "Status: 403\r\n")
             << "Content-type: text/html\r\n"
             << "\r\n"
             << " <html><head>"
             << "<title>403 Forbidden</title>"
             << "</head><body>"
             << "<h1>Forbidden</h1>"
             << "<p>"
             << sMoreText
             << "</p>"
             << "<hr>"
             << "</body></html>";
    break;
    case 404:
    	stream->operator <<( "Status: 404\r\n")
             << "Content-type: text/html\r\n"
             << "\r\n"
             << " <html><head>"
             << "<title>404 Not Found</title>"
             << "</head><body>"
             << "<h1>Not Found</h1>"
             << "<p>"
             << sMoreText
             << "</p>"
             << "<hr>"
             << "</body></html>";
    break;
    case 405:
    	stream->operator <<( "Status: 405\r\n")
             << "Content-type: text/html\r\n"
             << "\r\n"
             << " <html><head>"
             << "<title>405 Method Not Allowed</title>"
             << "</head><body>"
             << "<h1>Method Not Allowed</h1>"
             << "<p>"
             << sMoreText
             << "</p>"
             << "<hr>"
             << "</body></html>";
    break;
    case 406:
    	stream->operator <<( "Status: 406\r\n")
             << "Content-type: text/html\r\n"
             << "\r\n"
             << " <html><head>"
             << "<title>406 Not Acceptable</title>"
             << "</head><body>"
             << "<h1>Not Acceptabl</h1>"
             << "<p>"
             << sMoreText
             << "</p>"
             << "<hr>"
             << "</body></html>";
    break;
    case 407:
    	stream->operator <<("Status: 407\r\n")
             << "Content-type: text/html\r\n"
             << "\r\n"
             << " <html><head>"
             << "<title>407 Proxy Authentication Required</title>"
             << "</head><body>"
             << "<h1>Proxy Authentication Required</h1>"
             << "<p>"
             << sMoreText
             << "</p>"
             << "<hr>"
             << "</body></html>";
    break;
    case 408:
    	stream->operator <<( "Status: 408\r\n")
             << "Content-type: text/html\r\n"
             << "\r\n"
             << " <html><head>"
             << "<title>408 Request Timeout</title>"
             << "</head><body>"
             << "<h1>Request Timeout</h1>"
             << "<p>"
             << sMoreText
             << "</p>"
             << "<hr>"
             << "</body></html>";
    break;
    case 409:
    	stream->operator <<( "Status: 409\r\n")
                 << "Content-type: text/html\r\n"
                 << "\r\n"
                 << " <html><head>"
                 << "<title>409 Conflict</title>"
                 << "</head><body>"
                 << "<h1>Conflict</h1>"
                 << "<p>"
                 << sMoreText
                 << "</p>"
                 << "<hr>"
                 << "</body></html>";
        break;
    case 410:
    	stream->operator <<( "Status: 410\r\n")
             << "Content-type: text/html\r\n"
             << "\r\n"
             << " <html><head>"
             << "<title>410 Gone</title>"
             << "</head><body>"
             << "<h1>Gone</h1>"
             << "<p>"
             << sMoreText
             << "</p>"
             << "<hr>"
             << "</body></html>";
    break;
    case 411:
    	stream->operator <<( "Status: 411\r\n")
             << "Content-type: text/html\r\n"
             << "\r\n"
             << " <html><head>"
             << "<title>411 Length Required</title>"
             << "</head><body>"
             << "<h1>Length Required</h1>"
             << "<p>"
             << sMoreText
             << "</p>"
             << "<hr>"
             << "</body></html>";
    break;
    case 412:
    	stream->operator <<( "Status: 412\r\n")
             << "Content-type: text/html\r\n"
             << "\r\n"
             << " <html><head>"
             << "<title>412 Precondition Failed</title>"
             << "</head><body>"
             << "<h1>Precondition Failed</h1>"
             << "<p>"
             << sMoreText
             << "</p>"
             << "<hr>"
             << "</body></html>";
    break;
    case 413:
    	stream->operator <<( "Status: 413\r\n")
             << "Content-type: text/html\r\n"
             << "\r\n"
             << " <html><head>"
             << "<title>413 Request Entity Too Large</title>"
             << "</head><body>"
             << "<h1>Request Entity Too Large</h1>"
             << "<p>"
             << sMoreText
             << "</p>"
             << "<hr>"
             << "</body></html>";
    break;
    case 414:
    	stream->operator <<( "Status: 414\r\n")
             << "Content-type: text/html\r\n"
             << "\r\n"
             << " <html><head>"
             << "<title>414 Request-URI Too Large</title>"
             << "</head><body>"
             << "<h1>Request-URI Too Large</h1>"
             << "<p>"
             << sMoreText
             << "</p>"
             << "<hr>"
             << "</body></html>";
    break;
    case 415:
    	stream->operator <<( "Status: 415\r\n")
             << "Content-type: text/html\r\n"
             << "\r\n"
             << " <html><head>"
             << "<title>415 Unsupported Media Type</title>"
             << "</head><body>"
             << "<h1>Unsupported Media Type</h1>"
             << "<p>"
             << sMoreText
             << "</p>"
             << "<hr>"
             << "</body></html>";
    break;
    case 416:
    	stream->operator <<( "Status: 416\r\n")
             << "Content-type: text/html\r\n"
             << "\r\n"
             << " <html><head>"
             << "<title>416 Requested Range Not Satisfiable</title>"
             << "</head><body>"
             << "<h1>Requested Range Not Satisfiable</h1>"
             << "<p>"
             << sMoreText
             << "</p>"
             << "<hr>"
             << "</body></html>";
    break;
    case 417:
    	stream->operator <<( "Status: 417\r\n")
             << "Content-type: text/html\r\n"
             << "\r\n"
             << " <html><head>"
             << "<title>417 Expectation Failed</title>"
             << "</head><body>"
             << "<h1>Expectation Failed</h1>"
             << "<p>"
             << sMoreText
             << "</p>"
             << "<hr>"
             << "</body></html>";
    break;
    case 418:
    	stream->operator <<( "Status: 418\r\n")
             << "Content-type: text/html\r\n"
             << "\r\n"
             << " <html><head>"
             << "<title>418 I'm a teapot</title>"
             << "</head><body>"
             << "<h1>I'm a teapot</h1>"
             << "<p>"
             << sMoreText
             << "</p>"
             << "<hr>"
             << "</body></html>";
    break;
    case 422:
    	stream->operator <<( "Status: 422\r\n")
             << "Content-type: text/html\r\n"
             << "\r\n"
             << " <html><head>"
             << "<title>422 Unprocessable Entity</title>"
             << "</head><body>"
             << "<h1>Unprocessable Entity</h1>"
             << "<p>"
             << sMoreText
             << "</p>"
             << "<hr>"
             << "</body></html>";
    break;
    case 423:
    	stream->operator <<("Status: 423\r\n")
             << "Content-type: text/html\r\n"
             << "\r\n"
             << " <html><head>"
             << "<title>423 Locked</title>"
             << "</head><body>"
             << "<h1>Locked</h1>"
             << "<p>"
             << sMoreText
             << "</p>"
             << "<hr>"
             << "</body></html>";
    break;
    case 424:
    	stream->operator <<("Status: 424\r\n")
             << "Content-type: text/html\r\n"
             << "\r\n"
             << " <html><head>"
             << "<title>424 Failed Dependency</title>"
             << "</head><body>"
             << "<h1>Failed Dependency</h1>"
             << "<p>"
             << sMoreText
             << "</p>"
             << "<hr>"
             << "</body></html>";
    break;
    case 425:
    	stream->operator <<( "Status: 425\r\n")
             << "Content-type: text/html\r\n"
             << "\r\n"
             << " <html><head>"
             << "<title>425 Unordered Collection</title>"
             << "</head><body>"
             << "<h1>Unordered Collection</h1>"
             << "<p>"
             << sMoreText
             << "</p>"
             << "<hr>"
             << "</body></html>";
    break;
    case 426:
    	stream->operator <<( "Status: 426\r\n")
             << "Content-type: text/html\r\n"
             << "\r\n"
             << " <html><head>"
             << "<title>426 Upgrade Required</title>"
             << "</head><body>"
             << "<h1>Upgrade Required</h1>"
             << "<p>"
             << sMoreText
             << "</p>"
             << "<hr>"
             << "</body></html>";
    break;
    case 428:
    	stream->operator <<( "Status: 428\r\n")
             << "Content-type: text/html\r\n"
             << "\r\n"
             << " <html><head>"
             << "<title>428 Precondition Required</title>"
             << "</head><body>"
             << "<h1>Precondition Required</h1>"
             << "<p>"
             << sMoreText
             << "</p>"
             << "<hr>"
             << "</body></html>";
    break;
    case 429:
    	stream->operator <<( "Status: 429\r\n")
             << "Content-type: text/html\r\n"
             << "\r\n"
             << " <html><head>"
             << "<title>429 Too Many Requests</title>"
             << "</head><body>"
             << "<h1>Too Many Requests</h1>"
             << "<p>"
             << sMoreText
             << "</p>"
             << "<hr>"
             << "</body></html>";
    break;
    case 431:
    	stream->operator <<( "Status: 431\r\n")
             << "Content-type: text/html\r\n"
             << "\r\n"
             << " <html><head>"
             << "<title>431 Request Header Fields Too Large</title>"
             << "</head><body>"
             << "<h1>Request Header Fields Too Large</h1>"
             << "<p>"
             << sMoreText
             << "</p>"
             << "<hr>"
             << "</body></html>";
    break;
    case 434:
    	stream->operator <<( "Status: 434\r\n")
             << "Content-type: text/html\r\n"
             << "\r\n"
             << " <html><head>"
             << "<title>434 Requested host unavailable</title>"
             << "</head><body>"
             << "<h1>Requested host unavailable</h1>"
             << "<p>"
             << sMoreText
             << "</p>"
             << "<hr>"
             << "</body></html>";
    break;
    case 449:
    	stream->operator <<( "Status: 449\r\n")
             << "Content-type: text/html\r\n"
             << "\r\n"
             << " <html><head>"
             << "<title>449 Retry With</title>"
             << "</head><body>"
             << "<h1>Retry With</h1>"
             << "<p>"
             << sMoreText
             << "</p>"
             << "<hr>"
             << "</body></html>";
    break;
    case 451:
    	stream->operator <<( "Status: 451\r\n")
             << "Content-type: text/html\r\n"
             << "\r\n"
             << " <html><head>"
             << "<title>451 Unavailable For Legal Reasons</title>"
             << "</head><body>"
             << "<h1>Unavailable For Legal Reasons</h1>"
             << "<p>"
             << sMoreText
             << "</p>"
             << "<hr>"
             << "</body></html>";
    break;
    case 456:
    	stream->operator <<( "Status: 456\r\n")
             << "Content-type: text/html\r\n"
             << "\r\n"
             << " <html><head>"
             << "<title>456 Unrecoverable Error</title>"
             << "</head><body>"
             << "<h1>Unrecoverable Error</h1>"
             << "<p>"
             << sMoreText
             << "</p>"
             << "<hr>"
             << "</body></html>";
    break;
    case 499:
    	stream->operator <<( "Status: 499\r\n")
             << "Content-type: text/html\r\n"
             << "\r\n"
             << " <html><head>"
             << "<title>499 Client closed the connection before receiving a response</title>"
             << "</head><body>"
             << "<h1>Client closed the connection before receiving a response</h1>"
             << "<p>"
             << sMoreText
             << "</p>"
             << "<hr>"
             << "</body></html>";
    break;
    default:
    	stream->operator <<( "Status: " + to_string(nErrorCode) +"\r\n")
             << "Content-type: text/html\r\n"
             << "\r\n"
             << " <html><head>"
             << "<title>" + to_string(nErrorCode) + sMoreText + "</title>"
             << "</head><body>"
             << "<h1>" + sMoreText + "</h1>"
             << "<hr>"
             << "</body></html>";

    }
}

void ErrorResponder::showClientError(str sHeader, str sErrorText, str sMoreText)
{
	stream->operator <<( "Status: ") <<sHeader <<"\r\n"
             << "Content-type: text/html\r\n"
             << "\r\n"
             << " <html><head>"
             << "<title>"
             << sHeader << " " << sErrorText
             << "</title>"
             << "</head><body>"
             << "<h1>"
             << sErrorText
             << "</h1>"
             << "<p>"
             << sMoreText
             << "</p>"
             << "<hr>"
             << "</body></html>";
}
