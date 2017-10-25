#include "Widget_plot.h"

#include <QVBoxLayout>
#include <qpushbutton.h>

#include <qwt/qwt_plot_magnifier.h>


using DATA = std::array<QVector<QPointF>, 20>;

Widget_plot::Widget_plot(QWidget *parent)
{
	Set_Plot();
	Set_Legend();
	Set_Panner_Magnifier();
	Initialize_Display();
	connect(legend, &QwtLegend::checked, this,&Widget_plot::Legend_Checked);


}


void Widget_plot::Set_Plot()
{
	auto* lay = new QVBoxLayout;

	livelogviewer_plot = new QwtPlot;
	livelogviewer_plot->enableAxis(QwtPlot::yRight);
	livelogviewer_plot->setAxisTitle(QwtPlot::xBottom, tr("Runtime (s)"));
	livelogviewer_plot->setAxisTitle(QwtPlot::yLeft, tr("Temperature (°C)"));
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

void Widget_plot::Initialize_Display()
{
	QList<QColor> Color_list = { QColor(0,0,255),QColor(0,255,0),QColor(255, 0, 0), QColor(255,255, 0) ,QColor(148, 0, 211),QColor(138, 43, 226),QColor(186, 85, 211),QColor(218, 112, 214),QColor(221, 160, 221),QColor(238, 130, 238),QColor(208, 32, 144),QColor(176, 48, 96),QColor(139,69,19),QColor(160,82,45),QColor(205, 133, 63),QColor(222, 184, 135),QColor(244, 164, 96),QColor(210, 180, 140),QColor(188, 143, 143),QColor(245, 222, 179) };

	for (int i = 0; i < 20; i++)
	{
		
		QwtPlotCurve* myplotcurve;
		if (i == 0)
		{
			myplotcurve = new QwtPlotCurve("Source Pressure");
		}
		else if (i == 1)
		{
			myplotcurve = new QwtPlotCurve("Target Pressure");
		}
		else if (i == 2)
		{
			myplotcurve = new QwtPlotCurve("Mesure Pressure");
		}
		else if (i == 3)
		{
			myplotcurve = new QwtPlotCurve("Target Temperature");
		}
		else if (i < 12)
		{
			myplotcurve = new QwtPlotCurve(tr("Temperature %1 (Left)").arg(i - 3));
		}
		else
		{
			myplotcurve = new QwtPlotCurve(tr("Temperature %1 (Right)").arg(i - 3));
		}
		livelogviewer_curve.append(myplotcurve);
		

	}

	for (int m = 0; m < 20; m++)
	{
		livelogviewer_curve[m]->setPen(QPen(Color_list.at(m)));
		livelogviewer_curve[m]->setStyle(QwtPlotCurve::Lines);

		if (m < 3)
		{
			livelogviewer_curve[m]->setYAxis(QwtPlot::yRight);
		}
		else
		{
			livelogviewer_curve[m]->setYAxis(QwtPlot::yLeft);
		}
	}



}


void Widget_plot::Display_graph(DATA Points)
{
  
	for (int k = 0; k < 20; k++)
	{
		livelogviewer_curve[k]->setSamples(Points[k]);
		
		if (k < 3)
		{
			livelogviewer_curve[k]->attach(livelogviewer_plot);
			Show_Curve(livelogviewer_curve[k], true);
		}
		else
		{
			livelogviewer_curve[k]->attach(livelogviewer_plot);
			Show_Curve(livelogviewer_curve[k], false);
		}
		
	}

	livelogviewer_plot->replot();
	
}

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
