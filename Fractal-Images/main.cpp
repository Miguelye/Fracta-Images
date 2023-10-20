#include <iostream>
#include "FractalCreator.h"
#include "RGB.h"

using namespace std;

using namespace mayg;
using namespace std;

int main()
{

    FractalCreator fractalCreator(800, 600);

    fractalCreator.addColorRange(0.3, RGB(255, 0, 0));
    fractalCreator.addColorRange(0.5, RGB(0, 255, 0));
    fractalCreator.addColorRange(1.0, RGB(0, 0, 255));

    fractalCreator.addZoom(Zoom(300, 200, 0.1));
    fractalCreator.addZoom(Zoom(568, 100, 0.1));

    fractalCreator.run("test.bmp"); 

    cout << "finished\n";
    return 0;
}