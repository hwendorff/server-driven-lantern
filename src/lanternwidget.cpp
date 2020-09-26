#include "lanternwidget.h"
#include "QMap"
#include "QDebug"
#include "QLayout"


LanternWidget::LanternWidget(QWidget *parent) : QWidget(parent)
{
	QPixmap lanternPixmap = QPixmap(100, 100);
	lanternPixmap.fill(Qt::green);
	lantern = new QLabel(this);
	lantern->setPixmap(lanternPixmap);

	QVBoxLayout* vLayout = new QVBoxLayout;
	vLayout->addWidget(lantern);
	setLayout(vLayout);

	handlers = new commandHandlersMap;
	handlers->insert(CommandType::ON, std::bind(&LanternWidget::onHandler, this));
	handlers->insert(CommandType::OFF, std::bind(&LanternWidget::offHandler, this));
	handlers->insert(CommandType::COLOR, std::bind(&LanternWidget::changeColorHandler, this));
}

void LanternWidget::onHandler() {
    enabled = true;
}

void LanternWidget::offHandler() {
    enabled = false;
}

void LanternWidget::changeColorHandler() {
	if (isLanternEnabled()) {
		if (this->command) {
			/* color goes as [R][G][B] */
			/* value offset	  0  1	2  */
			int R = 0 + this->command->value[0];
			int G = 0 + this->command->value[1];
			int B = 0 + this->command->value[2];
			QColor newColor = QColor(R, G, B);
			changeLanternColor(newColor);
		}
	}
}

void LanternWidget::changeLanternColor(QColor newColor) {
	QPixmap current = *lantern->pixmap();

	current.fill(newColor);
	lantern->setPixmap(current);
}

void LanternWidget::processCommand(CommandType command) {
	std::function<void()> handler = this->handlers->value(command);
	handler();
	free(this->command);
}
