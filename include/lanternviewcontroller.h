#pragma once

#include <QString>
#include <QDebug>
#include <QtWidgets>
#include <QtNetwork/QTcpSocket>
#include <QLabel>
#include "lanternwidget.h"
#include "lanterncommandprotocol.h"

class NetworkService;
class ServerDataDialog;


class LanternViewController : public QWidget
{
	Q_OBJECT
private:
    LanternWidget *lantern;
    NetworkService *service;
    ServerDataDialog *serverDataDialog;
    QTimer *timeoutAtStartTimer;
public:
    void handleNetworkCommand(lanternCommand *command);
    explicit LanternViewController(QWidget *parent = nullptr);
	~LanternViewController();
private slots:
	void slotChangeServer();
    void slotGetServerData(QPair<QString, int> serverData);
    void slotStartTimeoutExpired();
};
