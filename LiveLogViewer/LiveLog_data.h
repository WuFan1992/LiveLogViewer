#pragma once

#include <QList>

using namespace std;

class LiveLog_data
{

public: 
	double time;
	// pressure 
	double source_pressure;
	double target_pressure;
	double mesure_pressure;
	double target_temperature;
	//  temperature
	QList<double> mesure_temp_one_line;

public:
	
	// get the value we want

	double get_time();
	double get_source_pressure();

	// only for the test

	void show_source_pressure();
	void show_target_pressure(); 
	void show_mesure_pressure();
	void show_target_temperature();
	void show_mesure_temp_one_line();

};
