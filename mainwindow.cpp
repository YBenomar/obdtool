#include "mainwindow.h"
#include <QSettings>
#include <QDeclarativeItem>
#include "gaugeitem.h"
#include <QDeclarativeContext>

MainWindow::MainWindow() : QMainWindow()
{

/*Request: "0601" "1"
Response: "7E8 10 1C 46 01 81 0E 0A CB 7E8 21 06 54 0E D8 01 87 10 7E8 22 00 9D 00 00 01 2C 01 7E8 23 88 10 00 84 00 00 02 7E8 24 58 00 00 00 00 00 00 "
Request: "0602" "2"
Response: "7E8 10 25 46 02 01 0A 0E 68 7E8 21 00 00 FF FF 02 81 0E 7E8 22 03 59 00 DC 0B B8 02 7E8 23 85 B1 F8 AA C5 68 00 7E8 24 00 02 86 10 03 92 00 7E8 25 00 17 70 00 00 00 00 "
Request: "0605" "5"
Response: "7E8 10 1C 46 05 81 0E 0A E5 7E8 21 06 54 0E D8 05 87 10 7E8 22 00 6B 00 00 01 2C 05 7E8 23 88 10 00 5D 00 00 02 7E8 24 58 00 00 00 00 00 00 "
Request: "0606" "6"
Response: "7E8 10 25 46 06 01 0A 0E 68 7E8 21 00 00 FF FF 06 81 0E 7E8 22 03 46 00 DC 0B B8 06 7E8 23 85 B1 F9 40 C5 68 00 7E8 24 00 06 86 10 03 3A 00 7E8 25 00 17 70 00 00 00 00 "
Request: "0621" "33"
Response: "7E8 10 0A 46 21 80 20 00 34 7E8 21 00 00 00 9E 00 00 00 "
Request: "0622" "34"
Response: "7E8 10 0A 46 22 80 20 00 19 7E8 21 00 00 00 B8 00 00 00 "
Request: "0633" "51"
Response: "7E8 10 0A 46 33 82 05 49 6A 7E8 21 0F 5E FF FF 00 00 00 "
Request: "0635" "53"
Response: "7E8 10 13 46 35 80 1C 00 18 7E8 21 00 00 06 C4 35 81 1C 7E8 22 00 1D 00 00 03 06 00 "
Request: "0636" "54"
Response: "7E8 10 13 46 36 80 1C 00 1A 7E8 21 00 00 06 C4 36 81 1C 7E8 22 00 1E 00 00 03 06 00 "
Request: "063A" "58"
Response: "7E8 10 1C 46 3A 80 FE E0 DE 7E8 21 E0 DE 7F FF 3A 81 FE 7E8 22 00 00 00 00 00 00 3A 7E8 23 82 FE E0 DE 80 00 E0 7E8 24 DE 00 00 00 00 00 00 "
Request: "063C" "60"
Response: "7E8 10 1C 46 3C 81 FE 00 00 7E8 21 00 00 00 00 3C 82 FE 7E8 22 00 00 00 00 00 00 3C 7E8 23 83 03 00 00 00 00 00 7E8 24 00 00 00 00 00 00 00 "
Request: "063D" "61"
Response: "7E8 10 1C 46 3D 80 A9 00 00 7E8 21 00 00 00 00 3D 81 FE 7E8 22 FB AD F5 4D 7F FF 3D 7E8 23 82 FE 00 00 00 00 00 7E8 24 00 00 00 00 00 00 00 "
Request: "06A1" "161"
Response: "7E8 10 2E 46 A1 80 30 00 00 7E8 21 00 00 51 E9 A1 81 30 7E8 22 00 00 00 00 02 DD A1 7E8 23 82 30 00 DA 00 00 51 7E8 24 E9 A1 83 30 00 00 00 7E8 25 00 02 DD A1 84 16 12 7E8 26 CC 00 00 21 2B 00 00 "
Request: "06A2" "162"
Response: "7E8 10 25 46 A2 0B 24 00 00 7E8 21 00 00 FF FF A2 0C 24 7E8 22 00 00 00 00 FF FF A2 7E8 23 80 30 00 00 00 00 51 7E8 24 E9 A2 81 30 00 00 00 7E8 25 00 02 DD 00 00 00 00 "
Request: "06A3" "163"
Response: "7E8 10 25 46 A3 0B 24 00 00 7E8 21 00 00 FF FF A3 0C 24 7E8 22 00 00 00 00 FF FF A3 7E8 23 80 30 00 00 00 00 51 7E8 24 E9 A3 81 30 00 00 00 7E8 25 00 02 DD 00 00 00 00 "
Request: "06A4" "164"
Response: "7E8 10 25 46 A4 0B 24 00 00 7E8 21 00 00 FF FF A4 0C 24 7E8 22 00 00 00 00 FF FF A4 7E8 23 80 30 00 00 00 00 51 7E8 24 E9 A4 81 30 00 00 00 7E8 25 00 02 DD 00 00 00 00 "
Request: "06A5" "165"
Response: "7E8 10 25 46 A5 0B 24 00 00 7E8 21 00 00 FF FF A5 0C 24 7E8 22 00 00 00 00 FF FF A5 7E8 23 80 30 00 00 00 00 51 7E8 24 E9 A5 81 30 00 00 00 7E8 25 00 02 DD 00 00 00 00 "
Request: "06A6" "166"
Response: "7E8 10 25 46 A6 0B 24 00 00 7E8 21 00 00 FF FF A6 0C 24 7E8 22 00 00 00 00 FF FF A6 7E8 23 80 30 00 00 00 00 51 7E8 24 E9 A6 81 30 00 00 00 7E8 25 00 02 DD 00 00 00 00 "
Request: "06A7" "167"
Response: "7E8 10 25 46 A7 0B 24 00 00 7E8 21 00 00 FF FF A7 0C 24 7E8 22 00 00 00 00 FF FF A7 7E8 23 80 30 00 00 00 00 51 7E8 24 E9 A7 81 30 00 00 00 7E8 25 00 02 DD 00 00 00 00 "
*/
/*QString qml = "import Qt 4.7\nimport GaugeImage 0.1\nRectangle {x:0\ny:0\nwidth: 1280\nheight: 800\ncolor: \"black\"\n";
qml += "GaugeImage {\nx:0\ny:0\nwidth:200\nheight:200\nminimum:-40\nmaximum:200\nnumLabels:3\nstartAngle:45\nendAngle:270\n";
qml += "Behavior on m_value {  PropertyAnimation { properties: \"m_value\"; duration: (propertyMap[\"0105_DURATION\"] ? propertyMap[\"0105_DURATION\"] : 500) } }\n";
qml += "m_value: (propertyMap[\"0105\"] ? propertyMap[\"0105\"] : 0)\n}\n";
qml += "GaugeImage {\nx:425\ny:0\nwidth:250\nheight:250\nminimum:0\nmaximum:655\nnumLabels:3\nstartAngle:90\nendAngle:270\n";
qml += "Behavior on m_value {  PropertyAnimation { properties: \"m_value\"; duration: (propertyMap[\"0110_DURATION\"] ? propertyMap[\"0110_DURATION\"] : 500) } }\n";
qml += "m_value: (propertyMap[\"0110\"] ? propertyMap[\"0110\"] : 0) * 10\n}\n";
qml += "GaugeImage {\nx:0\ny:150\nwidth:550\nheight:550\nminimum: 0\nmaximum: 7000\nnumLabels: 7\nstartAngle: 45\nendAngle: 315\n";
qml += "Behavior on m_value {  PropertyAnimation { properties: \"m_value\"; duration: (propertyMap[\"010C_DURATION\"] ? propertyMap[\"010C_DURATION\"] : 500) } }\n";
qml += "m_value: (propertyMap[\"010C\"] ? propertyMap[\"010C\"] : 0)\n}\n";
qml += "GaugeImage {\nx: 550\ny: 150\nwidth:550\nheight: 550\nminimum:0\nmaximum: 140\nnumLabels: 7\nstartAngle: 45\nendAngle: 315\n";
qml += "Behavior on m_value { PropertyAnimation { properties: \"m_value\"; duration: (propertyMap[\"010D_DURATION\"] ? propertyMap[\"010D_DURATION\"] : 500) } }\n";
qml += "m_value: (propertyMap[\"010D\"] ? propertyMap[\"010D\"] : 0)\n}\n";
qml += "GaugeImage {\nx: 975\ny: 0\nwidth:250\nheight: 250\nminimum:0\nmaximum: 140\nnumLabels: 7\nstartAngle: 45\nendAngle: 315\n";
qml += "Behavior on m_value { PropertyAnimation { properties: \"m_value\"; duration: (propertyMap[\"010F_DURATION\"] ? propertyMap[\"010F_DURATION\"] : 500) } }\n";
qml += "m_value: (propertyMap[\"010F\"] ? propertyMap[\"010F\"] : 0)\n}\n}";
*/
	ui.setupUi(this);


	connect(ui.actionSettings,SIGNAL(triggered()),this,SLOT(menu_settingsClicked()));
	connect(ui.actionConnect,SIGNAL(triggered()),this,SLOT(menu_actionConnectClicked()));
	connect(ui.readReadinessPushButton,SIGNAL(clicked()),this,SLOT(uiReadReadinessButtonClicked()));
	connect(ui.rawConsoleLineEdit,SIGNAL(returnPressed()),this,SLOT(rawConsoleReturnPressed()));
	connect(ui.connectPushButton,SIGNAL(clicked()),this,SLOT(connectButtonClicked()));
	connect(ui.pidSelectNonePushButton,SIGNAL(clicked()),this,SLOT(uiPidSelectClearClicked()));
	connect(ui.pidSelectSavePushButton,SIGNAL(clicked()),this,SLOT(uiPidSelectSaveClicked()));
	connect(ui.connectPushButton,SIGNAL(clicked()),this,SLOT(menu_actionConnectClicked()));
	connect(ui.disconnectPushButton,SIGNAL(clicked()),this,SLOT(menu_actionDisconnectClicked()));


	obdThread = new ObdThread(this);
	QObject::connect(obdThread,SIGNAL(pidReply(QString,QString,int,double)),this,SLOT(obdPidReceived(QString,QString,int,double)));
	QObject::connect(obdThread,SIGNAL(troubleCodesReply(QList<QString>)),this,SLOT(obdTroubleCodes(QList<QString>)));
	QObject::connect(obdThread,SIGNAL(consoleMessage(QString)),this,SLOT(obdConsoleMessage(QString)));
	QObject::connect(obdThread,SIGNAL(connected(QString)),this,SLOT(obdConnected(QString)));
	QObject::connect(obdThread,SIGNAL(disconnected()),this,SLOT(obdDisconnected()));
	QObject::connect(obdThread,SIGNAL(singleShotReply(QByteArray,QByteArray)),this,SLOT(obdSingleShotReply(QByteArray,QByteArray)));
	QObject::connect(obdThread,SIGNAL(protocolReply(QString)),this,SLOT(obdProtocolFound(QString)));
	QObject::connect(obdThread,SIGNAL(supportedPidsReply(QList<QString>)),this,SLOT(obdSupportedPids(QList<QString>)));
	QObject::connect(obdThread,SIGNAL(liberror(ObdThread::ObdError)),this,SLOT(obdError(ObdThread::ObdError)));
	QObject::connect(obdThread,SIGNAL(supportedModesReply(QList<QString>)),this,SLOT(obdSupportedModes(QList<QString>)));
	QObject::connect(obdThread,SIGNAL(mfgStringReply(QString)),this,SLOT(obdMfgString(QString)));
	QObject::connect(obdThread,SIGNAL(voltageReply(double)),this,SLOT(obdVoltage(double)));
	QObject::connect(obdThread,SIGNAL(monitorTestReply(QList<QString>)),this,SLOT(obdMonitorStatus(QList<QString>)));
	QObject::connect(obdThread,SIGNAL(onBoardMonitoringReply(QList<unsigned char>,QList<unsigned char>,QList<QString>,QList<QString>,QList<QString>)),this,SLOT(obdOnBoardMonitoringReply(QList<unsigned char>,QList<unsigned char>,QList<QString>,QList<QString>,QList<QString>)));
	obdThread->start();


	pidsPerSecondTimer = new QTimer(this);
	connect(pidsPerSecondTimer,SIGNAL(timeout()),this,SLOT(pidsPerSecondTimerTick()));
	pidsPerSecondTimer->start(1000);


	ui.connectionInfoTableWidget->setRowCount(16);
	ui.connectionInfoTableWidget->setColumnCount(2);
	ui.connectionInfoTableWidget->setColumnWidth(0,220);
	ui.connectionInfoTableWidget->setColumnWidth(1,400);
	ui.connectionInfoTableWidget->horizontalHeader()->hide();
	ui.connectionInfoTableWidget->verticalHeader()->hide();
	ui.connectionInfoTableWidget->setItem(0,0,new QTableWidgetItem("Com Port"));
	ui.connectionInfoTableWidget->setItem(1,0,new QTableWidgetItem("Baud Rate"));
	ui.connectionInfoTableWidget->setItem(2,0,new QTableWidgetItem("Region Information"));
	ui.connectionInfoTableWidget->setItem(3,0,new QTableWidgetItem("Connection State"));
	ui.connectionInfoTableWidget->setItem(4,0,new QTableWidgetItem("Interface"));
	ui.connectionInfoTableWidget->setItem(5,0,new QTableWidgetItem("Scan Tool"));
	ui.connectionInfoTableWidget->setItem(6,0,new QTableWidgetItem("OBD Protocol"));
	ui.connectionInfoTableWidget->setItem(7,0,new QTableWidgetItem("Vehicle Battery Voltage"));
	ui.connectionInfoTableWidget->setItem(8,0,new QTableWidgetItem("OBD Requirements"));
	ui.connectionInfoTableWidget->setItem(9,0,new QTableWidgetItem("MIL Status"));
	ui.connectionInfoTableWidget->setItem(10,0,new QTableWidgetItem("DTC's present"));
	ui.connectionInfoTableWidget->setItem(11,0,new QTableWidgetItem("Engine"));
	ui.connectionInfoTableWidget->setItem(12,0,new QTableWidgetItem("Service $05 - O2 Sensors"));
	ui.connectionInfoTableWidget->setItem(13,0,new QTableWidgetItem("Service $06 - On Board Monitoring"));
	ui.connectionInfoTableWidget->setItem(14,0,new QTableWidgetItem("Service $08 - In Use Performance Tracking"));
	ui.connectionInfoTableWidget->setItem(15,0,new QTableWidgetItem("Service $09 - Vehicle Information"));

	for (int i=0;i<16;i++)
	{
		ui.connectionInfoTableWidget->setItem(i,1,new QTableWidgetItem());
	}

	ui.pidSelectTableWidget->setRowCount(0);
	ui.pidSelectTableWidget->setColumnCount(3);
	ui.pidSelectTableWidget->setColumnWidth(0,100);
	ui.pidSelectTableWidget->setColumnWidth(1,200);
	ui.pidSelectTableWidget->setColumnWidth(2,50);
	ui.pidSelectTableWidget->setHorizontalHeaderLabels(QStringList() << "PID" << "Description" << "Priority");
	ui.pidSelectTableWidget->verticalHeader()->hide();

	//connect(ui.pidSelectTableWidget,SIGNAL(itemClicked(QTableWidgetItem*)))

	QSettings settings("IFS","obdqmltool");
	settings.beginGroup("settings");
	QString port = settings.value("comport","").toString();
	int baud = settings.value("baudrate",0).toInt();
	settings.endGroup();
	qDebug() << port << baud;
	ui.status_comPortLabel->setText("Com port: " + port);
	ui.status_comBaudLabel->setText("Baud Rate: " + QString::number(baud));
	obdThread->setPort(port);
	obdThread->setBaud(baud);
	m_port = port;
	m_baud = baud;
	ui.connectionInfoTableWidget->item(0,1)->setText(port);
	ui.connectionInfoTableWidget->item(1,1)->setText(QString::number(baud));

	gaugeView = new QDeclarativeView(ui.gaugesTab);
	qmlRegisterType<GaugeItem>("GaugeImage",0,1,"GaugeImage");
	gaugeView->rootContext()->setContextProperty("propertyMap",&propertyMap);
	gaugeView->setGeometry(0,0,this->width()-5,this->height()-(ui.statusbar->height()+30));
	gaugeView->setSource(QUrl("qrc:/gaugeview.qml"));
	gaugeView->show();

	//gaugeView->engine()->setProperty("propertyMap",propertyMap);

	ui.statusbar->addWidget(ui.status_comPortLabel);
	ui.statusbar->addWidget(ui.status_comBaudLabel);
	ui.statusbar->addWidget(ui.status_comStatusLabel);
	ui.statusbar->addWidget(ui.status_comInterfaceLabel);
	ui.statusbar->addWidget(ui.status_comProtocolLabel);
	ui.statusbar->addWidget(ui.status_pidUpdateRateLabel);

	ui.readPidsTableWidget->setColumnCount(7);
	ui.readPidsTableWidget->setColumnWidth(0,50);
	ui.readPidsTableWidget->setColumnWidth(1,200);
	ui.readPidsTableWidget->setColumnWidth(2,100);
	ui.readPidsTableWidget->setColumnWidth(3,75);
	ui.readPidsTableWidget->setColumnWidth(4,75);
	ui.readPidsTableWidget->setColumnWidth(5,75);
	ui.readPidsTableWidget->setColumnWidth(6,75);

	ui.readPidsTableWidget->setHorizontalHeaderLabels(QStringList() << "PID" << "Description" << "Value" << "Units" << "Minimum" << "Maximum" << "Average");
	ui.readPidsTableWidget->verticalHeader()->hide();

	//obdThread->addRequest(0x01,0x0C,1,0);
	//obdThread->addRequest(0x01,0x0D,2,0);
	//obdThread->addRequest(0x01,0x05,5,0);
	//obdThread->addRequest(0x01,0x10,1,0);
	//obdThread->addRequest(0x01,0x11,1,0);
	//obdThread->addRequest(0x01,0x04,2,0);
	//obdThread->addRequest(0x01,0x31,100,0);

	//addReadPidRow("010C");
	//addReadPidRow("010D");
	//addReadPidRow("0105");
	//addReadPidRow("0110");
	//addReadPidRow("0111");
	//addReadPidRow("0104");
	//addReadPidRow("0131");

	graph = new EGraph(ui.graphsTab);
	graph->setGeometry(0,0,800,600);
	graph->addGraph("RPM");
	graph->setMax(0,7000);
	graph->setMin(0,0);
	graph->addGraph("Speed");
	graph->setMax(1,255);
	m_graphPidMap["010D"] = 0;
	m_graphPidMap["010C"] = 1;
	graph->show();




	ui.nonconTableWidget->setColumnCount(3);
	ui.nonconTableWidget->setHorizontalHeaderLabels(QStringList() << "Non continuous monitoring tests" << "Supported" << "Completed");
	ui.nonconTableWidget->verticalHeader()->hide();
	ui.nonconTableWidget->setColumnWidth(0,200);
	ui.nonconTableWidget->setColumnWidth(1,75);
	ui.nonconTableWidget->setColumnWidth(2,75);

	ui.nonconTableWidget->setRowCount(8);
	ui.nonconTableWidget->setItem(0,0,new QTableWidgetItem("Catalyst"));
	ui.nonconTableWidget->setItem(1,0,new QTableWidgetItem("Heated catalyst"));
	ui.nonconTableWidget->setItem(2,0,new QTableWidgetItem("Evaporative system"));
	ui.nonconTableWidget->setItem(3,0,new QTableWidgetItem("Secondary air system"));
	ui.nonconTableWidget->setItem(4,0,new QTableWidgetItem("A/C System refridgerant"));
	ui.nonconTableWidget->setItem(5,0,new QTableWidgetItem("Oxygen sensor"));
	ui.nonconTableWidget->setItem(6,0,new QTableWidgetItem("Oxygen sensor heater"));
	ui.nonconTableWidget->setItem(7,0,new QTableWidgetItem("EGR System"));

	for (int i=0;i<8;i++)
	{
		ui.nonconTableWidget->setItem(i,1,new QTableWidgetItem());
		ui.nonconTableWidget->setItem(i,2,new QTableWidgetItem());
	}

	ui.conTableWidget->setColumnCount(3);
	ui.conTableWidget->setHorizontalHeaderLabels(QStringList() << "Continuous monitoring tests" << "Supported" << "Completed");
	ui.conTableWidget->verticalHeader()->hide();
	ui.conTableWidget->setColumnWidth(0,200);
	ui.conTableWidget->setColumnWidth(1,75);
	ui.conTableWidget->setColumnWidth(2,75);

	ui.conTableWidget->setRowCount(3);
	ui.conTableWidget->setItem(0,0,new QTableWidgetItem("Misfire"));
	ui.conTableWidget->setItem(1,0,new QTableWidgetItem("Fuel System"));
	ui.conTableWidget->setItem(2,0,new QTableWidgetItem("Comprehensive Component"));

	for (int i=0;i<3;i++)
	{
		ui.conTableWidget->setItem(i,1,new QTableWidgetItem());
		ui.conTableWidget->setItem(i,2,new QTableWidgetItem());
	}

	ui.monitorStatusTableWidget->setColumnCount(2);
	ui.monitorStatusTableWidget->setHorizontalHeaderLabels(QStringList() << "Monitor Status" << "Status");
	ui.monitorStatusTableWidget->verticalHeader()->hide();
	ui.monitorStatusTableWidget->setColumnWidth(0,200);
	ui.monitorStatusTableWidget->setColumnWidth(1,75);


	//ui.readinessTab->setVisible(false);
	//ui.readinessTab->hide();
	//ui.vehiclePidTab->hide();
	//ui.troubleCodesTab->hide();
	//ui.onBoardMonitoringTab->hide();
	//ui.tabWidget->hide();
	ui.tabWidget->removeTab(2);
	ui.tabWidget->removeTab(3);
	ui.tabWidget->removeTab(3);
	ui.tabWidget->removeTab(3);
	ui.tabWidget->removeTab(3);


}
void MainWindow::uiReadReadinessButtonClicked()
{
	obdThread->sendReqMonitorStatus();
}
void MainWindow::rawConsoleReturnPressed()
{
	//obdThread->
}
void MainWindow::menu_actionDisconnectClicked()
{
	obdThread->disconnect();
}

