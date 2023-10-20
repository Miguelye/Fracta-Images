#include "FractalCreator.h"
#include <assert.h>

namespace mayg
{

	FractalCreator::FractalCreator(int width, int height)
		: m_width(width), m_height(height),
		m_histogram(new int[Mandelbrot::MAX_ITERATIONS] {0}),
		m_fractal(new int[width * height] {0}),
		m_bitmap(width, height),
		m_zoomList(width, height)
	{
		m_zoomList.add(Zoom(m_width / 2, m_height / 2, 4.0 / m_width)); //Base image, setting coordinate (0,0) to the center of the image
	}

	void FractalCreator::run(string name)
	{
		calculateIteration();
		calculateTotalIterations();
		calculateRangeTotal();
		drawFractal();
		writeBitmap(name);
	}

	void FractalCreator::addColorRange(double rangeEnd, const RGB& rgb)
	{
		m_ranges.push_back(rangeEnd * Mandelbrot::MAX_ITERATIONS);
		m_colors.push_back(rgb);

		if (m_bGotFirstRange)
		{
			m_rangeTotals.push_back(0);
		}

		m_bGotFirstRange = true;
	}

	void FractalCreator::calculateRangeTotal()
	{
		int rangeIndex = 0;

		for (int i = 0; i < Mandelbrot::MAX_ITERATIONS; i++)
		{
			int pixels = m_histogram[i];

			if (i >= m_ranges[rangeIndex + 1]) {
				rangeIndex++;
			}

			m_rangeTotals[rangeIndex] += pixels;
		}


		for (int value: m_rangeTotals)
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
				//zooming
				pair<double, double> coords = m_zoomList.doZoom(x, y);

				int iterations = Mandelbrot::getIteration(coords.first, coords.second);

				m_fractal[y * m_width + x] = iterations;

				if (iterations != Mandelbrot::MAX_ITERATIONS)
				{
					m_histogram[iterations]++;
				}
			}
		}
	}

	void FractalCreator::calculateTotalIterations()
	{
		for (int i = 0; i < Mandelbrot::MAX_ITERATIONS; i++)
		{
			m_total += m_histogram[i];
		}
	}

	void FractalCreator::drawFractal()
	{

		RGB startColor(0, 0, 0);
		RGB endColor(0, 255, 0);
		RGB colorDiff = endColor - startColor;

		for (int y = 0; y < m_height; y++)
		{
			for (int x = 0; x < m_width; x++)
			{
				int iterations = m_fractal[y * m_width + x];

				int range = getRange(iterations);
				int rangeTotal = m_rangeTotals[range];
				int rangeStart = m_ranges[range];

				RGB& startColor = m_colors[range];
				RGB& endColor = m_colors[range+1];
				RGB colorDiff = endColor - startColor;

				uint8_t red = 0;
				uint8_t green = 0;
				uint8_t blue = 0;

				if (iterations != Mandelbrot::MAX_ITERATIONS)
				{

					//uint8_t color = (uint8_t)(256 * (double)iterations / Mandelbrot::MAX_ITERATIONS);
					//double hue = 0.0;

					int totalPixel = 0;

					for (int i = rangeStart; i <= iterations; i++)
					{
						//hue += (double)m_histogram[i] / m_total;
						totalPixel += m_histogram[i];
					}

					red = startColor.r + colorDiff.r * (double)totalPixel/rangeTotal;
					green = startColor.g + colorDiff.g * (double)totalPixel/rangeTotal;
					blue = startColor.b + colorDiff.b * (double)totalPixel/rangeTotal;

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