#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>

namespace Ui {
class Dialog;
}

class QSocketNotifier;

class Dialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit Dialog( QWidget* parent = 0 );

    ~Dialog();

    void timerEvent( QTimerEvent* );

public slots:
    void onSockActivated( int socket );
    
private:
    Ui::Dialog* ui;

    QSocketNotifier* notifier;
};

#endif // DIALOG_H
