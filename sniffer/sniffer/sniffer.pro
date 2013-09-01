#Необходимо разработать программу для получения всех пакетов начиная с уровня
#IP-протокола, получаемых сетевым адаптером, используя RAW Socket.
#Программа должна выводить значения всех полей заголовков пакетов IP,
#ICMP, TCP, UDP на экран/в файл.
#P.S большую часть кода честно взял с http://www.binarytides.com/packet-sniffer-code-in-c-using-linux-sockets-bsd-part-2/

TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.c

