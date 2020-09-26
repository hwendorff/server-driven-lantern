#include "lanternwidget.h"
#include "QMap"
#include "QDebug"
#include "QLayout"
#include "QGraphicsOpacityEffect"


LanternWidget::LanternWidget(QWidget *parent) : QWidget(parent)
{
    QPixmap lanternPixmap = QPixmap(":/pictures/lantern.png");
	lantern = new QLabel(this);
	lantern->setPixmap(lanternPixmap);
    QGraphicsOpacityEffect *effect = new QGraphicsOpacityEffect(lantern);
    effect->setOpacity(0.5);
    lantern->setGraphicsEffect(effect);
    lantern->setStyleSheet("background-color: rgb(255, 255, 255);");

	QVBoxLayout* vLayout = new QVBoxLayout;
	vLayout->addWidget(lantern);
	setLayout(vLayout);

	handlers = new commandHandlersMap;
	handlers->insert(CommandType::ON, std::bind(&LanternWidget::onHandler, this));
	handlers->insert(CommandType::OFF, std::bind(&LanternWidget::offHandler, this));
	handlers->insert(CommandType::COLOR, std::bind(&LanternWidget::changeColorHandler, this));
}

void LanternWidget::onHandler() {
    if (enabled == false) {
        enabled = true;
        lantern->graphicsEffect()->setEnabled(false);
    }
}

void LanternWidget::offHandler() {
    if (enabled == true) {
        enabled = false;
        lantern->graphicsEffect()->setEnabled(true);
        lantern->setStyleSheet("background-color: rgb(255, 255, 255);");
    }
}

void LanternWidget::changeColorHandler() {
	if (isLanternEnabled()) {
		if (this->command) {
			/* color goes as [R][G][B] */
			/* value offset	  0  1	2  */
			int R = 0 + this->command->value[0];
			int G = 0 + this->command->value[1];
			int B = 0 + this->command->value[2];
            QString styleSheetString = QString("background-color: rgb(%0, %1, %2);").arg(R).arg(G).arg(B);
            lantern->setStyleSheet(styleSheetString);
		}
	}
}

void LanternWidget::serverChangedHandler() {
    this->offHandler();
}

void LanternWidget::processCommand(CommandType command) {
	std::function<void()> handler = this->handlers->value(command);
	handler();
	free(this->command);
}
