#include "serverdatadialog.h"
#include <QtWidgets>

ServerDataDialog::ServerDataDialog(QWidget* parent): QDialog(parent) {
	hostLabel = new QLabel("Server name:");
	portLabel = new QLabel("Server port:");

	hostLineEdit = new QLineEdit;
	portLineEdit = new QLineEdit;
	portLineEdit->setValidator(new QIntValidator(1, 65535, this));
}

ServerDataDialog::~ServerDataDialog() {

}
