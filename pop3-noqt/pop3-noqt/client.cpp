#include "client.h"

#include <netdb.h>
#include <string.h>
#include <errno.h>
#include <iostream>
#include <sstream>
#include <sys/types.h>
#include <sys/socket.h>
#include <string>
#include <unistd.h>

/**
 * Конструктор класса - при успешном выполнение получат приветсвенное сообщение
 */
Client::Client(const std::string& ahostname, const unsigned short aport):
    shortMessage(false)
{
    memset(buffer, 0, sizeof(buffer));

    // получить IP
    if ((hostinfo = gethostbyname(ahostname.c_str())) == NULL) {
        std::cerr << "Can't get hostname" << std::endl;
        throw "Can't get host name"; // Да, я знаю про исключения в конструкторе!
    }

    // создаём сокет
    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        std::cerr << "Can't open socket, error = " << strerror(errno) << std::endl;
        throw "Can't open socket"; // Да, я знаю про исключения в конструкторе!
    }
    struct sockaddr_in address;
    memset(&address, 0, sizeof(address));
    address.sin_family = AF_INET;
    address.sin_addr = *(struct in_addr *)*hostinfo->h_addr_list;
    address.sin_port = htons(aport);
    int len = sizeof(address);

    // соединение
    if ((connect(sockfd, (struct sockaddr *)&address, len)) != 0) {
        std::cerr << "Can't connect to server, error = " << strerror(errno) << std::endl;
        throw "Can't connect to server"; // Да, я знаю про исключения в конструкторе!
    }

    // получаем приветсвющие сообщение
    int result = recv(sockfd, buffer, BUFLEN, 0);
    if (result != -1) {
        buffer[result] = '\0';
    }
    else {
        std::cerr << "An error occured during receiving greeting message from POP3 server" << std::endl;
        throw "Error during receiving greeting line"; // Да, я знаю про исключения в конструкторе!
    }
}

Client::~Client() {
    close(sockfd);
}

void Client::login(const std::string& user) {
    // печатаем пароль
    char *pass = getpass("Enter password (won't be printed):");

    std::string response;
    // USER
    try {
        response = sendReceive("USER " + user + "\n");
    }
    catch (const char * e) {
        std::string tmp(e);
        if (tmp == "Error response") {
            // USER command can receive an -ERR message even if the user exists! (security reasons).
            // If we receive -ERR for USER command, we ignore it
        }
        else throw e;
    }
    catch (...) {
        std::cerr << "An error occured during login" << std::endl;
        throw "Login error";
    }

    // PASS
    try {
        response = sendReceive("PASS " + (std::string)pass + "\n");
    }
    catch (const char * e) {
        std::string tmp(e);
        if (tmp == "Error response") {
            std::cerr << "Login is unsuccessful" << std::endl;
            throw e;
        }
    }
    catch (...) {
        std::cerr << "An error occured during login" << std::endl;
        throw "Login error";
    }
}

std::string Client::sendReceive(const std::string& message) {
    // отправка
    int result = send(sockfd, message.c_str(), message.length(), 0);
    if (result == -1) {
        throw "Message can't be sent";
    }

    // получка
    result = recv(sockfd, buffer, BUFLEN, 0);
    buffer[result] = '\0';
    if (result == -1) {
        throw "Message can't be received";
        close(sockfd);
    }

    // we've got the message, now check it
    std::string response = (std::string)buffer;
    if (! analyzeMessage(response)) {
        throw "Error response";
    }

    return response;
}

//проверка сообщения
bool Client::analyzeMessage(std::string& msg) const {
    // +OK
    if (msg.find("+OK") != std::string::npos) {
        if (msg.substr(0,3) == "+OK") { // проверяем, что ОК в начале
            return true;
        }
        else {
            throw("Invalid position of +OK status");
        }
    }
    // -ERR
    else if (msg.find("-ERR") != std::string::npos) {
        if (msg.substr(0,4) == "-ERR") { // проверяем, что еррор в начале
            // print status
            std::cerr << "Error response from server:" << msg.substr(4, msg.length()-4);
            return false;
        }
        else {
            throw("Invalid position of -ERR status");
        }
    } else {
        throw("Incorrect response message");
    }

    return false;	// варнинг
}

void Client::sendMessage(const std::string& message) {
    int result = send(sockfd, message.c_str(), message.length(), 0);
    if (result == -1) {
        std::cerr << "Message can't be sent" << std::endl;
        throw "Message can't be sent";
    }
}

void Client::receiveMessage(std::string& message) {
    int result=0;
    std::string tmp;

    // read data while there are any and no terminating CRLF has been found
    while ((result = recv(sockfd, buffer, BUFLEN, 0)) > 0) {
        buffer[result] = '\0';
        tmp += buffer;

        // check whether message ends up with "CRLF.CRLF". It indicates the end of message
        if (tmp.length() >= 5) {
            if (tmp.substr( tmp.length()-5, 5) == "\r\n.\r\n") {	// we've found the end of multi-line message
                break;
            }
        }
        else if (tmp == ".\r\n")
            break;
    }

    message = tmp;	// final response
}

void Client::listMails() {
    std::string message = "LIST\n";

    sendReceive(message);	// status message
    receiveMessage(message);	// data

    if (message.length() == 3) {	// = ".CRLF"
        std::cout << "No new messages" << std::endl;
        return;
    }

    if (shortMessage) {
        // remove last dot + CRLF
        message.erase( message.length() - 3, 3);
    }

    std::cout << message;
}

void Client::getMail(const unsigned int i) {
    // convert integer value to string
    std::stringstream ss;
    ss << i;
    std::string message = "RETR " + ss.str() + "\n";

    try {
        sendReceive(message);	// status message
        receiveMessage(message);	// data
    }
    catch (const char * e) {
        std::string tmp(e);
        if (tmp == "Error response") {
            std::cerr << "Can't get message " << i << std::endl;
            throw e;
        }
    }
    catch (...) {
        std::cerr << "An error occured during receiving message " << i << std::endl;
    }

    if (shortMessage) {
        // print message without header and last termination octet
        const size_t pos = message.find("\r\n\r\n");
        std::cout << message.substr(pos+4, message.length() - pos-4 -3 );	// last "-3" is to remove last ".\r\n"
    }
    else
        std::cout << message;
}

void Client::quit() {
    try {
        sendReceive("QUIT\n");
        close(sockfd);
    }
    catch (...) {
        // an error occured but we don't care, we are quitting anyway
    }
}
