#pragma once
#include <Qtwidgets>
#include <QCombobox>
#include <QWidget>
#include <QList>
#include <QVector>
#include <QTextStream>
#include <array>

#include "LiveLog_data.h"
#include "Widget_plot.h"


#include "qwt/qwt_plot_renderer.h"
#include "qtoolbutton.h"
#include "qtoolbar.h"


class Widget_element : public QWidget
{
	Q_OBJECT

public:
	Widget_element(QWidget *parent = Q_NULLPTR);
	virtual ~Widget_element() = default;
	using DATA = std::array<QVector<QPointF>, 20>;
	
private:
	
	//QPushButton *browseButton;
	//QPushButton *exportButton;
	QVBoxLayout* lay;
	QList<QString> Select_File();
	QList<LiveLog_data> mesure_temp_all_lines;
	
	//DATA Points;

	Widget_plot *widget_plot;
	

	void Set_Button();
	//void Infor_DateTime();
	void OpenFile();
	void Export_Plot();
	bool File_Existing(QList<QString> Filename_list);
	DATA Read_Data(QList<QString> Filename_list);

};