void MainWindow::connectButtonClicked()
{
	obdThread->connect();
}

void MainWindow::changeEvent(QEvent *evt)
{
	/*ui.tabWidget->setGeometry(0,0,this->width(),this->height()-(ui.statusbar->height()+20));
	ui.connectionInfoTableWidget->setGeometry(0,0,this->width()-5,this->height()-(ui.statusbar->height()+70));
	ui.pidSelectTableWidget->setGeometry(0,0,this->width()-5,this->height()-(ui.statusbar->height()+45));
	ui.readPidsTableWidget->setGeometry(0,0,this->width()-5,this->height()-(ui.statusbar->height()+45));*/
	//QMainWindow:changeEvent(evt);
}
void MainWindow::pidsPerSecondTimerTick()
{
	ui.status_pidUpdateRateLabel->setText("Pid Rate: " + QString::number(m_pidcount));
	m_pidcount=0;
}
void MainWindow::obdOnBoardMonitoringReply(QList<unsigned char> midlist,QList<unsigned char> tidlist,QList<QString> vallist,QList<QString> minlist,QList<QString> maxlist)
{
	for (int i=0;i<midlist.size();i++)
	{
		ObdInfo::ModeSixInfo midinfo = obdThread->getInfo()->getInfoFromByte(midlist[i]);
		ObdInfo::ModeSixInfo tidinfo = obdThread->getInfo()->getTestFromByte(tidlist[i]);
		qDebug() << QString::number(midlist[i],16) << QString::number(tidlist[i],16) << vallist[i] << minlist[i] << maxlist[i];
		if (tidinfo.id == 0)
		{
			qDebug() << midinfo.description << "MFG Test";
		}
		else
		{
			qDebug() << midinfo.description << tidinfo.description;
		}
	}
}
void MainWindow::clearReadPidsTable()
{
	m_readPidTableMap.clear();
	ui.readPidsTableWidget->clearContents();
	ui.readPidsTableWidget->setRowCount(0);
	QMap<QString, ObdThread::RequestClass>::const_iterator i = m_pidToReqClassMap.constBegin();
	while (i != m_pidToReqClassMap.constEnd())
	{
		obdThread->removeRequest(i.value());
	    //cout << i.key() << ": " << i.value() << endl;

	    ++i;
	}

	//m_pidToReqClassMap.clear();
}

