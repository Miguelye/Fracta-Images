#include "Mandelbrot.h"
#include <complex>

using namespace std;

namespace caveofprogramming
{

int Mandelbrot::getIteration(double x, double y)
{
    // Initialize the complex numbers 'z' and 'c'.
    complex<double> z = 0;        // 'z' is the current point being iterated.
    complex<double> c(x, y);      // 'c' is the constant complex number associated with the pixel.

    int iterations = 0;  // Keep track of the number of iterations.

    // Iterate until a maximum number of iterations is reached.
    while (iterations < MAX_ITERATIONS)
    {
        // Calculate the next value of 'z' using the Mandelbrot formula: z = z^2 + c.
        z = z * z + c;

        // Check if the magnitude (absolute value) of 'z' has exceeded 2.
        // If it has, break out of the loop, as this point is not in the Mandelbrot set.
        if (abs(z) > 2) {
            break;
        }

        // Increment the number of iterations for this point.
        iterations++;
    }
	return iterations;
}

}
