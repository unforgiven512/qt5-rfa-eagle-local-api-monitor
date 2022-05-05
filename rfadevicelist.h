#ifndef RFADEVICELIST_H_
#define RFADEVICELIST_H_

#include "rfa-default-creds.h"

#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QWidget>
#include <QProgressDialog>
#include <QBuffer>
#include <QXmlStreamReader>
#include <QUrl>


QT_BEGIN_NAMESPACE
class QFile;
class QLabel;
class QLineEdit;
class QTreeWidget;
class QTreeWidgetItem;
class QPushButton;
class QSslError;
class QAuthenticator;
class QNetworkReply;
class QCheckBox;
QT_END_NAMESPACE


class RFADeviceList: public QDialog {
	Q_OBJECT

public:
	explicit RFADeviceList(QWidget *parent = nullptr);

signals:

public slots:
	void fetch();
	void finished(QNetworkReply *reply);
	void readyRead();
	void metaDataChanged();
	QString itemActivated(QTreeWidgetItem *item);
	void error(QNetworkReply::NetworkError);

private slots:
	void slotAuthRequired(QNetworkReply*, QAuthenticator*);

private:
	void parseXml();
	void get(const QUrl &url);

	QXmlStreamReader xml;
	QXmlStreamWriter xmlreq;
	QString currentTag;
	QString hardwareAddressString;
	QString manufacturerString;
	QString modelIdString;
	QString protocolString;
	QString lastContactString;
	QString connectionStatusString;
	QString networkAddressString;
	QUrl url;
	QNetworkAccessManager qnam;
	QNetworkReply *reply;

	QLineEdit *lineEdit;
	QTreeWidget *treeWidget;
	QPushButton *fetchButton;
};


#endif	/* !RFADEVICELIST_H_ */
