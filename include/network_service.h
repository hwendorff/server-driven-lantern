#pragma once

#include <QtNetwork/QTcpSocket>
#include "lanternviewcontroller.h"

/* wrapper on tcpsocket, parse server commands and
 * sends to delegate (viewcontroller) */
class NetworkService: public QObject {
	Q_OBJECT
private:
    LanternViewController *delegate;
    QTcpSocket *pTcpSocket;
    QString host;
    QTimer *reconnectTimer;
    int port;
    bool needToReconnect = false;
public:
    explicit NetworkService(QString strHost, int nPort, LanternViewController *delegate);
	~NetworkService();
private slots:
	void slotReadyRead();
	void slotError(QAbstractSocket::SocketError);
	void slotConnected();
    void slotDisconnected();
    void slotReconnectTimerExpired();
};
