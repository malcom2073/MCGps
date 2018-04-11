#ifndef NMEADATASOURCE_H
#define NMEADATASOURCE_H

#include <QObject>
#include <QtSerialPort/QSerialPort>
#include <QFile>

class NMEADataSource : public QObject
{
	Q_OBJECT
public:
	explicit NMEADataSource(QObject *parent = 0);
	void loadFile(QString filename){}
	void start();
private:
	QSerialPort *m_serialPort;
	QByteArray m_buffer;
	void parseBuffer();
	double m_savedSpeed;
	QFile *m_logFile;

	QFile *m_nmeaLogFile;
private slots:
	void serialReadyRead();
signals:
	void location(double lon,double lat, long time, long sats, double alt);
	void signalStatus(int mode,double pdop,double hdop,double vdop);
	void speedOverGround(double speed);
public slots:
};

#endif // NMEADATASOURCE_H
