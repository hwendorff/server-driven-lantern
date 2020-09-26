#include "network_service.h"
#include "iostream"
#include <QString>
#include <QDebug>
#include <QColor>
#include <QDataStream>
#include "lanterncommandprotocol.h"
#include "cstring"

NetworkService::NetworkService(QString strHost, int nPort, LanternViewController *delegate):
    delegate(delegate),
    host(strHost),
    port(nPort)
{
	pTcpSocket = new QTcpSocket(this);
    reconnectTimer = new QTimer(this);

	pTcpSocket->connectToHost(strHost, static_cast<uint16_t>(nPort));

    connect(reconnectTimer, SIGNAL(timeout()),
            this, SLOT(slotReconnectTimerExpired()));
    connect(pTcpSocket, SIGNAL(connected()),
            this, SLOT(slotConnected()));
    connect(pTcpSocket, SIGNAL(disconnected()),
            this, SLOT(slotDisconnected()));
    connect(pTcpSocket, SIGNAL(readyRead()),
            this, SLOT(slotReadyRead()));
    connect(pTcpSocket, SIGNAL(error(QAbstractSocket::SocketError)),
            this, SLOT(slotError(QAbstractSocket::SocketError)));
}

NetworkService::~NetworkService() {
    this->pTcpSocket->disconnectFromHost();
    qDebug() << "Network service turned off";
}
void NetworkService::slotReadyRead() {
	QDataStream in(pTcpSocket);
    in.setVersion(QDataStream::Qt_5_4);
	char buf[1024] = {0};
	int data_size = in.readRawData(buf, 1024);
	/* minimal length of command is 3 (1 for type, 2 for length) */
	if (data_size >= 3) {
		CommandType command_type = CommandType(buf[0]);
		uint16_t command_length = static_cast<uint16_t>(buf[1] << 8 | buf[2]);
		if (data_size == command_length + 3) {
			/* command is good */
            lanternCommand *command = new lanternCommand(command_type, command_length);
			std::memcpy(command->value, &buf[3], command_length);
			delegate->handleNetworkCommand(command);
		} else {
			qDebug() << "Error: Incorrect value in command packet";
			return;
		}
	} else {
		qDebug() << "Error: Incorrect command packet";
	}
}

void NetworkService::slotError(QAbstractSocket::SocketError err) {
	QString strError = "Error: " + (err == QAbstractSocket::HostNotFoundError ? "Host not found." :
						err == QAbstractSocket::RemoteHostClosedError ?
                        "Remote host closed." :
						err == QAbstractSocket::ConnectionRefusedError ?
						"Connection refused." :
						QString(pTcpSocket->errorString()));
    if (err == QAbstractSocket::RemoteHostClosedError)
        this->needToReconnect = true;
	qDebug() << strError;
    this->pTcpSocket->disconnectFromHost();
}

void NetworkService::slotConnected() {
	qDebug() << "Received the connected() signal";
}

void NetworkService::slotDisconnected() {
    qDebug() << "Disconnected from server";
    if (this->needToReconnect) {
        reconnectTimer->start(3000);
    }
}

void NetworkService::slotReconnectTimerExpired() {
    if (this->needToReconnect) {
        if (pTcpSocket) {
            reconnectTimer->stop();
            needToReconnect = false;
            delete pTcpSocket;
            pTcpSocket = new QTcpSocket(this);
            qDebug() << "Try to connect again";
            pTcpSocket->connectToHost(host, static_cast<uint16_t>(port));

            connect(pTcpSocket, SIGNAL(connected()),
                    this, SLOT(slotConnected()));
            connect(pTcpSocket, SIGNAL(disconnected()),
                    this, SLOT(slotDisconnected()));
            connect(pTcpSocket, SIGNAL(readyRead()),
                    this, SLOT(slotReadyRead()));
            connect(pTcpSocket, SIGNAL(error(QAbstractSocket::SocketError)),
                    this, SLOT(slotError(QAbstractSocket::SocketError)));
        }
    }
}