void MainWindow::addReadPidRow(QString pid,int priority)
{
	ObdInfo::Pid *p = obdThread->getInfo()->getPidFromString(pid);
	if (!p)
	{
		qDebug() << "Not valid" << pid;
		return;
	}
	ui.readPidsTableWidget->setRowCount(ui.readPidsTableWidget->rowCount()+1);
	int index = ui.readPidsTableWidget->rowCount()-1;
	ui.readPidsTableWidget->setItem(index,0,new QTableWidgetItem(pid));

	ui.readPidsTableWidget->setItem(index,1,new QTableWidgetItem(p->description));
	QTableWidgetItem *val = new QTableWidgetItem();
	ui.readPidsTableWidget->setItem(index,2,val);
	m_readPidTableMap[pid] = val;
	ui.readPidsTableWidget->setItem(index,3,new QTableWidgetItem(p->unit));
	ui.readPidsTableWidget->setItem(index,4,new QTableWidgetItem(QString::number(p->min)));
	ui.readPidsTableWidget->setItem(index,5,new QTableWidgetItem(QString::number(p->max)));
	ui.readPidsTableWidget->setItem(index,6,new QTableWidgetItem("avg"));
	ObdThread::RequestClass req;
	req.mode = p->mode;
	req.pid = p->pid;
	req.repeat = true;
	req.priority = priority;
	req.wait = 0;
	req.type = ObdThread::MODE_PID;
	obdThread->addRequest(req);
	m_pidToReqClassMap[pid] = req;

}
void MainWindow::resizeEvent(QResizeEvent *evt)
{
	ui.tabWidget->setGeometry(0,0,this->width(),this->height()-(ui.statusbar->height()+20));
}

