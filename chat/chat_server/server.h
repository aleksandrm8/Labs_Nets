#ifndef SERVER_H
#define SERVER_H

#include <QObject>
#include <QAbstractSocket>
#include <QHash>

class Server : public QObject
{
    Q_OBJECT
public:
    explicit Server( const QString& type, int port, QObject* parent = 0 );

signals:
    void stopServer();
    void warning( const QString& );
    void usersOnServerChanged( const QStringList& );

private slots:
    void onDisconnected();
    void onReadyRead();
    void onNewConnection();

protected:
    void sendUserList();

private:
    QObject* serverObject;
    QHash< QString, QAbstractSocket* > clients;
    QAbstractSocket::SocketType type;
};

#endif // SERVER_H
