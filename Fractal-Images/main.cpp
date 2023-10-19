#include <iostream>
#include <cstdint>
#include <memory>
#include <math.h>
#include "Bitmap.h"
#include "Mandelbrot.h"
#include "ZoomList.h"
#include "FractalCreator.h"

using namespace std;

using namespace mayg;
using namespace std;

int main()
{
    int const m_width = 800;
    int const m_height = 600; 

    FractalCreator fractalCreator(800, 600);

    fractalCreator.addZoom(Zoom(300, m_height - 200, 0.1));
    fractalCreator.addZoom(Zoom(568, m_height - 100, 0.1));

    fractalCreator.calculateIteration();
    fractalCreator.calculateTotalIterations();
    fractalCreator.drawFractal();
    fractalCreator.writeBitmap("test.bmp");

    cout << "finished\n";
    return 0;
}