void MainWindow::obdSingleShotReply(QByteArray req,QByteArray reply)
{
	qDebug() << "Raw Reply" << req << reply;
	if (req.startsWith("AT@1"))
	{

	}
	if (req.startsWith("ATRV"))
	{

	}
}
void MainWindow::obdVoltage(double volts)
{
	ui.connectionInfoTableWidget->item(7,1)->setText(QString::number(volts));
}

void MainWindow::obdMfgString(QString string)
{
	ui.connectionInfoTableWidget->item(5,1)->setText(string);
}

void MainWindow::obdSupportedModes(QList<QString> list)
{
	if (list.contains("05"))
	{
		ui.connectionInfoTableWidget->item(12,1)->setText("Supported");
	}
	else
	{
		ui.connectionInfoTableWidget->item(12,1)->setText("Not supported");
	}
	if (list.contains("06"))
	{
		ui.connectionInfoTableWidget->item(13,1)->setText("Supported");
	}
	else
	{
		ui.connectionInfoTableWidget->item(13,1)->setText("Not Supported");
	}
	if (list.contains("08"))
	{
		ui.connectionInfoTableWidget->item(14,1)->setText("Supported");
	}
	else
	{
		ui.connectionInfoTableWidget->item(14,1)->setText("Not Supported");
	}
	if (list.contains("09"))
	{
		ui.connectionInfoTableWidget->item(15,1)->setText("Supported");
	}
	else
	{
		ui.connectionInfoTableWidget->item(15,1)->setText("Not Supported");
	}
}

