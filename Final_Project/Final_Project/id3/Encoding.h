#ifndef MDI_ENCODING
#define MDI_ENCODING

#include <iostream>
#include <locale>

using namespace std;

namespace MetadataInfo {
	namespace ID3 {
		class Encoding {
		public:
			static wstring mbstowstr(const char *buffer, int size);
			static wstring mbstowstr_l(const char *buffer, int size, std::locale loc);
		};
	}
}

#endif