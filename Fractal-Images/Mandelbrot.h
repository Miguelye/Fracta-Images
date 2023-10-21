#pragma once
//Class holding the equation for the mandelbrot set

namespace mayg {


class Mandelbrot
{
public:
	//how many iteration to be done before finding out if the complex number is unstable or stable
	static int const MAX_ITERATIONS = 1000;

public:
	//methond containing the mandelbrot formula and return the number of iterations before the number becomes unstable if ever
	static int getIteration(double x, double y); //takes 2 parameters, the x and y coordinates

};

}