#include "ID3v23Reader.h"

using namespace MetadataInfo::ID3;


bool ID3v23Reader::IsValidType(FILE *fp) {
	H_ID3V2 temp;
	rewind(fp);
	fread(&temp, sizeof(temp), 1, fp);

	if (memcmp(temp.marker, "ID3", 3) == 0) {
		return (temp.version.major == 0x03);
	}
	return false;
}



bool ID3v23Reader::LoadHeader() {
	rewind(this->m_fp);
	fread(&this->m_header, sizeof(this->m_header), 1, this->m_fp);

	if (memcmp(this->m_header.marker, "ID3", 3) == 0) {
		ReadAllFrame(this->m_fp);
		return true;
	}
	return false;
}



wstring ID3v23Reader::GetStringValue(InfoKind metadataType) {
	wstring result(L"");
	int position = this->GetFramePosition(metadataType);
	if (position < 0) { return result; }

	H_FRAME_ID3V23 frame;
	fseek(this->m_fp, position, SEEK_SET);
	fread(&frame, sizeof(frame), 1, this->m_fp);

	long frame_size = ID3v2Reader::Convert4BytesToLittleEndian(frame.size);
	char *buffer = (char *)malloc(frame_size);
	fread(buffer, frame_size, 1, this->m_fp);

	// --- 추후 수정
	switch (frame.id[0]) {
	case 'T':
		if (buffer[0] == 0x00) {
			result = this->ConvertToText(&buffer[1], frame_size - 1, CharSet::ISO_8859_1);
		} else if (buffer[0] == 0x01) {
			result = this->ConvertToText(&buffer[3], (frame_size - 3) / 2, CharSet::UCS_2);
		}
		break;
	case 'W':
		if (InfoKind::USER_DEFINED_WEB) {
			if (buffer[0] == 0x00) {
				result = this->ConvertToText(&buffer[2], frame_size - 2, CharSet::ISO_8859_1);
				break;
			} else if (buffer[0] == 0x01) {
				result = this->ConvertToText(&buffer[2], (frame_size - 2) / 2, CharSet::UCS_2);
				break;
			}
		}
		result = this->ConvertToText(buffer, frame_size, CharSet::ISO_8859_1);
		break;
	case 'I':
		if (buffer[0] == 0x00) {
			result = this->ConvertToText(&buffer[1], frame_size - 1, CharSet::ISO_8859_1);
		} else if (buffer[0] == 0x01) {
			result = this->ConvertToText(&buffer[1], (frame_size - 1) / 2, CharSet::UCS_2);
		}
		break;
	case 'M':
		break;
	case 'E':
		break;
	default:
		int i = 0;
		break;
	}


	free(buffer);

	return result;
}



void ID3v23Reader::ReadAllFrame(FILE *fp) {
	fseek(fp, sizeof(this->m_header), SEEK_SET);

	long limit = ID3v2Reader::ReadSynchSize(this->m_header.size) + 10;

	// read extension header
	if (this->ContainsExtenedHeader() == true) {
		fread(&this->m_ext_header, sizeof(this->m_ext_header), 1, fp);
	}

	// prepare to read frames
	H_FRAME_ID3V23 frame;
	int frame_size = sizeof(frame);

	// read all frame
	this->m_info_list.clear();
	while (ftell(fp) < limit) {
		int t = ftell(fp);
		// read next
		if (fread(&frame, frame_size, 1, fp) <= 0) { break; }

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
		long x = ID3v2Reader::Convert4BytesToLittleEndian(frame.size);
		fseek(fp, ID3v2Reader::Convert4BytesToLittleEndian(frame.size), SEEK_CUR);
	}
}



bool ID3v23Reader::IsUnsynchronisationUsed() {
	return ((this->m_header.flags & 0x80) == 1);
}



bool ID3v23Reader::ContainsExtenedHeader() {
	return ((this->m_header.flags & 0x40) == 1);
}



bool ID3v23Reader::IsExperimentalStage() {
	return ((this->m_header.flags & 0x20) == 1);
}



