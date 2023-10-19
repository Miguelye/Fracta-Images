#include <iostream>
#include "FractalCreator.h"
#include "RGB.h"

using namespace std;

using namespace mayg;
using namespace std;

int main()
{
    int const m_width = 800;
    int const m_height = 600; 

    FractalCreator fractalCreator(800, 600);
    fractalCreator.run("test.bmp");

    cout << "finished\n";
    return 0;
}