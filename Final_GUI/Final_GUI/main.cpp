#include "Final_GUI.h"
#include "QtLoginWindow.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[]) {
	// Application window
	QApplication a(argc, argv);
	a.setQuitOnLastWindowClosed(false);
	// Login window
	QtLoginWindow w;
	w.show();
	return a.exec(); // Start app
}
