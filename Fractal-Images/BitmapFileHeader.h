#pragma once

//information about the file

#include <cstdint>

using namespace std;
#pragma pack(2) //makes C++ align everything on two byte boundaries

namespace mayg {

struct BitmapFileHeader
{
	char header[2]{ 'B', 'M' };
	int32_t fileSize;
	int32_t reserved{ 0 };
	int32_t dataOffset;

};
}