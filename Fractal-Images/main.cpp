#include <iostream>
#include "FractalCreator.h"
#include "RGB.h"

using namespace std;

using namespace mayg;
using namespace std;

int main()
{

    FractalCreator fractalCreator(1600, 1200);

    fractalCreator.addColorRange(0.0, RGB(0, 0, 0)); //pixels with iteration ranging from 0 to 3 are black
    fractalCreator.addColorRange(0.3, RGB(255, 0, 0));
    fractalCreator.addColorRange(0.6, RGB(255, 255, 0));
    fractalCreator.addColorRange(1.0, RGB(255, 255, 255));

    fractalCreator.addZoom(Zoom(600, 400, 0.1));
    fractalCreator.addZoom(Zoom(1080, 320, 0.1));
    /*fractalCreator.addZoom(Zoom(568, 100, 0.1));
    fractalCreator.addZoom(Zoom(275, 200, 0.07));*/


    fractalCreator.run("test.bmp"); 

    cout << "finished\n";
    return 0;
}