#pragma once

#include <QtWidgets/QMainWindow>
#include <QMainWindow>
#include<QTextEdit>


class LiveLogViewer : public QMainWindow
{
	Q_OBJECT

public:
	LiveLogViewer(QWidget *parent = Q_NULLPTR);
	


private:
	void OpenFile();
	
	//QAction *openAction;

	
};


