#include "dialog.h"
#include "ui_dialog.h"
#include "pinger.h"

#include <QThread>

Dialog::Dialog( QWidget* parent ) :
    QDialog( parent ),
    ui( new Ui::Dialog ),
    thread(0)
{
    ui->setupUi( this );

    connect( this->ui->pingButton, SIGNAL( toggled( bool ) ), this, SLOT( setPingingEnabled( bool ) ) );
}

Dialog::~Dialog()
{
    this->setPingingEnabled( false );

    delete ui;
}

void Dialog::setPingingEnabled( bool enabled )
{
    if( enabled )
    {
        this->thread = new QThread( this );

        this->pinger = new Pinger(0);

        this->pinger->moveToThread( this->thread );

        connect( this->pinger, SIGNAL( log( const QString&, QColor ) ), this, SLOT( onLog( QString,QColor ) ) );

        this->thread->start();

        this->pinger->execute( this->ui->adressEdit->text().toStdString(), this->ui->intervalSpin->value() );
    }
    else
    {
        this->thread->quit();

        delete this->pinger;
    }
}

void Dialog::onLog( const QString& msg, QColor color )
{
    this->ui->listWidget->addItem( msg );

    this->ui->listWidget->item( this->ui->listWidget->count() - 1 )->setTextColor( color );

    this->repaint();
}
