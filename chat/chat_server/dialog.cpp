#include "dialog.h"
#include "ui_dialog.h"

#include <QDebug>
#include <QErrorMessage>

Dialog::Dialog( QWidget* parent ) :
    QDialog( parent ),
    ui( new Ui::Dialog ),
    server( 0 )
{
    this->ui->setupUi( this );

    this->ui->typeBox->addItem( "Tcp" );
    //this->ui->typeBox->addItem( "Udp" );

    connect( this->ui->button, SIGNAL( toggled( bool ) ), this, SLOT( toggleServerState( bool ) ) );
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::onServerStopped()
{
    this->ui->button->toggle();

    this->ui->usersWidget->clear();

    qWarning( tr( "Server stopped" ).toLatin1() );
}

void Dialog::onUsersOnServerChanged( const QStringList& users )
{
    this->ui->usersWidget->clear();

    this->ui->usersWidget->addItems( users );
}

void Dialog::toggleServerState( bool toggle )
{
    if( toggle )
    {
        this->server = new Server( this->ui->typeBox->currentText(),
                                   this->ui->spinPort->value(),
                                   this );

        connect( this->server, SIGNAL( stopServer() ), this, SLOT( onServerStopped() ) );

        connect( this->server, SIGNAL( usersOnServerChanged( const QStringList& ) ),
                 this, SLOT( onUsersOnServerChanged( const QStringList& ) ) );
    }
    else
    {
        this->server->deleteLater();
    }

    this->toogleUiState( toggle );
}

void Dialog::toogleUiState( bool toggle )
{
    this->ui->button->setText( toggle ? tr( "Stop" ) : tr( "Start" ) );

    this->ui->typeBox->setEnabled( !toggle );

    this->ui->spinPort->setEnabled( !toggle );
}
