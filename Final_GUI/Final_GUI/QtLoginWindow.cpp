#include "QtLoginWindow.h"
#include <QtWidgets/QApplication>
#include <QCloseEvent>
#include <QMessageBox>

#include <fstream>
#include <filesystem>

#include "../utils/StringUtils.h"
#include "../utils/Utils.h"

#define SETTINGS_FILENAME		"data/settings.json"
#define KEY_IS_FIRST_LAUNCH		"IsFirstLaunch"
#define KEY_IS_ADMIN			"IsAdmin"
#define KEY_IS_PLAYLIST_LOCKED	"IsPlaylistLocked"
#define KEY_USER_ID				"ID"
#define KEY_USER_PW				"PW"

using namespace std;
using namespace utils;
using namespace stringutils;

QtLoginWindow::QtLoginWindow(QWidget *parent)
	: QMainWindow(parent) {
	ui.setupUi(this);
	// Set window title
	this->setWindowTitle("Login");
	// Disable resizing
	this->statusBar()->setSizeGripEnabled(false);
	this->setFixedSize(this->size());
}

QtLoginWindow::~QtLoginWindow() {}

void QtLoginWindow::closeEvent(QCloseEvent *event) {
	event->accept();
	if (mQuitProgram) {
		qApp->quit();
	} else {
		mQuitProgram = true;
	}
}

// Check if this is first launch
bool QtLoginWindow::IsFirstLaunch() const {
	ifstream ifs(SETTINGS_FILENAME);
	// Consider as first launch if settings file is not found
	if (!ifs || ifs.peek() == EOF) {
		if (ifs.is_open()) {
			ifs.close();
		}
		return true;
	}
	Json::Value json;
	ifs >> json;
	bool isFirstLaunch = json.get(KEY_IS_FIRST_LAUNCH, true).asBool();
	if (ifs.is_open()) {
		ifs.close();
	}
	return isFirstLaunch;
}

// Check user id and password
bool QtLoginWindow::Authorize(const string &inputId, const string &inputPw,
	bool &isAdmin, bool &isPlaylistLocked) const {
	// Get user account info 
	const string path = "data/user/" + inputId + "/accountinfo.json";
	ifstream ifs(path);
	if (!ifs || ifs.peek() == EOF) {
		//cout << "\n\tFailed to open account info file. (" << path << ")\n";
		if (ifs.is_open()) {
			ifs.close();
		}
		return false;
	}
	// Get id & password from file
	Json::Value value;
	ifs >> value;
	const string id = Utf8ToAnsi(value.get(KEY_USER_ID, "").asString());
	const string pw = Utf8ToAnsi(value.get(KEY_USER_PW, "").asString());
	// Compare id & password
	if (inputId.compare(id) == 0 && inputPw.compare(pw) == 0) {
		isAdmin = value.get(KEY_IS_ADMIN, false).asBool();
		isPlaylistLocked = value.get(KEY_IS_PLAYLIST_LOCKED, true).asBool();
		return true;
	}
	return false;
}

void QtLoginWindow::ExitClicked() {
	qApp->quit();
}

void QtLoginWindow::LoginClicked() {
	// ID field cannot be empty
	if (ui.lineEdit_ID->text().length() == 0) {
		QMessageBox::critical(this, "Error", "ID field cannot be empty!");
		//msg.show();
		return;
	}

	QString qid = ui.lineEdit_ID->text(), qpw = ui.lineEdit_PW->text();
	string id = qid.toLocal8Bit().toStdString(), pw = qpw.toLocal8Bit().toStdString();
	bool isAdmin = false, isPlaylistLocked = true;
	// Check if id and pw match
	if (Authorize(id, pw, isAdmin, isPlaylistLocked)) {
		// Start program
		mQuitProgram = false;
		mainWindow = new QtMainWindow(this, id, isAdmin, isPlaylistLocked);
		mainWindow->show();
		this->close();
	} else {
		QMessageBox::critical(this, "Error", "Nonexistent ID or wrong password!");
	}
}

void QtLoginWindow::RegisterClicked() {
	// ID field cannot be empty
	if (ui.lineEdit_ID->text().length() == 0) {
		QMessageBox::critical(this, "Error", "ID field cannot be empty!");
		return;
	}

	QString qid = ui.lineEdit_ID->text(), qpw = ui.lineEdit_PW->text();
	string id = qid.toLocal8Bit().toStdString(), pw = qpw.toLocal8Bit().toStdString();

	{
	// Check if id already exists
		string path = "data/user/" + id;
		if (filesystem::exists(path) && filesystem::is_directory(path)) { // already exists
			QMessageBox::critical(this, "Error", "ID already exists!");
			return;
		}
	}

	Json::Value account;
	account[KEY_USER_ID] = AnsiToUtf8(id);
	account[KEY_USER_PW] = AnsiToUtf8(pw);
	account[KEY_IS_ADMIN] = IsFirstLaunch();

	// Write account info to file
	string accountinfo = "data/user/" + id + "/accountinfo.json";

	// Create directory first if not exists
	filesystem::path path = filesystem::current_path().string() +
		string("/") + accountinfo;
	if (!filesystem::exists(path.parent_path())) {
		try {
			filesystem::create_directories(path.parent_path());
		} catch (std::filesystem::filesystem_error & e) {
			QMessageBox::critical(this, "Error", "Fs Error");
			return;
		}
	}
	// Write to file
	ofstream ofs(accountinfo);
	if (!ofs) {
		QMessageBox::critical(this, "Error", "Account info write error");
		return;
	}
	ofs << account;
	ofs.close();

	if (IsFirstLaunch()) {
		// Write record of first launch
		ofstream ofs(SETTINGS_FILENAME);
		if (!ofs) {
			return;
		}
		Json::Value value;
		value[KEY_IS_FIRST_LAUNCH] = false;
		ofs << value;
		if (ofs.is_open()) {
			ofs.close();
		}
		QMessageBox::information(this, "Successfully registered", "Successfully added admin ID!");
	} else {
		QMessageBox::information(this, "Successfully registered", "Successfully added ID!");
	}
}
