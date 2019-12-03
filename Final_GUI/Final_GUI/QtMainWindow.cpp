#include "QtMainWindow.h"
#include "QtLoginWindow.h"
#include "QtAddMusicManually.h"
#include "QtSearchMusicWindow.h"
#include "QtSearchOnWebWindow.h"
#include <QCloseEvent>
#include <QMenu>
#include <QWidgetAction>
#include <QString>

#include <string>

#include "LyricsManager.h"
#include "PlaylistItem.h"
#include "DoublyIterator.h"
#include "SortedDoublyIterator.h"

#define WINDOW_SIZE_LYRICS_SHOWN	1591, 627
#define WINDOW_SIZE_LYRICS_HIDDEN	1220, 627

#define MUSIC_LIST_COL_TITLE		0
#define MUSIC_LIST_COL_ARTIST		1
#define MUSIC_LIST_COL_GENRE		2
#define MUSIC_LIST_COL_COMPOSER		3
#define MUSIC_LIST_COL_ID			4

#define PLAYLIST_COL_TITLE			0
#define PLAYLIST_COL_ARTIST			1
#define PLAYLIST_COL_PLAYED_TIMES	2

using namespace std;

QtMainWindow::QtMainWindow(QWidget *parent, const string &id,
	const bool isAdmin)
	: QMainWindow(parent), mId(id), mIsAdmin(isAdmin), isLyricsShown(false),
	mCurPlaylistIter(nullptr) {
	ui.setupUi(this);
	// Disable resizing
	this->statusBar()->setSizeGripEnabled(false);
	this->setFixedSize(WINDOW_SIZE_LYRICS_HIDDEN);

	// UI components
	qTableMusicList = ui.table_musiclist;
	qTablePlaylist = ui.table_playlist;
	qTableCurPlaylist = ui.table_playlist_current;

	// Enable music list editing only for admin
	if (!mIsAdmin) {
		ui.btn_musicList_add->setEnabled(false);
		ui.btn_musicList_remove->setEnabled(false);
	}

	// Set music list column size
	qTableMusicList->horizontalHeader()->setDefaultSectionSize(
		(qTableMusicList->size().width() - 20) / qTableMusicList->columnCount());
	qTablePlaylist->horizontalHeader()->setDefaultSectionSize(
		(qTablePlaylist->size().width() - 20) / qTablePlaylist->columnCount());
	qTableCurPlaylist->horizontalHeader()->setDefaultSectionSize(
		(qTableCurPlaylist->size().width() - 20) / qTableCurPlaylist->columnCount());

	// Play button
	connect(ui.btn_player_play, SIGNAL(clicked()), this, SLOT(PlayerPlayClicked()));
	connect(ui.btn_player_prev, SIGNAL(clicked()), this, SLOT(PlayerPrevClicked()));
	connect(ui.btn_player_next, SIGNAL(clicked()), this, SLOT(PlayerNextClicked()));

	// Search button
	connect(ui.btn_searchMusic, SIGNAL(clicked()), this, SLOT(SearchMusicClicked()));

	// Dropdown menu for add music button
	{
		QMenu *menu = new QMenu("Add music", this);
		QAction *act0 = new QAction("Add from file", this);
		QAction *act1 = new QAction("Add from folder", this);
		QAction *act2 = new QAction("Search on web", this);
		act0->setObjectName("act0");
		act1->setObjectName("act1");
		act1->setObjectName("act2");
		connect(act0, SIGNAL(triggered()), this, SLOT(AddFromFileClicked()));
		connect(act1, SIGNAL(triggered()), this, SLOT(AddFromFolderClicked()));
		connect(act2, SIGNAL(triggered()), this, SLOT(SearchOnWebClicked()));
		menu->addAction(act0);
		menu->addAction(act1);
		menu->addAction(act2);
		ui.btn_musicList_add->setMenu(menu);
	}

	// Dropdown menu for play button
	{
		QMenu *menu = new QMenu("Play options", this);
		QAction *act0 = new QAction("Play from start", this);
		QAction *act1 = new QAction("Play in frequency order", this);
		QAction *act2 = new QAction("Shuffle", this);
		act0->setObjectName("act0");
		act1->setObjectName("act1");
		act1->setObjectName("act2");
		connect(act0, SIGNAL(triggered()), this, SLOT(PlayFromStartClicked()));
		connect(act1, SIGNAL(triggered()), this, SLOT(PlayInFreqOrderClicked()));
		connect(act2, SIGNAL(triggered()), this, SLOT(PlayShuffleClicked()));
		menu->addAction(act0);
		menu->addAction(act1);
		menu->addAction(act2);
		ui.btn_playlist_play->setMenu(menu);
	}

	// Display login info
	if (mIsAdmin) {
		ui.label_loginInfo->setText(QString::fromLocal8Bit(
			std::string("Now logged in as: " + mId + " (ADMIN)").c_str()));
	} else {
		ui.label_loginInfo->setText(QString::fromLocal8Bit(
			std::string("Now logged in as: " + mId).c_str()));
	}

	// Run app
	mApp.Run(mId, mIsAdmin);

	// Display music master list
	RefreshMusicList();
	// Display playlist
	RefreshPlaylist();
}

