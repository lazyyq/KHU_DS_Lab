#include "QtSearchMusicWindow.h"
#include "QtMainWindow.h"
#include <QMenu>
#include <QAction>
#include <string>

#include "SimpleItem.h"
#include "SortedDoublyIterator.h"
#include "SortedDoublyLinkedList.h"

#define TABLE_COL_TITLE			0
#define TABLE_COL_ARTIST		1
#define TABLE_COL_GENRE			2
#define TABLE_COL_COMPOSER		3

QtSearchMusicWindow::QtSearchMusicWindow(QWidget *parent, SortedList<MusicItem> *masterList,
	SortedDoublyLinkedList<Singer> *singerList, SortedDoublyLinkedList<Genre> *genreList)
	: QMainWindow(parent), mMasterList(masterList), mSingerList(singerList), mGenreList(genreList) {
	ui.setupUi(this);

	qTable = ui.table;

	// Set window title
	this->setWindowTitle("Search");
	// Disable resizing
	this->setFixedSize(this->size());

	// Set table header size
	ui.table->horizontalHeader()->setDefaultSectionSize(
		(ui.table->size().width() - 20) / ui.table->columnCount());

	// Search button dropdown menu
	QMenu *menu = new QMenu("Search music", this);
	QAction *act0 = new QAction("Search by artist name", this);
	QAction *act1 = new QAction("Search by genre", this);
	act0->setObjectName("act0");
	act1->setObjectName("act1");
	connect(act0, SIGNAL(triggered()), this, SLOT(SearchByArtistClicked()));
	connect(act1, SIGNAL(triggered()), this, SLOT(SearchByGenreClicked()));
	menu->addAction(act0);
	menu->addAction(act1);
	ui.btn_search->setMenu(menu);
}

QtSearchMusicWindow::~QtSearchMusicWindow() {}

void QtSearchMusicWindow::SearchClicked() {
	if (mMasterList->IsEmpty()) {
		return;
	}

	int curRow = 0;
	qTable->clearContents();
	qTable->setRowCount(0);
	QString qInput = ui.lineEdit->text();

	// Search for title
	mMasterList->ResetIterator();
	MusicItem music;
	int index = mMasterList->GetNextItem(music);
	while (index > -1) {
		QString qTitle = QString::fromLocal8Bit(music.GetName().c_str());
		// Check if title contains input
		if (qTitle.indexOf(qInput, 0, Qt::CaseInsensitive) > -1) {
			// Title matches, add to list
			QString qArtist = QString::fromLocal8Bit(music.GetArtist().c_str());
			QString qGenre = QString::fromLocal8Bit(music.GetGenre().c_str());
			QString qComposer = QString::fromLocal8Bit(music.GetMelodizer().c_str());
			qTable->setRowCount(curRow + 1);
			qTable->setItem(curRow, TABLE_COL_TITLE, new QTableWidgetItem(qTitle));
			qTable->setItem(curRow, TABLE_COL_ARTIST, new QTableWidgetItem(qArtist));
			qTable->setItem(curRow, TABLE_COL_GENRE, new QTableWidgetItem(qGenre));
			qTable->setItem(curRow, TABLE_COL_COMPOSER, new QTableWidgetItem(qComposer));
			++curRow;
		}
		index = mMasterList->GetNextItem(music);
	}
}

void QtSearchMusicWindow::SearchByArtistClicked() {
	if (mMasterList->IsEmpty() || mSingerList->IsEmpty()) {
		return;
	}

	qTable->clearContents();
	qTable->setRowCount(0);
	QString qSingerName = ui.lineEdit->text();
	// Get singer name to search
	Singer singer;
	singer.SetName(qSingerName.toLocal8Bit().toStdString());

	if (!mSingerList->Get(singer)) {
		return;
	}

	MusicItem music; // Temporary variable to hold info from music master list

	int curRow = 0; // Table current row
	// Iterate through singer's song list
	SortedDoublyIterator<SimpleItem> iter(singer.GetSongList());
	for (SimpleItem song = iter.Next(); iter.NextNotNull(); song = iter.Next()) {
		music.SetId(song.GetId());
		if (mMasterList->Retrieve(music) == -1) {
			continue;
		}

		// Add to table
		QString qTitle = QString::fromLocal8Bit(music.GetName().c_str());
		QString qArtist = QString::fromLocal8Bit(music.GetArtist().c_str());
		QString qGenre = QString::fromLocal8Bit(music.GetGenre().c_str());
		QString qComposer = QString::fromLocal8Bit(music.GetMelodizer().c_str());
		qTable->setRowCount(curRow + 1);
		qTable->setItem(curRow, TABLE_COL_TITLE, new QTableWidgetItem(qTitle));
		qTable->setItem(curRow, TABLE_COL_ARTIST, new QTableWidgetItem(qArtist));
		qTable->setItem(curRow, TABLE_COL_GENRE, new QTableWidgetItem(qGenre));
		qTable->setItem(curRow, TABLE_COL_COMPOSER, new QTableWidgetItem(qComposer));
		++curRow;

	}
}

void QtSearchMusicWindow::SearchByGenreClicked() {
	if (mMasterList->IsEmpty() || mGenreList->IsEmpty()) {
		return;
	}

	qTable->clearContents();
	qTable->setRowCount(0);
	QString qGenreName = ui.lineEdit->text();
	// Get genre name to search
	Genre genre;
	genre.SetName(qGenreName.toLocal8Bit().toStdString());

	if (!mGenreList->Get(genre)) {
		return;
	}

	MusicItem music; // Temporary variable to hold info from music master list

	int curRow = 0; // Table current row
	// Iterate through genre's song list
	SortedDoublyIterator<SimpleItem> iter(genre.GetSongList());
	for (SimpleItem song = iter.Next(); iter.NextNotNull(); song = iter.Next()) {
		music.SetId(song.GetId());
		if (mMasterList->Retrieve(music) == -1) {
			continue;
		}

		// Add to table
		QString qTitle = QString::fromLocal8Bit(music.GetName().c_str());
		QString qArtist = QString::fromLocal8Bit(music.GetArtist().c_str());
		QString qGenre = QString::fromLocal8Bit(music.GetGenre().c_str());
		QString qComposer = QString::fromLocal8Bit(music.GetMelodizer().c_str());
		qTable->setRowCount(curRow + 1);
		qTable->setItem(curRow, TABLE_COL_TITLE, new QTableWidgetItem(qTitle));
		qTable->setItem(curRow, TABLE_COL_ARTIST, new QTableWidgetItem(qArtist));
		qTable->setItem(curRow, TABLE_COL_GENRE, new QTableWidgetItem(qGenre));
		qTable->setItem(curRow, TABLE_COL_COMPOSER, new QTableWidgetItem(qComposer));
		++curRow;

	}
}
