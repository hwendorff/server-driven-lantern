#include <QtWidgets>
#include "serverdatadialog.h"
#include "network_service.h"

ServerDataDialog::ServerDataDialog(QWidget *parent): QDialog(parent) {
    delegate = static_cast<LanternViewController *>(parent);
    setWindowFlags(Qt::FramelessWindowHint | Qt::Dialog);

    hostLabel = new QLabel("Server name:");
	portLabel = new QLabel("Server port:");

	hostLineEdit = new QLineEdit;
	portLineEdit = new QLineEdit;
	portLineEdit->setValidator(new QIntValidator(1, 65535, this));

    connectButton =  new QPushButton("Connect");
    connectButton->setDefault(true);
    connectButton->setEnabled(false);

    quitButton = new QPushButton("Quit");

    buttonsBox = new QDialogButtonBox;
    buttonsBox->addButton(connectButton, QDialogButtonBox::ActionRole);
    buttonsBox->addButton(quitButton, QDialogButtonBox::RejectRole);

    connect(connectButton, SIGNAL(clicked()),
            this, SLOT(slotConnectToServer()));
    connect(quitButton, SIGNAL(clicked()),
            this, SLOT(close()));

    connect(hostLineEdit, SIGNAL(textChanged(QString)),
            this, SLOT(slotEnableConnectButton()));
    connect(portLineEdit, SIGNAL(textChanged(QString)),
            this, SLOT(slotEnableConnectButton()));

    QGridLayout *dialogWindowLayout = new QGridLayout;
    dialogWindowLayout->addWidget(hostLabel, 0, 0);
    dialogWindowLayout->addWidget(hostLineEdit, 0, 1);
    dialogWindowLayout->addWidget(portLabel, 1, 0);
    dialogWindowLayout->addWidget(portLineEdit, 1, 1);
    dialogWindowLayout->addWidget(buttonsBox, 2, 0, 1, 2);
    setLayout(dialogWindowLayout);
}

ServerDataDialog::~ServerDataDialog() {

}

void ServerDataDialog::slotEnableConnectButton() {
    bool enable(!hostLineEdit->text().isEmpty() && !portLineEdit->text().isEmpty());
    connectButton->setEnabled(enable);
}

void ServerDataDialog::slotConnectToServer() {
    QPair<QString, int> serverData = {
        hostLineEdit->text(),
        portLineEdit->text().toInt(),
    };
    emit editingServerDataDone(serverData);
    this->hide();
}