QtMainWindow::~QtMainWindow() {
	if (mCurPlaylistIter) {
		delete mCurPlaylistIter;
	}
}

void QtMainWindow::AddMusicToList(const QString &qTitle, const QString &qArtist,
	const QString &qGenre, const QString &qComposer) {
	// Add to list
	string title = qTitle.toLocal8Bit().toStdString();
	string artist = qArtist.toLocal8Bit().toStdString();
	string genre = qGenre.toLocal8Bit().toStdString();
	string composer = qComposer.toLocal8Bit().toStdString();
	MusicItem data;
	data.SetRecord("", title, composer, artist, genre);
	string id = MusicItem::GenerateMusicId(data);
	data.SetId(id);
	mApp.AddMusic(data);

	// Refresh
	RefreshMusicList();

	/*qTableMusicList->setRowCount(mMusicListRowCount + 1);
	qTableMusicList->setItem(mMusicListRowCount, MUSIC_LIST_COL_TITLE, new QTableWidgetItem(title));
	qTableMusicList->setItem(mMusicListRowCount, MUSIC_LIST_COL_ARTIST, new QTableWidgetItem(artist));
	qTableMusicList->setItem(mMusicListRowCount, MUSIC_LIST_COL_GENRE, new QTableWidgetItem(genre));
	qTableMusicList->setItem(mMusicListRowCount, MUSIC_LIST_COL_COMPOSER, new QTableWidgetItem(composer));
	++mMusicListRowCount;*/
}

void QtMainWindow::closeEvent(QCloseEvent *event) {
	event->accept();
	FinishProgram();
	if (!mQuitProgram) {
		mQuitProgram = true;
		((QtLoginWindow *)parent())->show();
	} else {
		qApp->quit();
	}
}

void QtMainWindow::FinishProgram() {
	mApp.Save(); // Save lists
}

void QtMainWindow::RefreshMusicList() {
	// Clear table first
	qTableMusicList->clearContents();
	qTableMusicList->setRowCount(0);
	int mMusicListRowCount = 0;

	// Add music items from master list
	MusicItem data;
	mApp.mMasterList.ResetIterator(); // Reset pointer
	int curIndex = mApp.mMasterList.GetNextItem(data);
	while (curIndex > -1) {
		++mMusicListRowCount;
		qTableMusicList->setRowCount(mMusicListRowCount);
		QString qTitle = QString::fromLocal8Bit(data.GetName().c_str());
		QString qArtist = QString::fromLocal8Bit(data.GetArtist().c_str());
		QString qGenre = QString::fromLocal8Bit(data.GetGenre().c_str());
		QString qComposer = QString::fromLocal8Bit(data.GetMelodizer().c_str());
		QString qId = QString::fromLocal8Bit(data.GetId().c_str());
		qTableMusicList->setItem(curIndex, MUSIC_LIST_COL_TITLE, new QTableWidgetItem(qTitle));
		qTableMusicList->setItem(curIndex, MUSIC_LIST_COL_ARTIST, new QTableWidgetItem(qArtist));
		qTableMusicList->setItem(curIndex, MUSIC_LIST_COL_GENRE, new QTableWidgetItem(qGenre));
		qTableMusicList->setItem(curIndex, MUSIC_LIST_COL_COMPOSER, new QTableWidgetItem(qComposer));
		qTableMusicList->setItem(curIndex, MUSIC_LIST_COL_ID, new QTableWidgetItem(qId));
		curIndex = mApp.mMasterList.GetNextItem(data);
	}
}

