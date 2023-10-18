#include <iostream>
#include <cstdint>
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

    Bitmap bitmap(WIDTH, HEIGHT);

    for (int y = 0; y < HEIGHT; y++)
    {
        for (int x = 0; x < WIDTH; x++)
        {
            //Scaling making the range from -1 to 1;
            double xFractal = (x - WIDTH / 2) * 2.0 / WIDTH; //first we take the half of the width so we get simetrical with 0 (-400 to 400) then we multiply this with the fraction 2/width to get 1 (-1 to 1)
            double yFractal = (y - HEIGHT / 2) * 2.0 / HEIGHT;

            int iterations = Mandelbrot::getIteration(xFractal, yFractal);

            uint8_t red = (uint8_t)(256 * (double)iterations / Mandelbrot::MAX_ITERATIONS);

            bitmap.setPixel(x, y, red, red, red);

            //cheking if range is proper
            if (red < min) min = red;
            if (red > max) max = red;

            //bitmap.setPixel(x, y, 255, 0, 0);
        }
    }


    bitmap.write("test.bmp");

    cout << "finished\n";
    cout << min << ", " << max << endl;
    return 0;
}