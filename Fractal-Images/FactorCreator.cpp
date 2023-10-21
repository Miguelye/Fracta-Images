#include "FractalCreator.h"
#include <assert.h>

namespace mayg
{
	//Constructor
	FractalCreator::FractalCreator(int width, int height)
		: m_width(width), m_height(height),
		m_histogram(new int[Mandelbrot::MAX_ITERATIONS] {0}),
		m_fractal(new int[width * height] {0}),
		m_bitmap(width, height),
		m_zoomList(width, height)
	{
		//The first "Zoom" is to make the center of the image its origin (0,0) since the origin of a bitmap is located on the bottom left of the image
		m_zoomList.add(Zoom(m_width / 2, m_height / 2, 4.0 / m_width)); //Base image, setting coordinate (0,0) to the center of the image
	}

	//Function that makes sure every other method is call in the right order.
	void FractalCreator::run(string name)
	{
		calculateIteration();
		calculateTotalIterations();
		calculateRangeTotal();
		drawFractal();
		writeBitmap(name);
	}

	//adds one color the image and its range
	void FractalCreator::addColorRange(double rangeEnd, const RGB& rgb)
	{
		//rangeEnd is a number between 0 to 1, so we multiply it with max iteration to give the range of the iterations, not the percentage
		m_ranges.push_back(rangeEnd * Mandelbrot::MAX_ITERATIONS);
		m_colors.push_back(rgb);

		//this is to ignore the first range, which we dont want to count.
		if (m_bGotFirstRange)
		{
			m_pixelsPerRange.push_back(0);
		}

		m_bGotFirstRange = true;
	}

	//calculates how many iterations in the ranges provided
	void FractalCreator::calculateRangeTotal()
	{
		//keeps track of the current range
		int rangeIndex = 0;

		//loop use to store how many pixels each iteration has and then store then in the corresponding range.
		for (int i = 0; i < Mandelbrot::MAX_ITERATIONS; i++)
		{
			//variable holding how many pixels in the current iteration
			int pixels = m_histogram[i];

			//if the end of the range is met, then move to next range
			if (i >= m_ranges[rangeIndex + 1]) {
				rangeIndex++;
			}

			//add number of pixels to the vector holding the total number os pixel in current range
			m_pixelsPerRange[rangeIndex] += pixels;
		}

		//debugging
		for (int value: m_pixelsPerRange)
		{
			std::cout << "Range total: " << value << std::endl;
		}
	}


	void FractalCreator::calculateIteration()
	{
		for (int y = 0; y < m_height; y++)
		{
			for (int x = 0; x < m_width; x++)
			{
				//Applis zooming.
				pair<double, double> coords = m_zoomList.doZoom(x, y);

				//gets how many iteration the given pixel has, if belonging to the mandelbrot set or not
				int iterations = Mandelbrot::getIteration(coords.first, coords.second);

				//assinging the number of iteration to the current pixel on the image
				m_fractal[y * m_width + x] = iterations;

				//do not count the pixels with max iterations
				if (iterations != Mandelbrot::MAX_ITERATIONS)
				{
					m_histogram[iterations]++;
				}
			}
		}
	}

	void FractalCreator::calculateTotalIterations()
	{
		//adds how many pixels are there
		for (int i = 0; i < Mandelbrot::MAX_ITERATIONS; i++)
		{
			m_total += m_histogram[i];
		}
	}

	void FractalCreator::drawFractal()
	{
		//nested loops representing each pixels of the images
		for (int y = 0; y < m_height; y++)
		{
			for (int x = 0; x < m_width; x++)
			{
				//get the iteration of current pixel
				int iterations = m_fractal[y * m_width + x];

				//get what range the pixel belongs to depending on the number of iterations
				int range = getRange(iterations);
				//get how many pixels the current range has
				int rangeTotal = m_pixelsPerRange[range];
				int rangeStart = m_ranges[range];

				//the start color input by the user
				RGB& startColor = m_colors[range];
				RGB& endColor = m_colors[range+1];
				RGB colorDiff = endColor - startColor;

				uint8_t red = 0;
				uint8_t green = 0;
				uint8_t blue = 0;

				if (iterations != Mandelbrot::MAX_ITERATIONS)
				{
					//how many pixels in the current range
					int totalPixel = 0;

					for (int i = rangeStart; i <= iterations; i++)
					{
						totalPixel += m_histogram[i];
					}

					//assingning the color to the pixel
					red = startColor.r + colorDiff.r * (double)totalPixel/rangeTotal;
					green = startColor.g + colorDiff.g * (double)totalPixel/rangeTotal;
					blue = startColor.b + colorDiff.b * (double)totalPixel/rangeTotal;

					//painting the pixel
					m_bitmap.setPixel(x, y, red, green, blue);
				}

			}
		}
	}

	int FractalCreator::getRange(int iterations) const
	{
		int range = 0;

		for (int i = 1; i < m_ranges.size(); i++)
		{
			range = i;

			if (m_ranges[i] > iterations)
			{
				break;
			}
		}

		range--;

		assert(range > -1);
		assert(range < m_ranges.size());

		return range;
	}

	void FractalCreator::addZoom(const Zoom& zoom)
	{
		m_zoomList.add(zoom);
	}

	void FractalCreator::writeBitmap(std::string name)
	{
		m_bitmap.write(name);
	}

}