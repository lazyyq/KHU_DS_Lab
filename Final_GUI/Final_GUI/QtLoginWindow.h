#pragma once

#include <QMainWindow>
#include "ui_QtLoginWindow.h"

#include "QtMainWindow.h"

class QtLoginWindow : public QMainWindow {
	Q_OBJECT

public:
	QtLoginWindow(QWidget *parent = Q_NULLPTR);
	~QtLoginWindow();

private:
	Ui::QtLoginWindow ui;
	QtMainWindow *mainWindow;

	bool mQuitProgram = true;

	void closeEvent(QCloseEvent *event);

	// 프로그램 첫번째 실행인지 확인
	bool IsFirstLaunch() const;

	// 주어진 아이디와 비번으로 사용자가 존재하는지, 관리자인지 확인
	bool Authorize(const std::string &inputId,
		const std::string &inputPw, bool &isAdmin) const;


private slots:
	void ExitClicked();
	void LoginClicked();
	void RegisterClicked();
};