void QtMainWindow::RefreshPlaylist() {
	// Clear playlist table first
	qTablePlaylist->clearContents();
	qTablePlaylist->setRowCount(0);
	int rowCount = 0;

	// Add items
	SortedDoublyIterator<PlaylistItem> iter(mApp.mPlayer->mPlaylist);
	for (PlaylistItem item = iter.Next(); iter.NextNotNull(); item = iter.Next()) {
		qTablePlaylist->setRowCount(rowCount + 1);
		// Get music with playlistitem info
		MusicItem music;
		music.SetId(item.GetId());
		if (mApp.mMasterList.Retrieve(music) == -1) {
			// Music not found in master list
			continue;
		}
		QString qTitle = QString::fromLocal8Bit(music.GetName().c_str());
		QString qArtist = QString::fromLocal8Bit(music.GetArtist().c_str());
		QString qPlayedTimes = QString::number(item.GetPlayedTimes());
		qTablePlaylist->setItem(rowCount, PLAYLIST_COL_TITLE, new QTableWidgetItem(qTitle));
		qTablePlaylist->setItem(rowCount, PLAYLIST_COL_ARTIST, new QTableWidgetItem(qArtist));
		qTablePlaylist->setItem(rowCount, PLAYLIST_COL_PLAYED_TIMES, new QTableWidgetItem(qPlayedTimes));
		++rowCount;
	}
}

void QtMainWindow::RefreshCurPlaylist() {
	// Clear playlist table first
	qTableCurPlaylist->clearContents();
	qTableCurPlaylist->setRowCount(0);
	int rowCount = 0;

	// Add items
	DoublyIterator<PlaylistItem> iter(mCurPlaylist);
	for (PlaylistItem item = iter.Next(); iter.NextNotNull(); item = iter.Next()) {
		qTableCurPlaylist->setRowCount(rowCount + 1);
		// Get music with playlistitem info
		MusicItem music;
		music.SetId(item.GetId());
		if (mApp.mMasterList.Retrieve(music) == -1) {
			// Music not found in master list
			continue;
		}
		QString qTitle = QString::fromLocal8Bit(music.GetName().c_str());
		QString qArtist = QString::fromLocal8Bit(music.GetArtist().c_str());
		qTableCurPlaylist->setItem(rowCount, PLAYLIST_COL_TITLE, new QTableWidgetItem(qTitle));
		qTableCurPlaylist->setItem(rowCount, PLAYLIST_COL_ARTIST, new QTableWidgetItem(qArtist));
		++rowCount;
	}
}

void QtMainWindow::Play(PlaylistItem &item, const int index) {
	mCurPlaylistIndex = index;
	MusicItem music;
	music.SetId(item.GetId());
	if (mApp.mMasterList.Retrieve(music) == -1) {
		// Music doesn't exist in master list
		return;
	}

	// Set title & artist
	const QString qTitle = QString::fromLocal8Bit(music.GetName().c_str());
	const QString qArtist = QString::fromLocal8Bit(music.GetArtist().c_str());
	ui.label_playerTitle->setText(qTitle);
	ui.label_playerArtist->setText(qArtist);

	// Set lyrics if exists
	string lyrics;
	if (mLyricsManager.GetLyrics(music, lyrics)) {
		// Lyrics exists
		QString qLyrics = QString::fromStdString(lyrics);
		ui.text_lyrics->setText(qLyrics);
	} else {
		// Lyrics not found
		ui.text_lyrics->setText("Lyrics not found!");
	}
	// Disable save lyrics button
	ui.btn_saveLyrics->setEnabled(false);

	// Update original playlist
	mApp.mPlayer->mPlaylist.Get(item);
	item.IncreasePlayedTimes();
	mApp.mPlayer->mPlaylist.Replace(item);
	RefreshPlaylist();
}

