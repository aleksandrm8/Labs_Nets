#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>

#include "server.h"

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
    void onServerStopped();

private slots:
    void toggleServerState( bool toggle );
    void onUsersOnServerChanged( const QStringList& users );

protected:
    void toogleUiState( bool toggle );
    
private:
    Ui::Dialog* ui;
    Server* server;
};

#endif // DIALOG_H
