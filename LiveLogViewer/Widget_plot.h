#pragma once
#include <Qtwidgets>
#include "qwt/qwt_plot_curve.h" 
#include "qwt/qwt_plot.h" 


class Widget_plot : public QWidget
{

public:
	Widget_plot(QWidget *parent = Q_NULLPTR);
	virtual ~Widget_plot() = default;

	QwtPlot* livelogviewer_plot; 
	QVector<QwtPlotCurve*> livelogviewer_curve; 

private:
	void Set_Plot(); 
public:
	void Display_graph(QVector<QPointF> *Points); 
	void Combobox_Change(int index);
   
};
