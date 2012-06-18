/*
    Personal-qt
    Copyright (C) 2012 Karasu

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

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
#include "databasemanager.h"

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

    DatabaseManager dbManager;

private:
    Ui::MainDialog *ui;

    HttpDaemon *httpDaemon;

public slots:
    void updateTime();
    void importCSV(QString fileName = "resultatsConsulta.csv");
};

#endif // MAINDIALOG_H