void MainWindow::uiPidSelectTableClicked(int row, int column)
{
	for (int i=0;i<ui.pidSelectTableWidget->rowCount();i++)
	{
		if (ui.pidSelectTableWidget->item(i,0)->checkState() == Qt::Checked)
		{
			if (!m_readPidTableMap.contains(ui.pidSelectTableWidget->item(i,0)->text()))
			{
				//Pid is not currently on our list! Let's add it.
				//addReadPidRow(ui.pidSelectTableWidget->item(i,0)->text(),ui.pidSelectTableWidget->item(i,2)->text().toInt());
			}
		}
		else
		{
			if (!m_readPidTableMap.contains(ui.pidSelectTableWidget->item(i,0)->text()))
			{
			}
		}
	}
}
void MainWindow::obdMonitorStatus(QList<QString> list)
{
	for (int i=0;i<list.size();i++)
	{
		if (list[i].size() != 3)
		{
			qDebug() << "Invalid obdMonitorStatus returned:" << list[i] << "line" << i;
			return;
		}
	}
	if (list.size() != 11)
	{
		qDebug() << "Invalid list size returned for obdMonitorStatus." << list.size();
		return;
	}
	//ui.conTableWidget->item(0,1)->setText(((list[0][0] == '0') ? "N" : "Y"));
	//ui.conTableWidget->item(0,2)->setText((list[0][0]=='0') ? "" : (list[0][2] == '1') ? "N" : "Y");
	for (int i=0;i<3;i++)
	{
		ui.conTableWidget->item(i,1)->setText(((list[i][0] == '0') ? "N" : "Y"));
		ui.conTableWidget->item(i,2)->setText((list[i][0]=='0') ? "" : (list[i][2] == '1') ? "N" : "Y");
	}
	for (int i=3;i<list.size();i++)
	{
		ui.nonconTableWidget->item(i-3,1)->setText(((list[i][0] == '0') ? "N" : "Y"));
		ui.nonconTableWidget->item(i-3,2)->setText((list[i][0]=='0') ? "" : (list[i][2] == '1') ? "N" : "Y");
	}
	/*if (list[0][0] == '0')
	{
		ui.conTableWidget->item(0,1)->setText("N");
		//Misfire supported
	}
	else
	{
		ui.conTableWidget->item(0,1)->setText("Y");
		if (list[0][2] == '1')
		{
			//Misfire incomplete
			ui.conTableWidget->item(0,2)->setText("N");
		}
		else
		{
			ui.conTableWidget->item(0,2)->setText("Y");
		}

	}
	if (list[1][0] == '0')
	{
		ui.conTableWidget->item(1,1)->setText("N");
	}*/
}

