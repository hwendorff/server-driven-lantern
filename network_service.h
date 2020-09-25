#pragma once

#include <QtNetwork/QTcpSocket>
#include "lanternviewcontroller.h"

class NetworkService: public QObject {
	Q_OBJECT
private:
	LanternViewController* delegate;
	QTcpSocket* pTcpSocket;
public:
	NetworkService(const QString& strHost, int nPort, LanternViewController* delegate);
	~NetworkService();
private slots:
	void slotReadyRead();
	void slotError(QAbstractSocket::SocketError);
	void slotConnected();
};
