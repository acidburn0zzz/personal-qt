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

#include "maindialog.h"
#include "ui_maindialog.h"

#include "constants.h"

#include <QTextCodec>
#include <QDesktopServices>
#include <QDir>
#include <QMessageBox>
#include <QStringList>

MainDialog::MainDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MainDialog)
{
    QTextCodec *utf8Codec = QTextCodec::codecForName("UTF-8");
    QTextCodec::setCodecForTr(utf8Codec);
    QTextCodec::setCodecForCStrings(utf8Codec);
    QTextCodec::setCodecForLocale(utf8Codec);

    QString appDataDir(QDesktopServices::storageLocation(QDesktopServices::DataLocation));

    if (!QDir(appDataDir).exists())
    {
        // It doesn't exist, we have to create it.
        if (!QDir().mkpath(appDataDir))
        {
            // Can't create directory, try to use application one (this may work in windows)
            appDataDir = QCoreApplication::applicationFilePath();
        }
    }

    qDebug() << QString("Application data will be stored in : %1").arg(appDataDir);

    // Open our database
    if (!dbManager.openDB())
    {
        qDebug() << "Error: can't create/open database.";
        QMessageBox::critical(this, tr("Matrícula-qt"),
                              tr("Error crític: No puc obrir la base de dades."
                              "Si us plau, posi's en contacte amb el seu distribuidor "
                              "per a obtenir ajuda"));
        this->close();
        qFatal("Can't create/open database file!");
    }

    ui->setupUi(this);

    ui->timeLabel->setText("");
    ui->warnLabel->setText("");

    ui->wellcomeLabel->setText("Si us plau, introdueix el teu codi");

    ui->code->setEchoMode(QLineEdit::Password);
    ui->code->installEventFilter(this);

    setWindowState(windowState() ^ Qt::WindowFullScreen);

    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(updateTime()));
    timer->start(1000);

    updateTime();

    ui->imageLabel->setPixmap(QPixmap(":/institut.png"));

    httpDaemon = new HttpDaemon(8080);
}

MainDialog::~MainDialog()
{
    delete ui;
    delete httpDaemon;
}

void MainDialog::updateTime()
{
    if (ui != NULL && ui->timeLabel != NULL)
    {
        QTime time = QTime::currentTime();
        QString myTime = QString().sprintf("%02d:%02d:%02d", time.hour(), time.minute(), time.second());
        ui->timeLabel->setText(myTime);

        QDate date = QDate::currentDate();
        QString myDate = QString("%1/%2/%3").arg(date.day()).arg(date.month()).arg(date.year());
        ui->dateLabel->setText(myDate);
    }
}

bool MainDialog::eventFilter(QObject *object, QEvent *event)
{
    if (object == ui->code && event->type() == QEvent::KeyPress)
    {
        QKeyEvent *keyEvent = static_cast<QKeyEvent *>(event);

        if (keyEvent->key() == Qt::Key_Return || keyEvent->key() == Qt::Key_Enter)
        {
            checkCode();
        }

        return false;
    }
    else
    {
        return QObject::eventFilter(object, event);
    }
}

void MainDialog::checkCode()
{
    QCryptographicHash hash(QCryptographicHash::Sha1);

    hash.addData(ui->code->text().toUtf8());

    QString hashValue = QString(hash.result().toHex());

    qDebug() << hashValue;

    ui->warnLabel->setText(tr("El codi no és correcte!"));
    ui->code->setText("");

}

void MainDialog::importCSV(QString fileName)
{
    qDebug() << "Importing all users from resultatsConsulta.csv";

    QSqlDatabase db = QSqlDatabase::database(DB_CONNECTION_NAME);

    QFile csvFile(fileName);

    if (csvFile.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QTextStream in(&csvFile);
        QSqlQuery qry(db);

        while (!in.atEnd())
        {
           QString line = in.readLine();

           if (!line.startsWith('#'))
           {
               qDebug() << line;

               QStringList data = line.split(";");

               qry.prepare("INSERT INTO Personal (NIF, Nom, Codi) VALUES (:nif, :nom, :codi)");

               qry.bindValue(":nom", data[1]);
               qry.bindValue(":nif", data[2]);




               /*
               QCryptographicHash hash(QCryptographicHash::Sha1);
               hash.addData(text);
               qry.bindValue(":codi", QString(hash.result().toHex());
               */


               if (!qry.exec())
               {
                   qDebug() << qry.lastError().text();
               }
           }
        }

        csvFile.close();
    }

    db.close();
}