MainWindow::~MainWindow()
{
//	obdThread->disconnect();
//	while (obdThread->isRunning());
//	delete obdThread;
}
void MainWindow::menu_settingsClicked()
{
	settingsWidget = new SettingsWidget();
	connect(settingsWidget,SIGNAL(saveSettings(QString,int)),this,SLOT(settings_saveComPort(QString,int)));
	//QMdiSubWindow *win = ui.mdiArea->addSubWindow(settingsWidget);
	//win->setGeometry(100,100,311,156);
	settingsWidget->setSettings(m_port,m_baud);
	settingsWidget->show();
}
void MainWindow::obdSupportedPids(QList<QString> pidlist)
{
	ui.pidSelectTableWidget->clearContents();
	ui.pidSelectTableWidget->setRowCount(pidlist.size());
	for (int i=0;i<pidlist.size();i++)
	{
		ObdInfo::Pid *p = obdThread->getInfo()->getPidFromString(pidlist[i]);
		if (p)
		{
			ui.pidSelectTableWidget->setItem(i,0,new QTableWidgetItem(pidlist[i]));
			if (!p->bitencoded)
			{
			ui.pidSelectTableWidget->item(i,0)->setCheckState(Qt::Checked);
			}

			if (obdThread->getInfo()->getPidFromString(pidlist[i]))
			{
				ui.pidSelectTableWidget->setItem(i,1,new QTableWidgetItem(p->description));
				ui.pidSelectTableWidget->setItem(i,2,new QTableWidgetItem("1"));
			}
		}
		else
		{
			ui.pidSelectTableWidget->setItem(i,0,new QTableWidgetItem(pidlist[i]));
			ui.pidSelectTableWidget->setItem(i,1,new QTableWidgetItem("INVALID"));
			ui.pidSelectTableWidget->setItem(i,2,new QTableWidgetItem("1"));
		}
	}
}
void MainWindow::obdProtocolFound(QString protocol)
{
	ui.connectionInfoTableWidget->item(6,1)->setText(protocol);
	ui.status_comProtocolLabel->setText("Protocol: " + protocol);
}

