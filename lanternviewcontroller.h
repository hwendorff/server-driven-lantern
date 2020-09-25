#pragma once

#include <QString>
#include <QDebug>
#include <QtWidgets>
#include <QtNetwork/QTcpSocket>
#include <QLabel>
#include "lanternwidget.h"
#include "lanterncommandprotocol.h"

class NetworkService;
class LanternViewController : public QWidget
{
	Q_OBJECT
private:

	QDialog* serverDataDialog;
	LanternWidget* lanternW;
    NetworkService*  service;
public:
	void handleNetworkCommand(lanternCommand* command);
	LanternViewController(const QString& strHost, int nPort, QWidget *parent = nullptr);
	~LanternViewController();
private slots:
	void slotChangeServer();
};