void QtMainWindow::PlayPrev() {
	if (mCurPlaylist.IsEmpty()) {
		return;
	}

	PlaylistItem item;
	// Check if we're at the beginning of playlist
	if (mCurPlaylistIndex == 0) {
		// Move to last
		mCurPlaylistIter->PointerToLast();
		item = mCurPlaylistIter->Prev();
		mCurPlaylistIndex = mCurPlaylist.GetLength() - 1;
	} else {
		// Previous music
		item = mCurPlaylistIter->Prev();
		--mCurPlaylistIndex;
	}
	Play(item, mCurPlaylistIndex);
}

void QtMainWindow::PlayNext() {
	if (mCurPlaylist.IsEmpty()) {
		return;
	}

	PlaylistItem item;
	// Check if we're at the end of playlist
	if (mCurPlaylistIndex == mCurPlaylist.GetLength() - 1) {
		// Move to first
		mCurPlaylistIter->ResetPointer();
		item = mCurPlaylistIter->Next();
		mCurPlaylistIndex = 0;
	} else {
		// Next music
		item = mCurPlaylistIter->Next();
		++mCurPlaylistIndex;
	}
	Play(item, mCurPlaylistIndex);
}

void QtMainWindow::LogoutClicked() {
	mQuitProgram = false;
	this->close();
}

void QtMainWindow::AddMusicPopup() {
	QtAddMusicManually *a = new QtAddMusicManually(this);
	a->show();
}

void QtMainWindow::MusicCellDoubleClicked(int row, int col) {
	// Get id of music in chosen row
	const QString qId = qTableMusicList->item(row, MUSIC_LIST_COL_ID)->text();
	const string id = qId.toLocal8Bit().toStdString();

	// Add to player
	mApp.mPlayer->AddToPlaylist(id);
	RefreshPlaylist();

	/*qTableMusicList_2->setRowCount(tmp_musicrow + 1);
	for (int i = 0, len = qTableMusicList_2->columnCount(); i < len; ++i) {
		if (qTableMusicList->item(row, i)) {
			QString qstr = qTableMusicList->item(row, i)->text();
			qTableMusicList_2->setItem(tmp_musicrow, i, new QTableWidgetItem(qstr));
		}
	}
	++tmp_musicrow;*/
}

// ????
void QtMainWindow::PlaylistCellDoubleClicked(int row, int col) {
	//// row > 0
	//// Get selected playlist item from playlist
	//SortedDoublyIterator<PlaylistItem> iter(mApp.mPlayer->mPlaylist);
	//PlaylistItem item = iter.Next();
	//for (int i = 0; i < row; ++i) {
	//	item = iter.Next();
	//}
	//
	//// Add to current playlist
	//mCurPlaylist.Add(item);
	//RefreshCurPlaylist();
}

void QtMainWindow::CurPlaylistCellDoubleClicked(int row, int col) {
	// Get selected playlist item from current playlist
	if (!mCurPlaylistIter) {
		mCurPlaylistIter = new DoublyIterator<PlaylistItem>(mCurPlaylist);
	}
	mCurPlaylistIter->ResetPointer();
	PlaylistItem item = mCurPlaylistIter->Next();
	for (int i = 0; i < row; ++i) {
		item = mCurPlaylistIter->Next();
	}
	mCurPlaylistIndex = row;
	Play(item, mCurPlaylistIndex);
}

void QtMainWindow::ShowLyricsClicked() {
	if (isLyricsShown) {
		isLyricsShown = false;
		ui.btn_showLyrics->setText("Show lyrics >>");
		this->setFixedSize(WINDOW_SIZE_LYRICS_HIDDEN);
	} else {
		isLyricsShown = true;
		ui.btn_showLyrics->setText("Hide lyrics <<");
		this->setFixedSize(WINDOW_SIZE_LYRICS_SHOWN);
	}
}

void QtMainWindow::PlayerPlayClicked() {
	if (mCurPlaylist.IsEmpty()) {
		return;
	}
	PlaylistItem item;
	mCurPlaylist.GetItemAt(item, mCurPlaylistIndex);
	Play(item, mCurPlaylistIndex);
}

