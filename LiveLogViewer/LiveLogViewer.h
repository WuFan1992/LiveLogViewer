#pragma once

#include <QtWidgets/QMainWindow>
#include <QMainWindow>
#include<QTextEdit>
#include <QCombobox>
#include <QVBoxLayout>
#include "LiveLog_data.h"
#include "qwt/qwt_plot_curve.h"
#include "qwt/qwt_plot.h"


class LiveLogViewer : public QMainWindow
{
	Q_OBJECT

public:
	LiveLogViewer(QWidget *parent = Q_NULLPTR);
	QwtPlot* livelogviewer_plot;
	//QwtPlotCurve livelogviewer_curve;
	QVector<QwtPlotCurve *> livelogviewer_curve;
	QList<LiveLog_data> mesure_temp_all_lines;
	QComboBox* combobox;
	QVBoxLayout* lay;

private:
	void OpenFile();
	void Select_File(QString path );
	void Open_Each_File(QString path_dir, QString Filename);
public:
	void Display_graph();
	void Set_Combobox();
	void Combobox_Change(int index);
	
};


