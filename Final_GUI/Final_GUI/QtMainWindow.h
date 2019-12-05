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
		const bool isAdmin, const bool isPlaylistLocked);
	~QtMainWindow();

	void AddMusicToList(const QString &qTitle, const QString &qArtist,
		const QString &qGenre, const QString &qComposer);

	void SetPlaylist(const std::string &username);

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

	// Playlist. Might be current user's, or other user's playlist if we're
	// exploring other users' playlists.
	SortedDoublyLinkedList<PlaylistItem> *mPlaylist;

	std::string mId;
	bool mIsAdmin = false;

	//int mMusicListRowCount = 0; // Music list max row
	//int mPlaylistRowCount = 0; // Playlist max row
	//int mCurPlaylistRowCount = 0; // Current playlist max row

	int mCurPlaylistIndex = 0; // Current index in current playlist
	// Iterator for current playlist. Used to track which music we're playing right now.
	DoublyIterator<PlaylistItem> *mCurPlaylistIter;

	bool mIsPlaylistLocked; // Is our playlist invisible to others?
	bool isLyricsShown;

	std::string mCurLyrics; // Lyrics fetched from web.

	// Are we listening to our own playlist, or is it someone else's?
	bool mMyPlaylist = true;

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

	// Set if we're using our playlist, or other user's playlist.
	// true for ours, false if not.
	// If false, disable certain functionalities that may modify the playlist.
	void SetPlaylistState(const bool isOurs);

private slots:
	void LogoutClicked();
	void AddMusicPopup();
	void PlaylistCellDoubleClicked(int row, int col);
	void CurPlaylistCellDoubleClicked(int row, int col);
	void ShowLyricsClicked();

	// Music list cell has changed(Music updated)
	void MusicListCellChanged(int row, int col);

	void PlayerPlayClicked();
	void PlayerPrevClicked();
	void PlayerNextClicked();

	// Add music from music list to playlist
	void MusicListToPlaylistClicked();

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
	// Recommend
	void PlayRecommendClicked();

	// Get lyrics from web
	void SearchForLyricsClicked();
	// Save fetched lyrics to file
	void SaveLyricsClicked();

	// Lock/unlock user playlist
	void LockPlaylistClicked();

	// Explore playlist / Get back to our playlist
	void ExplorePlaylistClicked();
};
