#pragma once
#include <Qtwidgets>
#include <QCombobox>
#include <QWidget>
#include <QList>
#include <QVector>
#include <QTextStream>

#include "LiveLog_data.h"
#include "Widget_plot.h"


class Widget_element : public QWidget
{
	Q_OBJECT

public:
	Widget_element(QWidget *parent = Q_NULLPTR);
	virtual ~Widget_element() = default;

private:
	
	QPushButton *browseButton;
	//QComboBox* combobox;
	QVBoxLayout* lay;
	QList<QString> Select_File();
	QList<LiveLog_data> mesure_temp_all_lines;


	QVector<QPointF> Points[20];


	Widget_plot *widget_plot;

	void Set_Button();
	//void Set_Combobox();

	void OpenFile();
	bool File_Existing(QList<QString> Filename_list);
	void Read_Data(QList<QString> Filename_list);

};



