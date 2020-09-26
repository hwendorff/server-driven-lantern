#include "lanternviewcontroller.h"
#include "iostream"
#include "network_service.h"
#include "serverdatadialog.h"


LanternViewController::LanternViewController(QWidget *parent)
    : QWidget(parent)
{
    QPushButton* anotherServerButton = new QPushButton("&Another server");
    connect(anotherServerButton, SIGNAL(clicked()), SLOT(slotChangeServer()));

    lantern = new LanternWidget(this);
    service = nullptr;

    /* Layout */
    QVBoxLayout* vLayout = new QVBoxLayout;
    vLayout->addWidget(new QLabel("<H1>Simple Lantern</H1>"));
    //QLayout::setAlignment(lanternW, Qt::AlignHCenter);
    vLayout->addWidget(lantern);
    vLayout->addWidget(anotherServerButton);
    setLayout(vLayout);

    /* Construct dialog window */
    serverDataDialog = new ServerDataDialog(this);
    //this->serverDataDialog->show();
    connect(serverDataDialog, SIGNAL(editingServerDataDone(QPair<QString, int>)),
            this, SLOT(slotGetServerData(QPair<QString, int>)));
}

LanternViewController::~LanternViewController()
{

}

void LanternViewController::handleNetworkCommand(lanternCommand* command) {
    CommandType type = command->type;
    lantern->command = std::move(command);
    lantern->processCommand(type);
}

void LanternViewController::slotChangeServer() {
    this->serverDataDialog->show();
    /*QPropertyAnimation *animation = new QPropertyAnimation(lantern, "background");
    animation->setDuration(2000);
    animation->setStartValue(QColor(0, 0, 0));
    animation->setEndValue(QColor(240, 240, 240));
    animation->start();*/
}

void LanternViewController::showEvent(QShowEvent *event) {
    QWidget::showEvent(event);
}

void LanternViewController::slotGetServerData(QPair<QString, int> serverData) {
    if (service) {
        delete service;
    }
    service = new NetworkService(serverData.first, serverData.second, this);
}
