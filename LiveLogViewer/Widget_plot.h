#pragma once
#include <Qtwidgets>
#include <qwt/qwt_legend_data.h>
#include<qwt/qwt_plot_item.h>
#include <qwt/qwt_legend.h>
#include <qwt/qwt_legend_label.h>
#include "qwt/qwt_symbol.h"
#include "qwt/qwt_plot_curve.h" 
#include "qwt/qwt_plot.h" 
#include "qwt/qwt_plot_histogram.h"


class Widget_plot : public QWidget
{

public:
	Widget_plot(QWidget *parent = Q_NULLPTR);
	virtual ~Widget_plot() = default;

	QwtPlot* livelogviewer_plot; 
	QVector<QwtPlotCurve*> livelogviewer_curve; 
	QwtLegend *legend;
	
private:
	void Set_Plot(); 
public:
	void Display_graph(QVector<QPointF> *Points); 
	//void Combobox_Change(int index);


	void Show_Curve(QwtPlotItem *item, bool on);
	void Legend_Checked(const QVariant &iteminfo, bool on);
   
};
