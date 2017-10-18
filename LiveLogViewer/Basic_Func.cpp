#include "Basic_Func.h"
#include "LiveLog_data.h"
#include "LiveLogViewer.h"
#include <QList>
#include <QVector>
#include <qDebug>
#include <QString>
#include <QTime>



/*
double QString_to_Double(QString time_in_string)
{
	QRegExp rx_time("(\\d+)");

	double time_in_double;


	QList<double> list;
	int pos = 0;

	while((pos = rx_time.indexIn(time_in_string, pos)) != -1)
	{
		list << rx_time.cap(1).toDouble();
		pos += rx_time.matchedLength();

	}
	
	time_in_double = list.at(0) * 10000 + list.at(1) * 100 + list.at(2);
	
	return time_in_double;
}

*/


double QString_to_Double(QString time_in_string)
{

	QRegExp rx_time("(\\d+)");

	double time_in_double;


	QList<int> list;
	int pos = 0;

	while ((pos = rx_time.indexIn(time_in_string, pos)) != -1)
	{
		list << rx_time.cap(1).toDouble();
		pos += rx_time.matchedLength();

	}

	QTime qtime = QTime(list.at(0), list.at(1), list.at(2));
	int time_in_second = QTime(0, 0, 0).secsTo(qtime);
	return (double)time_in_second;

}
