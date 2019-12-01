#include "ID3v22Reader.h"

using namespace MetadataInfo::ID3;




bool ID3v22Reader::IsValidType(FILE *fp) {
	H_ID3V2 temp;
	rewind(fp);
	fread(&temp, sizeof(temp), 1, fp);

	if (memcmp(temp.marker, "ID3", 3) == 0) {
		return (temp.version.major == 0x02);
	}
	return false;
}



bool ID3v22Reader::LoadHeader() {
	rewind(this->m_fp);
	fread(&this->m_header, sizeof(this->m_header), 1, this->m_fp);

	if (memcmp(this->m_header.marker, "ID3", 3) == 0) {
		ReadAllFrame(this->m_fp);
		return true;
	}
	return false;
}



void ID3v22Reader::ReadAllFrame(FILE *fp) {
	fseek(fp, sizeof(this->m_header), SEEK_SET);

	long limit = ID3v2Reader::ReadSynchSize(this->m_header.size);
	H_FRAME_ID3V22 frame;
	int frame_size = sizeof(frame);

	// read all frame
	this->m_info_list.clear();
	while ((ftell(fp) < limit) && (fread(&frame, frame_size, 1, fp) > 0)) {
		// create frame_pos
		H_FRAME_POS_ID3V2 frame_pos;
		frame_pos.id = FrameIdTometadataType(frame.id);
		frame_pos.position = ftell(fp) - frame_size;

		// insert into list
		if (frame_pos.id != InfoKind::NONE) {
			m_info_list.push_back(frame_pos.id);
			m_frame_list.push_back(frame_pos);
		}

		// read next
		fseek(fp, ID3v2Reader::Convert3BytesToLittleEndian(frame.size), SEEK_CUR);
	}
}



long ID3v22Reader::GetBinarySize(InfoKind metadataType) {
	int position = GetFramePosition(metadataType);
	if (position < 0) { return false; }
	fseek(this->m_fp, position, SEEK_SET);

	// read frame
	H_FRAME_ID3V22 frame;
	fread(&frame, sizeof(frame), 1, this->m_fp);
	return ID3v2Reader::Convert3BytesToLittleEndian(frame.size);
}



long ID3v22Reader::GetBinaryValue(InfoKind metadataType, void *destBuffer, long size) {
	// find frame position
	int position = GetFramePosition(metadataType) + sizeof(H_FRAME_ID3V22);
	if (position < 0) { return 0L; }
	fseek(this->m_fp, position, SEEK_SET);

	// read
	return fread(destBuffer, size, 1, this->m_fp);
}


wstring ID3v22Reader::GetStringValue(InfoKind metadataType) {
	return L"";
}


bool ID3v22Reader::IsUnsynchronisationUsed() {
	return ((this->m_header.flags & 0x80) != 0);
}



bool ID3v22Reader::IsCompressionUsed() {
	return ((this->m_header.flags & 0x40) != 0);
}



