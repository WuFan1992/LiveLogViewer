#include "Draw_graph.h"
#include "LiveLog_data.h"
#include "LiveLogViewer.h"
#include <QList>
#include <QVector>
#include <qDebug>

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

