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
	int m_width{ 0 };				//Width of the image
	int m_height{ 0 };				//Height of the image
	int m_total{ 0 };				//total number of iterations, not counting the max number
	unique_ptr<int[]> m_histogram;	//storing how many pixels for each iteration
	unique_ptr<int[]> m_fractal;	//storing the iterations of each pixel
	Bitmap m_bitmap;				//Object contaning the infomation of the bitmap
	ZoomList m_zoomList;			//Object where the imformation of the zoom is store (input by the user)
	vector<int> m_ranges;			//vector containing the ranges (input by the user)
	vector<RGB> m_colors;			//number of colors used depending on how many ranges there are (input by the user)
	vector<int> m_pixelsPerRange;	//vector containing the total of pixels between each range
	bool m_bGotFirstRange{ false };	//bool tracking if we got first range, since we don't count the first one.


	void calculateIteration();			//Method that handles how many iteration per pixels finding out if belong to the mandelbrot set or not(stable or unstable)
	void calculateTotalIterations();	//calculate total iteration of all pixels(sums of all iterations)
	void calculateRangeTotal();			//calculates how many iteratios between each of the ranges.
	void drawFractal();					//draws the mandelbrot image
	void writeBitmap(std::string name); //creates the file and writes to it
	int getRange(int iterations) const;	//return the range of which the pixel, depending on how many iterations, belong to.


public:
	FractalCreator(int width, int height);					//constructor
	void addColorRange(double rangeEnd, const RGB& rgb);	//creates a range and it's color depending on the input of the user
	void run(string name);									//makes sure all the methods are call in the correct order
	void addZoom(const Zoom& zoom);							//implements the desire zoom on the image.

};

}
