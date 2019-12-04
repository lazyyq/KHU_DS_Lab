#pragma once

#include <QMainWindow>
#include "ui_QtSelectPlaylistWindow.h"

#include "PlaylistItem.h"
#include "SortedDoublyLinkedList.h"

class QtSelectPlaylistWindow : public QMainWindow {
	Q_OBJECT

public:
	QtSelectPlaylistWindow(QWidget *parent, const std::string &id,
		SortedDoublyLinkedList<PlaylistItem> *playlist);
	~QtSelectPlaylistWindow();

private:
	Ui::QtSelectPlaylistWindow ui;

	SortedDoublyLinkedList<PlaylistItem> *mPlaylist;

private slots:
	void PlaylistSelected(int row, int col);
};
