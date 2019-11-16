#ifndef MDI_ID3v2
#define MDI_ID3v2

/****************************************************************************
 Frames can be up to 16MB in length, while total tag size is limited to 256MB

 ID3v2.3 : A frame could contain multiple values, separated with a / character.
 ID3v2.4 : It uses a null byte to separate multiple values
****************************************************************************/

#define ENCODING_MARKER_ISO_8859_1 0x00     // ISO-8859-1 (ASCII).
#define ENCODING_MARKER_UTF_16     0x01     // UCS-2 (UTF-16 encoded Unicode with BOM), in ID3v2.2 and ID3v2.3.
#define ENCODING_MARKER_UTF_16BE   0x02     // UTF-16BE encoded Unicode without BOM, in ID3v2.4.
#define ENCODING_MARKER_UTF_8      0x03     // UTF-8 encoded Unicode, in ID3v2.4.


/*
#define $00     Other
#define $01     32x32 pixels 'file icon' (PNG only)
#define $02     Other file icon
#define $03     Cover (front)
#define $04     Cover (back)
#define $05     Leaflet page
#define $06     Media (e.g. label side of CD)
#define $07     Lead artist/lead performer/soloist
#define $08     Artist/performer
#define $09     Conductor
#define $0A     Band/Orchestra
#define $0B     Composer
#define $0C     Lyricist/text writer
#define $0D     Recording Location
#define $0E     During recording
#define $0F     During performance
#define $10     Movie/video screen capture
#define $11     A bright coloured fish
#define $12     Illustration
#define $13     Band/artist logotype
#define $14     Publisher/Studio logotype
*/




namespace MetadataInfo {
	namespace ID3 {

		// version
		typedef struct {
			char major;
			char revision;
		} VERSION;


		// ID3v2 Header
		typedef struct {
			char    marker[3];
			VERSION version;
			char    flags;
			char    size[4];
		} H_ID3V2;


		// ID3v2 Extended Header
		typedef struct {
			char    size[4];
			char    flags[2];
			char    padding[4];
		} H_EXT_ID3V2;


		// ID3v2.2 Frame Header
		typedef struct {
			char id[3];
			char size[3];
		} H_FRAME_ID3V22;


		// ID3v2.3 Frame Header
		typedef struct {
			char id[4];
			char size[4];
			char flag[2];
		} H_FRAME_ID3V23;


		// frame position
		typedef struct {
			InfoKind id;
			long position;
		} H_FRAME_POS_ID3V2;


		// Text Information Frame
		typedef struct {
			char id[3];
			char size[3];
			char encoding;
		} ID3V22_TEXT;
	}
}

#endif