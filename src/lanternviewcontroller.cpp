#include "lanternviewcontroller.h"
#include "iostream"
#include "network_service.h"
#include "serverdatadialog.h"


LanternViewController::LanternViewController(QWidget *parent)
    : QWidget(parent)
{
    QPushButton *anotherServerButton = new QPushButton("&Another server");
    connect(anotherServerButton, SIGNAL(clicked()), SLOT(slotChangeServer()));

    lantern = new LanternWidget(this);
    service = nullptr;

    /* Layout */
    QVBoxLayout* vLayout = new QVBoxLayout;
    QLabel *windowLabel = new QLabel("<H1>Simple Lantern</H1>");
    windowLabel->setAlignment(Qt::AlignHCenter);
    vLayout->addWidget(windowLabel);

    vLayout->addWidget(lantern);
    vLayout->addWidget(anotherServerButton);
    setLayout(vLayout);
    this->setStyleSheet("background-color: rgb(255, 255, 255);");

    /* set timer at startup before dialog window shows */
    timeoutAtStartTimer = new QTimer(this);
    connect(timeoutAtStartTimer, SIGNAL(timeout()),
            this, SLOT(slotStartTimeoutExpired()));
    /* 1 sec after startup */
    timeoutAtStartTimer->start(1000);

    /* Construct dialog window */
    serverDataDialog = new ServerDataDialog(this);
    connect(serverDataDialog, SIGNAL(editingServerDataDone(QPair<QString, int>)),
            this, SLOT(slotGetServerData(QPair<QString, int>)));
}

LanternViewController::~LanternViewController()
{

}

void LanternViewController::handleNetworkCommand(lanternCommand *command) {
    CommandType type = command->type;
    lantern->command = std::move(command);
    lantern->processCommand(type);
}

void LanternViewController::slotChangeServer() {
    if (timeoutAtStartTimer->isActive())
        timeoutAtStartTimer->stop();
    this->serverDataDialog->show();
}

void LanternViewController::slotGetServerData(QPair<QString, int> serverData) {
    if (service) {
        delete service;
    }
    /* $0 - hostname, $1 - port, $2 - delegate */
    service = new NetworkService(serverData.first, serverData.second, this);
    lantern->serverChangedHandler();
}

void LanternViewController::slotStartTimeoutExpired() {
    this->serverDataDialog->show();
    timeoutAtStartTimer->stop();
}
