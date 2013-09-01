#ifndef CONNECTION_H
#define CONNECTION_H

#include <QObject>
#include <QAbstractSocket>
#include <QColor>
#include <QPointer>


class Client : public QObject
{
    Q_OBJECT

public:
    explicit Client( const QString& m_nickname, QObject* parent = 0 );

    QString nickname() const;

    bool sendMessage( const QString& text );

public slots:
    void createTcpSocket();
    void createUdpSocket();
    virtual void destroySocket();
    virtual void connectSocketToHost( const QString& address, quint16 port );

signals:
    void message( const QString& text, QColor color );
    void connectionSuccess();
    void connectionClosed();
    void usersOnServerChanged( const QStringList& );

protected:
    virtual void initSocket();

private slots:
    void onSocketReadyRead();
    void onSocketConnected();
    void onSocketDisconnected();
    void onSocketError( QAbstractSocket::SocketError error );

private:
    QPointer< QAbstractSocket > socket;
    quint16 blockSize;
    QString m_nickname;
};

#endif // CONNECTION_H
