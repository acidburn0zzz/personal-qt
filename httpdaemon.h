#ifndef HTTPDAEMON_H
#define HTTPDAEMON_H

#include <QTcpServer>
#include <QTcpSocket>
#include <QDateTime>
#include <QDebug>
#include <QStringList>

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
