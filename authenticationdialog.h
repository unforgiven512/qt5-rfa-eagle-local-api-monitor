#ifndef AUTHENTICATIONDIALOG_H_
#define AUTHENTICATIONDIALOG_H_

#include "rfa-default-creds.h"

#include <QDialog>


namespace Ui {
class AuthenticationDialog;
}


class AuthenticationDialog: public QDialog {
	Q_OBJECT

public:
	explicit AuthenticationDialog(QWidget *parent = 0);
	~AuthenticationDialog();

private:
	Ui::AuthenticationDialog *ui;
};


#endif	/* !AUTHENTICATIONDIALOG_H_ */
