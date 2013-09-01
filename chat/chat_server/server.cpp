#include "server.h"

#include <QStringList>
#include <QTcpServer>
#include <QUdpSocket>
#include <QTcpSocket>
#include <QRegExp>
#include <QDebug>

Server::Server( const QString& type,
                int port,
                QObject* parent ) :
    QObject( parent )
{
    if( type == "Tcp" )
    {
        this->type = QAbstractSocket::TcpSocket;

        QTcpServer* server = new QTcpServer( this );

        server->listen( QHostAddress::Any, port );

        this->serverObject = server;

        connect( server, SIGNAL( newConnection() ),
                 this, SLOT( onNewConnection() ) );
    }
    else if( type == "Udp" )
    {
        this->type = QAbstractSocket::UdpSocket;

        QUdpSocket* udpSocket = new QUdpSocket( this );

        udpSocket->bind( port, QUdpSocket::ShareAddress );

        connect( udpSocket, SIGNAL( readyRead() ), this, SLOT( onReadyRead() ) );

        this->serverObject = udpSocket;
    }
}

void Server::sendUserList()
{
    QStringList userList;

    foreach( const QString& user, this->clients.keys() )
    {
        userList << user;
    }

    foreach( QAbstractSocket* client, this->clients.values() )
    {
        client->write( QString( "/users:" + userList.join( "," ) + "\n" ).toUtf8() );
    }

    emit this->usersOnServerChanged( userList );
}

void Server::onDisconnected()
{
    QAbstractSocket* client = static_cast< QAbstractSocket* >( this->sender() );

    this->clients.remove( this->clients.key( client ) );

    sendUserList();
}

void Server::onReadyRead()
{  
    QAbstractSocket* client = static_cast< QAbstractSocket* >( this->sender() );

    while( client->canReadLine() )
    {
        QString line = QString::fromUtf8( client->readLine() ).trimmed();

        QRegExp meRegex( "^/me:(.*)$" );

        if( meRegex.indexIn( line ) != -1 )
        {
            QString user = meRegex.cap( 1 );

            this->clients[ user ] = client;

            sendUserList();
        }
        else if( this->clients.values().contains( client ) )
        {
            QString message = line;

            QString user = this->clients.key( client );

            foreach( QAbstractSocket* otherClient, this->clients.values() )
            {
                otherClient->write( QString ( user + ":" + message + "\n" ).toUtf8() );
            }
        }
        else
        {
            emit this->warning( tr( "Got bad message from client:" ) + client->peerAddress().toString() + line );
        }
    }
}

void Server::onNewConnection()
{
    QAbstractSocket* client = 0;

    if( this->type == QAbstractSocket::TcpSocket )
    {
        QTcpServer* server = qobject_cast< QTcpServer* >( this->serverObject );

        if( server )
        {
            client = server->nextPendingConnection();
        }
    }
    else if( this->type == QAbstractSocket::UdpSocket )
    {
         client = new QUdpSocket( this->serverObject );
    }

    connect( client, SIGNAL( readyRead() ), this, SLOT( onReadyRead() ) );
    connect( client, SIGNAL( disconnected() ), this, SLOT( onDisconnected() ) );
}
