#include "Basic_Func.h"
#include <QList>
#include <QVector>
#include <qDebug>
#include <QString>


double Set_Time(QString time_in_string,int file_index, int num_line,DATETIME *begin_datetime,int total_file, bool end_or_not)
{
	
	QDateTime qdatetime = QDateTime::fromString(time_in_string, "dd.MM.yyyy/hh:mm:ss");
	if ((file_index == 0) && (num_line == 7))
	{
		
		begin_datetime->begin_date =qdatetime.date();
		begin_datetime->begin_time = qdatetime.time();
	}
	if ((file_index == total_file-1 ) && (end_or_not))
	{
		begin_datetime->end_date = qdatetime.date();
		begin_datetime->end_time = qdatetime.time();

	}
	
	int time_in_second = QTime(begin_datetime->begin_time.hour(), begin_datetime->begin_time.minute(), begin_datetime->begin_time.second()).secsTo(qdatetime.time());
	
	return (double)time_in_second;

}
