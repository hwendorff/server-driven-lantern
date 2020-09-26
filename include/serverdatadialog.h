#pragma once

#include <QtWidgets>

class LanternViewController;

/*  used to enter hostname and port of new server */
class ServerDataDialog: public QDialog {
	Q_OBJECT
private:
    LanternViewController *delegate;
	QLabel *hostLabel;
	QLabel *portLabel;
	QLineEdit *hostLineEdit;
	QLineEdit *portLineEdit;
    QPushButton *connectButton;
    QPushButton *quitButton;
    QDialogButtonBox *buttonsBox;
public:
    explicit ServerDataDialog(QWidget *parent = nullptr);
	~ServerDataDialog();
signals:
    void editingServerDataDone(QPair<QString, int> serverData);
private slots:
    void slotEnableConnectButton();
    void slotConnectToServer();
};
