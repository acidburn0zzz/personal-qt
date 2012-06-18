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

#ifndef HTTPDAEMON_H
#define HTTPDAEMON_H

#include <QTcpServer>
#include <QTcpSocket>
#include <QDateTime>
#include <QDebug>
#include <QStringList>
#include <QSqlDatabase>
#include <QSqlQuery>

class HttpDaemon : public QTcpServer
{
    Q_OBJECT
public:
    explicit HttpDaemon(int port, QObject *parent = 0);
    
    void incomingConnection(int socket);

    inline void pause() { disabled = true; }
    inline void resume() { disabled = false; }
signals:
    
public slots:
    void readClient();
    void discardClient();

private:
    bool disabled;
};

#endif // HTTPDAEMON_H
