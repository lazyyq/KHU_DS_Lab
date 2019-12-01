#pragma once

#include <QMainWindow>
#include "ui_QtMainWindow.h"

#include <QString>

#include "Application.h"
#include "DoublyLinkedList.h"
#include "PlaylistItem.h"

class QtMainWindow : public QMainWindow {
	Q_OBJECT

public:
	QtMainWindow(QWidget *parent, const std::string &id,
		const bool isAdmin);
	~QtMainWindow();

	void AddMusicToList(const QString &qTitle, const QString &qArtist,
		const QString &qGenre, const QString &qComposer);

signals:
	void closed();

private:
	Ui::QtMainWindow ui;
	bool mQuitProgram = true;

	// UI components
	QTableWidget *qTableMusicList, *qTablePlaylist, *qTableCurPlaylist;

	Application mApp;
	LyricsManager mLyricsManager;
	// Current playlist.
	// Playlist         => User's collection of music to play.
	// Current playlist => Items that are currently on play queue.
	DoublyLinkedList<PlaylistItem> mCurPlaylist;

	std::string mId;
	bool mIsAdmin = false;

	//int mMusicListRowCount = 0; // Music list max row
	//int mPlaylistRowCount = 0; // Playlist max row
	//int mCurPlaylistRowCount = 0; // Current playlist max row

	int mCurPlaylistIndex = 0; // Current index in current playlist
	// Iterator for current playlist. Used to track which music we're playing right now.
	DoublyIterator<PlaylistItem> *mCurPlaylistIter;

	bool isLyricsShown;

	std::string mCurLyrics; // Lyrics fetched from web.

	void closeEvent(QCloseEvent *event);

	// Tasks to do when program finishes
	void FinishProgram();

	// Refresh music list table
	void RefreshMusicList();

	// Refresh playlist table
	void RefreshPlaylist();

	// Refresh current playlist table
	void RefreshCurPlaylist();

	// Play music (Display music title, artist, lyrics on screen)
	void Play(PlaylistItem &item, const int index);

	// Play previous music
	void PlayPrev();

	// Play next music
	void PlayNext();

private slots:
	void LogoutClicked();
	void AddMusicPopup();
	void MusicCellDoubleClicked(int row, int col);
	void PlaylistCellDoubleClicked(int row, int col);
	void CurPlaylistCellDoubleClicked(int row, int col);
	void ShowLyricsClicked();

	void PlayerPlayClicked();
	void PlayerPrevClicked();
	void PlayerNextClicked();

	// Add music from file
	void AddFromFileClicked();
	// Add music from folder
	void AddFromFolderClicked();
	// Search music on web (genius)
	void SearchOnWebClicked();

	// Search music
	void SearchMusicClicked();

	// Remove item from master list
	void RemoveFromMusicListClicked();
	// Remove item from playlist
	void RemoveFromPlaylistClicked();

	// Play from start
	void PlayFromStartClicked();
	// Play in frequency order
	void PlayInFreqOrderClicked();
	// Shuffle
	void PlayShuffleClicked();

	// Get lyrics from web
	void SearchForLyricsClicked();
	// Save fetched lyrics to file
	void SaveLyricsClicked();
};
