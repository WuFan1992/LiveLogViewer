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
using namespace std;

LiveLogViewer::LiveLogViewer(QWidget *parent)
	: QMainWindow(parent)
{
	QPushButton *browseButton = new QPushButton(tr("Browser"), this);

	
	connect(browseButton, &QAbstractButton::clicked, this, &LiveLogViewer::OpenFile);
    
}

void LiveLogViewer::OpenFile()
{
	int num_line = 1;  // The number of line
	
	int num_file_in_dir; // The number of files in the directory 


	QList<LiveLog_data> mesure_temp_all_lines;   // This QList is used to save all the lines , for each is in the form of Class LiveLog_data

	QRegExp rx_time("(\\d*\\:\\d*\\:\\d*)");
	QRegExp rx_press_tempe("(\\d*\\.\\d+)");

	QString path = QFileDialog::getOpenFileName(this, tr("Open File"), ".", tr("Text Files(*.txt)"));
	QDir dir = QFileInfo(path).absoluteDir();
	QString path_dir = dir.absolutePath();

	num_file_in_dir = dir.count();
	num_file_in_dir -= 2;    // The directory contains "." and ".." so we must reduce 2 which is the last result.
	
	QStringList all_file_name = dir.entryList();  // get all the name of file which are in the same directory as the select file.

   qDebug() << path;
   qDebug() << dir;
   qDebug() << path_dir;

 
	QStringList list;
  

	for (int i = 2; i < 3; ++i)
	{

		QString path_test = path_dir + QString("/") + all_file_name.at(i);

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
					data_each_line.set_time(rx_time.cap(1));

					//list << rx_time.cap(1);

					// colone number
					int num_colone = 1;

					while ((pos_rx_press_tempe = rx_press_tempe.indexIn(line, pos_rx_press_tempe)) != -1)
					{
						if (num_colone == 3)
						{
							data_each_line.add_source_press(rx_press_tempe.cap(1).toDouble());
						
						}
						else if (num_colone == 4)
						{
							data_each_line.add_target_press(rx_press_tempe.cap(1).toDouble());

						}
						else if (num_colone == 5)
						{
							data_each_line.add_mesure_press(rx_press_tempe.cap(1).toDouble());
						
						}
						else if (num_colone == 6)
						{

							data_each_line.add_target_temperature(rx_press_tempe.cap(1).toDouble());
						}
						else if (num_colone >= 7)
						{

							data_each_line.add_temp_list(rx_press_tempe.cap(1).toDouble());
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
					data_each_line.show_target_temperature();
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

}
