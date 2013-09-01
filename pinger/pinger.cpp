#include "pinger.h"

#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <linux/ip.h>
#include <linux/icmp.h>

namespace
{
    char* getip()
    {
        char buffer[256];
        struct hostent* h;

        gethostname( buffer, 256 );
        h = gethostbyname( buffer );

        if( h )
            return inet_ntoa(*(struct in_addr *)h->h_addr);
        else
            return "localhost";

    }

    unsigned short in_cksum( unsigned short *addr, int len )
    {
        register int sum = 0;
        u_short answer = 0;
        register u_short *w = addr;
        register int nleft = len;
        /*
         * Our algorithm is simple, using a 32 bit accumulator (sum), we add
         * sequential 16 bit words to it, and at the end, fold back all the
         * carry bits from the top 16 bits into the lower 16 bits.
         */
        while (nleft > 1)
        {
          sum += *w++;
          nleft -= 2;
        }
        /* mop up an odd byte, if necessary */
        if (nleft == 1)
        {
          *(u_char *) (&answer) = *(u_char *) w;
          sum += answer;
        }
        /* add back carry outs from top 16 bits to low 16 bits */
        sum = (sum >> 16) + (sum & 0xffff);       /* add hi 16 to low 16 */
        sum += (sum >> 16);               /* add carry */
        answer = ~sum;              /* truncate to 16 bits */
        return (answer);
    }
}

Pinger::Pinger( QObject *parent ) :
    QObject(parent)
{}

void Pinger::execute( const std::string& destAddress, int interval )
{
    if ( getuid() != 0 )
    {
        this->log( QString( "Root privelidges needed!" ), Qt::red );
    }


    this->log( tr( "Start pinging " ) + QString::fromStdString( destAddress ) +
               tr( " with " ) + QString::number( interval ) + " ms.", Qt::black );

    struct iphdr* ip = new iphdr;
    struct iphdr* ip_reply = new iphdr;
    struct icmphdr* icmp = new icmphdr;
    char* packet = new char( sizeof(struct iphdr) + sizeof(struct icmphdr) / sizeof( char ));
    char* buffer = new char( sizeof(struct iphdr) + sizeof(struct icmphdr) / sizeof( char ));

    this->log( tr( "Getting ip..." ), Qt::darkYellow );

    srcAddress = ::getip();

    this->log( tr( "from: " ) + QString::fromStdString( srcAddress ), Qt::darkYellow );

    ip->ihl          = 5;
    ip->version      = 4;
    ip->tos          = 0;
    ip->tot_len      = sizeof(struct iphdr) + sizeof(struct icmphdr);
    ip->id           = htons(random());
    ip->ttl          = 255;
    ip->protocol     = IPPROTO_ICMP;
    ip->saddr        = inet_addr( srcAddress.c_str() );
    ip->daddr        = inet_addr( destAddress.c_str() );

    int sockfd;
    int optval;

    if ( ( sockfd = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP ) ) == -1 )
    {
        this->log( QString( "Can't create socket!" ), Qt::red );
    }

    setsockopt( sockfd, IPPROTO_IP, IP_HDRINCL, &optval, sizeof(int) );

    icmp->type               = ICMP_ECHO;
    icmp->code               = 0;
    icmp->un.echo.id         = 0;
    icmp->un.echo.sequence   = 0;
    icmp->checksum           = 0;
    icmp->checksum           = ::in_cksum((unsigned short *)icmp, sizeof(struct icmphdr));

    ip->check                = ::in_cksum((unsigned short *)ip, sizeof(struct iphdr));

    struct sockaddr_in connection;

    connection.sin_family = AF_INET;
    connection.sin_addr.s_addr = inet_addr( destAddress.c_str() );

    //Отправляем пакет

    sendto( sockfd, packet, ip->tot_len, 0, ( struct sockaddr * )&connection, sizeof( struct sockaddr ) );

    this->log( "Sent " + QString::number( sizeof( packet ) ) +
               " byte packet to " + QString::fromStdString( destAddress ), Qt::darkYellow );

// Ждём ответа

    int addrlen = sizeof( connection );

    if( recv( sockfd, buffer, sizeof(struct iphdr) + sizeof( struct icmphdr ), 0 )
   == -1 )

//    if ( recvfrom( sockfd,
//                   buffer,
//                   sizeof(struct iphdr) + sizeof(struct icmphdr),
//                   0,
//                   (struct sockaddr*)&connection,
//                   &addrlen )
//         == -1 )
    {
        this->log( QString( "No answer!"), Qt::red );
    }
    else
    {
        this->log( "Received" + QString::number( sizeof( buffer ) ) +
                   " byte reply from " + QString::fromStdString( destAddress ) , Qt::green );

        ip_reply = (struct iphdr*) buffer;

        this->log( "ID:" + QString::number( ntohs( ip_reply->id ) ) + "\tTTL:" + QString::number( ip_reply->ttl ),
                   Qt::green );
    }

    ::close( sockfd );

    delete ip;
    delete ip_reply;
    delete icmp;
    delete packet;
    delete buffer;
}

