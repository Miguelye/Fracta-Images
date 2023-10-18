#include <iostream>
#include "Bitmap.h"

using namespace std;

using namespace caveofprogramming;
using namespace std;

int main()
{
    Bitmap bitmap(800, 600);

    bitmap.write("test.bmp");

    cout << "Hello World!\n";
}