#include "Widget_plot.h"

Widget_plot::Widget_plot(QWidget *parent)
{
	Set_Plot();

}


void Widget_plot::Set_Plot()
{

	livelogviewer_plot = new QwtPlot;
	livelogviewer_plot->enableAxis(QwtPlot::yRight);
	livelogviewer_plot->setAxisTitle(QwtPlot::xBottom, tr("Runtime (s)"));
	livelogviewer_plot->setAxisTitle(QwtPlot::yLeft, tr("Temperature (°C)"));
	livelogviewer_plot->setAxisTitle(QwtPlot::yRight, tr("Pressure (mBar)"));

}



void Widget_plot::Display_graph(QVector<QPointF> *Points)
{
	QList<QColor> Color_list = { QColor(0,0,255),QColor(0,255,0),QColor(255, 0, 0), QColor(0, 0, 0) ,QColor(15, 15, 15),QColor(30, 30, 30),QColor(45, 45, 45),QColor(60, 60, 60),QColor(75, 75, 75),QColor(90, 90, 90),QColor(105, 105, 105),QColor(120, 120, 120),QColor(135,135,135),QColor(150,150,150),QColor(165, 165, 165),QColor(180, 180, 180),QColor(195, 195, 195),QColor(210, 210, 210),QColor(225, 225, 225),QColor(240, 240, 240) };

	for (int i = 0; i < 20; i++)
	{
		QwtPlotCurve* myplotcurve = new QwtPlotCurve;
		livelogviewer_curve.append(myplotcurve);
	}


	for (int k = 0; k < 20; k++)
	{
		livelogviewer_curve[k]->setSamples(Points[k]);
		livelogviewer_curve[k]->setPen(QPen(Color_list.at(k)));
		livelogviewer_curve[k]->setStyle(QwtPlotCurve::Lines);
		if (k < 3)
			livelogviewer_curve[k]->setYAxis(QwtPlot::yRight);
		else
			livelogviewer_curve[k]->setYAxis(QwtPlot::yLeft);
		livelogviewer_curve[k]->attach(livelogviewer_plot);
	}
	livelogviewer_plot->replot();


}



void Widget_plot::Combobox_Change(int index)
{
	for (int p = 0; p < 20; p++)
	{
		livelogviewer_curve[p]->detach();
	}

	livelogviewer_curve[index]->attach(livelogviewer_plot);
	livelogviewer_plot->replot();

}