void QtMainWindow::PlayerPrevClicked() {
	PlayPrev();
}

void QtMainWindow::PlayerNextClicked() {
	PlayNext();
}

void QtMainWindow::AddFromFileClicked() {
	mApp.AddMusicFromFile();
	RefreshMusicList();
}

void QtMainWindow::AddFromFolderClicked() {
	mApp.AddMusicFromFolder();
	RefreshMusicList();
}

void QtMainWindow::SearchOnWebClicked() {
	QtSearchOnWebWindow *window = new QtSearchOnWebWindow(this);
	window->show();

}

void QtMainWindow::SearchMusicClicked() {
	QtSearchMusicWindow *window =
		new QtSearchMusicWindow(this, &mApp.mMasterList, &mApp.mSingerList, &mApp.mGenreList);
	window->show();
}

void QtMainWindow::RemoveFromMusicListClicked() {
	// Get selected rows in playlist
	QModelIndexList selection = qTableMusicList->selectionModel()->selectedRows();
	// Iterate backwards, since we do not want to mess with the ordering.
	for (int i = selection.count() - 1; i >= 0; --i) {
		// Delete items in selected rows
		int row = selection.at(i).row();
		mApp.mMasterList.ResetIterator();
		MusicItem music;
		for (int j = 0; j < row + 1; ++j) {
			mApp.mMasterList.GetNextItem(music);
		}
		mApp.mMasterList.Delete(music);

		// Delete from other lists as well, code copied from Application.cpp
		{
			SimpleItem simple; // ���� ����Ʈ�� �帣 ����Ʈ �˻���
			string id = music.GetId(), artistName = music.GetArtist(),
				genreName = music.GetGenre();;
			simple.SetId(id);

			// ������ ���� ���� �̸� �޾ƿ���
			Singer singer;
			singer.SetName(artistName);

			// �ش� ������ �� ����Ʈ������ ����
			if (mApp.mSingerList.Get(singer)) {
				singer.RemoveSong(simple);
				mApp.mSingerList.Replace(singer);
			}

			// ������ ���� �帣 �̸� �޾ƿ���
			Genre genre;
			genre.SetName(genreName);

			// �ش� ������ �帣 ����Ʈ������ ����
			if (mApp.mGenreList.Get(genre)) {
				genre.RemoveSong(simple);
				mApp.mGenreList.Replace(genre);
			}
		}

		SortedDoublyIterator<PlaylistItem> iter(mApp.mPlayer->mPlaylist);
		for (PlaylistItem item = iter.Next(); iter.NextNotNull(); item = iter.Next()) {
			if (item.GetId().compare(music.GetId()) == 0) {
				mApp.mPlayer->mPlaylist.Delete(item);
				mCurPlaylist.Delete(item);
				iter.ResetPointer();
			}
		}
		RefreshMusicList();
		RefreshPlaylist();
		RefreshCurPlaylist();
	}
}

void QtMainWindow::RemoveFromPlaylistClicked() {
	// Get selected rows in playlist
	QModelIndexList selection = qTablePlaylist->selectionModel()->selectedRows();
	// Iterate backwards, since we do not want to mess with the ordering.
	for (int i = selection.count() - 1; i >= 0; --i) {
		// Delete items in selected rows
		int row = selection.at(i).row();
		PlaylistItem item;
		mApp.mPlayer->mPlaylist.GetItemAt(item, row);
		mApp.mPlayer->mPlaylist.Delete(item);
		mCurPlaylist.DeleteAll(item);
	}
	RefreshPlaylist();
	RefreshCurPlaylist();
}

