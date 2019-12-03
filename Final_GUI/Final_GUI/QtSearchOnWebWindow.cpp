#include "QtSearchOnWebWindow.h"
#include "QtMainWindow.h"
#include <QMessageBox>
#include <QString>
#include <QTableWidget>

#include <string>
#include <json/json.h>

#include "GeniusAccessToken.h"
#include "http/HttpRequest.h"

#define TABLE_COL_TITLE			0
#define TABLE_COL_ARTIST		1
#define TABLE_COL_GENRE			2
#define TABLE_COL_COMPOSER		3

QtSearchOnWebWindow::QtSearchOnWebWindow(QWidget *parent)
	: QMainWindow(parent) {
	ui.setupUi(this);

	// Disable resizing
	this->setFixedSize(this->size());

	// Set table header size
	ui.table->horizontalHeader()->setDefaultSectionSize(
		(ui.table->size().width() - 20) / ui.table->columnCount());
}

QtSearchOnWebWindow::~QtSearchOnWebWindow() {}

void QtSearchOnWebWindow::SearchClicked() {
	// Check if input is empty
	if (ui.lineEdit_title->text().length() == 0) {
		QMessageBox::critical(this, "Error", "Title field cannot be empty!");
		return;
	}

	// Empty table
	ui.table->clearContents();
	ui.table->setRowCount(0);

	// Get input info
	const QString qTitle = ui.lineEdit_title->text(),
		qArtist = ui.lineEdit_artist->text();
	const std::string title = qTitle.toLocal8Bit().toStdString(),
		artist = qArtist.toLocal8Bit().toStdString();

	// Send request to genius
	HttpRequest req;
	const std::string searchApi = "https://api.genius.com/search";
	req.SetUrl(searchApi);
	req.AddParam("q", artist + " " + title);
	req.AddParam("access_token", GENIUS_ACCESS_TOKEN);

	std::string result;
	int resultCode;
	req.SendGetRequest(result, resultCode);
	if (resultCode != 200) {
		QMessageBox::critical(this, "Error", "Error from genius!");
		return;
	}

	// Parse response
	Json::Value json;
	JSONCPP_STRING err;
	Json::CharReaderBuilder builder;
	Json::CharReader *reader = builder.newCharReader();
	if (!reader->parse(result.c_str(),
		result.c_str() + result.length(), &json, &err)) {
		QMessageBox::critical(this, "Error", "Error while parsing JSON!");
		return;
	}

	// Store search results
	Json::Value hits = json["response"]["hits"];
	// Check if result is empty
	if (hits.size() == 0) {
		QMessageBox::critical(this, "Oops", "No search results!");
		return;
	}

	int curRow = 0;
	for (Json::Value entry : hits) {
		// Check if result type is song
		if (entry.get("type", "").asString().compare("song") != 0) {
			continue;
		}
		// Add each item to table
		const std::string title = entry["result"].get("title", "Unknown").asString();
		const std::string artist = entry["result"]["primary_artist"].get("name", "Unknown").asString();

		const QString qTitle = QString::fromStdString(title.c_str());
		const QString qArtist = QString::fromStdString(artist.c_str());
		// We cannot get genre or composer
		const QString qGenre = "Unknown", qComposer = "Unknown";
		// Set table
		ui.table->setRowCount(curRow + 1);
		ui.table->setItem(curRow, TABLE_COL_TITLE, new QTableWidgetItem(qTitle));
		ui.table->setItem(curRow, TABLE_COL_ARTIST, new QTableWidgetItem(qArtist));
		ui.table->setItem(curRow, TABLE_COL_GENRE, new QTableWidgetItem(qGenre));
		ui.table->setItem(curRow, TABLE_COL_COMPOSER, new QTableWidgetItem(qComposer));
		++curRow;
	}

}

void QtSearchOnWebWindow::TableCellDoubleClicked(int row, int col) {
	// Get selected music info from table
	QString qTitle = ui.table->item(row, TABLE_COL_TITLE)->text();
	QString qArtist = ui.table->item(row, TABLE_COL_ARTIST)->text();
	QString qGenre = ui.table->item(row, TABLE_COL_GENRE)->text();
	QString qComposer = ui.table->item(row, TABLE_COL_COMPOSER)->text();
	// Add to list
	((QtMainWindow *)parent())->AddMusicToList(qTitle, qArtist, qGenre, qComposer);
}
