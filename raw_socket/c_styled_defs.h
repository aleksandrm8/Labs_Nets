#ifndef C_STYLED_DEFS_H
#define C_STYLED_DEFS_H

//                                      Протокол ICMP ( RFC 792)

// тип ICMP пакета
#define ICMP_ECHO_REPLY                 0
#define ICMP_UNREACHABLE            	3
#define ICMP_QUENCH                     4
#define ICMP_REDIRECT               	5
#define ICMP_ECHO                       8
#define ICMP_TIME                       11
#define ICMP_PARAMETER              	12
#define ICMP_TIMESTAMP              	13
#define ICMP_TIMESTAMP_REPLY            14
#define ICMP_INFORMATION                15
#define ICMP_INFORMATION_REPLY          16

// ICMP коды для ICMP типа ICMP_UNREACHABLE
#define ICMP_UNREACHABLE_NET			0
#define ICMP_UNREACHABLE_HOST			1
#define ICMP_UNREACHABLE_PROTOCOL		2
#define ICMP_UNREACHABLE_PORT			3
#define ICMP_UNREACHABLE_FRAGMENTATION	4
#define ICMP_UNREACHABLE_SOURCE         5
#define ICMP_UNREACHABLE_SIZE			8

// ICMP коды для ICMP типа ICMP_TIME
#define ICMP_TIME_TRANSIT               0
#define ICMP_TIME_FRAGMENT              1

// ICMP коды для ICMP типа ICMP_REDIRECT
#define ICMP_REDIRECT_NETWORK			0
#define ICMP_REDIRECT_HOST              1
#define ICMP_REDIRECT_SERVICE_NETWORK   2
#define ICMP_REDIRECT_SERVICE_HOST		3

struct icmp_header
{
    unsigned char   type;			// тип ICMP- пакета
    unsigned char   code;			// код ICMP- пакета
    unsigned short  crc ;			// контрольная сумма
    union
    {
        struct
        {
            unsigned char uc1;
            unsigned char uc2;
            unsigned char uc3;
            unsigned char uc4;
        } s_uc;

        struct
        {
            unsigned short us1;
            unsigned char us2;
        } s_us;

        unsigned long s_ul;
    } s_icmp;				// зависит от типа
};


//http://komsoft.ru/pma/gen_packet.htm

#endif // C_STYLED_DEFS_H
