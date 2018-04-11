#include <QCoreApplication>
#include "mcgpsprovider.h"

int main(int argc, char *argv[])
{
	QCoreApplication a(argc, argv);
	MCGpsProvider mcgps;
	return a.exec();
}
