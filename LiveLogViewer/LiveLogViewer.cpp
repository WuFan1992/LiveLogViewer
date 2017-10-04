#include "LiveLogViewer.h"
#include <QAction>
#include <Qtwidgets>
#include <QString>
#include <QFile>
#include <QMessageBox>
#include <QTextEdit>
#include <QDebug>

LiveLogViewer::LiveLogViewer(QWidget *parent)
	: QMainWindow(parent)
{
	QPushButton *browseButton = new QPushButton(tr("Browser"), this);

	
	connect(browseButton, &QAbstractButton::clicked, this, &LiveLogViewer::OpenFile);
    

	
}

void LiveLogViewer::OpenFile()
{
	QString path = QFileDialog::getOpenFileName(this, tr("Open File"), ".", tr("Text Files(*.txt)"));

	if (!path.isEmpty())
	{

		QFile file(path);
		if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
		{

			QMessageBox::warning(this, tr("Read File"), tr("Can not open file:\n%1").arg(path));
			return;

		}

		QTextStream in(&file);
		while (!in.atEnd())
		{
			QString line = in.readLine();
			qDebug() << line;

		}

	}
	else
	{

		QMessageBox::warning(this, tr("Path"), tr("You did not select any file"));


	}


}
