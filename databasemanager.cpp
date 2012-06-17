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

#include "databasemanager.h"
#include "constants.h"

DatabaseManager::DatabaseManager(QObject *parent) :
    QObject(parent)
{
}

DatabaseManager::~DatabaseManager()
{
    closeDB();
}

bool DatabaseManager::openDB(QString filePath)
{
    if (!QSqlDatabase::contains())
    {
        // Find QSLite driver
        QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE", DB_CONNECTION_NAME);

        if (filePath.isEmpty())
        {
            // Set database file name and path
            filePath = QDesktopServices::storageLocation(QDesktopServices::DataLocation);

            if (!QDir(filePath).exists())
            {
                // It doesn't exist, we have to create it.
                if (!QDir().mkpath(filePath))
                {
                    // Can't create directory, try to use application one (this may work in windows)
                    filePath = QCoreApplication::applicationFilePath();
                }
            }

            filePath.append(QDir::separator()).append("personal-qt.sqlite3");
        }

        filePath = QDir::toNativeSeparators(filePath);
        db.setDatabaseName(filePath);

        qDebug() << QString("Database file : %1").arg(filePath);

        QFile dbFile(db.databaseName());

        if (!dbFile.exists() || dbFile.size() <= 0)
        {
            qDebug() << "database does not exist or is corrputed. I'll try to create it.";

            if (!createDB())
            {
                qDebug() << "ERROR: Can't create a new database!";
                return false;
            }
        }
        else
        {
            qDebug() << "OK, database already exists.";
        }

        // Open databasee

        if (!db.open())
        {
            qDebug() << "ERROR: Can't open database!";
            qDebug() << db.lastError().text();
            return false;
        }
    }

    return true;
}

bool DatabaseManager::createDB()
{
    QSqlDatabase db = QSqlDatabase::database(DB_CONNECTION_NAME);

    // Db does not exist, or is corrupted. Open a new one and fill it.
    if (!db.open())
    {
        qDebug() << db.lastError().text();
        return false;
    }

    QFile sqlFile(":/personal-qt.sql");

    if (sqlFile.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QString sql = "";
        QTextStream in(&sqlFile);
        QSqlQuery qry(db);

        // qry.prepare(in.readAll());

        while (!in.atEnd())
        {
           QString line = in.readLine();

           if (line.startsWith('#'))
           {
               qDebug() << line;
           }
           else
           {
               sql += line;

               if (line.contains(';'))
               {
                   qDebug() << sql;

                   if (!qry.exec(sql))
                   {
                       qDebug() << qry.lastError().text();
                       sqlFile.close();
                       db.close();
                       return false;
                   }

                   sql = "";
               }
           }
        }

        sqlFile.close();
        db.close();

        return true;
    }
    else
    {
        db.close();
        return false;
    }
}

void DatabaseManager::closeDB()
{
    qDebug() << "Closing database";
    QSqlDatabase::database().close();
    QString connectionName = QSqlDatabase::database().connectionName();
    QSqlDatabase::removeDatabase(connectionName);
    qDebug() << "Database closed";
}

