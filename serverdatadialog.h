#pragma once

#include <QDialog>
#include <QLabel>
#include <QLineEdit>

class ServerDataDialog: public QDialog {
	Q_OBJECT
private:
	QLabel *hostLabel;
	QLabel *portLabel;
	QLineEdit *hostLineEdit;
	QLineEdit *portLineEdit;
	QPushButton *editingDonePushButton;
public:
	ServerDataDialog(QWidget* parent = nullptr);
	~ServerDataDialog();
};
