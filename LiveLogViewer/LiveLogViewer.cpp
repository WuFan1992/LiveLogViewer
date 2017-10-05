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

	QRegExp rx_time("(\\d*\\:\\d*\\:\\d*)");
	QRegExp rx_press_tempe("(\\d*\\.\\d+)");

	QString path = QFileDialog::getOpenFileName(this, tr("Open File"), ".", tr("Text Files(*.txt)"));
	QDir dir = QFileInfo(path).absoluteDir();
	//QDir dir = QDir::currentPath();

	num_file_in_dir = dir.count();
	num_file_in_dir -= 2;
	
	QStringList all_file_name = dir.entryList();  // get all the name of file which are in the same directory as the select file.

 // qDebug() << path;
	//qDebug() << dir;
	//qDebug() << num_file_in_dir;
	//qDebug() << all_file_name;
	
	for (int i = 2; i < all_file_name.size(); ++i)
	{
		qDebug() << all_file_name.at(i);

	}


	if (!path.isEmpty())
	{

		QFile file(path);
		if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
		{

			QMessageBox::warning(this, tr("Read File"), tr("Can not open file:\n%1").arg(path));
			return;

		}

		QTextStream in(&file);
		while (!in.atEnd())
		{
			QString line = in.readLine();
			QStringList list;
			
			if (num_line >= 7)
			{
				int pos_rx_time = 0; // position of time(hour:minutes:second) in one line
				int pos_rx_press_tempe = 0; // position of values of pression and temperature in one line
				pos_rx_time = rx_time.indexIn(line, pos_rx_time);
				list << rx_time.cap(1);

				while ((pos_rx_press_tempe = rx_press_tempe.indexIn(line, pos_rx_press_tempe)) != -1)
				{
					
					list << rx_press_tempe.cap(1);
					pos_rx_press_tempe += rx_press_tempe.matchedLength();

				}
				//qDebug() << list;
			}

			//num_line++;

		}
		file.close();
	}
	else
	{

		QMessageBox::warning(this, tr("Path"), tr("You did not select any file"));


	}


}
