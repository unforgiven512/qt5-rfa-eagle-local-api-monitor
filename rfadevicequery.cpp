#include <QtCore>
#include <QtWidgets>
#include <QtNetwork>
#include <QUrl>

#include "rfa-default-creds.h"

#include "rfadevicequery.h"
#include "ui_authenticationdialog.h"


const QString rfa_url = "http://10.4.23.76/";
const QString win_title = "Rainforest EAGLE Local API Device List (discovery)";

const int winsz_x = 800;
const int winsz_y = 600;

// HttpWindow::HttpWindow(QWidget *parent):
//		QDialog(parent),
//		statusLabel(new QLabel(tr("Please enter the URL of a file you want to download.\n\n"), this)),
//		urlLineEdit(new QLineEdit(defaultUrl)),
//		downloadButton(new QPushButton(tr("Download"))),
//		launchCheckBox(new QCheckBox("Launch file")),
//		defaultFileLineEdit(new QLineEdit(defaultFileName)),
//		downloadDirectoryLineEdit(new QLineEdit),
//		reply(Q_NULLPTR),
//		file(Q_NULLPTR),
//		httpRequestAborted(false) {
RFADeviceQuery::RFADeviceQuery(QWidget *parent): QDialog(parent), reply(0) {
	lineEdit = new QLineEdit(this);
	fetchButton = new QPushButton(tr("Get Devices"), this);
	treeWidget = new QTreeWidget(this);

	lineEdit->setText(rfa_url);

	connect(treeWidget, SIGNAL(itemActivated(QTreeWidgetItem*, int)), this, SLOT(itemActivated(QTreeWidgetItem*)));

	QStringList headerLabels;

	headerLabels << tr("HardwareAddress") << tr("Manufacturer") << tr("ModelId") << tr("Protocol") << tr("LastContact") << tr("ConnectionStatus") << tr("NetworkAddress");

	treeWidget->setHeaderLabels(headerLabels);
	treeWidget->header()->setSectionResizeMode(QHeaderView::ResizeToContents);

	connect(&qnam, &QNetworkAccessManager::authenticationRequired, this, &RFADeviceQuery::slotAuthRequired);
	connect(&qnam, SIGNAL(finished(QNetworkReply*)), this, SLOT(finished(QNetworkReply*)));
	connect(lineEdit, SIGNAL(returnPressed()), this, SLOT(fetch()));
	connect(fetchButton, SIGNAL(clicked()), this, SLOT(fetch()));

	QVBoxLayout *layout = new QVBoxLayout(this);
	QHBoxLayout *hboxLayout = new QHBoxLayout;

	hboxLayout->addWidget(lineEdit);
	hboxLayout->addWidget(fetchButton);

	layout->addLayout(hboxLayout);
	layout->addWidget(treeWidget);

	setWindowTitle(win_title);
	resize(winsz_x, winsz_y);
}


void RFADeviceQuery::get(const QUrl &url) {
	QNetworkRequest request(url);
	QByteArray reqData("<Command><Name>device_list</Name></Command>\n");

	if (reply) {
		reply->disconnect(this);
		reply->deleteLater();
	}

	request.setHeader(QNetworkRequest::ContentTypeHeader, "text/xml");

//	reply = qnam.get(request);
	reply = qnam.post(request, reqData);

	connect(reply, SIGNAL(readyRead()), this, SLOT(readyRead()));
	connect(reply, SIGNAL(metaDataChanged()), this, SLOT(metaDataChanged()));
	connect(reply, SIGNAL(error(QNetworkReply::NetworkError)), this, SLOT(error(QNetworkReply::NetworkError)));
}

void RFADeviceQuery::fetch() {
	lineEdit->setReadOnly(true);
	fetchButton->setEnabled(false);
	treeWidget->clear();

	xml.clear();

	QUrl url(lineEdit->text());
	get(url);
}

void RFADeviceQuery::metaDataChanged() {
	QUrl redirTarget;

	redirTarget = reply->attribute(QNetworkRequest::RedirectionTargetAttribute).toUrl();
	if (redirTarget.isValid()) {
		get(redirTarget);
	}
}


void RFADeviceQuery::readyRead() {
	int statusCode;

	statusCode = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();

	if ((statusCode >= 200) && (statusCode < 300)) {
		QByteArray data = reply->readAll();
		xml.addData(data);
		parseXml();
	}
}


void RFADeviceQuery::finished(QNetworkReply *reply) {
	Q_UNUSED(reply);

	lineEdit->setReadOnly(false);
	fetchButton->setEnabled(true);
}


void RFADeviceQuery::parseXml() {
	while (!xml.atEnd()) {
		xml.readNext();

		if (xml.isStartElement()) {
			currentTag = xml.name().toString();
		} else if (xml.isEndElement()) {
			if (xml.name() == "Device") {
				QTreeWidgetItem *item = new QTreeWidgetItem;
				item->setText(0, hardwareAddressString);
				item->setText(1, manufacturerString);
				item->setText(2, modelIdString);
				item->setText(3, protocolString);
				item->setText(4, lastContactString);
				item->setText(5, connectionStatusString);
				item->setText(6, networkAddressString);
				treeWidget->addTopLevelItem(item);
				hardwareAddressString.clear();
				manufacturerString.clear();
				modelIdString.clear();
				protocolString.clear();
				lastContactString.clear();
				connectionStatusString.clear();
				networkAddressString.clear();
			}
		} else if (xml.isCharacters() && !xml.isWhitespace()) {
			if (currentTag == "HardwareAddress") {
				hardwareAddressString += xml.text();
			} else if (currentTag == "Manufacturer") {
				manufacturerString += xml.text();
			} else if (currentTag == "ModelId") {
				modelIdString += xml.text();
			} else if (currentTag == "Protocol") {
				protocolString += xml.text();
			} else if (currentTag == "LastContact") {
				lastContactString += xml.text();
			} else if (currentTag == "ConnectionStatus") {
				connectionStatusString += xml.text();
			} else if (currentTag == "NetworkAddress") {
				networkAddressString += xml.text();
			}
		}
	}

	if (xml.error() && (xml.error() != QXmlStreamReader::PrematureEndOfDocumentError)) {
		qWarning() << "XML ERROR:" << xml.lineNumber() << ": " << xml.errorString();
	}
}

QString RFADeviceQuery::itemActivated(QTreeWidgetItem *item) {
	return (item->text(0));
}

void RFADeviceQuery::error(QNetworkReply::NetworkError) {
	qWarning("Error retreiving device list");
	reply->disconnect(this);
	reply->deleteLater();
	reply = 0;
}

void RFADeviceQuery::slotAuthRequired(QNetworkReply*, QAuthenticator *authenticator) {
	QDialog authDialog;
	Ui::AuthenticationDialog ui;

	ui.setupUi(&authDialog);
	authDialog.adjustSize();
	ui.siteDesc->setText(tr("%1 at %2").arg(authenticator->realm(), url.host()));

	/* prefill the dialog */
	ui.httpUser->setText(RFA_CREDS_USER);
	ui.httpPass->setText(RFA_CREDS_PASS);

	if (authDialog.exec() == QDialog::Accepted) {
		authenticator->setUser(ui.httpUser->text());
		authenticator->setPassword(ui.httpPass->text());
	}
}
