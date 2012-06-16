#ifndef MAINDIALOG_H
#define MAINDIALOG_H

#include <QDialog>
#include <QTime>
#include <QTimer>
#include <QDateTime>
#include <QPixmap>

namespace Ui {
    class MainDialog;
}

class MainDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit MainDialog(QWidget *parent = 0);
    ~MainDialog();
    
private:
    Ui::MainDialog *ui;

public slots:
    void updateTime();
};

#endif // MAINDIALOG_H
