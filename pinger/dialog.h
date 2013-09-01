#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QPointer>

class Pinger;

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit Dialog(QWidget *parent = 0);
    ~Dialog();

public slots:
    void setPingingEnabled( bool enabled );

    void onLog( const QString& msg, QColor color );
    
private:
    Ui::Dialog *ui;
    QThread* thread;
    QPointer< Pinger> pinger;
};

#endif // DIALOG_H
