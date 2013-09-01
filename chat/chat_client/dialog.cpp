#include "dialog.h"
#include "ui_dialog.h"

#include <QDebug>
#include <QTime>
#include <QInputDialog>

Dialog::Dialog( QWidget* parent ) :
    QDialog( parent ),
    ui( new Ui::Dialog ),
    client( new Client( QInputDialog::getText( this,
                                               tr( "Nickname Input" ),
                                               tr( "Enter Nickname"),
                                               QLineEdit::Normal ) ) )
{
    this->ui->setupUi(this);

    this->setWindowTitle( tr( "Chat: ") + this->client->nickname() );

    this->toogleUiState( false );

    this->ui->typeBox->addItem( "Tcp" );
    //this->ui->typeBox->addItem( "Udp" );

    connect( this->ui->connectButton, SIGNAL( toggled( bool ) ),
             this, SLOT( onConnectToggled( bool ) ) );

    connect( this->ui->sendButton, SIGNAL( clicked() ),
             this, SLOT( onSendTriggered() ) );

    connect( this->client, SIGNAL( connectionSuccess() ),
             this, SLOT( onConnectionSuccess() ) );

    connect( this->client, SIGNAL( message( const QString&, QColor ) ),
             this, SLOT( logMessage( const QString&, QColor ) ) );

    connect( this->client, SIGNAL( usersOnServerChanged( const QStringList& ) ),
             this, SLOT( onUsersOnServerChanged( const QStringList& ) ) );

    connect( this->client, SIGNAL( connectionClosed() ),
             this, SLOT( onConnectionClosed() ) );
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::onConnectToggled( bool toggled )
{
    if( toggled )
    {
        this->ui->connectButton->setText( tr( "Connecting" ) );

        const QString& type = this->ui->typeBox->currentText();

        QString message = tr( "Connecting to ") + this->ui->hostEdit->text() +
                          tr(" : ") +  QString::number( this->ui->spinPort->value() ) +
                          tr(" with ") + type;

        this->logMessage( message, Qt::darkYellow );

        if( type == "Tcp" )
        {
            this->client->createTcpSocket();
        }
        else if( type == "Udp" )
        {
            this->client->createUdpSocket();
        }
        else
        {
            this->logMessage( tr( "Error: " ) +
                              tr( "cant resolve socket type!" ), Qt::darkRed );

            this->ui->connectButton->toggle();

            return;
        }

        this->client->connectSocketToHost( this->ui->hostEdit->text(),
                                           this->ui->spinPort->value() );

        this->toogleUiState( true );
    }
    else
    {
        this->ui->connectButton->setText( tr( "Connect" ) );

        this->client->destroySocket();

        this->toogleUiState( false );
    }
}

void Dialog::onSendTriggered()
{
    const QString& message = this->ui->messageEdit->toPlainText();

    if ( message.isEmpty() )
    {
        return;
    }

    if( this->client->sendMessage( message ) )
    {
        this->ui->messageEdit->clear();
    }
    else
    {
        this->logMessage( tr("Error delivering: ") + message, Qt::darkRed );
    }
}

void Dialog::onConnectionSuccess()
{
    this->ui->connectButton->setText( tr( "Disconnect" ) );
}

void Dialog::onUsersOnServerChanged( const QStringList& users )
{
    this->ui->usersWidget->clear();

    this->ui->usersWidget->addItems( users );
}

void Dialog::onConnectionClosed()
{
    this->ui->connectButton->setChecked( false );

        this->ui->usersWidget->clear();
}

void Dialog::toogleUiState( bool toggle )
{
    this->ui->sendButton->setEnabled( toggle );

    this->ui->typeBox->setEnabled( !toggle );

    this->ui->hostEdit->setEnabled( !toggle );

    this->ui->spinPort->setEnabled( !toggle );
}

void Dialog::logMessage( const QString& text, QColor color )
{
    int i = this->ui->logWidget->count();

    this->ui->logWidget->insertItem( i, QTime::currentTime().toString() + " " + text );

    this->ui->logWidget->item( i )->setTextColor( color );

    this->ui->logWidget->scrollToBottom();
}
