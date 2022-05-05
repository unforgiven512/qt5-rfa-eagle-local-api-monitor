#ifndef RFADEVICEDETAILS_H_
#define RFADEVICEDETAILS_H_

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


class RFADeviceDetails: public QDialog {
	Q_OBJECT

public:
	RFADeviceDetails(QWidget *parent = nullptr);
	RFADeviceDetails(QWidget *parent = nullptr, QString rfa_devaddr = "");
	~RFADeviceDetails();

	QString rfa_hardware_address;

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
	void assembleRequest(const QString rfaDevAddr);
	void parseXml();
	void get(const QUrl &url);

	QXmlStreamReader xml;
	QXmlStreamWriter xmlreq;
#if 0
	QString reqdata;
#endif
	QByteArray xml_reqdata_ba;
	QBuffer xml_reqdata_buffer;
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


#endif	/* !RFADEVICEDETAILS_H_ */
