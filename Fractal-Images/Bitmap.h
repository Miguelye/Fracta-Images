#pragma once

#include <string>
#include <cstdint>
#include <memory>

using namespace std;

namespace mayg
{


class Bitmap
{
private:
	int m_width{ 0 };
	int m_height{ 0 };
	unique_ptr<uint8_t[]> m_pPixels{ nullptr }; //size of bits of the total number of pixels.

public:
	Bitmap(int width, int height);		//Constructor
	virtual ~Bitmap();					//Destructor
	void setPixel(int x, int y, uint8_t red, uint8_t green, uint8_t blue); //uint8_t is a unsigned integer of 8 bits

	bool write(string filename);
};

}