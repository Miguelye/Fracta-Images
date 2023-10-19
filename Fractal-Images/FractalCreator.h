#pragma once

#include "Bitmap.h"
#include "ZoomList.h"
#include <string>
#include <utility>
#include "Mandelbrot.h"
#include <memory>

namespace mayg
{

class FractalCreator
{
private:
	int m_width{ 0 };
	int m_height{ 0 };
	int m_total{ 0 };
	unique_ptr<int[]> m_histogram; //storing how many pixels for each iteration
	unique_ptr<int[]> m_fractal;   //storing the iterations of each pixel
	Bitmap m_bitmap;
	ZoomList m_zoomList;
	


public:
	FractalCreator(int width, int height);
	virtual ~FractalCreator();

	void calculateIteration();
	void calculateTotalIterations();
	void drawFractal();
	void addZoom(const Zoom& zoom);
	void writeBitmap(std::string name);
};

}
