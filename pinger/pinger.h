#ifndef PINGER_H
#define PINGER_H

#include <QObject>
#include <QColor>

class Pinger : public QObject
{
    Q_OBJECT
public:
    explicit Pinger( QObject *parent );

    void execute( const std::string& destAddress , int interval );
    
signals:
    void log( const QString& msg, QColor color );

private:
    std::string srcAddress;
};

#endif // PINGER_H
