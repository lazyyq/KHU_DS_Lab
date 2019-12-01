#pragma once

#include <QMainWindow>
#include "ui_QtAddMusicManually.h"

class QtAddMusicManually : public QMainWindow {
	Q_OBJECT

public:
	QtAddMusicManually(QWidget *parent = Q_NULLPTR);
	~QtAddMusicManually();

private:
	Ui::QtAddMusicManually ui;

private slots:
	void AddDone();
	void AddCancel();
};
