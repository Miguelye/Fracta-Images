#include <iostream>
#include "Bitmap.h"

using namespace std;

using namespace caveofprogramming;
using namespace std;

int main()
{
    int const WIDTH = 800;
    int const HEIGHT = 600;


    Bitmap bitmap(WIDTH, HEIGHT);

    for (size_t y = 0; y < HEIGHT; y++)
    {
        for (size_t x = 0; x < WIDTH; x++)
        {
            bitmap.setPixel(x, y, 255, 0, 0);
        }
    }

    bitmap.write("test.bmp");

    cout << "finished\n";
    return 0;
}