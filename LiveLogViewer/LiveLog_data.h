#pragma once
#include <QtWidgets/QMainWindow>
#include <QMainWindow>
#include<QTextEdit>
#include <QList>
#include <iostream>
using namespace std;

class LiveLog_data
{

	QString time;
	// pressure 
	double source_pressure;
	double target_pressure;
	double mesure_pressure;
	double target_temperature;
	//  temperature
	QList<double> mesure_temp_one_line;

public:
	void set_time(QString t);
	void add_source_press(double x);
	void add_target_press(double y);
	void add_mesure_press(double z);
	void add_target_temperature(double w);
	void add_temp_list(double l);



	// get the value we want

	QString get_time();
	double get_source_pressure();

	// only for the test

	void show_source_pressure();
	void show_target_pressure(); 
	void show_mesure_pressure();
	void show_target_temperature();
	void show_mesure_temp_one_line();

};
