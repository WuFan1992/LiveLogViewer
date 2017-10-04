#include "LiveLogViewer.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	LiveLogViewer w;
	w.show();
	return a.exec();
}