void MainWindow::settings_saveComPort(QString port,int baud)
{
	QSettings settings("IFS","obdqmltool");
	settings.beginGroup("settings");
	//QString port = settings.value("comport","").toString();
	//int baud = settings.value("baudrate",0).toInt();
	settings.setValue("comport",port);
	settings.setValue("baudrate",baud);
	settings.endGroup();
	m_port = port;
	m_baud = baud;
	obdThread->setPort(port);
	obdThread->setBaud(baud);
	ui.status_comPortLabel->setText("Com port: " + port);
	ui.status_comBaudLabel->setText("Baud Rate: " + QString::number(baud));
	ui.connectionInfoTableWidget->item(0,1)->setText(port);
	ui.connectionInfoTableWidget->item(1,1)->setText(QString::number(baud));
	settingsWidget->deleteLater();
}
void MainWindow::uiPidSelectClearClicked()
{
	for (int i=0;i<ui.pidSelectTableWidget->rowCount();i++)
	{
		if (ui.pidSelectTableWidget->item(i,0)->checkState() == Qt::Checked)
		{
		ui.pidSelectTableWidget->item(i,0)->setCheckState(Qt::Unchecked);
		}
	}
}

void MainWindow::uiPidSelectSaveClicked()
{
	clearReadPidsTable();
	for (int i=0;i<ui.pidSelectTableWidget->rowCount();i++)
	{
		if (ui.pidSelectTableWidget->item(i,0)->checkState() == Qt::Checked)
		{
			addReadPidRow(ui.pidSelectTableWidget->item(i,0)->text(),ui.pidSelectTableWidget->item(i,2)->text().toInt());
		}
	}
}

