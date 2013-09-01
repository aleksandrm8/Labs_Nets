#ifndef CLIENT_H
#define CLIENT_H

#include <string>

#define POP3_PORT 110

// Size of 512 bytes is determined by RFC 1939
#define BUFLEN 512

class Client {
    std::string host;				/// хост
    unsigned short port;			/// порт
    int sockfd;						/// сокет
    struct hostent *hostinfo;		/// IP адресс + порт
    char buffer[BUFLEN+1];			/// буфер сообщения

    std::string username;			/// логин

    bool shortMessage;				/// если true то пишет все данные с заголовком

    std::string sendReceive(const std::string& message);	/// отослать сообщение и получить подтверждение
    void sendMessage(const std::string& message);			/// отослать на сервер
    void receiveMessage(std::string& message);				/// получить сообщение
    bool analyzeMessage(std::string& msg) const;			/// проверить статус

    public:
    Client(const std::string& ahostname, const unsigned short aport=POP3_PORT);
    ~Client();

    void setShortMessage(const bool type=false)	{ shortMessage = type; }
    void login(const std::string& user);
    void listMails();
    void getMail(const unsigned int i);
    void quit();
};


#endif
