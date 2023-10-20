#pragma once


namespace mayg {


class Mandelbrot
{
public:
	static int const MAX_ITERATIONS = 10000;

public:
	static int getIteration(double x, double y);

};

}