void MainWindow::obdPidReceived(QString pid,QString val,int set, double time)
{
	//qDebug() << pid << val;
	propertyMap.setProperty(pid.toAscii(),val);
	//0105_DURATION
	if (m_pidTimeMap.contains(pid))
	{
		double newtime = QDateTime::currentMSecsSinceEpoch() - m_pidTimeMap[pid];
		//qDebug() << pid << val << set << QString::number(QDateTime::currentMSecsSinceEpoch(),'f') << newtime << QDateTime::currentMSecsSinceEpoch();
		propertyMap.setProperty(QString(pid + "_DURATION").toAscii(),newtime);
	}
	m_pidTimeMap[pid] = QDateTime::currentMSecsSinceEpoch();

	if (m_readPidTableMap.contains(pid))
	{
		m_readPidTableMap[pid]->setText(val);
	}
	m_pidcount++;
}
void MainWindow::obdConnected(QString version)
{
	ui.connectionInfoTableWidget->item(3,1)->setText("Connected");
	ui.connectionInfoTableWidget->item(4,1)->setText(version);
	//obdThread->switchBaud();
	//obdThread->sendReqOnBoardMonitors();
	obdThread->sendReqVoltage();
	obdThread->sendReqSupportedModes();
	obdThread->sendReqSupportedPids();
	obdThread->sendReqMfgString();
	ui.status_comStatusLabel->setText("Status: Connected");
	ui.status_comInterfaceLabel->setText("Interface: " + version);
	//ui.status_comBaudLabel->setText()
}
void MainWindow::menu_actionConnectClicked()
{
	obdThread->connect();
	ui.status_comStatusLabel->setText("Status: Connecting");
}

void MainWindow::obdDisconnected()
{
	ui.connectionInfoTableWidget->item(3,1)->setText("Disconnected");
}

void MainWindow::obdConsoleMessage(QString message)
{
	ui.debugTextBrowser->append(message);
}

void MainWindow::obdTroubleCodes(QList<QString> codes)
{
	qDebug() << "Codes:" << codes.size();
	ui.connectionInfoTableWidget->item(9,1)->setText("Clear");
	ui.connectionInfoTableWidget->item(10,1)->setText("0");
}
void MainWindow::obdError(ObdThread::ObdError err)
{
	qDebug() << "Error";
	if (err == ObdThread::UNABLE_TO_OPEN_COM_PORT)
	{
		ui.status_comStatusLabel->setText("Status: Unable to open Com Port");
	}
}