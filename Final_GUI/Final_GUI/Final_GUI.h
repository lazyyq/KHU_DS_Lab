#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_Final_GUI.h"

class Final_GUI : public QMainWindow
{
	Q_OBJECT

public:
	Final_GUI(QWidget *parent = Q_NULLPTR);

private:
	Ui::Final_GUIClass ui;
};
