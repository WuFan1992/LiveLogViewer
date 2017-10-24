#pragma once
#include <QMainWindow>
#include "Widget_element.h"


class LiveLogViewer : public QMainWindow
{
	Q_OBJECT

public:
	LiveLogViewer(QWidget *parent = Q_NULLPTR);
	Widget_element *widget_elements;

private:
	void setup_resolution();
	
};


