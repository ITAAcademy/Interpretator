#include "inc/errorresponder.h"

ErrorResponder::ErrorResponder()
{

}

ErrorResponder::~ErrorResponder()
{

}

void ErrorResponder::showError(int nErrorCode, str sMoreText)
{
    switch(nErrorCode)
    {
     case 400:
        cout << "Status: 400\r\n"
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
    cout << "Status: 401\r\n"
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
    cout << "Status: 402\r\n"
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
    cout << "Status: 403\r\n"
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
    cout << "Status: 404\r\n"
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
    cout << "Status: 405\r\n"
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
    cout << "Status: 406\r\n"
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
    cout << "Status: 407\r\n"
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
    cout << "Status: 408\r\n"
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
        cout << "Status: 409\r\n"
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
    cout << "Status: 410\r\n"
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
    cout << "Status: 411\r\n"
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
    cout << "Status: 412\r\n"
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
    cout << "Status: 413\r\n"
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
    cout << "Status: 414\r\n"
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
    cout << "Status: 415\r\n"
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
    cout << "Status: 416\r\n"
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
    cout << "Status: 417\r\n"
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
    cout << "Status: 418\r\n"
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
    cout << "Status: 422\r\n"
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
    cout << "Status: 423\r\n"
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
    cout << "Status: 424\r\n"
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
    cout << "Status: 425\r\n"
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
    cout << "Status: 426\r\n"
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
    cout << "Status: 428\r\n"
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
    cout << "Status: 429\r\n"
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
    cout << "Status: 431\r\n"
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
    cout << "Status: 434\r\n"
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
    cout << "Status: 449\r\n"
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
    cout << "Status: 451\r\n"
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
    cout << "Status: 456\r\n"
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
    cout << "Status: 499\r\n"
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
    }
}

void ErrorResponder::showClientError(str sHeader, str sErrorText, str sMoreText)
{
    cout << "Status: " <<sHeader <<"\r\n"
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
