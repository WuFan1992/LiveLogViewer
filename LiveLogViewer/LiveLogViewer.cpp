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
#include "LiveLog_data.h"
#include "Draw_graph.h"
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

	QList<LiveLog_data> mesure_temp_all_lines;   // This QList is used to save all the lines , for each is in the form of Class LiveLog_data

	//QRegExp rx_time("(\\d*\\:\\d*\\:\\d*)");
	//QRegExp rx_press_tempe("(\\d*\\.\\d+)");

	QString path = QFileDialog::getOpenFileName(this, tr("Open File"), ".", tr("Text Files(*.txt)"));

	Select_File(path, mesure_temp_all_lines);

	/*


	Here I put the function select_file

	void Select_File(QString path)

	void Open_Each_File(QString Path_dir, QStringList all_file_name, )

	*/


	/*
	QDir dir = QFileInfo(path).absoluteDir();
	QString path_dir = dir.absolutePath();

	num_file_in_dir = dir.count();
	num_file_in_dir -= 2;    // The directory contains "." and ".." so we must reduce 2 which is the last result.
	
	QStringList all_file_name = dir.entryList();  // get all the name of file which are in the same directory as the select file.

   qDebug() << path;
   qDebug() << dir;
   qDebug() << path_dir;

 
	QStringList list;
  
	//int files_total = all_file_name.size()

	for (int i = 2; i < 3; ++i)
	{

		QString path_test = path_dir + QString("/") + all_file_name.at(i);

		if (!path_test.isEmpty())
		{

			QFile file(path_test);
			//if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
			if (file.open(QIODevice::ReadOnly | QIODevice::Text))
			{

				QMessageBox::warning(this, tr("Read File"), tr("Can not open file:\n%1").arg(path_test));
				return;

			}

			QTextStream in(&file);
			while (!in.atEnd())
			{
				QString line = in.readLine();

				// initialize Class LiveLog_data which represent one line in the text
				LiveLog_data data_each_line ;

				//initialize Class as null

				LiveLog_data *p = &data_each_line;
				p = NULL;
				

				if ((num_line >= 7)&&(num_line <= 20))
				{
					int pos_rx_time = 0; // position of time(hour:minutes:second) in one line
					int pos_rx_press_tempe = 0; // position of values of pression and temperature in one line
					pos_rx_time = rx_time.indexIn(line, pos_rx_time);
					
					//set the time in the Class LiveLog_data
					data_each_line.time = rx_time.cap(1);

					//list << rx_time.cap(1);

					// colone number
					int num_colone = 1;

					while ((pos_rx_press_tempe = rx_press_tempe.indexIn(line, pos_rx_press_tempe)) != -1)
					{
						if (num_colone == 3)
						{
							data_each_line.source_pressure =  rx_press_tempe.cap(1).toDouble();
						
						}
						else if (num_colone == 4)
						{
							data_each_line.target_pressure = rx_press_tempe.cap(1).toDouble();

						}
						else if (num_colone == 5)
						{
							data_each_line.mesure_pressure = rx_press_tempe.cap(1).toDouble() ;
						
						}
						else if (num_colone == 6)
						{

							data_each_line.target_temperature = rx_press_tempe.cap(1).toDouble() ;
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


		// use the principal function
		//Draw_Graph(mesure_temp_all_lines);
	}


	*/
}






void LiveLogViewer::Open_Each_File(QString path_dir, QString Filename, QList<LiveLog_data> mesure_temp_all_lines)
{

	int num_line = 1;  // The number of line
	QRegExp rx_time("(\\d*\\:\\d*\\:\\d*)");
    QRegExp rx_press_tempe("(\\d*\\.\\d+)");
	QString path_test = path_dir + QString("/") + Filename;

	if (!path_test.isEmpty())
	{

		QFile file(path_test);
		//if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
		if (file.open(QIODevice::ReadOnly | QIODevice::Text))
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

			if ((num_line >= 7) && (num_line <= 20))
			{
				int pos_rx_time = 0; // position of time(hour:minutes:second) in one line
				int pos_rx_press_tempe = 0; // position of values of pression and temperature in one line
				pos_rx_time = rx_time.indexIn(line, pos_rx_time);

				//set the time in the Class LiveLog_data
				data_each_line.time = rx_time.cap(1);

				//list << rx_time.cap(1);

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





void LiveLogViewer::Select_File(QString path, QList<LiveLog_data> mesure_temp_all_lines)
{
	//Get the directory path
	QDir dir = QFileInfo(path).absoluteDir();
	QString path_dir = dir.absolutePath();

	int num_file_in_dir = dir.count();
	num_file_in_dir -= 2;    // The directory contains "." and ".." so we must reduce 2 which is the last result.

	QStringList all_file_name = dir.entryList();  // get all the name of file which are in the same directory as the select file.

	QStringList list;

	for (int i = 0; i < 3; i++)
	{


		Open_Each_File(path_dir, all_file_name.at(i), mesure_temp_all_lines);


	}

}
