#include "Widget_element.h"
#include "Widget_plot.h"
#include "LiveLog_data.h"
#include "Basic_Func.h"

using DATA = std::array<QVector<QPointF>, 20>;
Widget_element::Widget_element(QWidget *parent)
{
	

	widget_plot = new Widget_plot;
    lay = new QVBoxLayout;
	
	Set_Button();
	lay->addWidget(widget_plot);

	setLayout(lay);
	
}

void Widget_element::Set_Button()
{
	QPushButton *browseButton = new QPushButton(tr("Browser"));
	lay->addWidget(browseButton);

	connect(browseButton, &QPushButton::clicked, this, &Widget_element::OpenFile);

	QPushButton *exportButton = new QPushButton(tr("Export"));
	lay->addWidget(exportButton);
	connect(exportButton, &QPushButton::clicked, this, &Widget_element::Export_Plot);

}

void Widget_element::Infor_DateTime()
{
	QLabel *label_infor_begin_date = new QLabel;
	QLabel *label_infor_begin_time = new QLabel;
	QLabel *label_infor_end_date = new QLabel;
	QLabel *label_infor_end_time = new QLabel;
	label_infor_begin_date->setText(tr("Begin Date is %1 ").arg((begin_datetime->begin_date).toString()));
	label_infor_begin_time->setText(tr("Begin Time is %1 ").arg((begin_datetime->begin_time).toString()));
	label_infor_end_date->setText(tr("End Date is %1 ").arg((begin_datetime->end_date).toString()));
	label_infor_end_time->setText(tr("End Time is %1 ").arg((begin_datetime->end_time).toString()));
	lay->addWidget(label_infor_begin_date);
	lay->addWidget(label_infor_begin_time);
	lay->addWidget(label_infor_end_date);
	lay->addWidget(label_infor_end_time);

}


void Widget_element::Export_Plot()
{
	QwtPlotRenderer *renderer = new QwtPlotRenderer;
	renderer->exportTo(widget_plot->livelogviewer_plot, "LiveLogViewer_plot.pdf");
}


void Widget_element::OpenFile()
{

	QList<QString> Filename_list = Select_File();

	if (File_Existing(Filename_list))
	{
		DATA Points = Read_Data(Filename_list);
		widget_plot->Display_graph(Points);
		Infor_DateTime();
	}
	
}

bool Widget_element::File_Existing(QList<QString> Filename_list)
{
	for (int i = 0; i < Filename_list.size(); i++)
	{
		if (!Filename_list.at(i).isEmpty())
		{
			QFile file(Filename_list.at(i));
			if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
			{
				QMessageBox::warning(this, tr("Read File"), tr("Can not open file:\n%1").arg(Filename_list.at(i)));
				return 0;
			}
			file.close();
		}
		else
		{
			QMessageBox::warning(this, tr("Path"), tr("You did not select any file"));
			return 0;
		}
	}

	return 1;
}




DATA Widget_element::Read_Data(QList<QString> Filename_list)
{
	
	DATA Points;
	begin_datetime = new DATETIME;
	
	QRegExp rx_time("(\\d*\\.\\d*\\.\\d*\/\\d*\\:\\d*\\:\\d*)");
	QRegExp rx_press_tempe("(\\d*\\.\\d+)");

	for (int i = 0; i < Filename_list.size(); i++)
	{
		int num_line = 1;  // The number of line
		QFile file(Filename_list.at(i));
		file.open(QIODevice::ReadOnly | QIODevice::Text);
		QTextStream in(&file);
		while (!in.atEnd())
		{
			QString line = in.readLine();

			// initialize Class LiveLog_data which represent one line in the text
			LiveLog_data data_each_line;

			if ((num_line >= 7))
			{
				int pos_rx_time = 0; // position of time(hour:minutes:second) in one line
				int pos_rx_press_tempe = 0; // position of values of pression and temperature in one line
				pos_rx_time = rx_time.indexIn(line, pos_rx_time);

				double time_in_double = Set_Time(rx_time.cap(1),i,num_line,begin_datetime,Filename_list.size(),in.atEnd());

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

					num_colone++;
					pos_rx_press_tempe += rx_press_tempe.matchedLength();

				}
	
				mesure_temp_all_lines.append(data_each_line);
			}
			num_line++;
		}
		file.close();
		
	}


	for (int i = 0; i < mesure_temp_all_lines.size(); i++)
	{

		Points[0].append(QPointF(mesure_temp_all_lines.at(i).time, mesure_temp_all_lines.at(i).source_pressure));
		Points[1].append(QPointF(mesure_temp_all_lines.at(i).time, mesure_temp_all_lines.at(i).target_pressure));
		Points[2].append(QPointF(mesure_temp_all_lines.at(i).time, mesure_temp_all_lines.at(i).mesure_pressure));
		Points[3].append(QPointF(mesure_temp_all_lines.at(i).time, mesure_temp_all_lines.at(i).target_temperature));

		for (int j = 0; j < 16; j++)
		{
			Points[j + 4].append(QPointF(mesure_temp_all_lines.at(i).time, mesure_temp_all_lines.at(i).mesure_temp_one_line.at(j)));
		}
	}

	return Points;
}


QList<QString> Widget_element::Select_File()
{
	//Get the directory path
	QString path = QFileDialog::getOpenFileName(this, tr("Open File"), ".", tr("Text Files(*.txt)"));
	QDir dir = QFileInfo(path).absoluteDir();
	QString path_dir = dir.absolutePath();

	int num_file_in_dir = dir.count();
	num_file_in_dir -= 2;    // The directory contains "." and ".." so we must reduce 2 which is the last result.

	QStringList all_file_name = dir.entryList();  // get all the name of file which are in the same directory as the select file.

	QList<QString> Filename_list;

	for (int i = 2; i < all_file_name.size(); i++)   // change here
	{

		QString path_each_file = path_dir + QString("/") + all_file_name.at(i);
		Filename_list.append(path_each_file);

	}
	return Filename_list;

}

