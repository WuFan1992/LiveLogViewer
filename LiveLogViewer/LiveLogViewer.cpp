#include "LiveLogViewer.h"
#include <QAction>
#include <Qtwidgets>
#include <QString>
#include <QFile>
#include <QMessageBox>
#include <QTextEdit>
#include <QDebug>
#include <QDir>
#include <iostream>
#include <QPen>
#include "qwt/qwt_plot_curve.h"
#include "qwt/qwt_plot.h"
#include "LiveLog_data.h"
#include "Basic_Func.h"
using namespace std;

LiveLogViewer::LiveLogViewer(QWidget *parent)
	: QMainWindow(parent)
{
	QPushButton *browseButton = new QPushButton(tr("Browser"), this);

	connect(browseButton, &QPushButton::clicked, this, &LiveLogViewer::OpenFile);
    
}

void LiveLogViewer::OpenFile()
{
	//int num_line = 1;  // The number of line
	
	int num_file_in_dir; // The number of files in the directory 


	QString path = QFileDialog::getOpenFileName(this, tr("Open File"), ".", tr("Text Files(*.txt)"));


	Select_File(path);


	Display_graph();

}






void LiveLogViewer::Open_Each_File(QString path_dir, QString Filename)
{

	int num_line = 1;  // The number of line
	QRegExp rx_time("(\\d*\\:\\d*\\:\\d*)");
    QRegExp rx_press_tempe("(\\d*\\.\\d+)");
	QString path_test = path_dir + QString("/") + Filename;


	if (!path_test.isEmpty())
	{

		QFile file(path_test);
		if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
		{

			QMessageBox::warning(this, tr("Read File"), tr("Can not open file:\n%1").arg(path_test));
			return;

		}

		QTextStream in(&file);
		while (!in.atEnd())
		{
			QString line = in.readLine();

			// initialize Class LiveLog_data which represent one line in the text
			LiveLog_data data_each_line;

			//if ((num_line >= 7) && (num_line <= 20))
			if ((num_line >= 7))
			{
				int pos_rx_time = 0; // position of time(hour:minutes:second) in one line
				int pos_rx_press_tempe = 0; // position of values of pression and temperature in one line
				pos_rx_time = rx_time.indexIn(line, pos_rx_time);

				
				double time_in_double = QString_to_Double(rx_time.cap(1));
				data_each_line.time = time_in_double;

				// colone number
				int num_colone = 1;

				while ((pos_rx_press_tempe = rx_press_tempe.indexIn(line, pos_rx_press_tempe)) != -1)
				{
					if (num_colone == 3)
					{
						data_each_line.source_pressure = rx_press_tempe.cap(1).toDouble();

					}
					else if (num_colone == 4)
					{
						data_each_line.target_pressure = rx_press_tempe.cap(1).toDouble();

					}
					else if (num_colone == 5)
					{
						data_each_line.mesure_pressure = rx_press_tempe.cap(1).toDouble();

					}
					else if (num_colone == 6)
					{

						data_each_line.target_temperature = rx_press_tempe.cap(1).toDouble();
					}
					else if (num_colone >= 7)
					{

						data_each_line.mesure_temp_one_line.append(rx_press_tempe.cap(1).toDouble());
					}
					else
					{
						QString useless_value = rx_press_tempe.cap(1);

					}

					//list << rx_press_tempe.cap(1);
					num_colone++;
					pos_rx_press_tempe += rx_press_tempe.matchedLength();

				}
				//qDebug() << list;
				//data_each_line.show_target_temperature();
				mesure_temp_all_lines.append(data_each_line);
			}

			num_line++;

		}
		file.close();
	}
	else
	{

		QMessageBox::warning(this, tr("Path"), tr("You did not select any file"));


	}

}





void LiveLogViewer::Select_File(QString path)
{
	//Get the directory path
	QDir dir = QFileInfo(path).absoluteDir();
	QString path_dir = dir.absolutePath();

	int num_file_in_dir = dir.count();
	num_file_in_dir -= 2;    // The directory contains "." and ".." so we must reduce 2 which is the last result.

	QStringList all_file_name = dir.entryList();  // get all the name of file which are in the same directory as the select file.

	QStringList list;

	for (int i = 2; i < all_file_name.size()-1; i++)   // change here
	{


		Open_Each_File(path_dir, all_file_name.at(i));


	}

}


