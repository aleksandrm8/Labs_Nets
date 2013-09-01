#include "client.h"

#include <QTcpSocket>
#include <QUdpSocket>
#include <QRegExp>
#include <QDebug>

Client::Client( const QString& nickname , QObject* parent ) :
    QObject( parent ),
    socket( 0 ),
    blockSize( 0 ),
    m_nickname( nickname != QString() ? nickname : "default" )
{}

QString Client::nickname() const
{
    return m_nickname;
}

void Client::createTcpSocket()
{
    if( this->socket )
    {
        this->destroySocket();
    }

    this->socket = new QTcpSocket( this );

    this->initSocket();
}

void Client::createUdpSocket()
{
    if( this->socket )
    {
        this->destroySocket();
    }

    this->socket = new QUdpSocket( this );

    this->initSocket();
}

void Client::destroySocket()
{
    if( !this->socket )
    {
        return;
    }

    this->socket->disconnectFromHost();
}

void Client::connectSocketToHost( const QString& address, quint16 port )
{
    this->socket->connectToHost( address, port );
}

bool Client::sendMessage( const QString& text )
{
    if( !socket->isWritable() )
    {
        return false;
    }

    socket->write( QString( text + "\n").toUtf8() );

    return true;
}

void Client::initSocket()
{
    connect( this->socket, SIGNAL( readyRead() ),
             this, SLOT( onSocketReadyRead() ) );

    connect( this->socket, SIGNAL( connected() ),
             this, SLOT( onSocketConnected() ) );

    connect( this->socket, SIGNAL( disconnected() ),
             this, SLOT( onSocketDisconnected()));

    connect( this->socket, SIGNAL( error( QAbstractSocket::SocketError ) ),
             this, SLOT( onSocketError( QAbstractSocket::SocketError ) ) );
}

void Client::onSocketReadyRead()
{
    while( this->socket->canReadLine() )
    {
        QString line = QString::fromUtf8( socket->readLine() ).trimmed();

        qDebug()<<line;

        QRegExp messageRegex( "^([^:]+):(.*)$" );

        QRegExp usersRegex( "^/users:(.*)$" );

        if( usersRegex.indexIn( line ) != -1 )
        {         
            emit this->usersOnServerChanged( usersRegex.cap( 1 ).split(",") );
        }
        else if( messageRegex.indexIn(line) != -1 )
        {
            emit this->message( messageRegex.cap( 1 ) + tr( ": " )  + messageRegex.cap( 2 ), Qt::black );
        }
    }
}

void Client::onSocketConnected()
{
    emit this->connectionSuccess();
    emit this->message( "Success!", Qt::darkGreen );

    socket->write( QString( "/me:" + this->m_nickname + "\n" ).toUtf8() );
}

void Client::onSocketDisconnected()
{
   emit this->connectionClosed();
   emit this->message( "Conection closed.", Qt::darkYellow );
}

void Client::onSocketError( QAbstractSocket::SocketError error )
{
    if( error != QAbstractSocket::RemoteHostClosedError )
    {
        emit this->message( tr( "Error: ") + this->socket->errorString(), Qt::darkRed );

        emit this->connectionClosed();
    }
}
