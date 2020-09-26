#include "lanternviewcontroller.h"

#include <QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
    /*"emb2.extcam.xyz", 9991*/
    LanternViewController lanternVC;
    lanternVC.show();
    /* get screen center and move window to it */
    QScreen *thisScreen = QGuiApplication::screens().first();
    QPoint screenCenter = thisScreen->geometry().center();
    lanternVC.move(screenCenter -
                   QPoint(lanternVC.width() / 2,
                          lanternVC.height() / 2));
    lanternVC.setFixedSize(lanternVC.size());
	return a.exec();
}
