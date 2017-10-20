#include "Widget_plot.h"

#include <QVBoxLayout>
#include <qpushbutton.h>

#include <qwt/qwt_plot_magnifier.h>

Widget_plot::Widget_plot(QWidget *parent)
{
	Set_Plot();
	Set_Legend();
	Set_Panner_Magnifier();
	connect(legend, &QwtLegend::checked, this,&Widget_plot::Legend_Checked);


}


void Widget_plot::Set_Plot()
{
	auto* lay = new QVBoxLayout;

	livelogviewer_plot = new QwtPlot;
	livelogviewer_plot->enableAxis(QwtPlot::yRight);
	livelogviewer_plot->setAxisTitle(QwtPlot::xBottom, tr("Runtime (s)"));
	livelogviewer_plot->setAxisTitle(QwtPlot::yLeft, tr("Temperature (°C)*100"));
	livelogviewer_plot->setAxisTitle(QwtPlot::yRight, tr("Pressure (mBar)"));
	lay->addWidget(livelogviewer_plot);
	setLayout(lay);

}

void Widget_plot::Set_Legend()
{
	
	legend = new QwtLegend;
	legend->setDefaultItemMode(QwtLegendData::Checkable);
	livelogviewer_plot->insertLegend(legend, QwtPlot::RightLegend);


}


void Widget_plot::Set_Panner_Magnifier()
{

	// Set the panner
	plot_panner = new QwtPlotPanner(livelogviewer_plot->canvas());

	//Set the magnifier
	auto* magnifier = new QwtPlotMagnifier(livelogviewer_plot->canvas());
	magnifier->setMouseButton(Qt::NoButton);
	magnifier->setWheelFactor(1.5);


}


void Widget_plot::Display_graph(QVector<QPointF> *Points)
{

	QList<QColor> Color_list = { QColor(0,0,255),QColor(0,255,0),QColor(255, 0, 0), QColor(0, 0, 0) ,QColor(15, 15, 15),QColor(30, 30, 30),QColor(45, 45, 45),QColor(60, 60, 60),QColor(75, 75, 75),QColor(90, 90, 90),QColor(105, 105, 105),QColor(120, 120, 120),QColor(135,135,135),QColor(150,150,150),QColor(165, 165, 165),QColor(180, 180, 180),QColor(195, 195, 195),QColor(210, 210, 210),QColor(225, 225, 225),QColor(240, 240, 240) };

	for (int i = 0; i < 20; i++)
	{
		QwtPlotCurve* myplotcurve;
	     if (i ==0)
		 {myplotcurve = new QwtPlotCurve("Source Pressure");}
		 else if (i == 1)
		 {myplotcurve = new QwtPlotCurve("Target Pressure");}
		 else if (i == 2)
		 {myplotcurve = new QwtPlotCurve("Mesure Pressure");}
		 else if (i == 3)
		 {myplotcurve = new QwtPlotCurve("Target Temperature");}
		 else
		 {myplotcurve = new QwtPlotCurve(tr("Temperature %1").arg(i-3));}
		 livelogviewer_curve.append(myplotcurve);


	}


	for (int k = 0; k < 20; k++)
	{
		livelogviewer_curve[k]->setSamples(Points[k]);
		livelogviewer_curve[k]->setPen(QPen(Color_list.at(k)));
		livelogviewer_curve[k]->setStyle(QwtPlotCurve::Lines);
		if (k < 3)
		{
			livelogviewer_curve[k]->setYAxis(QwtPlot::yRight);
			livelogviewer_curve[k]->attach(livelogviewer_plot);
			Show_Curve(livelogviewer_curve[k], true);
		}
		else
		{
			
			livelogviewer_curve[k]->setYAxis(QwtPlot::yLeft);
			livelogviewer_curve[k]->attach(livelogviewer_plot);
			Show_Curve(livelogviewer_curve[k], false);

		}
		//livelogviewer_curve[k]->attach(livelogviewer_plot);
	}

	livelogviewer_plot->replot();
	
}


/*
void Widget_plot::Combobox_Change(int index)
{
	for (int p = 0; p < 20; p++)
	{
		livelogviewer_curve[p]->detach();
	}

	livelogviewer_curve[index]->attach(livelogviewer_plot);
	livelogviewer_plot->replot();

}
*/
void Widget_plot::Legend_Checked(const QVariant &iteminfo, bool on)
{
	QwtPlotItem *plotitem = livelogviewer_plot->infoToItem(iteminfo); // iteminfo contains the information of the type of the objet, infotoitem take the information and verify if it correspond to the given type.
	if (plotitem)
		Show_Curve(plotitem, on);


}

void Widget_plot::mouseDoubleClickEvent(QMouseEvent * evt)
{
	livelogviewer_plot->setAxisAutoScale(QwtPlot::xBottom, true);
	livelogviewer_plot->setAxisAutoScale(QwtPlot::yLeft, true);
	livelogviewer_plot->setAxisAutoScale(QwtPlot::yRight, true);
	livelogviewer_plot->updateAxes();
	livelogviewer_plot->replot();
}


void Widget_plot::Show_Curve(QwtPlotItem *item, bool on)
{
	item->setVisible(on);  // on can be true or false. if true , setvisible will set this item to be visible , if false , setvisible will set this item unseen.
	QwtLegend *lgd = qobject_cast<QwtLegend *>(legend);
	QList<QWidget *> legendWidgets = lgd->legendWidgets(livelogviewer_plot->itemToInfo(item));

	if (legendWidgets.size() == 1)
	{
		QwtLegendLabel *legendlabel = qobject_cast<QwtLegendLabel *>(legendWidgets[0]);

		if (legendlabel)
			legendlabel->setChecked(on);

	}
	
	livelogviewer_plot->replot();
	
}
