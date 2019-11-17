#ifndef MDI_ID3_READER_RACTORY
#define MDI_ID3_READER_RACTORY

#include "ID3Reader.h"


namespace MetadataInfo {
	namespace ID3 {

		class ID3ReaderFactory {
		public:
			virtual ID3Reader *CreateReader(FILE *) = 0;
		};
	}
}

#endif