#include "dialog.h"
#include "ui_dialog.h"

#include <QSocketNotifier>

#include <sys/socket.h>
#include <netinet/in.h>
#include <fcntl.h>
#include <errno.h>

namespace {
    const int defaultBufferSize = 1024;
}

Dialog::Dialog( QWidget* parent ) :
    QDialog( parent ),
    ui( new Ui::Dialog )
{
    ui->setupUi( this );

    connect( ui->exitButton, SIGNAL( clicked() ), this, SLOT( close() ) );

    int sock = socket( AF_INET, SOCK_RAW, IPPROTO_ICMP );

    if( sock == -1 )
    {
        this->ui->label1->setText( tr( "Socket Creation Failure." ) );

        this->ui->label2->setText( tr( "You need root access!" ) );

        return;
    }

    fcntl( sock, F_SETFL, fcntl( sock, F_GETFL, 0) | O_NONBLOCK ); // в режиме O_NONBLOCK

    notifier = new QSocketNotifier( sock, QSocketNotifier::Read );

    connect( notifier, SIGNAL( activated( int ) ), this, SLOT( onSockActivated( int ) ) );

    this->startTimer( 25 );
}

Dialog::~Dialog()
{
    delete ui;

    delete this->notifier;
}

void Dialog::timerEvent(QTimerEvent *)
{
    static int cnt = 0;

    QString message = QString::number( cnt++ );

    int sock = socket( AF_INET, SOCK_RAW, IPPROTO_ICMP );

    if( sock == -1 )
    {
        this->ui->label1->setText( tr( "Socket Creation Failure." ) );

        return;
    }
    this->ui->label1->setText( message );

    send( sock, message.toUtf8(), message.length(), 0 );
}

void Dialog::onSockActivated( int socket )
{
    unsigned char buff[ ::defaultBufferSize ];

    int length;

    while ( ( length = recv( socket, buff, 1024, 0 ) ) >= 0 )
    {
        this->ui->label2->setText( tr( "Received" ) + QString::number( length ) + tr( "bytes" ) );
    }
}
