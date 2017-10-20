#pragma once
//#include <Qtwidgets>

#include <QWidget>
#include <qwt/qwt_legend_data.h>
#include<qwt/qwt_plot_item.h>
#include <qwt/qwt_legend.h>
#include <qwt/qwt_legend_label.h>
#include "qwt/qwt_symbol.h"
#include "qwt/qwt_plot_curve.h" 
#include "qwt/qwt_plot.h" 
#include "qwt/qwt_plot_histogram.h"
#include "qwt/qwt_plot_panner.h"
#include "qwt/qwt_plot_zoomer.h"
#include "qwt/qwt_event_pattern.h"

#include <QList>
#include <QVector>
#include <QPushButton>
#include <array>

class Widget_plot : public QWidget
{
	Q_OBJECT
	
public:
	Widget_plot(QWidget *parent = Q_NULLPTR);
	virtual ~Widget_plot() = default;

	QVector<QwtPlotCurve*> livelogviewer_curve; 
	QwtPlot* livelogviewer_plot;

private:
	QwtLegend *legend;
	QwtPlotPanner *plot_panner;

private:
	void Set_Plot(); 
	void Set_Legend();
	void Set_Panner_Magnifier();
	
public:
	using DATA = std::array<QVector<QPointF>, 20>;
	void Initialize_Display();
	void Display_graph(DATA Points); 
	void Show_Curve(QwtPlotItem *item, bool on);
	void Legend_Checked(const QVariant &iteminfo, bool on);

protected:
	virtual void mouseDoubleClickEvent(QMouseEvent* evt) override;
   
};
