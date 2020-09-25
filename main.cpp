#include "lanternviewcontroller.h"

#include <QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	LanternViewController lanternVC("emb2.extcam.xyz", 9991);

	lanternVC.show();
	return a.exec();
}
