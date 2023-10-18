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

    double min = 999999;
    double max = -999999;

    unique_ptr<int[]> histogram(new int[Mandelbrot::MAX_ITERATIONS]());

    Bitmap bitmap(WIDTH, HEIGHT);

    for (int y = 0; y < HEIGHT; y++)
    {
        for (int x = 0; x < WIDTH; x++)
        {
            //Scaling making the range from -1 to 1;
            double xFractal = (x - WIDTH / 2 - 200) * 2.0 / HEIGHT; //first we take the half of the width so we get simetrical with 0 (-400 to 400) then we multiply this with the fraction 2/width to get 1 (-1 to 1)
            double yFractal = (y - HEIGHT / 2) * 2.0 / HEIGHT;

            int iterations = Mandelbrot::getIteration(xFractal, yFractal);

            if (iterations != Mandelbrot::MAX_ITERATIONS)
            {
                histogram[iterations]++;
            }
            

            uint8_t color = (uint8_t)(256 * (double)iterations / Mandelbrot::MAX_ITERATIONS);

            color = color * color * color;

            bitmap.setPixel(x, y, 0, color, 0);

            //cheking if range is proper
            if (color < min) min = color;
            if (color > max) max = color;

            //bitmap.setPixel(x, y, 255, 0, 0);
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