InfoKind ID3v22Reader::FrameIdTometadataType(const char *dest) {
	if (memcmp(dest, "UFI", 3) == 0) {
		return UNIQUE_FILE_ID;
	} else if (memcmp(dest, "TT1", 3) == 0) {
		return CONTENT_GROUP;
	} else if (memcmp(dest, "TT2", 3) == 0) {
		return TITLE;
	} else if (memcmp(dest, "TT3", 3) == 0) {
		return SUBTITLE;
	} else if (memcmp(dest, "TP1", 3) == 0) {
		return ARTIST;
	} else if (memcmp(dest, "TP2", 3) == 0) {
		return BAND;
	} else if (memcmp(dest, "TP3", 3) == 0) {
		return CONDUCTOR;
	} else if (memcmp(dest, "TP4", 3) == 0) {
		return MODIFIER;
	} else if (memcmp(dest, "TCM", 3) == 0) {
		return COMPOSERS;
	} else if (memcmp(dest, "TXT", 3) == 0) {
		return LYRICIST;
	} else if (memcmp(dest, "TLA", 3) == 0) {
		return LANGUAGE;
	} else if (memcmp(dest, "TCO", 3) == 0) {
		return CONTENT_TYPE;
	} else if (memcmp(dest, "TAL", 3) == 0) {
		return ALBUM;
	} else if (memcmp(dest, "TPA", 3) == 0) {
		return PART;
	} else if (memcmp(dest, "TRK", 3) == 0) {
		return TRACK;
	} else if (memcmp(dest, "TRC", 3) == 0) {
		return ITNL_STD_RCD_CDE;
	} else if (memcmp(dest, "TYE", 3) == 0) {
		return YEAR;
	} else if (memcmp(dest, "TDA", 3) == 0) {
		return DATE;
	} else if (memcmp(dest, "TIM", 3) == 0) {
		return TIME;
	} else if (memcmp(dest, "TRD", 3) == 0) {
		return RECORDING_DATE;
	} else if (memcmp(dest, "TMT", 3) == 0) {
		return MEDIA_TYPE;
	} else if (memcmp(dest, "TFT", 3) == 0) {
		return FILE_TYPE;
	} else if (memcmp(dest, "TBP", 3) == 0) {
		return BPM;
	} else if (memcmp(dest, "TCR", 3) == 0) {
		return COPYRIGHT;
	} else if (memcmp(dest, "TPB", 3) == 0) {
		return PUBLISHER;
	} else if (memcmp(dest, "TEN", 3) == 0) {
		return ENCODER;
	} else if (memcmp(dest, "TSS", 3) == 0) {
		return ENCODING_SETTING;
	} else if (memcmp(dest, "TOF", 3) == 0) {
		return ORIGIN_FILENAME;
	} else if (memcmp(dest, "TLE", 3) == 0) {
		return LENGTH;
	} else if (memcmp(dest, "TSI", 3) == 0) {
		return SIZE;
	} else if (memcmp(dest, "TDY", 3) == 0) {
		return PLAYLIST_DELAY;
	} else if (memcmp(dest, "TKE", 3) == 0) {
		return INITIAL_KEY;
	} else if (memcmp(dest, "TOT", 3) == 0) {
		return ORIGIN_ALBUM;
	} else if (memcmp(dest, "TOA", 3) == 0) {
		return ORIGIN_ARTIST;
	} else if (memcmp(dest, "TOL", 3) == 0) {
		return ORIGIN_LYRICIST;
	} else if (memcmp(dest, "TOR", 3) == 0) {
		return ORIGIN_YEAR;
	} else if (memcmp(dest, "WAF", 3) == 0) {
		return FILE_WEB;
	} else if (memcmp(dest, "WAR", 3) == 0) {
		return ARTIST_WEB;
	} else if (memcmp(dest, "WAS", 3) == 0) {
		return SOURCE_WEB;
	} else if (memcmp(dest, "WCM", 3) == 0) {
		return COMMERCIAL_WEB;
	} else if (memcmp(dest, "TCP", 3) == 0) {
		return COPYRIGHT_WEB;
	} else if (memcmp(dest, "TPB", 3) == 0) {
		return PUBLISHER_WEB;
	} else if (memcmp(dest, "IPL", 3) == 0) {
		return INVOLVED_PEOPLES;
	} else if (memcmp(dest, "MCI", 3) == 0) {
		return CD_ID;
	} else if (memcmp(dest, "ETC", 3) == 0) {
		return EVENT_CODES;
	} else {
		return NONE;
	}
}



int ID3v22Reader::GetFramePosition(InfoKind metadataType) {
	for (int i = 0; i < this->m_frame_list.size(); i++) {
		if (this->m_frame_list[i].id == metadataType) {
			return this->m_frame_list[i].position;
		}
	}
	return -1;
}



bool ID3v22Reader::ContainsInfo(InfoKind metadataType) {
	for (int i = 0; i < this->m_frame_list.size(); i++) {
		if (this->m_frame_list[i].id == metadataType) {
			return true;
		}
	}
	return false;
}
