#include <fstream>
#include "Bitmap.h"
#include "BitmapFileHeader.h"
#include "BitmapInfoHeader.h"

using namespace caveofprogramming;
using namespace std;

namespace caveofprogramming {

	//pPixels is multiply by 3 because each pixel is 3 bytes of size
	Bitmap::Bitmap(int width, int height) 
		: m_width(width), m_height(height), 
		  m_pPixels(new uint8_t[width * height * 3]()) {

}

bool Bitmap::write(string filename)
{
	BitmapFileHeader fileHeader;
	bitmapInfoHeader infoHeader;

	//information about the file
	fileHeader.fileSize = sizeof(BitmapFileHeader) + sizeof(bitmapInfoHeader) + (m_width * m_height * 3); // total size of the file
	fileHeader.dataOffset = sizeof(BitmapFileHeader) + sizeof(bitmapInfoHeader); //this is the size of data before the data of the actual bitmap starts.

	//information about the bitmap
	infoHeader.width = m_width;
	infoHeader.height = m_height;

	ofstream file;

	/// <summary>
	/// This object is used to open a file with the given name inside the string variable
	/// filename, there are also two flags that tells the object how to open and how the data will
	/// be written in the file:
	/// 
	/// ios::out: this mean that we intent to open the file for writing.
	///		It means you will be able to write data to the file, and if the
	///		file already exists, it will be truncated (its content will be deleted)
	///		before you start writing. If the file does not exist, it will be created.
	/// 
	/// ios::binary:  This flag specifies that you want to open the file in binary mode.
	///		In binary mode, data is treated as a sequence of bytes, and there is no automatic
	///		translation of line-ending characters. Binary mode is often used when working with non-text files,
	///		such as binary data or images.
	/// 
	/// </summary>
	/// <param name="filename"></param>
	/// <returns></returns>
	file.open(filename, ios::out | ios::binary);

	if (!file)
	{
		return false;
	}

	file.write((char*)&fileHeader, sizeof(fileHeader)); //write method expects an address to a char, so we need to cast it as such
	file.write((char*)&infoHeader, sizeof(infoHeader)); //then it ask for the size of the file
	file.write((char*)m_pPixels.get(), m_width * m_height * 3); //unique pointer cannot be casted, so we use get fucntion to get the raw pointer.


	file.close(); //always close a file whenever you open one

	if (!file)
	{
		return false;
	}
	return true;
}

void Bitmap::setPixel(int x, int y, uint8_t red, uint8_t green, uint8_t blue)
{
	//pointer to set the specific pixel located on the x and y coords.
	uint8_t* pPixel = m_pPixels.get(); //unique pointer cannot be assigned to normal pointer, that is why we use the get method to get the raw pointer.

	//y is the rows, we multiply this by the width and this will take us to the row we are interested in
	//then we move x(columns) amount of pixels, the pixels are size of 3 bytes, this is why we multiply x and y by 3
	pPixel += (y * 3) * m_width + (x * 3); //this pointer points to the pixel we want to change

	//the colors are reversed because the bitmap is use as a indian file format, reading from right to left
	pPixel[0] = blue;
	pPixel[1] = green;
	pPixel[2] = red;
}

Bitmap::~Bitmap() {

}



}