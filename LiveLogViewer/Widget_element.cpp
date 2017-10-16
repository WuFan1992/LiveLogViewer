#include "Widget_element.h"
#include "Widget_plot.h"
#include "LiveLog_data.h"
#include "Basic_Func.h"

Widget_element::Widget_element(QWidget *parent)
{
	

	widget_plot = new Widget_plot;
    lay = new QVBoxLayout;
	combobox = new QComboBox;

	Set_Button();
	lay->addWidget(widget_plot->livelogviewer_plot);
	Set_Combobox();
	

	setLayout(lay);
}

void Widget_element::Set_Button()
{
	browseButton = new QPushButton(tr("Browser"));
	lay->addWidget(browseButton);
	connect(browseButton, &QPushButton::clicked, this, &Widget_element::OpenFile);

}

void Widget_element::Set_Combobox()
{
	combobox->resize(100, 20);
	QIcon icon_stilla("C:/Users/admin/Pictures/icon_stilla.png");
	combobox->addItem(icon_stilla, "source pressure");
	combobox->addItem(icon_stilla, "target pressure");
	combobox->addItem(icon_stilla, "mesure pressure");
	combobox->addItem(icon_stilla, "target temperature");

	for (int i = 1; i < 17; i++)
	{
		combobox->addItem(icon_stilla, tr("Temperature %1").arg(i));

	}
	lay->addWidget(combobox);


	connect(combobox, static_cast<void(QComboBox::*)(int)>(&QComboBox::currentIndexChanged), widget_plot, &Widget_plot::Combobox_Change);

}




void Widget_element::OpenFile()
{

	QList<QString> Filename_list = Select_File();

	if (File_Existing(Filename_list))
	{
		Read_Data(Filename_list);
		widget_plot->Display_graph(Points);
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




void Widget_element::Read_Data(QList<QString> Filename_list)
{


	QRegExp rx_time("(\\d*\\:\\d*\\:\\d*)");
	QRegExp rx_press_tempe("(\\d*\\.\\d+)");

	qDebug() << Filename_list.size();
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

	//QVector<QPointF> Points[20];


	for (int i = 0; i < mesure_temp_all_lines.size(); i++)
	{

		Points[0].append(QPoint(mesure_temp_all_lines.at(i).time, mesure_temp_all_lines.at(i).source_pressure));
		Points[1].append(QPoint(mesure_temp_all_lines.at(i).time, mesure_temp_all_lines.at(i).target_pressure));
		Points[2].append(QPoint(mesure_temp_all_lines.at(i).time, mesure_temp_all_lines.at(i).mesure_pressure));
		Points[3].append(QPoint(mesure_temp_all_lines.at(i).time, mesure_temp_all_lines.at(i).target_temperature));

		for (int j = 0; j < 16; j++)
		{
			Points[j + 4].append(QPoint(mesure_temp_all_lines.at(i).time, mesure_temp_all_lines.at(i).mesure_temp_one_line.at(j)));
		}
	}




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
