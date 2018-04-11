#include "mcgpsprovider.h"
#include "nmeadatasource.h"
#include <QDebug>
#include <QJsonDocument>
#include <QTimer>

MCGpsProvider::MCGpsProvider(QObject *parent) : QObject(parent)
{
	////CNCA0
	NMEADataSource *m_dataSource = new NMEADataSource(this);
	connect(m_dataSource,SIGNAL(location(double,double,long,long,double)),this,SLOT(location(double,double,long,long,double)));
	connect(m_dataSource,SIGNAL(signalStatus(int,double,double,double)),this,SLOT(signalStatus(int,double,double,double)));
	connect(m_dataSource,SIGNAL(speedOverGround(double)),this,SLOT(speedOverGround(double)));
	m_dataSource->start();
	m_ipc = new MCIPC("GpsProvider",this);
	m_ipc->connectToHost("127.0.0.1",12345);
	QTimer *timer = new QTimer(this);
	connect(timer,SIGNAL(timeout()),this,SLOT(timerTick()));
	timer->start(250);
}
void MCGpsProvider::location(double lon,double lat, long time, long sats, double alt)
{
	qDebug() << "Incoming GPS:" << lon << lat << time << sats << alt;
	m_gpsMessage.setLocation(lon,lat,time,sats,alt);
}
void MCGpsProvider::signalStatus(int mode,double pdop,double hdop,double vdop)
{
	qDebug() << "GPS Status:" << mode << pdop << hdop << vdop;
	m_gpsMessage.setSignal(mode,pdop,hdop,vdop);
}
void MCGpsProvider::speedOverGround(double speed)
{
	qDebug() << "Speed:" << speed;
	m_gpsMessage.setSpeed(speed);
}
void MCGpsProvider::timerTick()
{
	QByteArray json = QJsonDocument(m_gpsMessage.makeMessage()).toJson();
	m_ipc->publishMessage("GpsProvider/navdata",json);
}
