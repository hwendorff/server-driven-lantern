#pragma once

#include <QWidget>
#include <QLabel>
#include "lanterncommandprotocol.h"

/* forward declaration */
class LanternWidget;

using commandHandlersMap = QMap<CommandType, std::function<void()>>;

class LanternWidget : public QWidget
{
	Q_OBJECT
private:
	bool enabled = false;
	QLabel* lantern;
	void onHandler();
	void offHandler();
	void changeColorHandler();
	commandHandlersMap* handlers;
public:
	void changeLanternColor(QColor newColor);
public:
	lanternCommand* command;
	explicit LanternWidget(QWidget *parent = nullptr);
	void processCommand(CommandType);
	bool isLanternEnabled() {
		return enabled;
	}
};

