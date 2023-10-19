#pragma once

#include "Bitmap.h"
#include "ZoomList.h"
#include "Mandelbrot.h"
#include <string>
#include <utility>
#include <memory>
#include <math.h>

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
	
	void calculateIteration();
	void calculateTotalIterations();
	void drawFractal();
	void addZoom(const Zoom& zoom);
	void writeBitmap(std::string name);


public:
	FractalCreator(int width, int height);
	void run(string name);

};

}