void LiveLogViewer::Display_graph()
{
	QVector<QVector<QPointF>> Points;

	livelogviewer_plot = new QwtPlot(this);

	for (int j = 0; j < 20; j++)
	{
		Points.append(QVector<QPointF>());
		QwtPlotCurve* myplotcurve = new QwtPlotCurve;
		livelogviewer_curve.append(myplotcurve);
	}

	//QVector<QPointF> points;
	for (int i = 0; i < mesure_temp_all_lines.size(); i++)
	{

		Points[0].append(QPoint(mesure_temp_all_lines.at(i).time, mesure_temp_all_lines.at(i).source_pressure));
		Points[1].append(QPoint(mesure_temp_all_lines.at(i).time, mesure_temp_all_lines.at(i).target_pressure));
		Points[2].append(QPoint(mesure_temp_all_lines.at(i).time, mesure_temp_all_lines.at(i).mesure_pressure));
		Points[3].append(QPoint(mesure_temp_all_lines.at(i).time, mesure_temp_all_lines.at(i).target_temperature));
		Points[4].append(QPoint(mesure_temp_all_lines.at(i).time, mesure_temp_all_lines.at(i).mesure_temp_one_line.at(0)));
		Points[5].append(QPoint(mesure_temp_all_lines.at(i).time, mesure_temp_all_lines.at(i).mesure_temp_one_line.at(1)));
		Points[6].append(QPoint(mesure_temp_all_lines.at(i).time, mesure_temp_all_lines.at(i).mesure_temp_one_line.at(2)));
		Points[7].append(QPoint(mesure_temp_all_lines.at(i).time, mesure_temp_all_lines.at(i).mesure_temp_one_line.at(3)));
		Points[8].append(QPoint(mesure_temp_all_lines.at(i).time, mesure_temp_all_lines.at(i).mesure_temp_one_line.at(4)));
		Points[9].append(QPoint(mesure_temp_all_lines.at(i).time, mesure_temp_all_lines.at(i).mesure_temp_one_line.at(5)));
		Points[10].append(QPoint(mesure_temp_all_lines.at(i).time, mesure_temp_all_lines.at(i).mesure_temp_one_line.at(6)));
		Points[11].append(QPoint(mesure_temp_all_lines.at(i).time, mesure_temp_all_lines.at(i).mesure_temp_one_line.at(7)));
		Points[12].append(QPoint(mesure_temp_all_lines.at(i).time, mesure_temp_all_lines.at(i).mesure_temp_one_line.at(8)));
		Points[13].append(QPoint(mesure_temp_all_lines.at(i).time, mesure_temp_all_lines.at(i).mesure_temp_one_line.at(9)));
		Points[14].append(QPoint(mesure_temp_all_lines.at(i).time, mesure_temp_all_lines.at(i).mesure_temp_one_line.at(10)));
		Points[15].append(QPoint(mesure_temp_all_lines.at(i).time, mesure_temp_all_lines.at(i).mesure_temp_one_line.at(11)));
		Points[16].append(QPoint(mesure_temp_all_lines.at(i).time, mesure_temp_all_lines.at(i).mesure_temp_one_line.at(12)));
		Points[17].append(QPoint(mesure_temp_all_lines.at(i).time, mesure_temp_all_lines.at(i).mesure_temp_one_line.at(13)));
		Points[18].append(QPoint(mesure_temp_all_lines.at(i).time, mesure_temp_all_lines.at(i).mesure_temp_one_line.at(14)));
		//Points[19].append(QPoint(mesure_temp_all_lines.at(i).time, mesure_temp_all_lines.at(i).mesure_temp_one_line.at(15)));

	}

	
	/*

	for (int k = 0; k < 2; k++)
	{
		livelogviewer_curve[k]->attach(livelogviewer_plot);
		livelogviewer_curve[k]->setSamples(Points[k]);
		switch(k) {
		case 0: livelogviewer_curve[0]->setPen(QPen(Qt::red)); break;
		case 1: livelogviewer_curve[0]->setPen(QPen(QColor(0,255,0))); break;

		
		}
		//livelogviewer_curve[k]->setPen(QPen(Qt::red));
		livelogviewer_curve[k]->setStyle(QwtPlotCurve::Lines);
	}

	



	livelogviewer_plot->show();
	livelogviewer_plot->replot();

	*/
}