InfoKind ID3v23Reader::FrameIdTometadataType(const char *dest) {
	if (memcmp(dest, "AENC", 4) == 0) {
		return AUDIO_ENCRYPT;
	} else if (memcmp(dest, "APIC", 4) == 0) {
		return COVER_IMAGE;
	} else if (memcmp(dest, "COMM", 4) == 0) {
		return COMMENT;
	} else if (memcmp(dest, "COMR", 4) == 0) {
		return COMMERCIAL_FRAME;
	} else if (memcmp(dest, "ENCR", 4) == 0) {
		return ENCRYPT_METHOD;
	} else if (memcmp(dest, "EQUA", 4) == 0) {
		return EQUALIZATION;
	} else if (memcmp(dest, "ETCO", 4) == 0) {
		return EVENT_CODES;
	} else if (memcmp(dest, "GEOB", 4) == 0) {
		return GENERAL_ENCAPSULATED_OBJ;
	} else if (memcmp(dest, "GRID", 4) == 0) {
		return GROUP_ID;
	} else if (memcmp(dest, "IPLS", 4) == 0) {
		return INVOLVED_PEOPLES;
	} else if (memcmp(dest, "LINK", 4) == 0) {
		return LINK_INFO;
	} else if (memcmp(dest, "MCDI", 4) == 0) {
		return CD_ID;
	} else if (memcmp(dest, "MLLT", 4) == 0) {
		return LOCATION_TABLE;
	} else if (memcmp(dest, "OWNE", 4) == 0) {
		return OWNERSHIP_FRAME;
	} else if (memcmp(dest, "PRIV", 4) == 0) {
		return PRIVATE_FRAME;
	} else if (memcmp(dest, "PCNT", 4) == 0) {
		return PLAY_COUNTER;
	} else if (memcmp(dest, "POPM", 4) == 0) {
		return POPULARIMETER;
	} else if (memcmp(dest, "POSS", 4) == 0) {
		return POSITION_SYNCHRONISATION_FRAME;
	} else if (memcmp(dest, "RBUF", 4) == 0) {
		return RECOMMENDED_BUFFER_SIZE;
	} else if (memcmp(dest, "RVAD", 4) == 0) {
		return RELATIVE_VOLUME_ADJUSTMENT;
	} else if (memcmp(dest, "RVRB", 4) == 0) {
		return REVERBB;
	} else if (memcmp(dest, "SYLT", 4) == 0) {
		return SYNCH_LYRIC;
	} else if (memcmp(dest, "SYTC", 4) == 0) {
		return SYNCH_TEMPO_CODES;
	} else if (memcmp(dest, "TALB", 4) == 0) {
		return ALBUM;
	} else if (memcmp(dest, "TBPM", 4) == 0) {
		return BPM;
	} else if (memcmp(dest, "TCOM", 4) == 0) {
		return COMPOSERS;
	} else if (memcmp(dest, "TCON", 4) == 0) {
		return CONTENT_TYPE;
	} else if (memcmp(dest, "TCOP", 4) == 0) {
		return COPYRIGHT;
	} else if (memcmp(dest, "TDAT", 4) == 0) {
		return DATE;
	} else if (memcmp(dest, "TDLY", 4) == 0) {
		return PLAYLIST_DELAY;
	} else if (memcmp(dest, "TENC", 4) == 0) {
		return ENCODER;
	} else if (memcmp(dest, "TEXT", 4) == 0) {
		return LYRICIST;
	} else if (memcmp(dest, "TFLT", 4) == 0) {
		return FILE_TYPE;
	} else if (memcmp(dest, "TIME", 4) == 0) {
		return TIME;
	} else if (memcmp(dest, "TIT1", 4) == 0) {
		return CONTENT_GROUP;
	} else if (memcmp(dest, "TIT2", 4) == 0) {
		return TITLE;
	} else if (memcmp(dest, "TIT3", 4) == 0) {
		return SUBTITLE;
	} else if (memcmp(dest, "TKEY", 4) == 0) {
		return INITIAL_KEY;
	} else if (memcmp(dest, "TLAN", 4) == 0) {
		return LANGUAGE;
	} else if (memcmp(dest, "TLEN", 4) == 0) {
		return LENGTH;
	} else if (memcmp(dest, "TMED", 4) == 0) {
		return MEDIA_TYPE;
	} else if (memcmp(dest, "TOAL", 4) == 0) {
		return ORIGIN_TITLE;
	} else if (memcmp(dest, "TOFN", 4) == 0) {
		return ORIGIN_FILENAME;
	} else if (memcmp(dest, "TOLY", 4) == 0) {
		return ORIGIN_LYRICIST;
	} else if (memcmp(dest, "TOPE", 4) == 0) {
		return ORIGIN_ARTIST;
	} else if (memcmp(dest, "TORY", 4) == 0) {
		return ORIGIN_YEAR;
	} else if (memcmp(dest, "TOWN", 4) == 0) {
		return FILE_OWNER;
	} else if (memcmp(dest, "TPE1", 4) == 0) {
		return ARTIST;
	} else if (memcmp(dest, "TPE2", 4) == 0) {
		return BAND;
	} else if (memcmp(dest, "TPE3", 4) == 0) {
		return CONDUCTOR;
	} else if (memcmp(dest, "TPE4", 4) == 0) {
		return MODIFIER;
	} else if (memcmp(dest, "TPOS", 4) == 0) {
		return PART;
	} else if (memcmp(dest, "TPUB", 4) == 0) {
		return PUBLISHER;
	} else if (memcmp(dest, "TRCK", 4) == 0) {
		return TRACK;
	} else if (memcmp(dest, "TRDA", 4) == 0) {
		return RECORDING_DATE;
	} else if (memcmp(dest, "TRSN", 4) == 0) {
		return INTERNET_RADIO_STATION_NAME;
	} else if (memcmp(dest, "TRSO", 4) == 0) {
		return INTERNET_RADIO_STATION_OWNER;
	} else if (memcmp(dest, "TSIZ", 4) == 0) {
		return SIZE;
	} else if (memcmp(dest, "TSRC", 4) == 0) {
		return ITNL_STD_RCD_CDE;
	} else if (memcmp(dest, "TSSE", 4) == 0) {
		return ENCODING_SETTING;
	} else if (memcmp(dest, "TYER", 4) == 0) {
		return YEAR;
	} else if (memcmp(dest, "TXXX", 4) == 0) {
		return USER_DEFINED;
	} else if (memcmp(dest, "UFID", 4) == 0) {
		return UNIQUE_FILE_ID;
	} else if (memcmp(dest, "USER", 4) == 0) {
		return TERMS_OF_USER;
	} else if (memcmp(dest, "USLT", 4) == 0) {
		return LYRIC;
	} else if (memcmp(dest, "WCOM", 4) == 0) {
		return COMMERCIAL_WEB;
	} else if (memcmp(dest, "WCOP", 4) == 0) {
		return COPYRIGHT_WEB;
	} else if (memcmp(dest, "WOAF", 4) == 0) {
		return FILE_WEB;
	} else if (memcmp(dest, "WOAR", 4) == 0) {
		return ARTIST_WEB;
	} else if (memcmp(dest, "WOAS", 4) == 0) {
		return SOURCE_WEB;
	} else if (memcmp(dest, "WORS", 4) == 0) {
		return INTERNET_RADIO_STATION_WEB;
	} else if (memcmp(dest, "WPAY", 4) == 0) {
		return PAYMENT_WEB;
	} else if (memcmp(dest, "WPUB", 4) == 0) {
		return PUBLISHER_WEB;
	} else if (memcmp(dest, "WXXX", 4) == 0) {
		return USER_DEFINED_WEB;
	} else {
		return NONE;
	}
}



long ID3v23Reader::GetBinarySize(InfoKind metadataType) {
	int position = GetFramePosition(metadataType);
	if (position < 0) { return false; }
	fseek(this->m_fp, position, SEEK_SET);

	// read frame
	H_FRAME_ID3V23 frame;
	fread(&frame, sizeof(frame), 1, this->m_fp);
	return ID3v2Reader::Convert4BytesToLittleEndian(frame.size) - sizeof(frame.flag);
}



long ID3v23Reader::GetBinaryValue(InfoKind metadataType, void *destBuffer, long size) {
	// find frame position
	int position = GetFramePosition(metadataType) + sizeof(H_FRAME_ID3V23);
	if (position < 0) { return 0L; }
	fseek(this->m_fp, position, SEEK_SET);

	// read
	return fread(destBuffer, size, 1, this->m_fp);
}