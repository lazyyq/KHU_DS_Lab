#pragma once

#include <QMainWindow>
#include "ui_QtSearchOnWebWindow.h"

// Search on web window
class QtSearchOnWebWindow : public QMainWindow {
	Q_OBJECT

public:
	QtSearchOnWebWindow(QWidget *parent = Q_NULLPTR);
	~QtSearchOnWebWindow();

private:
	Ui::QtSearchOnWebWindow ui;

private slots:
	void SearchClicked();
	void TableCellDoubleClicked(int row, int col);
};
