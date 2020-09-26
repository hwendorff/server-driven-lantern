#include "lanternviewcontroller.h"

#include <QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
    /*"emb2.extcam.xyz", 9991*/
    LanternViewController lanternVC;

	lanternVC.show();
	return a.exec();
}
