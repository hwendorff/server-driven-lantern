#include "lanternviewcontroller.h"
#include "iostream"
#include  "network_service.h"

LanternViewController::LanternViewController(const QString& strHost, int nPort, QWidget *parent)
	: QWidget(parent)
{
	QPushButton* anotherServerButton = new QPushButton("&Another server");
	connect(anotherServerButton, SIGNAL(clicked()), SLOT(slotChangeServer()));

	lanternW = new LanternWidget(this);

    service = new NetworkService(strHost, nPort, this);
	/* Layout */
	QVBoxLayout* vLayout = new QVBoxLayout;
	vLayout->addWidget(new QLabel("<H1>Simple Lantern</H1>"));
	//QLayout::setAlignment(lanternW, Qt::AlignHCenter);
	vLayout->addWidget(lanternW);
	vLayout->addWidget(anotherServerButton);
	setLayout(vLayout);

	/* Construct dialog window */
	serverDataDialog = new QDialog(this);
}

LanternViewController::~LanternViewController()
{

}

void LanternViewController::handleNetworkCommand(lanternCommand* command) {
	CommandType type = command->type;
	lanternW->command = std::move(command);
	lanternW->processCommand(type);
}

void LanternViewController::slotChangeServer() {
	/*QPropertyAnimation *animation = new QPropertyAnimation(lantern, "background");
	animation->setDuration(2000);
    animation->setStartValue(QColor(0, 0, 0));
    animation->setEndValue(QColor(240, 240, 240));
    animation->start();*/
}
