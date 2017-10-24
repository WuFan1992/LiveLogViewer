#pragma once
#include <iostream>
#include <QList>
#include <QTime>
#include <QDateTime>
#include "LiveLogViewer.h"
#include "LiveLog_data.h"

using namespace std;

class BEGIN_DATETIME
{
public:
	QDate begin_date;
	QTime begin_time;

};

double Set_Time(QString time_in_string,int file_index, int num_line,BEGIN_DATETIME *begin_datetime);

