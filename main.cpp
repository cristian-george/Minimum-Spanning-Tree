#include "MST.h"
#include <QtWidgets/QApplication>

int main(int argc, char* argv[])
{
	QApplication a(argc, argv);
	MST w;
	w.showMaximized();
	return a.exec();
}
