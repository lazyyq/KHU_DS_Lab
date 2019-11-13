#ifndef MDI_ID3v1
#define MDI_ID3v1


namespace MetadataInfo {
	namespace ID3 {

		typedef struct {
			char marker[3];
			char title[30];
			char artist[30];
			char album[30];
			char year[4];
			char comment[30];
			char genre[1];
		} H_ID3v1;


		// Extended tag (placed before the ID3v1 tag): 227 bytes
		typedef struct {
			char marker[4];
			char title[60];
			char artist[60];
			char album[60];
			char speed[1];
			char genre[30];
			char start_time[6];
			char end_time[6];
			H_ID3v1 ID3v1_header;
		} H_ID3v1_EXT;
	}
}

#endif