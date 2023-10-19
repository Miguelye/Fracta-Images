#include <iostream>
#include <cstdint>
#include <memory>
#include <math.h>
#include "Bitmap.h"
#include "Mandelbrot.h"
#include "ZoomList.h"

using namespace std;

using namespace mayg;
using namespace std;

int main()
{
    int const WIDTH = 800;
    int const HEIGHT = 600; 

    ZoomList zoomList(WIDTH, HEIGHT);

    zoomList.add(Zoom(WIDTH / 2, HEIGHT / 2, 4.0/WIDTH));
    zoomList.add(Zoom(300, HEIGHT - 200, 0.1));
    zoomList.add(Zoom(568, HEIGHT - 100, 0.1));

    unique_ptr<int[]> histogram(new int[Mandelbrot::MAX_ITERATIONS]{0}); //storing how many pixels for each iteration
    unique_ptr<int[]> fractal(new int[WIDTH*HEIGHT]{0});   //storing the iterations of each pixel

    Bitmap bitmap(WIDTH, HEIGHT);

    for (int y = 0; y < HEIGHT; y++)
    {
        for (int x = 0; x < WIDTH; x++)
        {
            //zooming
            pair<double, double> coords = zoomList.doZoom(x, y);

            //double xFractal = (x - WIDTH / 2 - 200) * 2.0 / HEIGHT; //first we take the half of the width so we get simetrical with 0 (-400 to 400) then we multiply this with the fraction 2/width to get 1 (-1 to 1)
            //double yFractal = (y - HEIGHT / 2) * 2.0 / HEIGHT;

            int iterations = Mandelbrot::getIteration(coords.first, coords.second);
            //int iterations = Mandelbrot::getIteration(xFractal, yFractal);

            fractal[y * WIDTH + x] = iterations;

            if (iterations != Mandelbrot::MAX_ITERATIONS)
            {
                histogram[iterations]++;
            }
        }
    }

    int total = 0;
    for (int i = 0; i < Mandelbrot::MAX_ITERATIONS; i++)
    {
        total += histogram[i];
    }


    for (int y = 0; y < HEIGHT; y++)
    {
        for (int x = 0; x < WIDTH; x++)
        {

            uint8_t red = 0;
            uint8_t green = 0;
            uint8_t blue = 0;

            int iterations = fractal[y * WIDTH + x];

            if (iterations != Mandelbrot::MAX_ITERATIONS)
            {

                uint8_t color = (uint8_t)(256 * (double)iterations / Mandelbrot::MAX_ITERATIONS);
            
                double hue = 0.0;

                for (int i = 0; i <= iterations; i++)
                {
                    hue += (double)histogram[i]/total;
                }

                uint8_t green = pow(255, hue);
                bitmap.setPixel(x, y, red, green, blue);
            }

        }
    }

    bitmap.write("test.bmp");

    cout << "finished\n";
    for (size_t i = 0; i < Mandelbrot::MAX_ITERATIONS; i++)
    {
        cout << histogram[i] << endl;
    }
    return 0;
}