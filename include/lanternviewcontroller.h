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
    LanternWidget* lantern;
    NetworkService*  service;
    ServerDataDialog* serverDataDialog;
protected:
    void showEvent(QShowEvent *event) override;
public:
	void handleNetworkCommand(lanternCommand* command);
    LanternViewController(QWidget *parent = nullptr);
	~LanternViewController();
private slots:
	void slotChangeServer();
    void slotGetServerData(QPair<QString, int> serverData);
};
