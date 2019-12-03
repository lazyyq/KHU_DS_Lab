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

	// ���α׷� ù��° �������� Ȯ��
	bool IsFirstLaunch() const;

	// �־��� ���̵�� ������� ����ڰ� �����ϴ���, ���������� Ȯ��
	bool Authorize(const std::string &inputId,
		const std::string &inputPw, bool &isAdmin) const;


private slots:
	void ExitClicked();
	void LoginClicked();
	void RegisterClicked();
};
