#pragma once

#include <QtWidgets/QMainWindow>
#include <QMainWindow>
#include<QTextEdit>
#include "LiveLog_data.h"


class LiveLogViewer : public QMainWindow
{
	Q_OBJECT

public:
	LiveLogViewer(QWidget *parent = Q_NULLPTR);
	


private:
	void OpenFile();
	void Select_File(QString path, QList<LiveLog_data> mesure_temp_all_lines);
	void Open_Each_File(QString path_dir, QString Filename, QList<LiveLog_data> mesure_temp_all_lines);
	
	//QAction *openAction;

	
};