void QtMainWindow::PlayFromStartClicked() {
	if (mApp.mPlayer->mPlaylist.IsEmpty()) {
		return;
	}

	mCurPlaylist.MakeEmpty();

	// Add playlist items to current playlist in order
	{
		SortedDoublyIterator<PlaylistItem> iter(mApp.mPlayer->mPlaylist);
		for (PlaylistItem item = iter.Next(); iter.NextNotNull(); item = iter.Next()) {
			mCurPlaylist.Add(item);
		}
	}
	// Play first item, if exist
	{
		if (!mCurPlaylistIter) {
			mCurPlaylistIter = new DoublyIterator<PlaylistItem>(mCurPlaylist);
		}
		mCurPlaylistIter->ResetPointer();
		PlaylistItem firstItem = mCurPlaylistIter->Next();
		Play(firstItem, 0);
	}
	RefreshCurPlaylist();
}

void QtMainWindow::PlayInFreqOrderClicked() {
	if (mApp.mPlayer->mPlaylist.IsEmpty()) {
		return;
	}

	mCurPlaylist.MakeEmpty();

	// Get most played count
	int played = 0;
	SortedDoublyIterator<PlaylistItem> iter(mApp.mPlayer->mPlaylist);
	for (PlaylistItem item = iter.Next(); iter.NextNotNull(); item = iter.Next()) {
		if (played < item.GetPlayedTimes()) {
			played = item.GetPlayedTimes();
		}
	}

	// Add to playlist
	// Iterate through list and get items with current most played count
	while (played >= 0) {
		iter.ResetPointer();
		for (PlaylistItem item = iter.Next(); iter.NextNotNull(); item = iter.Next()) {
			if (item.GetPlayedTimes() == played) {
				mCurPlaylist.Add(item);
			}
		}
		--played;
	}
	// Play first item, if exist
	{
		if (!mCurPlaylistIter) {
			mCurPlaylistIter = new DoublyIterator<PlaylistItem>(mCurPlaylist);
		}
		mCurPlaylistIter->ResetPointer();
		PlaylistItem firstItem = mCurPlaylistIter->Next();
		Play(firstItem, 0);
	}
	RefreshCurPlaylist();
}

void QtMainWindow::PlayShuffleClicked() {
	if (mApp.mPlayer->mPlaylist.IsEmpty()) {
		return;
	}

	mCurPlaylist.MakeEmpty();

	// Add items from playlist to current playlist
	const int totalItems = mApp.mPlayer->mPlaylist.GetLength();
	SortedDoublyLinkedList<PlaylistItem> temp(mApp.mPlayer->mPlaylist);
	srand(time(0));
	for (int i = 0; i < totalItems; ++i) {
		int random = rand() % (totalItems - i);
		PlaylistItem item;
		temp.GetItemAt(item, random);
		mCurPlaylist.Add(item);
		temp.Delete(item);
	}
	// Play first item, if exist
	{
		if (!mCurPlaylistIter) {
			mCurPlaylistIter = new DoublyIterator<PlaylistItem>(mCurPlaylist);
		}
		mCurPlaylistIter->ResetPointer();
		PlaylistItem firstItem = mCurPlaylistIter->Next();
		Play(firstItem, 0);
	}
	RefreshCurPlaylist();
}

#include "utils/StringUtils.h"
void QtMainWindow::SearchForLyricsClicked() {
	// Get currently playing music
	PlaylistItem item;
	mCurPlaylist.GetItemAt(item, mCurPlaylistIndex);
	MusicItem music;
	music.SetId(item.GetId());
	if (mApp.mMasterList.Retrieve(music) == -1) {
		return;
	}

	// Get lyrics
	string lyrics;
	if (!mLyricsManager.GetLyricsFromGenius(music, lyrics)) {
		return;
	}

	// Show on screen
	mCurLyrics = lyrics;
	QString qLyrics = QString::fromStdString(lyrics);
	ui.text_lyrics->setText(qLyrics);
	// Enable save lyrics button
	ui.btn_saveLyrics->setEnabled(true);
}

void QtMainWindow::SaveLyricsClicked() {
	// Get currently playing music
	PlaylistItem item;
	mCurPlaylist.GetItemAt(item, mCurPlaylistIndex);
	MusicItem music;
	music.SetId(item.GetId());
	if (mApp.mMasterList.Retrieve(music) == -1) {
		return;
	}

	// Save lyrics
	mLyricsManager.SaveLyrics(music, mCurLyrics);
	// Disable save button
	ui.btn_saveLyrics->setEnabled(false);
}
