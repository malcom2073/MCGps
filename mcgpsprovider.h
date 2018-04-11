#ifndef MCGPSPROVIDER_H
#define MCGPSPROVIDER_H

#include <QObject>
#include "mcipc.h"
class GpsMessage
{
public:
	void setLocation(double lon,double lat,long time, long sats, double alt)
	{
		m_lat = lat;
		m_lon = lon;
		m_time = time;
		m_sats = sats;
		m_alt = alt;
	};
	void setSignal(int mode, double pdop,double hdop,double vdop)
	{
		m_mode = mode;
		m_pdop = pdop;
		m_hdop = hdop;
		m_vdop = vdop;
	};
	void setSpeed(double speed)
	{
		m_speed = speed;
	};

	double m_lat;
	double m_lon;
	long m_time;
	long m_sats;
	double m_alt;
	int m_mode;
	double m_pdop;
	double m_hdop;
	double m_vdop;
	double m_speed;
	QJsonObject makeMessage()
	{
		QJsonObject msg;
		msg.insert("latitude",m_lat);
		msg.insert("longitude",m_lon);
		msg.insert("time",m_time);
		msg.insert("sats",m_sats);
		msg.insert("altitude",m_alt);
		msg.insert("mode",m_mode);
		msg.insert("pdop",m_pdop);
		msg.insert("hdop",m_hdop);
		msg.insert("vdop",m_vdop);
		msg.insert("speed",m_speed);
		return msg;
	};
};

class MCGpsProvider : public QObject
{
	Q_OBJECT
public:
	explicit MCGpsProvider(QObject *parent = 0);
private:
	MCIPC *m_ipc;
	GpsMessage m_gpsMessage;
signals:
private slots:
	void location(double lon,double lat, long time, long sats, double alt);
	void signalStatus(int mode,double pdop,double hdop,double vdop);
	void speedOverGround(double speed);
	void timerTick();
public slots:
};

#endif // MCGPSPROVIDER_H
