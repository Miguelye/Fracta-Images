#pragma once

#include "Bitmap.h"
#include "ZoomList.h"
#include "Mandelbrot.h"
#include "RGB.h"
#include <string>
#include <utility>
#include <memory>
#include <math.h>
#include <vector>
#include <iostream>

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
	vector<int> m_ranges;
	vector<RGB> m_colors;
	vector<int> m_rangeTotals;
	bool m_bGotFirstRange{ false };


	void calculateIteration();
	void calculateTotalIterations();
	void calculateRangeTotal();
	void drawFractal();
	void writeBitmap(std::string name);


public:
	FractalCreator(int width, int height);
	void addColorRange(double rangeEnd, const RGB& rgb);
	void run(string name);
	void addZoom(const Zoom& zoom);

};

}
