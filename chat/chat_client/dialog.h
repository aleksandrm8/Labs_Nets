#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>

#include "client.h"

namespace Ui
{
    class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit Dialog( QWidget* parent = 0 );
    ~Dialog();

public slots:
    void logMessage( const QString& text, QColor color );

protected:
    void toogleUiState( bool toggle );

private slots:
    void onConnectToggled( bool toggled );   
    void onSendTriggered();
    void onConnectionSuccess();
    void onUsersOnServerChanged( const QStringList& users );
    void onConnectionClosed();
    
private:
    Ui::Dialog* ui;
    QPointer< Client > client;
};

#endif // DIALOG_H
