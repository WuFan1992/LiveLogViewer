#pragma once
#include <iostream>
#include <QList>
#include <QTime>
#include <QDateTime>

using namespace std;

class DATETIME
{
public:
	QDate begin_date;
	QTime begin_time;

	QDate end_date;
	QTime end_time;
};

double Set_Time(QString time_in_string,int file_index, int num_line,DATETIME *begin_datetime,int total_file,bool end_or_not);

