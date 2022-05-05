#ifndef MAINWINDOW_H_
#define MAINWINDOW_H_

#include "rfa-default-creds.h"

#include <QMainWindow>


namespace Ui {
class MainWindow;
}



class MainWindow: public QMainWindow {
	Q_OBJECT

public:
	explicit MainWindow(QWidget *parent = 0);
	~MainWindow();

private:
	Ui::MainWindow *ui;
};


#endif	/* !MAINWINDOW_H_ */
