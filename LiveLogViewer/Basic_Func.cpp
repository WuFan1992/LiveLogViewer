#include "Basic_Func.h"
#include "LiveLog_data.h"
#include "LiveLogViewer.h"
#include <QList>
#include <QVector>
#include <qDebug>
#include <QString>

/*

void Draw_Graph(QList<LiveLog_data> mesure_temp_all_lines)
{
	QVector<QString> x_time; 
	QVector<double> mesure_temp_1;

	for (int i = 0; i < mesure_temp_all_lines.size(); i++)
	{

		// First get one element(type Class LiveLog_data)
		LiveLog_data livelog_data_tempory = mesure_temp_all_lines.at(i);
		QString x_time_tempory = livelog_data_tempory.get_time();
		double source_pressure_tempory = livelog_data_tempory.get_source_pressure();
		
		x_time.append(x_time_tempory);
		mesure_temp_1.append(source_pressure_tempory);

		qDebug() << source_pressure_tempory;
		
	}

	


}

*/


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