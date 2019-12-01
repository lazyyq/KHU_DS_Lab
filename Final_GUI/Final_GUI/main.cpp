#include "Final_GUI.h"
#include "QtLoginWindow.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[]) {
	QApplication a(argc, argv);
	a.setQuitOnLastWindowClosed(false);
	QtLoginWindow w;
	w.show();
	return a.exec();
}
