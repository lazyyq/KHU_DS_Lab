#include "QtAddMusicManually.h"
#include "QtMainWindow.h"
#include <QString>

QtAddMusicManually::QtAddMusicManually(QWidget *parent)
	: QMainWindow(parent) {
	ui.setupUi(this);
	// Disable resizing
	//this->statusBar()->setSizeGripEnabled(false);
	this->setFixedSize(this->size());
}

QtAddMusicManually::~QtAddMusicManually() {}

void QtAddMusicManually::AddDone() {
	//std::string title = ui.lineEdit_title->text().toLocal8Bit().constData();
	//std::string artist = ui.lineEdit_artist->text().toLocal8Bit().constData();
	//std::string genre = ui.lineEdit_genre->text().toLocal8Bit().constData();
	//std::string composer = ui.lineEdit_composer->text().toLocal8Bit().constData();
	// Get records from lineedit
	QString title = ui.lineEdit_title->text();
	QString artist = ui.lineEdit_artist->text();
	QString genre = ui.lineEdit_genre->text();
	QString composer = ui.lineEdit_composer->text();
	if (title.length() == 0) title = "Unknown";
	if (artist.length() == 0) artist = "Unknown";
	if (genre.length() == 0) genre = "Unknown";
	if (composer.length() == 0) composer = "Unknown";
	// Add
	((QtMainWindow *)parent())->AddMusicToList(title, artist, genre, composer);
	this->close();
}

void QtAddMusicManually::AddCancel() {
	this->close();
}
