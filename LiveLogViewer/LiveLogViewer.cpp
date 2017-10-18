#include "LiveLogViewer.h"
#include "Widget_element.h"

using namespace std;

LiveLogViewer::LiveLogViewer(QWidget *parent)
	: QMainWindow(parent)
{

	widget_elements = new Widget_element;
	setCentralWidget(widget_elements);
	setup_resolution();
}


void LiveLogViewer::setup_resolution()
{
	resize(1024,768);
}
