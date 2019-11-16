#ifndef MDI_ID3_DEFAULT_READER_RACTORY
#define MDI_ID3_DEFAULT_READER_RACTORY


#include "ID3ReaderFactory.h"

namespace MetadataInfo {
	namespace ID3 {
		class ID3DefaultReaderFactory : ID3ReaderFactory {
		public:
			ID3DefaultReaderFactory();
			virtual ID3Reader *CreateReader(FILE *fp);
		};
	}
}

#endif