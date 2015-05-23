#include "inc/errorresponder.h";

ErrorResponder::ErrorResponder()
{

}

ErrorResponder::~ErrorResponder()
{

}

void ErrorResponder::showError(int nErrorCode, str sMoreText)
{
    if(sMoreText =="";)
        sMoreText = sDefaultText;
    switch(nErrorCode)
    {
     case 400:
                stream << "Status: 400\r\n";;
                        stream << "Content-type: text/html\r\n";;
                        stream << "\r\n";;
                        stream << " <html><head>";;
                        stream << "<title>400 Bad Request</title>";;
                        stream << "</head><body>";;
                        stream << "<h1>Bad Request</h1>";;
                        stream << "<p>";;
                        stream <<  sMoreText;
                        stream << "</p>";;
                        stream << "<hr>";;
                        stream << "</body></html>";;
    break;
    case 401:
            stream << "Status: 401\r\n";;
                    stream << "Content-type: text/html\r\n";;
                    stream << "\r\n";;
                    stream << " <html><head>";;
                    stream << "<title>401 Unauthorized</title>";;
                    stream << "</head><body>";;
                    stream << "<h1>Unauthorized</h1>";;
                    stream << "<p>";;
                    stream <<  sMoreText;
                    stream << "</p>";;
                    stream << "<hr>";;
                    stream << "</body></html>";;
    break;
    case 402:
            stream << "Status: 402\r\n";;
                    stream << "Content-type: text/html\r\n";;
                    stream << "\r\n";;
                    stream << " <html><head>";;
                    stream << "<title>402 Payment Required</title>";;
                    stream << "</head><body>";;
                    stream << "<h1>Payment Required</h1>";;
                    stream << "<p>";;
                    stream <<  sMoreText;
                    stream << "</p>";;
                    stream << "<hr>";;
                    stream << "</body></html>";;
    break;
    case 403:
            stream << "Status: 403\r\n";;
                    stream << "Content-type: text/html\r\n";;
                    stream << "\r\n";;
                    stream << " <html><head>";;
                    stream << "<title>403 Forbidden</title>";;
                    stream << "</head><body>";;
                    stream << "<h1>Forbidden</h1>";;
                    stream << "<p>";;
                    stream <<  sMoreText;
                    stream << "</p>";;
                    stream << "<hr>";;
                    stream << "</body></html>";;
    break;
    case 404:
            stream << "Status: 404\r\n";;
                    stream << "Content-type: text/html\r\n";;
                    stream << "\r\n";;
                    stream << " <html><head>";;
                    stream << "<title>404 Not Found</title>";;
                    stream << "</head><body>";;
                    stream << "<h1>Not Found</h1>";;
                    stream << "<p>";;
                    stream <<  sMoreText;
                    stream << "</p>";;
                    stream << "<hr>";;
                    stream << "</body></html>";;
        break;
    case 405:
            stream << "Status: 405\r\n";;
                    stream << "Content-type: text/html\r\n";;
                    stream << "\r\n";;
                    stream << " <html><head>";;
                    stream << "<title>405 Method Not Allowed</title>";;
                    stream << "</head><body>";;
                    stream << "<h1>Method Not Allowed</h1>";;
                    stream << "<p>";;
                    stream <<  sMoreText;
                    stream << "</p>";;
                    stream << "<hr>";;
                    stream << "</body></html>";;
    break;
    case 406:
            stream << "Status: 406\r\n";;
                    stream << "Content-type: text/html\r\n";;
                    stream << "\r\n";;
                    stream << " <html><head>";;
                    stream << "<title>406 Not Acceptable</title>";;
                    stream << "</head><body>";;
                    stream << "<h1>Not Acceptabl</h1>";;
                    stream << "<p>";;
                    stream <<  sMoreText;
                    stream << "</p>";;
                    stream << "<hr>";;
                    stream << "</body></html>";;
    break;
    case 407:
            stream << "Status: 407\r\n";;
                    stream << "Content-type: text/html\r\n";;
                    stream << "\r\n";;
                    stream << " <html><head>";;
                    stream << "<title>407 Proxy Authentication Required</title>";;
                    stream << "</head><body>";;
                    stream << "<h1>Proxy Authentication Required</h1>";;
                    stream << "<p>";;
                    stream <<  sMoreText;
                    stream << "</p>";;
                    stream << "<hr>";;
                    stream << "</body></html>";;
    break;
    case 408:
            stream << "Status: 408\r\n";
                    stream << "Content-type: text/html\r\n";
                    stream << "\r\n";
                    stream << " <html><head>";
                    stream << "<title>408 Request Timeout</title>";
                    stream << "</head><body>";
                    stream << "<h1>Request Timeout</h1>";
                    stream << "<p>";
                    stream <<  sMoreText;
                    stream << "</p>";
                    stream << "<hr>";
                    stream << "</body></html>";;
    break;
    case 409:
                stream << "Status: 409\r\n";
                        stream << "Content-type: text/html\r\n";
                        stream << "\r\n";
                        stream << " <html><head>";
                        stream << "<title>409 Conflict</title>";
                        stream << "</head><body>";
                        stream << "<h1>Conflict</h1>";
                        stream << "<p>";
                        stream <<  sMoreText;
                        stream << "</p>";
                        stream << "<hr>";
                        stream << "</body></html>";;
        break;
    case 410:
            stream << "Status: 410\r\n";
                    stream << "Content-type: text/html\r\n";
                    stream << "\r\n";
                    stream << " <html><head>";
                    stream << "<title>410 Gone</title>";
                    stream << "</head><body>";
                    stream << "<h1>Gone</h1>";
                    stream << "<p>";
                    stream <<  sMoreText;
                    stream << "</p>";
                    stream << "<hr>";
                    stream << "</body></html>";;
    break;
    case 411:
            stream << "Status: 411\r\n";
                    stream << "Content-type: text/html\r\n";
                    stream << "\r\n";
                    stream << " <html><head>";
                    stream << "<title>411 Length Required</title>";
                    stream << "</head><body>";
                    stream << "<h1>Length Required</h1>";
                    stream << "<p>";
                    stream <<  sMoreText;
                    stream << "</p>";
                    stream << "<hr>";
                    stream << "</body></html>";;
    break;
    case 412:
            stream << "Status: 412\r\n";
                    stream << "Content-type: text/html\r\n";
                    stream << "\r\n";
                    stream << " <html><head>";
                    stream << "<title>412 Precondition Failed</title>";
                    stream << "</head><body>";
                    stream << "<h1>Precondition Failed</h1>";
                    stream << "<p>";
                    stream <<  sMoreText;
                    stream << "</p>";
                    stream << "<hr>";
                    stream << "</body></html>";;
    break;
    case 413:
            stream << "Status: 413\r\n";
                    stream << "Content-type: text/html\r\n";
                    stream << "\r\n";
                    stream << " <html><head>";
                    stream << "<title>413 Request Entity Too Large</title>";
                    stream << "</head><body>";
                    stream << "<h1>Request Entity Too Large</h1>";
                    stream << "<p>";
                    stream <<  sMoreText;
                    stream << "</p>";
                    stream << "<hr>";
                    stream << "</body></html>";;
    break;
    case 414:
            stream << "Status: 414\r\n";
                    stream << "Content-type: text/html\r\n";
                    stream << "\r\n";
                    stream << " <html><head>";
                    stream << "<title>414 Request-URI Too Large</title>";
                    stream << "</head><body>";
                    stream << "<h1>Request-URI Too Large</h1>";
                    stream << "<p>";
                    stream <<  sMoreText;
                    stream << "</p>";
                    stream << "<hr>";
                    stream << "</body></html>";;
    break;
    case 415:
            stream << "Status: 415\r\n";
                    stream << "Content-type: text/html\r\n";
                    stream << "\r\n";
                    stream << " <html><head>";
                    stream << "<title>415 Unsupported Media Type</title>";
                    stream << "</head><body>";
                    stream << "<h1>Unsupported Media Type</h1>";
                    stream << "<p>";
                    stream <<  sMoreText;
                    stream << "</p>";
                    stream << "<hr>";
                    stream << "</body></html>";;
    break;
    case 416:
            stream << "Status: 416\r\n";
                    stream << "Content-type: text/html\r\n";
                    stream << "\r\n";
                    stream << " <html><head>";
                    stream << "<title>416 Requested Range Not Satisfiable</title>";
                    stream << "</head><body>";
                    stream << "<h1>Requested Range Not Satisfiable</h1>";
                    stream << "<p>";
                    stream <<  sMoreText;
                    stream << "</p>";
                    stream << "<hr>";
                     stream << "</body></html>";;
    break;
    case 417:
            stream << "Status: 417\r\n";
                    stream << "Content-type: text/html\r\n";
                    stream << "\r\n";
                    stream << " <html><head>";
                    stream << "<title>417 Expectation Failed</title>";
                    stream << "</head><body>";
                    stream << "<h1>Expectation Failed</h1>";
                    stream << "<p>";
                    stream <<  sMoreText;
                    stream << "</p>";
                    stream << "<hr>";
                    stream << "</body></html>";;
    break;
    case 418:
            stream << "Status: 418\r\n";
                    stream << "Content-type: text/html\r\n";
                    stream << "\r\n";
                    stream << " <html><head>";
                    stream << "<title>418 I'm a teapot</title>";
                    stream << "</head><body>";
                    stream << "<h1>I'm a teapot</h1>";
                    stream << "<p>";
                    stream <<  sMoreText;
                    stream << "</p>";
                    stream << "<hr>";
                    stream << "</body></html>";;
    break;
    case 422:
            stream << "Status: 422\r\n";
                    stream << "Content-type: text/html\r\n";
                    stream << "\r\n";
                    stream << " <html><head>";
                    stream << "<title>422 Unprocessable Entity</title>";
                    stream << "</head><body>";
                    stream << "<h1>Unprocessable Entity</h1>";
                    stream << "<p>";
                    stream <<  sMoreText;
                    stream << "</p>";
                    stream << "<hr>";
                    stream << "</body></html>";;
    break;
    case 423:
            stream << "Status: 423\r\n";
                    stream << "Content-type: text/html\r\n";
                    stream << "\r\n";
                    stream << " <html><head>";
                    stream << "<title>423 Locked</title>";
                    stream << "</head><body>";
                    stream << "<h1>Locked</h1>";
                    stream << "<p>";
                    stream <<  sMoreText;
                    stream << "</p>";
                    stream << "<hr>";
                    stream << "</body></html>";;
    break;
    case 424:
            stream << "Status: 424\r\n";
                    stream << "Content-type: text/html\r\n";
                    stream << "\r\n";
                    stream << " <html><head>";
                    stream << "<title>424 Failed Dependency</title>";
                    stream << "</head><body>";
                    stream << "<h1>Failed Dependency</h1>";
                    stream << "<p>";
                    stream <<  sMoreText;
                    stream << "</p>";
                    stream << "<hr>";
                    stream << "</body></html>";;
    break;
    case 425:
            stream << "Status: 425\r\n";
                    stream << "Content-type: text/html\r\n";
                    stream << "\r\n";
                    stream << " <html><head>";
                    stream << "<title>425 Unordered Collection</title>";
                    stream << "</head><body>";
                    stream << "<h1>Unordered Collection</h1>";
                    stream << "<p>";
                    stream <<  sMoreText;
                    stream << "</p>";
                    stream << "<hr>";
                    stream << "</body></html>";;
    break;
    case 426:
            stream << "Status: 426\r\n";
                    stream << "Content-type: text/html\r\n";
                    stream << "\r\n";
                    stream << " <html><head>";
                    stream << "<title>426 Upgrade Required</title>";
                    stream << "</head><body>";
                    stream << "<h1>Upgrade Required</h1>";
                    stream << "<p>";
                    stream <<  sMoreText;
                    stream << "</p>";
                    stream << "<hr>";
                    stream << "</body></html>";;
    break;
    case 428:
            stream << "Status: 428\r\n";
                    stream << "Content-type: text/html\r\n";
                    stream << "\r\n";
                    stream << " <html><head>";
                    stream << "<title>428 Precondition Required</title>";
                    stream << "</head><body>";
                    stream << "<h1>Precondition Required</h1>";
                    stream << "<p>";
                    stream <<  sMoreText;
                    stream << "</p>";
                    stream << "<hr>";
                    stream << "</body></html>";;
    break;
    case 429:
            stream << "Status: 429\r\n";
            stream << "Content-type: text/html\r\n";
            stream << "\r\n";
            stream << " <html><head>";
            stream << "<title>429 Too Many Requests</title>";
            stream << "</head><body>";
            stream << "<h1>Too Many Requests</h1>";
            stream << "<p>";
            stream <<  sMoreText;
            stream << "</p>";
            stream << "<hr>";
            stream << "</body></html>";;
    break;
    case 431:
            stream << "Status: 431\r\n";
            stream << "Content-type: text/html\r\n";
            stream << "\r\n";
            stream << " <html><head>";
            stream << "<title>431 Request Header Fields Too Large</title>";
            stream << "</head><body>";
            stream << "<h1>Request Header Fields Too Large</h1>";
            stream << "<p>";
            stream <<  sMoreText;
            stream << "</p>";
            stream << "<hr>";
            stream << "</body></html>";;
    break;
    case 434:
     stream << "Status: 434\r\n";
            stream << "Content-type: text/html\r\n";
            stream << "\r\n";
            stream << " <html><head>";
            stream << "<title>434 Requested host unavailable</title>";
            stream << "</head><body>";
            stream << "<h1>Requested host unavailable</h1>";
            stream << "<p>";
            stream <<  sMoreText;
            stream << "</p>";
            stream << "<hr>";
            stream << "</body></html>";;
    break;
    case 449:
            stream << "Status: 449\r\n";
            stream << "Content-type: text/html\r\n";
            stream << "\r\n";
            stream << " <html><head>";
            stream << "<title>449 Retry With</title>";
            stream << "</head><body>";
            stream << "<h1>Retry With</h1>";
            stream << "<p>";
            stream <<  sMoreText;
            stream << "</p>";
            stream << "<hr>";
            stream << "</body></html>";;
    break;
    case 451:
            stream << "Status: 451\r\n";
            stream << "Content-type: text/html\r\n";
            stream << "\r\n";
            stream << " <html><head>";
            stream << "<title>451 Unavailable For Legal Reasons</title>";
            stream << "</head><body>";
            stream << "<h1>Unavailable For Legal Reasons</h1>";
            stream << "<p>";
            stream <<  sMoreText;
            stream << "</p>";
            stream << "<hr>";
            stream << "</body></html>";;
    break;
    case 456:
            stream << "Status: 456\r\n";
            stream << "Content-type: text/html\r\n";
            stream << "\r\n";
            stream << " <html><head>";
            stream << "<title>456 Unrecoverable Error</title>";
            stream << "</head><body>";
            stream << "<h1>Unrecoverable Error</h1>";
            stream << "<p>";
            stream <<  sMoreText;
            stream << "</p>";
            stream << "<hr>";
            stream << "</body></html>";;
    break;
    case 499:
            stream << "Status: 499\r\n";
            stream << "Content-type: text/html\r\n";
            stream << "\r\n";
            stream << " <html><head>";
            stream << "<title>499 Client closed the connection before receiving a response</title>";
            stream << "</head><body>";
            stream << "<h1>Client closed the connection before receiving a response</h1>";
            stream << "<p>";
            stream <<  sMoreText;
            stream << "</p>";
            stream << "<hr>";
            stream << "</body></html>";;
    break;
    }
}

void ErrorResponder::showClientError(str sHeader, str sErrorText, str sMoreText)
{
            stream << "Status:";
            stream << sHeader;
            stream <<"\r\n";
            stream << "Content-type: text/html\r\n";
            stream << "\r\n";
            stream << " <html><head>";
            stream << "<title>";
            stream <<  sHeader;
            stream << " ";
            stream <<  sErrorText;
            stream << "</title>";
            stream << "</head><body>";
            stream << "<h1>";
            stream <<  sErrorText;
            stream << "</h1>";
            stream << "<p>";
            stream <<  sMoreText;
            stream << "</p>";
            stream << "<hr>";
            stream << "</body></html>";;
}
