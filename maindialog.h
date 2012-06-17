#ifndef MAINDIALOG_H
#define MAINDIALOG_H

#include <QDialog>
#include <QTime>
#include <QTimer>
#include <QDateTime>
#include <QPixmap>
#include <QCryptographicHash>
#include <QKeyEvent>

#include "httpdaemon.h"

namespace Ui {
    class MainDialog;
}

class MainDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit MainDialog(QWidget *parent = 0);
    ~MainDialog();

protected:
    bool eventFilter(QObject *object, QEvent *event);

    void checkCode(void);

private:
    Ui::MainDialog *ui;

    HttpDaemon *httpDaemon;

public slots:
    void updateTime();
};

#endif // MAINDIALOG_H
