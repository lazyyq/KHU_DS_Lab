#pragma once

#include <QMainWindow>
#include "ui_QtSearchMusicWindow.h"

#include "Genre.h"
#include "MusicItem.h"
#include "Singer.h"
#include "SortedDoublyLinkedList.h"
#include "SortedList.h"

class QtSearchMusicWindow : public QMainWindow {
	Q_OBJECT

public:
	QtSearchMusicWindow(QWidget *parent, SortedList<MusicItem> *masterList,
		SortedDoublyLinkedList<Singer> *singerList,
		SortedDoublyLinkedList<Genre> *genreList);
	~QtSearchMusicWindow();

private:
	Ui::QtSearchMusicWindow ui;
	QTableWidget *qTable;

	SortedList<MusicItem> *mMasterList;
	SortedDoublyLinkedList<Singer> *mSingerList;
	SortedDoublyLinkedList<Genre> *mGenreList;

private slots:
	// Search button clicked
	void SearchClicked();

	void SearchByArtistClicked();
	void SearchByGenreClicked();
};
