#include "QtSelectPlaylistWindow.h"
#include "QtMainWindow.h"
#include <QString>
#include <QMessageBox>

#include <iostream>
#include <string>
#include <fstream>
#include <filesystem>
#include <json/json.h>

#include "utils/StringUtils.h"

namespace fs = std::filesystem;

QtSelectPlaylistWindow::QtSelectPlaylistWindow(QWidget *parent,
	const std::string &_id, SortedDoublyLinkedList<PlaylistItem> *playlist)
	: QMainWindow(parent) {
	ui.setupUi(this);

	// Set window title
	this->setWindowTitle("Select a playlist");
	// Disable resizing
	this->setFixedSize(this->size());

	// Set table column size
	ui.table->horizontalHeader()->setDefaultSectionSize(
		(ui.table->size().width() - 20) / ui.table->columnCount());

	// Display user list with playlist unlocked
	int row = 0;
	for (const fs::directory_entry &entry : fs::directory_iterator("data/user")) {
		if (!entry.is_directory()) {
			continue;
		}
		// Get account info
		std::string accountinfo = entry.path().string() + "/accountinfo.json";
		ifstream ifs(accountinfo);
		if (!ifs) {
			continue;
		}
		Json::Value json;
		ifs >> json;
		ifs.close();
		if (json.get("IsPlaylistLocked", true).asBool()) {
			// This user has his playlist locked, ignore.
			continue;
		}
		// Add id to table
		std::string id = stringutils::Utf8ToAnsi(json.get("ID", "").asString());
		if (_id.compare(id) == 0) {
			// This is my playlist, skip
			continue;
		}
		QString qId = QString::fromLocal8Bit(id.c_str());
		ui.table->setRowCount(row + 1);
		ui.table->setItem(row, 0, new QTableWidgetItem(qId));
		++row;
	}

}

QtSelectPlaylistWindow::~QtSelectPlaylistWindow() {}

void QtSelectPlaylistWindow::PlaylistSelected(int row, int col) {
	// Get selected username
	QString qUsername = ui.table->item(row, 0)->text();
	std::string username = qUsername.toLocal8Bit().toStdString();
	((QtMainWindow *)parent())->SetPlaylist(username);
	this->close();
}
