#include "rfa-default-creds.h"

#include <QApplication>
#include <QDesktopWidget>
#include <QDir>

#include "mainwindow.h"
#include "rfadevicedetails.h"
#include "rfadevicelist.h"
#include "rfadevicequery.h"



int main(int argc, char *argv[]) {
	QApplication a(argc, argv);
//	MainWindow w;
//	w.show();

	RFADeviceList rfaDevListWin;
	const QRect availableSize = QApplication::desktop()->availableGeometry(&rfaDevListWin);
	rfaDevListWin.resize(availableSize.width() / 4, availableSize.height() / 5);
	rfaDevListWin.move((availableSize.width() - rfaDevListWin.width()) / 2, (availableSize.height() - rfaDevListWin.height()) / 2);

	rfaDevListWin.show();

	return (a.exec());
}
