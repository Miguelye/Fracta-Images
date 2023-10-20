#include <iostream>
#include "FractalCreator.h"
#include "RGB.h"

using namespace std;

using namespace mayg;
using namespace std;

int main()
{

    FractalCreator fractalCreator(800, 600);

    fractalCreator.addColorRange(0.0, RGB(0, 0, 0)); //pixels with iteration ranging from 0 to 3 are black
    fractalCreator.addColorRange(0.3, RGB(255, 0, 0)); //ranging from 300 to 500(assuming max iteration is 1000) are red
    fractalCreator.addColorRange(0.5, RGB(0, 255, 0)); //500 to 999 are green
    fractalCreator.addColorRange(1.0, RGB(0, 0, 255)); //1000 are blue

    fractalCreator.addZoom(Zoom(300, 200, 0.1));
    fractalCreator.addZoom(Zoom(568, 100, 0.1));

    fractalCreator.run("test.bmp"); 

    cout << "finished\n";
    return 0;
}