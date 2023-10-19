#include <iostream>
#include <cstdint>
#include <memory>
#include "Bitmap.h"
#include "Mandelbrot.h"

using namespace std;

using namespace caveofprogramming;
using namespace std;

int main()
{
    int const WIDTH = 800;
    int const HEIGHT = 600; 

    unique_ptr<int[]> histogram(new int[Mandelbrot::MAX_ITERATIONS]{0}); //storing how many pixels for each iteration
    unique_ptr<int[]> fractal(new int[WIDTH*HEIGHT]{0});   //storing the iterations of each pixel

    Bitmap bitmap(WIDTH, HEIGHT);

    for (int y = 0; y < HEIGHT; y++)
    {
        for (int x = 0; x < WIDTH; x++)
        {
            //Scaling making the range from -1 to 1;
            double xFractal = (x - WIDTH / 2 - 200) * 2.0 / HEIGHT; //first we take the half of the width so we get simetrical with 0 (-400 to 400) then we multiply this with the fraction 2/width to get 1 (-1 to 1)
            double yFractal = (y - HEIGHT / 2) * 2.0 / HEIGHT;

            int iterations = Mandelbrot::getIteration(xFractal, yFractal);

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

            int iterations = fractal[y * WIDTH + x];

            uint8_t color = (uint8_t)(256 * (double)iterations / Mandelbrot::MAX_ITERATIONS);
            
            double hue = 0;

            for (int i = 0; i <= iterations; i++)
            {
                hue += (double)histogram[i]/total;
            }

            uint8_t red = 0;
            uint8_t green = hue * 255;
            uint8_t blue = 0;

            bitmap.setPixel(x, y, red, green, blue);
        }
    }

    bitmap.write("test.bmp");

    cout << "finished\n";
    cout << min << ", " << max << endl;
    for (size_t i = 0; i < Mandelbrot::MAX_ITERATIONS; i++)
    {
        cout << histogram[i] << endl;
    }
    return 0;
}