#include <iostream>
#include <string>
#include <fstream>

#include <json/json.h>

using namespace std;

class MusicItem {
public:
	MusicItem(string s1, string s2, string s3, string s4, string s5) :
		mId(s1), mTitle(s2), mComposer(s3), mArtist(s4), mGenre(s5) {}
	string mId, mTitle, mComposer, mArtist, mGenre;

	friend ostream &operator<<(ostream &os, const MusicItem &item);
};

ostream &operator<<(ostream &os, const MusicItem &item) {
	cout << item.mId << endl
		<< item.mTitle << endl
		<< item.mComposer << endl
		<< item.mArtist << endl
		<< item.mGenre << endl;

	return os;
}


int main() {
	{
		vector<MusicItem> musics;
		MusicItem music1("f83d7a", "2002", "composer1", "anne marie", "pop");
		MusicItem music2("f83dsa", "2002", "composer1", "anne marie", "pop");
		musics.push_back(music1);
		musics.push_back(music2);

		Json::Value root;
		for (const auto &item : musics) {
			Json::Value music;
			music["ID"] = item.mId.c_str();
			music["Title"] = item.mTitle.c_str();
			music["Composer"] = item.mComposer.c_str();
			music["Artist"] = item.mArtist.c_str();
			music["Genre"] = item.mGenre.c_str();
			music["int"] = 3;
			root.append(music);
		}
		cout << root << endl;

		ofstream ofs("test.json");
		ofs << root;
		ofs.close();
	}

	try {
		Json::Value root;
		Json::CharReaderBuilder builder;
		Json::CharReader *reader = builder.newCharReader();
		ifstream ifs("test.json");
		ifs >> root;
		ifs.close();

		//for (int i = 0, len = root.size(); i < len; ++i) {
			//const Json::Value &jsonItem = root[i];
		for (const auto &jsonItem : root) {
			const string id = jsonItem.get("ID", "").asString();
			const string title = jsonItem["Title"].asString();
			const string composer = jsonItem["Composer"].asString();
			const string artist = jsonItem["Artist"].asString();
			const string genre = jsonItem["Genre"].asString();
			MusicItem item(id, title, composer, artist, genre);
			cout << item << endl;
		}
	} catch (Json::LogicError & e) {
		cout << e.what() << endl;
	}

	return 0;
}
