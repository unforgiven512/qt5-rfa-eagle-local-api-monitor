#include "rfa-default-creds.h"

#include "authenticationdialog.h"
#include "ui_authenticationdialog.h"



AuthenticationDialog::AuthenticationDialog(QWidget *parent): QDialog(parent), ui(new Ui::AuthenticationDialog) {
	ui->setupUi(this);
}

AuthenticationDialog::~AuthenticationDialog() {
	delete ui;
}
