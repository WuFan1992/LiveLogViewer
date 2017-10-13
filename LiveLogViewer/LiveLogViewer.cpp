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
#include <QCombobox>
#include "qwt/qwt_plot_curve.h"
#include "qwt/qwt_plot.h"
#include "LiveLog_data.h"
#include "Basic_Func.h"
using namespace std;

LiveLogViewer::LiveLogViewer(QWidget *parent)
	: QMainWindow(parent)
{
	//auto* lay = new QVBoxLayout;
	lay = new QVBoxLayout;

	QPushButton *browseButton = new QPushButton(tr("Browser"));
	connect(browseButton, &QPushButton::clicked, this, &LiveLogViewer::OpenFile);
	lay->addWidget(browseButton);

	livelogviewer_plot = new QwtPlot;
	livelogviewer_plot->enableAxis(QwtPlot::yRight);
	livelogviewer_plot->setAxisTitle(QwtPlot::xBottom, tr("Runtime (s)"));
	livelogviewer_plot->setAxisTitle(QwtPlot::yLeft, tr("Temperature (°C)"));
	livelogviewer_plot->setAxisTitle(QwtPlot::yRight, tr("Pressure (mBar)"));
	lay->addWidget(livelogviewer_plot);

	Set_Combobox();
	lay->addWidget(combobox);


	auto* w = new QWidget;
	w->setLayout(lay);
	setCentralWidget(w);
	showMaximized();
}

void LiveLogViewer::OpenFile()
{
	
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

	//QStringList list;

	for (int i = 2; i < all_file_name.size()-1; i++)   // change here
	{


		Open_Each_File(path_dir, all_file_name.at(i));


	}

}


void LiveLogViewer::Display_graph()
{
	QVector<QVector<QPointF>> Points;

	for (int j = 0; j < 20; j++)
	{
		Points.append(QVector<QPointF>());
		QwtPlotCurve* myplotcurve = new QwtPlotCurve;
		livelogviewer_curve.append(myplotcurve);
	}


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
		Points[19].append(QPoint(mesure_temp_all_lines.at(i).time, mesure_temp_all_lines.at(i).mesure_temp_one_line.at(15)));

	}

	for (int k = 0; k < 20; k++)
	{
		livelogviewer_curve[k]->setSamples(Points[k]);
		switch(k) {
		case 0: livelogviewer_curve[k]->setPen(QPen(QColor(0, 0, 255))); break;
		case 1: livelogviewer_curve[k]->setPen(QPen(QColor(0,255,0))); break;
		case 2: livelogviewer_curve[k]->setPen(QPen(QColor(255, 0, 0))); break;
		case 3: livelogviewer_curve[k]->setPen(QPen(QColor(0, 0, 0))); break;
		case 4: livelogviewer_curve[k]->setPen(QPen(QColor(15, 15, 15))); break;
		case 5: livelogviewer_curve[k]->setPen(QPen(QColor(30, 30, 30))); break;
		case 6: livelogviewer_curve[k]->setPen(QPen(QColor(45, 45, 45))); break;
		case 7: livelogviewer_curve[k]->setPen(QPen(QColor(60, 60, 60))); break;
		case 8: livelogviewer_curve[k]->setPen(QPen(QColor(75, 75, 75))); break;
		case 9: livelogviewer_curve[k]->setPen(QPen(QColor(90, 90, 90))); break;
		case 10: livelogviewer_curve[k]->setPen(QPen(QColor(105, 105, 105))); break;
		case 11: livelogviewer_curve[k]->setPen(QPen(QColor(120, 120, 120))); break;
		case 12: livelogviewer_curve[k]->setPen(QPen(QColor(135,135,135))); break;
		case 13: livelogviewer_curve[k]->setPen(QPen(QColor(150,150,150))); break;
		case 14: livelogviewer_curve[k]->setPen(QPen(QColor(165, 165, 165))); break;
		case 15: livelogviewer_curve[k]->setPen(QPen(QColor(180, 180, 180))); break;
		case 16: livelogviewer_curve[k]->setPen(QPen(QColor(195, 195, 195))); break;
		case 17: livelogviewer_curve[k]->setPen(QPen(QColor(210, 210, 210))); break;
		case 18: livelogviewer_curve[k]->setPen(QPen(QColor(225, 225, 225))); break;
		case 19: livelogviewer_curve[k]->setPen(QPen(QColor(240, 240, 240))); break;

		}
		livelogviewer_curve[k]->setStyle(QwtPlotCurve::Lines);
		if (k < 3)
			livelogviewer_curve[k]->setYAxis(QwtPlot::yRight);
		else
			livelogviewer_curve[k]->setYAxis(QwtPlot::yLeft);
		livelogviewer_curve[k]->attach(livelogviewer_plot);
	}
	livelogviewer_plot->replot();

	connect(combobox, static_cast<void(QComboBox::*)(int)>(&QComboBox::currentIndexChanged), this, &LiveLogViewer::Combobox_Change);

}



void LiveLogViewer::Set_Combobox()
{

	combobox = new QComboBox;
	combobox->resize(100, 20);
	QIcon icon_stilla("C:/Users/admin/Pictures/icon_stilla.png");
	combobox->addItem(icon_stilla, "source pressure");
	combobox->addItem(icon_stilla, "target pressure");
	combobox->addItem(icon_stilla, "mesure pressure");
	combobox->addItem(icon_stilla, "target temperature");
	combobox->addItem(icon_stilla, "temperature 1");
	combobox->addItem(icon_stilla, "temperature 2");
	combobox->addItem(icon_stilla, "temperature 3");
	combobox->addItem(icon_stilla, "temperature 4");
	combobox->addItem(icon_stilla, "temperature 5");
	combobox->addItem(icon_stilla, "temperature 6");
	combobox->addItem(icon_stilla, "temperature 7");
	combobox->addItem(icon_stilla, "temperature 8");
	combobox->addItem(icon_stilla, "temperature 9");
	combobox->addItem(icon_stilla, "temperature 10");
	combobox->addItem(icon_stilla, "temperature 11");
	combobox->addItem(icon_stilla, "temperature 12");
	combobox->addItem(icon_stilla, "temperature 13");
	combobox->addItem(icon_stilla, "temperature 14");
	combobox->addItem(icon_stilla, "temperature 15");
	combobox->addItem(icon_stilla, "temperature 16");


}




void LiveLogViewer::Combobox_Change(int index)
{

	for (int p = 0; p < 20; p++)
	{
		livelogviewer_curve[p]->detach();
	}

	livelogviewer_curve[index]->attach(livelogviewer_plot);
	
}
