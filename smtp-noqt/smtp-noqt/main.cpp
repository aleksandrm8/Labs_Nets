#include<iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

using namespace std;

#define HELO "HELO 192.168.1.1\r\n"
#define DATA "DATA\r\n"
#define QUIT "QUIT\r\n"

int sock;
struct sockaddr_in server;
struct hostent *hp, *gethostbyname();
char buf[BUFSIZ+1];
int len;
char *host_id="192.168.0.1"; //локалхост

char *from_id="rogachev@postavte_zachot.com";
char *to_id="rogachev@postavte_zachot.com";

char *sub="testmail\r\n";

char wkstr[100]="hello how r u\r\n";

   /*=====Отправка сокета=====*/

   void send_socket(char *s)
   {
       write(sock,s,strlen(s));
       write(1,s,strlen(s));
       //printf("Client:%s\n",s);
   }

   //=====Чтение сокета=====*/

   void read_socket()
   {
       len = read(sock,buf,BUFSIZ);
       write(1,buf,len);
     //printf("Server:%s\n",buf);
   }

   /*=====MAIN=====*/
   int main(int argc, char* argv[])
   {

   /*=====Создание сокета=====*/
   sock = socket(AF_INET, SOCK_STREAM, 0);
   if (sock==-1)
   {
    perror("opening stream socket");
    exit(1);
   }
   else
     cout << "socket created\n";
   /*=====Верификация=====*/
   server.sin_family = AF_INET;
   hp = gethostbyname(host_id);
   if (hp==(struct hostent *) 0)
   {
    fprintf(stderr, "%s: unknown host\n", host_id);
    exit(2);
   }

   /*=====Соединение с портом 25=====*/
   memcpy((char *) &server.sin_addr, (char *) hp->h_addr, hp->h_length);
   server.sin_port=htons(25); /* SMTP PORT */
   if (connect(sock, (struct sockaddr *) &server, sizeof server)==-1)
   {
    perror("connecting stream socket");
    exit(1);
   }
   else
     cout << "Connected\n";
   /*=====Отправка сообщений =====*/
   read_socket(); /* SMTP Server logon string */
   send_socket(HELO); /* introduce ourselves */
   read_socket(); /*Read reply */
   send_socket("MAIL FROM: ");
   send_socket(from_id);
   send_socket("\r\n");
   read_socket(); /* Sender OK */
   send_socket("VRFY ");
   send_socket(from_id);
   send_socket("\r\n");
   read_socket(); // Sender OK */
   send_socket("RCPT TO: "); /*Mail to*/
   send_socket(to_id);
   send_socket("\r\n");
   read_socket(); // Recipient OK*/
   send_socket(DATA);// body to follow*/
   send_socket("Subject: ");
   send_socket(sub);
   read_socket(); // Recipient OK*/
   send_socket(wkstr);
   send_socket(".\r\n");
   read_socket();
   send_socket(QUIT); /* quit */
   read_socket(); // log off */

   //=====Close socket and finish=====*/
   close(sock);
   exit(0);
 }

