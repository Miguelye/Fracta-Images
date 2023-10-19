#include "FractalCreator.h"


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

	FractalCreator::~FractalCreator()
	{


	}

	void FractalCreator::calculateIteration()
	{
		for (int y = 0; y < m_height; y++)
		{
			for (int x = 0; x < m_width; x++)
			{
				//zooming
				pair<double, double> coords = m_zoomList.doZoom(x, y);

				//double xFractal = (x - WIDTH / 2 - 200) * 2.0 / HEIGHT; //first we take the half of the width so we get simetrical with 0 (-400 to 400) then we multiply this with the fraction 2/width to get 1 (-1 to 1)
				//double yFractal = (y - HEIGHT / 2) * 2.0 / HEIGHT;

				int iterations = Mandelbrot::getIteration(coords.first, coords.second);
				//int iterations = Mandelbrot::getIteration(xFractal, yFractal);

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
		for (int y = 0; y < m_height; y++)
		{
			for (int x = 0; x < m_width; x++)
			{

				uint8_t red = 0;
				uint8_t green = 0;
				uint8_t blue = 0;

				int iterations = m_fractal[y * m_width + x];

				if (iterations != Mandelbrot::MAX_ITERATIONS)
				{

					uint8_t color = (uint8_t)(256 * (double)iterations / Mandelbrot::MAX_ITERATIONS);

					double hue = 0.0;

					for (int i = 0; i <= iterations; i++)
					{
						hue += (double)m_histogram[i] / m_total;
					}

					uint8_t green = pow(255, hue);
					m_bitmap.setPixel(x, y, red, green, blue);
				}

			}
		}
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