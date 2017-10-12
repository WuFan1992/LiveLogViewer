#include "LiveLog_data.h"
#include <iostream>
#include <qDebug>
using namespace std;

/*
void LiveLog_data::add_temp_list(double l)
{

	mesure_temp_one_line.append(l);

}
*/



void LiveLog_data::show_source_pressure()
{
	qDebug() << source_pressure;
}

void LiveLog_data::show_target_pressure()
{
	qDebug() << target_pressure;

}

void LiveLog_data::show_mesure_pressure()
{
	qDebug() << mesure_pressure;

}

void LiveLog_data::show_target_temperature()
{
	qDebug() << target_temperature;
 
}

void LiveLog_data::show_mesure_temp_one_line()
{
	for (int j = 0; j < mesure_temp_one_line.size(); j++)
	{
		qDebug() << mesure_temp_one_line.at(j);
	}

}


double LiveLog_data::get_time()
{
	return time;
}


double LiveLog_data::get_source_pressure()
{

	return source_pressure;
}